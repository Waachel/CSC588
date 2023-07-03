//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Stop_ASND_COMMAND_H
#define Stop_ASND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class Stop_ASndCmd : public Command
{

public:
	// Big 4
	Stop_ASndCmd() = delete;
	Stop_ASndCmd(const Stop_ASndCmd&) = delete;
	Stop_ASndCmd& operator = (const Stop_ASndCmd&) = delete;
	~Stop_ASndCmd() = default;

	Stop_ASndCmd(Snd::ID snd_id, Snd* pSnd);

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