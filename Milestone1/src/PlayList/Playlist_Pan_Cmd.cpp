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
float setVolumeOnPlaylistPan = 0.0f;

Playlist_Pan_Cmd::Playlist_Pan_Cmd(Voice* _pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Pan_Cmd::SetPan(float snd_pan)
{
	soundPan = snd_pan;
}

void Playlist_Pan_Cmd::SetVolume(float volume)
{
	setVolumeOnPlaylistPan = volume;
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

	UpdatePan(soundPan);

}


// --- End of File ---