//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AzulCore.h"
#include "PanLeft.h"
#include "TestThreadOne.h"
#include "SndMan.h"

using namespace ThreadFramework;

void PanLeft::PanLeft_Main(Snd* &pSnd)
{
	SimpleBanner b;

	Debug::out("- Pan Left - \n");
	Handle::Status status1;
	status1 = pSnd->Play(0.5f);
	status1 = pSnd->Pan(-1.0);
}

void PanLeft::PanLeft_Stop(Snd* &pSnd)
{

	Debug::out("- Stop Left - \n");
	Handle::Status status1;
	status1 = pSnd->Stop();
}
