//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Volume_PL_CMD_H
#define Volume_PL_CMD_H

#include "PlaylistCmd.h"
#include "Voice.h"

class Playlist_Volume_Cmd : public PlaylistCmd
{

public:
	// Big 4v
	Playlist_Volume_Cmd() = delete;
	Playlist_Volume_Cmd(const Playlist_Volume_Cmd&) = delete;
	Playlist_Volume_Cmd& operator = (const Playlist_Volume_Cmd&) = delete;
	~Playlist_Volume_Cmd() = default;

	Playlist_Volume_Cmd(Voice* pVoice);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;
public:
	// Data
	Voice* pVoice;
};

#endif

// --- End of File ---