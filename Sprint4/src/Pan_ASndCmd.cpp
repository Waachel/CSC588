//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Pan_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

float sound_pan = 0;

Pan_ASndCmd::Pan_ASndCmd(Snd::ID id, Snd* _pSnd, float snd_pan)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	sound_pan = snd_pan;
	assert(pSnd);
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