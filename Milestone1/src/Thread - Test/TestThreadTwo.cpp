//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "TestThreadTwo.h"
#include "AzulCore.h"
#include "LeftRightPan.h"
#include "SndMan.h"
//#include "Snd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"


using namespace ThreadFramework;
using namespace std::chrono_literals;


void TestThreadTwoMain()
{
	SimpleBanner b;

	Timer T1;
	T1.tic();


	Handle::Status status;
	Snd* pSndF = SndMan::Add(Snd::ID::Seinfeld);
	status = pSndF->Play(0.8f);
	status = pSndF->Pan(0.0);

	std::this_thread::sleep_for(10s);

	status = pSndF->Pan(1.0);

	std::this_thread::sleep_for(10s);

	status = pSndF->Pan(-1.0);

	std::this_thread::sleep_for(10s);

	status = pSndF->Pan(0.0);

	std::this_thread::sleep_for(10s);

	status = pSndF->Pan(1.0);

	std::this_thread::sleep_for(10s);

	status = pSndF->Pan(-1.0);

}


//---  End of File ---
