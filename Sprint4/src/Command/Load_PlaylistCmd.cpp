//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Load_PlaylistCmd.h"
#include "PlaylistJukeBox.h"

Load_PlaylistCmd::Load_PlaylistCmd(Snd::ID _snd_id, PlaylistData *pPlaylistData)
	: Command(),
	snd_id(_snd_id),
	poPlaylistData(pPlaylistData)
{

}


void Load_PlaylistCmd::Execute()
{
	Wave::ID wave_id = this->poPlaylistData->GetFirstWaveID();

	VoiceCallback *pCallback = this->poPlaylistData->Create_VoiceCallback();
	assert(pCallback);

	delete this->poPlaylistData;

	PlaylistJukeBox::Add(snd_id, wave_id, pCallback);

	delete this;
}


// --- End of File ---