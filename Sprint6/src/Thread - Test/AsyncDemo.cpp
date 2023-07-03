//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AsyncDemo.h"
#include "AzulCore.h"
#include "SndMan.h"
#include "AlarmCmd.h"
#include "TimeEventMan.h"
#include "UserAsyncLoadCallback.h"
#include "Audio.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

bool AsyncWaitForTime(Timer& t, Time TriggerTime)
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

void AsyncDemoMain()
{
	SimpleBanner b;

	Timer T1;
	T1.tic();

	UserAsyncLoadCallback* pUserAsyncLoadCallback = new UserAsyncLoadCallback();
	Audio::Load(Audio::Async::LOAD, Wave::ID::Beethoven, "Beethoven_stereo.wav", pUserAsyncLoadCallback);

	Snd* pSndA = SndMan::Add(Snd::ID::Electro);
	Handle::Status status1;
	//pan right
	status1 = pSndA->Pan(1.0);
	status1 = pSndA->Vol(0.3f);
	status1 = pSndA->Play();

	Command* pCmd;
	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 0 * Time(Duration::TIME_ONE_SECOND));

	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 5 * Time(Duration::TIME_ONE_SECOND));

	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 10 * Time(Duration::TIME_ONE_SECOND));

	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 15 * Time(Duration::TIME_ONE_SECOND));

	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 20 * Time(Duration::TIME_ONE_SECOND));

	pCmd = new AlarmCmd();
	TimeEventMan::Add(pCmd, 25 * Time(Duration::TIME_ONE_SECOND));

	if (AsyncWaitForTime(T1, 60 * Time(TIME_ONE_SECOND)))
	{
		// ---------------------------------------
		// Priority Table
		// ---------------------------------------
		Snd::KillAllActive();
		Snd::PrintPriorityTable();

		// ---------------------------------------
		// Wave Table
		// ---------------------------------------
		Audio::WaveTableDump();
		Audio::RemoveAllWaves();
		Audio::WaveTableDump();
	}
}


//---  End of File ---
