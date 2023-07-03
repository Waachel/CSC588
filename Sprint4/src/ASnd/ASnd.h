//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_H
#define ASND_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Snd.h"
#include "Voice.h"
#include "Playlist.h"
#include "PlaylistCmd.h"

class ASnd : public DLink
{
public:
	// Big 4
	ASnd();
	ASnd(const ASnd&) = delete;
	ASnd& operator = (const ASnd&) = delete;
	virtual ~ASnd();

	void Set(Snd::ID snd_id, Snd* pSnd);

	void Dump();
	void Wash();

	virtual bool Compare(DLink* pTargetNode) override;

	void Play();
	void Pan(float snd_pan);

private:
	void privClear();


public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------

	Playlist* pPlaylist;
	Snd::ID snd_id;
	Snd* pSnd;
	PlaylistCmd* pPlaylistCmd;

	Handle handle;
};

#endif

// --- End of File ---