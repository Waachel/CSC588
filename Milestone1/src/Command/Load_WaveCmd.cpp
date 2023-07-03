//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Load_WaveCmd.h"
#include "WaveMan.h"

float sound_panOnLoadWave = 0;
float setSndVolumeOnLoadWave = 0.0f;

Load_WaveCmd::Load_WaveCmd(Wave::ID _id, const char *const _pWaveName, I_File_CB *_pFileCB)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pIFileCB(_pFileCB)
{
	assert(pWaveName);
	assert(pIFileCB);
}

void Load_WaveCmd::SetVolume(float volume)
{
	setSndVolumeOnLoadWave = volume;
}

void Load_WaveCmd::SetPan(float snd_pan)
{
	sound_panOnLoadWave = snd_pan;
}

void Load_WaveCmd::Execute()
{
	WaveMan::Add(this->id, this->pWaveName, this->pIFileCB);

	delete this;
}


// --- End of File ---