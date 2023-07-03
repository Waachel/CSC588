//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef AUDIO_THREAD_H
#define AUDIO_THREAD_H

#include "CircularData.h"

void AudioMain(bool &QuitFlag, CircularData *pAudioIn, CircularData *pGameIn);

#endif

//---  End of File ---
