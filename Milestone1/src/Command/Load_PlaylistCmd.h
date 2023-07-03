//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_LOAD_COMMAND_H
#define Playlist_LOAD_COMMAND_H

#include "Command.h"
#include "Snd.h"
#include "Wave.h"
#include "Playlist.h"
#include "PlaylistData.h"


class Load_PlaylistCmd : public Command
{

public:
	// Big 4
	 Load_PlaylistCmd() = delete;
	 Load_PlaylistCmd(const Load_PlaylistCmd &) = delete;
	 Load_PlaylistCmd &operator = (const Load_PlaylistCmd &) = delete;
	~Load_PlaylistCmd() = default;

	Load_PlaylistCmd(Snd::ID snd_id, PlaylistData *pPlaylistData);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;

public:
	// Data
	Snd::ID snd_id;
	PlaylistData *poPlaylistData;
};

#endif

// --- End of File ---