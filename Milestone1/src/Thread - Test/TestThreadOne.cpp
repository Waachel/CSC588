//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "TestThreadOne.h"
#include "AzulCore.h"
#include "LeftRightPan.h"
#include "PanQuickChange.h"
#include "PartF.h"
#include "VolumeChange.h"
#include "SndMan.h"

//#include "Snd.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

bool WaitForTime(Timer &t, Time TriggerTime)
{
	Time deltaTime(TIME_ZERO);

	if (deltaTime != TriggerTime)
	{
		while (!Time::quotient(deltaTime, TriggerTime))
		{
			// Spin
			deltaTime = t.toc();
		}
	}
	return true;
}

void TestThreadOneMain()
{
	SimpleBanner b;

	Timer T1;
	T1.tic();

	Snd* pSndA = SndMan::Add(Snd::ID::Fiddle);

	Handle::Status status1;
	status1 = pSndA->Play(0.5f);

	if (WaitForTime(T1, 3 * Time(TIME_ONE_SECOND)))
	{
		pSndA = SndMan::Add(Snd::ID::Fiddle);
		status1 = pSndA->Play(0.5f);
		status1 = pSndA->Pan(-1.0);
	}

	if (WaitForTime(T1, 6 * Time(TIME_ONE_SECOND)))
	{
		//status = pSndA->Pan(1.0);
		pSndA = SndMan::Add(Snd::ID::Fiddle);
		status1 = pSndA->Play(0.5f);
		status1 = pSndA->Pan(1.0);
	}

	if (WaitForTime(T1, 10 * Time(TIME_ONE_SECOND)))
	{
		std::thread t(LeftRightPan_Main);
		Debug::SetName(t, "-LeftRightPan-");
		t.join();
	}

	if (WaitForTime(T1, 15 * Time(TIME_ONE_SECOND)))
	{
		std::thread t(RightLeftPan_Main);
		Debug::SetName(t, "-RightLeftPan-");
		t.join();
	}

	if (WaitForTime(T1, 20 * Time(TIME_ONE_SECOND)))
	{
		std::thread t(VolumeUp_Main);
		Debug::SetName(t, "-Volume Up-");
		t.join();
	}

	if (WaitForTime(T1, 25 * Time(TIME_ONE_SECOND)))
	{
		std::thread t(VolumeDown_Main);
		Debug::SetName(t, "-Volume Down-");
		t.join();
	}

	if (WaitForTime(T1, 30 * Time(TIME_ONE_SECOND)))
	{
		std::thread t1(QuickPan_Main);
		Debug::SetName(t1, "-Part E-");
		t1.join();
	}

	if (WaitForTime(T1, 80 * Time(TIME_ONE_SECOND)))
	{
		std::thread t1(PartF_Main);
		Debug::SetName(t1, "-Part F-");
		t1.join();

	}

}

//---  End of File ---
