//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "InputMan.h"
#include "Panning.h"
#include "Volume.h"
#include "Pitch.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

// --------------------------------------------------------
// HACK warning
// --------------------------------------------------------

IXAudio2 *pXAudio2 = nullptr;
IXAudio2MasteringVoice *pMasterVoice = nullptr;
IXAudio2SourceVoice* pSound = nullptr;

// Horrible hack - should be part of the buffer/voice
WAVEFORMATEXTENSIBLE wfx = { {0} };
XAUDIO2_BUFFER buffer = { 0 };
BYTE *pDataBuffer = nullptr;
BYTE* pDataBufferLoop = nullptr;

void InitializeXAudio2()
{
	// Initializes the COM library for use by the calling thread
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// -------------------------------------------------------
	// Create an instance, use its default processor
	// -------------------------------------------------------
	HRESULT hr;

	// move to global
	//IXAudio2* pXAudio2 = 0;

	if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		printf("error %x", (unsigned int)hr);
		assert(false);
	}

	// -------------------------------------------------------
	// Creating a master voice, with default settings:
	//
	//      InputChannels = XAUDIO2_DEFAULT_CHANNELS,
	//      InputSampleRate = XAUDIO2_DEFAULT_SAMPLERATE,
	//      Flags = 0,
	//      szDeviceId = NULL,
	//      *pEffectChain = NULL,
	//      StreamCategory = AudioCategory_GameEffects
	// -------------------------------------------------------

	// move to global
	//IXAudio2MasteringVoice* pMasterVoice = 0;

	if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
	{
		printf("error %x", (unsigned int)hr);
		assert(false);
	}

}

void LoadBuffer(const char *pFileName)
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
	// WAVEFORMATEXTENSIBLE wfx = { 0 };
	// XAUDIO2_BUFFER buffer = { 0 };
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

	pDataBuffer = new BYTE[dwChunkSize];
	assert(pDataBuffer != 0);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, pDataBuffer, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBuffer;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	buffer.LoopCount = 0;				  // looping...

	ferror = FileSlow::Close(FileHandle);
	assert(ferror == FileSlow::Error::SUCCESS);
}

void LoadBufferLoop(const char* pFileName)
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
	// WAVEFORMATEXTENSIBLE wfx = { 0 };
	// XAUDIO2_BUFFER buffer = { 0 };
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

	pDataBufferLoop = new BYTE[dwChunkSize];
	assert(pDataBufferLoop != 0);

	// Fill the data...
	cerror = ReadChunkData(FileHandle, pDataBufferLoop, dwChunkSize, dwChunkPosition);
	assert(cerror == ChunkError::CHUNK_SUCCESS);

	buffer.AudioBytes = dwChunkSize;  //buffer containing audio data
	buffer.pAudioData = pDataBufferLoop;  //size of the audio buffer in bytes
	buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer
	buffer.LoopCount = 4;				  // looping...

	ferror = FileSlow::Close(FileHandle);
	assert(ferror == FileSlow::Error::SUCCESS);
}

void CallSoundPan()
{
	HRESULT hr;

	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	IXAudio2SourceVoice *pSourceVoice;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX *)&wfx)))
	{
		assert(false);
	}

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
	pSourceVoice->SetVolume(0.2f);
	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		assert(false);
	}

	pSound = pSourceVoice;

	std::thread t_Panning(PanningMain, pMasterVoice, pSound, hr);

	Debug::SetName(t_Panning, "--Panning--");
	t_Panning.detach();

	std::this_thread::sleep_for(std::chrono::seconds(40));

	/*	pSourceVoice->DestroyVoice();
		pMasterVoice->DestroyVoice();
		pXAudio2->Release();

		delete[] pDataBuffer;

		// Closes the COM library on the current thread
		CoUninitialize();*/
}

void CallSoundVolume()
{
	HRESULT hr;

	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	IXAudio2SourceVoice* pSourceVoice;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		assert(false);
	}

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

	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		assert(false);
	}

	pSound = pSourceVoice;

	std::thread t_Volume(VolumeMain, pSound, hr);

	Debug::SetName(t_Volume, "--Volume--");
	t_Volume.detach();

	std::this_thread::sleep_for(std::chrono::seconds(33));
	
	/*	pSourceVoice->DestroyVoice();
		pMasterVoice->DestroyVoice();
		pXAudio2->Release();

		delete[] pDataBuffer;

		// Closes the COM library on the current thread
		CoUninitialize();*/
}

void CallSoundPitch()
{
	HRESULT hr;

	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	IXAudio2SourceVoice* pSourceVoice;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		assert(false);
	}

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
	pSourceVoice->SetVolume(0.2f);
	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		assert(false);
	}

	pSound = pSourceVoice;

	std::thread t_Pitching(PitchMain, pSound, hr);

	Debug::SetName(t_Pitching, "--Pitching--");
	t_Pitching.detach();

	std::this_thread::sleep_for(std::chrono::seconds(43));
	
/*	pSourceVoice->DestroyVoice();
	pMasterVoice->DestroyVoice();
	pXAudio2->Release();

	delete[] pDataBuffer;

	// Closes the COM library on the current thread
	CoUninitialize();*/
}

void CallSound()
{
	HRESULT hr;

	// -------------------------------------------------------
	// Create a source voice
	//		Format in wfx
	// -------------------------------------------------------

	IXAudio2SourceVoice* pSourceVoice;
	if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx)))
	{
		assert(false);
	}

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
	pSourceVoice->SetVolume(0.2f);
	if (FAILED(hr = pSourceVoice->Start(0)))
	{
		assert(false);
	}

	pSound = pSourceVoice;

	std::this_thread::sleep_for(std::chrono::seconds(5));
}

void AudioMain(bool &QuitFlag, CircularData *pAudioIn, CircularData *pGameIn)
{
	SimpleBanner b;
	// Read Panning Key
	Keyboard* key = InputMan::GetKeyboard();

	// -----------------------------------------
	// Higher level call... Kind of...
	// -----------------------------------------

	// Initialize
	InitializeXAudio2();

	// Load
	LoadBuffer("../../AudioFiles/BabyElephantWalk60.wav");

	// Call sound
	//CallSoundPan();

	// ----------------------------------------
	// Loop for ever until quit is hit
	// ----------------------------------------
	while (!QuitFlag)
	{
		int val;

		if (key->GetKeyState(Keyboard::KEY_P))
		{
			// Initialize
			//InitializeXAudio2();

			// Load
			//LoadBuffer("../../AudioFiles/BabyElephantWalk60.wav");

			//Call sound and pan
			CallSoundPan();
		}

		if (key->GetKeyState(Keyboard::KEY_V))
		{
			// Initialize
			//InitializeXAudio2();

			// Load
			//LoadBuffer("../../AudioFiles/BabyElephantWalk60.wav");

			//Call sound and change volume
			CallSoundVolume();
		}

		if (key->GetKeyState(Keyboard::KEY_H))
		{
			// Initialize
			//InitializeXAudio2();

			// Load
			//LoadBuffer("../../AudioFiles/BabyElephantWalk60.wav");

			//Call sound and change pitch
			CallSoundPitch();
		}

		if (key->GetKeyState(Keyboard::KEY_L))
		{
			// Initialize
			InitializeXAudio2();

			// Load
			LoadBufferLoop("../../AudioFiles/gun-gunshot-02.wav");

			//Call sound and change pitch
			CallSound();

			delete[] pDataBufferLoop;
		}

		if (pAudioIn->PopFront(val) == true)
		{
			Debug::out("receive: %x <--- \n", val);

			// echo back the complement
			int data = ~val & 0xFF;
			Debug::out("---> send: %x \n", data);

			bool status = pGameIn->PushBack(data);

			assert(status);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
	delete[] pDataBuffer;
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
