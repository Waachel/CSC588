//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_H
#define WAVE_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Thread - File\I_File_CB.h"

typedef unsigned char RawData;

class Wave : public DLink
{
public:
	enum class Status
	{
		PENDING,
		READY,
		EMPTY
	};

	enum ID
	{
		Fiddle = 0x77770000,
		Bassoon,
		Strings,
		Calliope,
		Oboe,
		Oboe2_mono,
		SongA,
		SongB,
		Intro,
		A,
		AtoB,
		B,
		BtoC,
		C,
		CtoA,
		End,
		Empty
	};

	static const unsigned int NAME_SIZE = 256;

public:
	// Big 4
	Wave();
	Wave(const Wave &) = delete;
	Wave &operator = (const Wave &) = delete;
	virtual ~Wave();

	void SetPending(const char *const pWaveName, Wave::ID name, I_File_CB *pIFileCB);

	void SetId(Wave::ID id);
	Wave::ID GetId() const;

	void Register(WAVEFORMATEXTENSIBLE *poWfx,RawData *poRawBuff,unsigned long rawBuffSize);
		
	void Dump();
	void Wash();

	virtual bool Compare(DLink *pTargetNode) override;

private:
	void privClear();
	void privLoadBuffer(const char *const pWaveName);
	void privSetName(const char *const pWaveName);

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

	WAVEFORMATEXTENSIBLE	*poWfx;
	RawData					*poRawBuff;
	unsigned long           rawBuffSize;
	ID                      id;
	char                    strName[NAME_SIZE];
	I_File_CB				*pIFileCB;
	Status                  status;

	Handle handle;
};

#endif

// --- End of File ---