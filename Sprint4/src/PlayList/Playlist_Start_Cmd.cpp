//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Playlist_Start_Cmd.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "SndMan.h"

Playlist_Start_Cmd::Playlist_Start_Cmd(Voice *_pVoice)
	: pVoice(_pVoice)
{
	assert(pVoice);
}

void Playlist_Start_Cmd::SetPan(float snd_pan)
{

}

void Playlist_Start_Cmd::Execute()
{
	// -------------------------------------------------------
	// Start the source voice
	// -------------------------------------------------------
	assert(pVoice);
	Handle::Status status;
	status = pVoice->Start();
	assert(status == Handle::Status::SUCCESS);

//	delete this;
}


// --- End of File ---