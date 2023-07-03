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
		Fiddle = 0x77770000,
		Bassoon,
		Strings,
		Calliope,
		Oboe,
		SongA,
		SongB,
		Seinfeld,
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

	Handle::Status Play();
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
