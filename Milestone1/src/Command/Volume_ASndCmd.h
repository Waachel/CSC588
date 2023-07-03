//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Volume_ASND_COMMAND_H
#define Volume_ASND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class Volume_ASndCmd : public Command
{

public:
	// Big 4
	Volume_ASndCmd() = delete;
	Volume_ASndCmd(const Volume_ASndCmd&) = delete;
	Volume_ASndCmd& operator = (const Volume_ASndCmd&) = delete;
	~Volume_ASndCmd() = default;

	Volume_ASndCmd(Snd::ID snd_id, Snd* pSnd);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;

public:
	// Data
	Snd::ID snd_id;
	Snd* pSnd;
};

#endif

// --- End of File ---