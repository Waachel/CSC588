//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PLAY_ASND_COMMAND_H
#define PLAY_ASND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class Play_ASndCmd : public Command
{

public:
	// Big 4
	Play_ASndCmd() = delete;
	Play_ASndCmd(const Play_ASndCmd &) = delete;
	Play_ASndCmd &operator = (const Play_ASndCmd &) = delete;
	~Play_ASndCmd() = default;

	Play_ASndCmd(Snd::ID snd_id, Snd *pSnd);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;

public:
	// Data
	Snd::ID snd_id;
	Snd *pSnd;
};

#endif

// --- End of File ---