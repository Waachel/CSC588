//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_MANAGER_H
#define SND_MANAGER_H

#include "CircularData.h"

class SndManager
{
public:
	// Defaults
	SndManager(const SndManager&) = delete;
	const SndManager& operator = (const SndManager&) = delete;
	~SndManager();

	// Public methods:
	static void Create();
	static void Update();
	static bool SendData(int val);
	static void Destroy();

	static CircularData* GetInBuff();
	static CircularData* GetOutBuff();

private:
	static SndManager* privGetInstance();

	SndManager();

	CircularData* pIn;  // Game to Audio
	CircularData* pOut; // Audio to Game
};

#endif


// End of File 
