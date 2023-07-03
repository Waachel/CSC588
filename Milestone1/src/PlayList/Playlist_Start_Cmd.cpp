//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Playlist_Start_Cmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SndMan.h"

float setVolume = 0.0f;
float setPanOnStartCmd = 0.0f;

Playlist_Start_Cmd::Playlist_Start_Cmd(Voice *_pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Start_Cmd::SetVolume(float volume)
{
	setVolume = volume;
}

void Playlist_Start_Cmd::SetPan (float snd_pan)
{
	setPanOnStartCmd = snd_pan;
}

void Playlist_Start_Cmd::Execute()
{
	// -------------------------------------------------------
	// Start the source voice
	// -------------------------------------------------------
	assert(pVoice);
	Handle::Status status;
	status = pVoice->Start(setVolume);
	assert(status == Handle::Status::SUCCESS);

//	delete this;
}


// --- End of File ---