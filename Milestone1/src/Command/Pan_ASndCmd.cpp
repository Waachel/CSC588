//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Pan_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

float sound_pan = 0;
float setSndVolume = 0.0f;

Pan_ASndCmd::Pan_ASndCmd(Snd::ID id, Snd* _pSnd)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	
	assert(pSnd);
}

void Pan_ASndCmd::SetVolume(float volume)
{
	setSndVolume = volume;
}

void Pan_ASndCmd::SetPan(float snd_pan)
{
	sound_pan = snd_pan;
}

void Pan_ASndCmd::Execute()
{
	assert(this->pSnd);

	ASnd* pASnd = pSnd->GetASnd();
	assert(pASnd);

	Debug::out("Pan_ASndCmd::Exe() pSnd:%p pASnd:%p\n", this->pSnd, pASnd);
	pASnd->Pan(sound_pan);


	delete this;
}


// --- End of File ---