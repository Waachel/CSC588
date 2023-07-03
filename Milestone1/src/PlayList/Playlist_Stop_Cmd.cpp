//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Playlist_Stop_Cmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SndMan.h"

float setVolumeOnStop = 0.0f;
float setPanOnStopCmd = 0.0f;

Playlist_Stop_Cmd::Playlist_Stop_Cmd(Voice* _pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Stop_Cmd::SetVolume(float volume)
{
	setVolumeOnStop = volume;
}

void Playlist_Stop_Cmd::SetPan(float snd_pan)
{
	setPanOnStopCmd = snd_pan;
}

void Playlist_Stop_Cmd::Execute()
{
	// -------------------------------------------------------
	// Stop the source voice
	// -------------------------------------------------------
	assert(pVoice);
	Handle::Status status;
	status = pVoice->Stop();
	assert(status == Handle::Status::SUCCESS);

	//	delete this;
}


// --- End of File ---