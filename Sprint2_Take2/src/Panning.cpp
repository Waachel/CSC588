//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "InputMan.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;



void PanSound(IXAudio2MasteringVoice* pMasteringVoice, IXAudio2SourceVoice* pSound, float snd_pan)
{
	DWORD dwChannelMask;
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

void PanningMain(IXAudio2MasteringVoice* pMasteringVoice, IXAudio2SourceVoice* pSound, HRESULT hr)
{
	SimpleBanner B;

	for (int i = 0; i < 30; i++)
	{
		float val = -1.0f;
		Debug::out("(%d) val:%f \n", i, val);
		PanSound(pMasteringVoice, pSound, val);
		std::this_thread::sleep_for(100ms);
	}

	for (int i = -100; i < 0; i++)
	{
		float val = (float)i / 99.0f;
		Debug::out("(%d) val:%f \n", i, val);
		PanSound(pMasteringVoice, pSound, val);
		std::this_thread::sleep_for(100ms);
	}	
	
	for (int i = 0; i < 100; i++)
	{
		float val = (float)i / 99.0f;
		Debug::out("(%d) val:%f \n", i, val);

		PanSound(pMasteringVoice, pSound, val);

		std::this_thread::sleep_for(100ms);
	}

	for (int i = 0; i < 30; i++)
	{
		float val = 1.0f;
		Debug::out("(%d) val:%f \n", i, val);
		PanSound(pMasteringVoice, pSound, val);
		std::this_thread::sleep_for(100ms);
	}

	for (int i = 100; i > 0; i--)
	{
		float val = (float)i / 99.0f;
		Debug::out("(%d) val:%f \n", i, val);
		PanSound(pMasteringVoice, pSound, val);
		std::this_thread::sleep_for(100ms);
	}

	hr = pSound->Stop();

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
