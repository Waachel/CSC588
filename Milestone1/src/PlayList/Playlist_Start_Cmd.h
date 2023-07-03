//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef START_PL_CMD_H
#define START_PL_CMD_H

#include "PlaylistCmd.h"
#include "Voice.h"

class Playlist_Start_Cmd : public PlaylistCmd
{

public:
	// Big 4v
	Playlist_Start_Cmd() = delete;
	Playlist_Start_Cmd(const Playlist_Start_Cmd &) = delete;
	Playlist_Start_Cmd &operator = (const Playlist_Start_Cmd &) = delete;
	~Playlist_Start_Cmd() = default;

	Playlist_Start_Cmd(Voice *pVoice);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;
public:
	// Data
	Voice *pVoice;
};

#endif

// --- End of File ---