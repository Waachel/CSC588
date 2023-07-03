//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CREATE_ASND_COMMAND_H
#define CREATE_ASND_COMMAND_H

#include "Command.h"
#include "Snd.h"

class Create_ASndCmd : public Command
{

public:
	// Big 4
	Create_ASndCmd() = delete;
	Create_ASndCmd(const Create_ASndCmd&) = delete;
	Create_ASndCmd& operator = (const Create_ASndCmd&) = delete;
	~Create_ASndCmd() = default;

	Create_ASndCmd(Snd::ID snd_id, Snd* pSnd);

	virtual void Execute() override;

public:
	// Data
	Snd::ID snd_id;
	Snd* pSnd;
};

#endif

// --- End of File ---