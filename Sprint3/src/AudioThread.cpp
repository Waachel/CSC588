//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "SndCallRegistry.h"
#include "AudioEngine.h"
#include "InputMan.h"
#include "Panning.h"
#include "Volume.h"
#include "Pitch.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

// --------------------------------------------------------
// HACK warning
// --------------------------------------------------------
IXAudio2SourceVoice* pVoice = nullptr;
float Volume = 0.5f;
float Pitch = 1.0f;
float Panning = 0.0f;

void LoadBuffer(const char *pFileName, WAVEFORMATEXTENSIBLE &wfx, XAUDIO2_BUFFER &buffer,UINT32 numOfLoops, unsigned char *&pDataBuffer)
{
	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	FileSlow::Handle FileHandle;
	FileSlow::Error ferror;

	// Open file
	// Based on the input parameter
	ferror = FileSlow::Open(FileHandle, pFileName, FileSlow::Mode::READ);
	assert(ferror == FileSlow::Error::SUCCESS);

	// Set file to beginning
	ferror = FileSlow::Seek(FileHandle, FileSlow::Location::BEGIN, 0);
	assert(ferror == FileSlow::Error::SUCCESS);

	// -------------------------------------------------------
	// Audio Format - wfx
	// Audio Buffer - how to play it back
	// -------------------------------------------------------
	
	// Move to Global
	wfx = { {0} };
	buffer = { 0 };
	// buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cerror;

	// Scan to the RIFF and load file type
	cerror = FindChunk(FileHandle, fourccRIFF, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	if (filetype != fourccWAVE)
	{
		assert(false);
	}

	// Read the FMT: format
	cerror = FindChunk(FileHandle, fourccFMT, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);
	cerror = ReadChunkData(FileHandle, &wfx, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cerror = FindChunk(FileHandle, fourccDATA, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	pDataBuffer = new unsigned char[dwChunkSize];
	assert(pDataBuffer != 0);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, pDataBuffer, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	buffer.LoopCount = numOfLoops;				  // looping...

	ferror = FileSlow::Close(FileHandle);
	assert(ferror == FileSlow::Error::SUCCESS);
}

void PanSound(IXAudio2SourceVoice* pSound, float snd_pan)
{
	DWORD dwChannelMask;

	IXAudio2MasteringVoice* pMasteringVoice = AudioEngine::GetMasterVoice();
	pMasteringVoice->GetChannelMask(&dwChannelMask);

	float outputMatrix[8];
	// SPEAKER_STEREO // SPEAKER_FRONT_LEFT (0x1) | SPEAKER_FRONT_RIGHT (0x2)
	assert(dwChannelMask == 0x3);

	// pan of -1.0 indicates all left speaker, 
	// 1.0 is all right speaker, 0.0 is split between left and right
	float left = 0.5f - snd_pan / 2;
	float right = 0.5f + snd_pan / 2;

	outputMatrix[2];

	outputMatrix[0] = left;
	outputMatrix[1] = right;

	// Assuming pVoice sends to pMasteringVoice
	XAUDIO2_VOICE_DETAILS VoiceDetails;
	pSound->GetVoiceDetails(&VoiceDetails);

	XAUDIO2_VOICE_DETAILS MasterVoiceDetails;
	pMasteringVoice->GetVoiceDetails(&MasterVoiceDetails);

	HRESULT hr;
	hr = pSound->SetOutputMatrix(NULL, VoiceDetails.InputChannels, MasterVoiceDetails.InputChannels, outputMatrix);
	assert(hr == S_OK);
}

void PitchSound(IXAudio2SourceVoice* pSound, float snd_pitch)
{
	//frequency ratio calculation
	//float frequencyRatio = snd_pitch / 1024.0f;

	pSound->SetFrequencyRatio(snd_pitch);
}

void CallSound(CircularData *pOut, WAVEFORMATEXTENSIBLE &wfx, XAUDIO2_BUFFER &buffer, VoiceCallback *&pCallback, float desiredVolume, float desiredPitch, float desiredPanning)
{
	HRESULT hr;

	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	IXAudio2SourceVoice *pSourceVoice;

	// Create a Callback object!!!
	pCallback = new VoiceCallback(pOut);
	IXAudio2 *pXAudio2 = AudioEngine::GetXAudio2();
	hr = pXAudio2->CreateSourceVoice(&pSourceVoice, &wfx.Format, 0, XAUDIO2_MAX_FREQ_RATIO, pCallback);
	assert(hr == S_OK);


	//if(FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX *) &wfx)))
	//{
	//	assert(false);
	//}

	// -------------------------------------------------------
	// Create a move the voice onto the voice queue
	//		Only files on the queue can be played
	//		There is no deep copy, we still hold the buffer while its active
	// -------------------------------------------------------

	if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
	{
		assert(false);
	}

	// -------------------------------------------------------
	// Start the source voice
	// -------------------------------------------------------
	//Volume
	pSourceVoice->SetVolume(desiredVolume);

	//Panning
	PanSound(pSourceVoice, desiredPanning);

	//Pitch
	PitchSound(pSourceVoice, desiredPitch);

	//Store Voice
	pVoice = pSourceVoice;

	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		assert(false);
	}

}

void AudioMain(bool &QuitFlag, CircularData *pAudioIn, CircularData *pGameIn)
{
	SimpleBanner b;
    AudioEngine audioEngine;

	// -----------------------------------------
	// Higher level call... Kind of...
	// -----------------------------------------

	// Initialize
	WAVEFORMATEXTENSIBLE wfx0;
	XAUDIO2_BUFFER    buffer0;
	unsigned char *pDataBuff0 = nullptr;
	VoiceCallback *pCallback0 = nullptr;

	WAVEFORMATEXTENSIBLE wfx1;
	XAUDIO2_BUFFER    buffer1;
	unsigned char *pDataBuff1 = nullptr;
	VoiceCallback *pCallback1 = nullptr;

	WAVEFORMATEXTENSIBLE wfx2;
	XAUDIO2_BUFFER    buffer2;
	unsigned char *pDataBuff2 = nullptr;
	VoiceCallback *pCallback2 = nullptr;

	WAVEFORMATEXTENSIBLE wfx3;
	XAUDIO2_BUFFER    buffer3;
	unsigned char *pDataBuff3 = nullptr;
	VoiceCallback *pCallback3 = nullptr;

	WAVEFORMATEXTENSIBLE wfx4;
	XAUDIO2_BUFFER    buffer4;
	unsigned char* pDataBuff4 = nullptr;
	VoiceCallback* pCallback4 = nullptr;
	//InitializeXAudio2();

	// Load
    LoadBuffer("../../AudioFiles/Bassoon_mono.wav", wfx0, buffer0, 0, pDataBuff0);
	LoadBuffer("../../AudioFiles/Oboe_mono.Wav", wfx1, buffer1, 0, pDataBuff1);
	LoadBuffer("../../AudioFiles/BabyElephantWalk60.wav", wfx2, buffer2, 0, pDataBuff2);
	LoadBuffer("../../AudioFiles/gun-gunshot-02.wav", wfx3, buffer3, 4, pDataBuff3);
	LoadBuffer("../../AudioFiles/Fiddle_mono.wav", wfx4, buffer4, 0, pDataBuff4);
	// Call Snd
	//CallSoundPan();

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------
	while (!QuitFlag)
	{
		int val;

        if(pAudioIn->PopFront(val) == true)
		{
			Debug::out("%x \n", val);

			if(val == (int) SndId::BASSOON_ID)
			{
				Debug::out("--->Snd started\n");
				CallSound(pGameIn, wfx0, buffer0, pCallback0, Volume, Pitch, Panning);
			}

			if(val == (int) SndId::STRINGS_ID)
			{
				Debug::out("--->Snd started\n");
				CallSound(pGameIn, wfx1, buffer1, pCallback1, Volume, Pitch, Panning);
			}

			if (val == (int)SndId::FIDDLE_ID)
			{
				Debug::out("--->Snd started\n");
				CallSound(pGameIn, wfx4, buffer4, pCallback4, Volume, Pitch, Panning);
			}

			if(val == (int) SndId::ELEPHANT_ID)
			{
				Debug::out("--->Snd started\n");
				CallSound(pGameIn, wfx2, buffer2, pCallback2, 0.5, 1.0, 0.0);
			}

			//looping leaks
			if (val == (int)SndId::GUNSHOT_ID)
			{
				Debug::out("--->Snd started\n");
				CallSound(pGameIn, wfx3, buffer3, pCallback3, Volume, Pitch, Panning);
			}

			//Volume Up
			if (val == (int)SndId::CHANGE_VOLUME_UP_ID)
			{
				Debug::out("--->Volume Changed\n");
				Volume = 1.5f;
			}

			//Volume Down
			if (val == (int)SndId::CHANGE_VOLUME_DOWN_ID)
			{
				Debug::out("--->Volume Changed\n");
				Volume = 0.1f;
			}

			//Pitch High
			if (val == (int)SndId::CHANGE_PITCH_HIGH_ID)
			{
				Debug::out("--->Pitch Changed\n");
				Pitch = 1024.0f / 500.0f;
			}

			//Pitch Low
			if (val == (int)SndId::CHANGE_PITCH_LOW_ID)
			{
				Debug::out("--->Pitch Changed\n");
				Pitch = 500.0f / 1024.0f;
			}

			//Panning Left
			if (val == (int)SndId::CHANGE_PANNING_LEFT_ID)
			{
				Debug::out("--->Panning Changed\n");
				Panning = -1.0f;
			}

			//Panning Right
			if (val == (int)SndId::CHANGE_PANNING_RIGHT_ID)
			{
				Debug::out("--->Panning Changed\n");
				Panning = 1.0f;
			}

			//Stop
			if (val == (int)SndId::STOP_ID)
			{
				Debug::out("--->Snd Stopped\n");
				pVoice->Stop();
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	}
	delete[] pDataBuff0;
	delete[] pDataBuff1;
	delete[] pDataBuff2;
	delete[] pDataBuff3;
	delete[] pDataBuff4;

	delete pCallback0;
	delete pCallback1;
	delete pCallback2;
	delete pCallback3;
	delete pCallback4;
}



//		// wait for 3 seconds
//		Sleep(3000);
//
//		pSourceVoice->Stop();
//
//		pSourceVoice->DestroyVoice();
//		pMasterVoice->DestroyVoice();
//		pXAudio2->Release();
//
//		delete[] pDataBuffer;
//
//		// Closes the COM library on the current thread
//		CoUninitialize();
//
//		break;
//	}
//
//}

//---  End of File ---
