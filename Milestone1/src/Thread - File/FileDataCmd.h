//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef FILE_DATA_H
#define FILE_DATA_H

#include "Wave.h"
#include "Command.h"

struct FileDataCmd : public Command
{
	FileDataCmd() = delete;
	FileDataCmd(const FileDataCmd &) = delete;
	FileDataCmd &operator = (const FileDataCmd &) = delete;
	~FileDataCmd() = default;

	FileDataCmd(const char *const pWaveName, Wave *pWave);
	void LoadBuffer(const char *const pWaveName);

	void Execute() override;
	virtual void SetVolume(float volume) override;
	virtual void SetPan(float snd_pan) override;

	WAVEFORMATEXTENSIBLE	*poWfx;
	RawData					*poRawBuff;
	unsigned long           rawBuffSize;
	Wave                    *pWave;
};

#endif

//---  End of File ---
