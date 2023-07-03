//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Pan_PL_CMD_H
#define Pan_PL_CMD_H

#include "PlaylistCmd.h"
#include "Voice.h"
#include "AzulCore.h"

class Playlist_Pan_Cmd : public PlaylistCmd
{

public:
	// Big 4v
	Playlist_Pan_Cmd() = delete;
	Playlist_Pan_Cmd(const Playlist_Pan_Cmd&) = delete;
	Playlist_Pan_Cmd& operator = (const Playlist_Pan_Cmd&) = delete;
	~Playlist_Pan_Cmd() = default;

	Playlist_Pan_Cmd(Voice* pVoice);

	virtual void Execute() override;
	virtual void SetPan(float snd_pan) override;
	bool WaitForTime(Timer& t, Time TriggerTime);

	void UpdatePan(float pan);
	virtual void SetVolume(float volume) override;

public:
	// Data
	Voice* pVoice;
	AudioEngine* engine;
};

#endif

// --- End of File ---