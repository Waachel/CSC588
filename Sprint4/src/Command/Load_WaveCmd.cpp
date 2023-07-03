//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Load_WaveCmd.h"
#include "WaveMan.h"

Load_WaveCmd::Load_WaveCmd(Wave::ID _id, const char *const _pWaveName, I_File_CB *_pFileCB)
	: Command(),
	id(_id),
	pWaveName(_pWaveName),
	pIFileCB(_pFileCB)
{
	assert(pWaveName);
	assert(pIFileCB);
}

void Load_WaveCmd::Execute()
{
	WaveMan::Add(this->id, this->pWaveName, this->pIFileCB);

	delete this;
}


// --- End of File ---