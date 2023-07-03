//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef STRING_THIS_H
#define STRING_THIS_H

#include "Handle.h"

class StringThis
{
public:
	static const unsigned int BUFFER_SIZE = 64;
public:
	StringThis(Handle::Status status);

	operator char* ();

	// data:
	char buffer[BUFFER_SIZE];
};

#define StringMe(x)  ((char *)StringThis(x)) 

#endif

// --- End of File ---
