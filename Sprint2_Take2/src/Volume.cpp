//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "InputMan.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;


void VolumeMain(IXAudio2SourceVoice* pSound, HRESULT hr)
{
	SimpleBanner B;

	for (int i = 0; i < 15; i++)
	{
		//std::this_thread::sleep_for(100ms);
		float volume = (float)i / 9.0f;
		Debug::out("(%d) volume:%f \n", i, volume);
		pSound->SetVolume(volume);

		std::this_thread::sleep_for(1000ms);
	}

	for (int i = 15; i > 0; i--)
	{
		//std::this_thread::sleep_for(100ms);
		float volume = (float)i / 9.0f;
		Debug::out("(%d) volume:%f \n", i, volume);
		pSound->SetVolume(volume);

		std::this_thread::sleep_for(1000ms);
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
