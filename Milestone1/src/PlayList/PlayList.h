//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Playlist_H
#define Playlist_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Snd.h"
#include "Voice.h"
#include "PlaylistCmd.h"
#include "VoiceCallback.h"


class Playlist : public DLink
{
public:
	enum class Type
	{
		PlayOnce,
		PlayRepeated,
		Stitched,
		Default = PlayOnce,
		Uninitialized
	};

public:
	// Big 4
	Playlist();
	Playlist(const Playlist &) = delete;
	Playlist &operator = (const Playlist &) = delete;
	virtual ~Playlist();

	void Set(Snd::ID snd_id, Wave::ID wave_id, VoiceCallback *pCallback);

	void SetId(Snd::ID id);
	Snd::ID GetId() const;

	void Dump();
	void Wash();

	virtual bool Compare(DLink *pTargetNode) override;

private:
	void privClear();
	void privLoadBuffer(const char *const pWaveName);
	void privSetName(const char *const pWaveName);

public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------

	// In the future it can be many...
	Voice *pVoice;

	// Command pattern
	PlaylistCmd *poCmd;
	PlaylistCmd* poPanCmd;
	PlaylistCmd* poVolumeCmd;
	PlaylistCmd* poStopCmd;

	Snd::ID id;
	Type    type;

	Handle handle;
};

#endif

// --- End of File ---