//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef FILE_LOAD_COMMAND_H
#define FILE_LOAD_COMMAND_H

#include "Command.h"
#include "Wave.h"

class FileLoadCmd : public Command
{
public:
	// Big 4
	FileLoadCmd() = delete;
	FileLoadCmd(const FileLoadCmd &) = delete;
	FileLoadCmd &operator = (const FileLoadCmd &) = delete;
	~FileLoadCmd();

	FileLoadCmd(Wave::ID id, const char *const pWaveName, Wave *pWave);

	virtual void Execute() override;

public:
	// Data
	Wave::ID wave_id;
	const char *const pWaveName;
	Wave *pWave;
};

#endif

// --- End of File ---