//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Create_ASndCmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "ASndMan.h"

Create_ASndCmd::Create_ASndCmd(Snd::ID id, Snd* _pSnd)
	: Command(),
	snd_id(id),
	pSnd(_pSnd)
{
	assert(pSnd);
}


void Create_ASndCmd::Execute()
{
	assert(this->pSnd);

	ASnd* pASnd = ASndMan::Add(this->snd_id, this->pSnd);
	assert(pASnd);

	//Debug::out("Create_ASndCmd():Snd:%p ASnd:%p\n", pSnd, pASnd);
	delete this;
}


// --- End of File ---