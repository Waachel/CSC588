//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Stop_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

float setSndVolumeOnStop = 0.0f;
float sound_panOnStop = 0;

Stop_ASndCmd::Stop_ASndCmd(Snd::ID id, Snd* _pSnd)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	assert(pSnd);
}

void Stop_ASndCmd::SetVolume(float volume)
{
	setSndVolumeOnStop = volume;
}

void Stop_ASndCmd::SetPan(float snd_pan)
{
	sound_panOnStop = snd_pan;
}

void Stop_ASndCmd::Execute()
{
	assert(this->pSnd);

	ASnd* pASnd = pSnd->GetASnd();
	assert(pASnd);

	Debug::out("Stop_ASndCmd::Exe() pSnd:%p pASnd:%p\n", this->pSnd, pASnd);
	pASnd->Stop();

	delete this;
}


// --- End of File ---