//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Playlist_Volume_Cmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SndMan.h"

float setVolumeCmd = 0.0f;
float setPanOnVolumeCmd = 0.0f;

Playlist_Volume_Cmd::Playlist_Volume_Cmd(Voice* _pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Volume_Cmd::SetVolume(float volume)
{
	setVolumeCmd = volume;
}

void Playlist_Volume_Cmd::SetPan(float snd_pan)
{
	setPanOnVolumeCmd = snd_pan;
}

void Playlist_Volume_Cmd::Execute()
{
	// -------------------------------------------------------
	// Volume the source voice
	// -------------------------------------------------------
	assert(pVoice);
	Handle::Status status;
	status = pVoice->SetVolume(setVolumeCmd);
	assert(status == Handle::Status::SUCCESS);

	//	delete this;
}


// --- End of File ---