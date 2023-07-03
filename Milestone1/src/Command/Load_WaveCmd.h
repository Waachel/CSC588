//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef LOAD_WAVE_COMMAND_H
#define LOAD_WAVE_COMMAND_H

#include "Command.h"
#include "Wave.h"
#include "Thread - File\I_File_CB.h"

class Load_WaveCmd : public Command
{
public:
	// Big 4
	Load_WaveCmd() = delete;
	Load_WaveCmd(const Load_WaveCmd &) = delete;
	Load_WaveCmd &operator = (const Load_WaveCmd &) = delete;
	~Load_WaveCmd() = default;

	Load_WaveCmd(Wave::ID id, const char *const pWaveName, I_File_CB *pFileCB);

	virtual void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;

public:
	// Data
	Wave::ID id;
	const char *const pWaveName;
	I_File_CB *pIFileCB;
};

#endif

// --- End of File ---