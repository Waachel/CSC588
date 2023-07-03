//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "VoiceCallback.h"
#include "AudioThread.h"
#include "XAudio2Wrapper.h"
#include "InputMan.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;


void LoopingMain(IXAudio2SourceVoice* pSound, HRESULT hr)
{
	SimpleBanner B;

	XAUDIO2_BUFFER buffer;

	buffer.LoopCount = 5;

}




//---  End of File ---
