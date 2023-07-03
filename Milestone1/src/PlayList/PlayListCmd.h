//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_COMMAND_H
#define Playlist_COMMAND_H

#include "Handle.h"

class PlaylistCmd
{
public:
	enum Type
	{
		Play,
		Stop,
		Pan,
		Uninitialized
	};

public:
	// Big 4
	PlaylistCmd() = default;
	PlaylistCmd(const PlaylistCmd &) = default;
	PlaylistCmd &operator = (const PlaylistCmd &) = default;
	virtual ~PlaylistCmd() = default;

	virtual void Execute() = 0;
	virtual void SetPan(float snd_pan) = 0;
	virtual void SetVolume(float volume) = 0;

public:
	// Data

};

#endif

// --- End of File ---