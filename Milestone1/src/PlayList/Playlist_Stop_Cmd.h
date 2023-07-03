//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Stop_PL_CMD_H
#define Stop_PL_CMD_H

#include "PlaylistCmd.h"
#include "Voice.h"

class Playlist_Stop_Cmd : public PlaylistCmd
{

public:
	// Big 4v
	Playlist_Stop_Cmd() = delete;
	Playlist_Stop_Cmd(const Playlist_Stop_Cmd&) = delete;
	Playlist_Stop_Cmd& operator = (const Playlist_Stop_Cmd&) = delete;
	~Playlist_Stop_Cmd() = default;

	Playlist_Stop_Cmd(Voice* pVoice);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;
public:
	// Data
	Voice* pVoice;
};

#endif

// --- End of File ---