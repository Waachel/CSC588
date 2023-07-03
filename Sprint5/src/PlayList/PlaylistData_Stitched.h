//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PLAYLIST_DATA_STITCHED_H
#define PLAYLIST_DATA_STITCHED_H

#include "XAudio2Wrapper.h"
#include "PlaylistData.h"
#include "Wave.h"
#include "VoiceCallback_Stitched.h"

// p - pointer
// po - pointer owned (composition)
// ps - pointer to static
// por - pointer owned recieved
// pc - pointer created then transferred to por

class PlaylistData_Stitched : public PlaylistData
{
public:
	PlaylistData_Stitched() = delete;
	PlaylistData_Stitched(const PlaylistData_Stitched &) = delete;
	PlaylistData_Stitched &operator = (const PlaylistData_Stitched &) = delete;
	virtual ~PlaylistData_Stitched() = default;

	PlaylistData_Stitched(Wave::ID wA, Wave::ID wB, Wave::ID wC, Wave::ID wD)
		: PlaylistData(), waveA(wA), waveB(wB), waveC(wC), waveD(wD)
	{
	}

	virtual Wave::ID GetFirstWaveID() override
	{
		return this->waveA;
	}

	virtual VoiceCallback *Create_VoiceCallback() override
	{
		return new VoiceCallback_Stitched(waveB, waveC, waveD);
	}

	Wave::ID waveA;
	Wave::ID waveB;
	Wave::ID waveC;
	Wave::ID waveD;

};

#endif

// --- End of File ---