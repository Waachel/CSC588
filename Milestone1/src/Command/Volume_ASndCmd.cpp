//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Volume_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

float setSndVolumeOnVolume = 0.0f;
float sound_panOnVolume = 0;

Volume_ASndCmd::Volume_ASndCmd(Snd::ID id, Snd* _pSnd)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	assert(pSnd);
}

void Volume_ASndCmd::SetVolume(float volume)
{
	setSndVolumeOnVolume = volume;
}

void Volume_ASndCmd::SetPan(float snd_pan)
{
	sound_panOnVolume = snd_pan;
}

void Volume_ASndCmd::Execute()
{
	assert(this->pSnd);

	ASnd* pASnd = pSnd->GetASnd();
	assert(pASnd);

	Debug::out("Volume_ASndCmd::Exe() pSnd:%p pASnd:%p\n", this->pSnd, pASnd);
	pASnd->Volume(setSndVolumeOnVolume);


	delete this;
}


// --- End of File ---