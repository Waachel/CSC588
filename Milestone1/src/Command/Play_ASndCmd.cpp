//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Play_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

float setSndVolumeOnPlay = 0.0f;
float sound_panOnPlay = 0;

Play_ASndCmd::Play_ASndCmd(Snd::ID id, Snd *_pSnd)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	assert(pSnd);
}

void Play_ASndCmd::SetVolume(float volume)
{
	setSndVolumeOnPlay = volume;
}

void Play_ASndCmd::SetPan(float snd_pan)
{
	sound_panOnPlay = snd_pan;
}

void Play_ASndCmd::Execute()
{
	assert(this->pSnd);

	ASnd *pASnd = pSnd->GetASnd();
	assert(pASnd);

	Debug::out("Play_ASndCmd::Exe() pSnd:%p pASnd:%p\n",this->pSnd, pASnd);
	pASnd->Play(setSndVolumeOnPlay);


	delete this;
}


// --- End of File ---