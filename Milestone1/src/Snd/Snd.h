//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#ifndef SND_H
#define SND_H

#include "Handle.h"
#include "DLink.h"
#include "Snd.h"
class ASnd;


class Snd : public DLink
{
public:
	enum ID
	{ 
		Fiddle = 101,
		Bassoon = 102,
		Oboe2_mono = 103,
		SongA = 104,
		SongB = 105,
		Seinfeld = 201,
		Strings,
		Calliope,
		Oboe,
		Intro,
		A,
		AtoB,
		B,
		BtoC,
		C,
		CtoA,
		End, 
		Uninitialized
	};
public:
	// Big 4
	Snd();
	Snd(const Snd &) = delete;
	Snd &operator = (const Snd &) = delete;
	virtual ~Snd();

	void Set(Snd::ID snd_id);
	void Dump();
	void Wash();
	virtual bool Compare(DLink *pTargetNode) override;

	void Set(ASnd *pASnd);
	ASnd *GetASnd();

	// public
	Snd(Snd::ID sndId);

	Handle::Status Play(float volume);
	Handle::Status Stop();
	Handle::Status SetVolume(float volume);
	Handle::Status Pan(float snd_pan);
	//	Handle::Status Stop();

private:
	void privClear();


public:
	//----------------------------------------------------
	// Data
	//----------------------------------------------------
	Snd::ID snd_id;
	ASnd *pASnd;

	Handle handle;
};

#endif
