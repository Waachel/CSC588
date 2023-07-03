//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "InputMan.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;


void PitchMain(IXAudio2SourceVoice* pSound, HRESULT hr)
{
	int changeNumber = 0;
	SimpleBanner B;

	for (int i = 10; i < 30; i++)
	{
			//Debug::out("(%d) Pitch:%f \n", i);

			float tens = (float)i * 100.0f;

			float frequencyRatio = (float) tens / 1024.0f;

			pSound->SetFrequencyRatio(frequencyRatio);

			Debug::out("(%d) Pitch:%f \n", changeNumber);

			std::this_thread::sleep_for(1000ms);
			changeNumber++;

	}



	for (int i = 10; i < 30; i++)
	{
		
		float tens = (float)i * 100.0f;

		float frequencyRatio = 1024.0f / (float)tens;

		pSound->SetFrequencyRatio(frequencyRatio);

		Debug::out("(%d) Pitch:%f \n", changeNumber);

		std::this_thread::sleep_for(1000ms);
		changeNumber--;
	}

	pSound->SetFrequencyRatio(1);
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
