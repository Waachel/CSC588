//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Pan_ASND_COMMAND_H
#define Pan_ASND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class Pan_ASndCmd : public Command
{

public:
	// Big 4
	Pan_ASndCmd() = delete;
	Pan_ASndCmd(const Pan_ASndCmd&) = delete;
	Pan_ASndCmd& operator = (const Pan_ASndCmd&) = delete;
	~Pan_ASndCmd() = default;

	Pan_ASndCmd(Snd::ID snd_id, Snd* pSnd);

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