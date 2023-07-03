//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef AUDIO_H
#define AUDIO_H

#include "Wave.h"
#include "WaveTable.h"

class Audio
{
public:
	enum class Blocking
	{
		LOAD
	};

	enum class Async
	{
		LOAD
	};

public:
	static void Create();
	static void Destroy();

	static void Load(const Blocking, Wave::ID wave_id, const char *const pWaveName);

	static WaveTable *GetWaveTable();
	static void WaveTableDump();

private:
	Audio();
	Audio(const Audio &) = delete;
	Audio &operator = (const Audio &) = delete;
	~Audio();

	WaveTable *poWaveTable;

	static Audio *privGetInstance();
	static Audio *posInstance;
};

#endif

//---  End of File ---