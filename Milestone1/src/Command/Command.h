//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

#include "Handle.h"

class Command
{
public:
	enum Type
	{
		LoadWave,
		PlaySnd,
		Uninitialized
	};

public:
	// Big 4
	Command() = default;
	Command(const Command&) = default;
	Command& operator = (const Command&) = default;
	virtual ~Command() = default;

	virtual void Execute() = 0;
	virtual void SetVolume(float volume) = 0;
	virtual void SetPan(float snd_pan) = 0;

public:
	// Data

	Handle handle;
};

#endif

// --- End of File ---