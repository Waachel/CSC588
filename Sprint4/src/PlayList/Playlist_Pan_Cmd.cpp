//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Playlist_Pan_Cmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SndMan.h"
#include "AzulCore.h"

using namespace ThreadFramework;
using namespace std::chrono_literals;

float soundPan = 0;

Playlist_Pan_Cmd::Playlist_Pan_Cmd(Voice* _pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Pan_Cmd::SetPan(float snd_pan)
{
	soundPan = snd_pan;
}

bool Playlist_Pan_Cmd::WaitForTime(Timer& t, Time TriggerTime)
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

void Playlist_Pan_Cmd::UpdatePan(float pan)
{
	assert(pVoice);
	Handle::Status status;
	status = pVoice->Pan(engine->GetMasterVoice(), pan);
	assert(status == Handle::Status::SUCCESS);
}

void Playlist_Pan_Cmd::Execute()
{
	Timer T1;
	T1.tic();

	UpdatePan(0.0);
	std::this_thread::sleep_for(10s);

	if (WaitForTime(T1, 10 * Time(TIME_ONE_SECOND)))
	{
		//Debug::out("- 10 Sec\n");
	}

	UpdatePan(1.0);

	std::this_thread::sleep_for(10s);

	if (WaitForTime(T1, 20 * Time(TIME_ONE_SECOND)))
	{
		//Debug::out("- 20 Sec\n");
	}

	UpdatePan(-1.0);

	std::this_thread::sleep_for(10s);

	if (WaitForTime(T1, 30 * Time(TIME_ONE_SECOND)))
	{
		//Debug::out("- 30 Sec\n");
	}

	UpdatePan(0.0);

	std::this_thread::sleep_for(10s);

	if (WaitForTime(T1, 40 * Time(TIME_ONE_SECOND)))
	{
		//Debug::out("- 40 Sec\n");
	}


	UpdatePan(1.0);

	std::this_thread::sleep_for(10s);

	if (WaitForTime(T1, 50 * Time(TIME_ONE_SECOND)))
	{
		//Debug::out("- 50 Sec\n");
	}

	UpdatePan(-1.0);
}


// --- End of File ---