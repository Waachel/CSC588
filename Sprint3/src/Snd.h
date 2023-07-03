//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_H
#define SND_H

#include "HandleMan.h"
#include "SndCallRegistry.h"

class Snd
{
public:
	// defaults
	Snd() = delete;

	Snd(const Snd&);
	const Snd& operator=(const Snd&);
	~Snd();

	// public
	Snd(SndId snd);

	Handle::Status Play();

	Handle::Status Volume();
	
	Handle::Status Panning();

	Handle::Status Pitch();
	
	Handle::Status Stop();

private:
	SndId	sndID;

	// Here's the magic
	HANDLE_VARABLE
};

#endif


// End of File 
