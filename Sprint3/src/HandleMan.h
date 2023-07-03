//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef HANDLE_MAN_H
#define HANDLE_MAN_H

#include "Handle.h"

class HandleMan
{
private:

	// constants
	static const unsigned int TABLE_SIZE = 4;
	static const unsigned int INVALID_STATE = 0x0;
	static const unsigned int STARTING_ID = 0xAAAA0000;

	// Nested class
	class HandleTable
	{
	public:
		Handle::ID id;
	};


public:
	HandleMan();
	~HandleMan();

	//-----------------------------------------------------
	// You cannot copy the singleton
	//-----------------------------------------------------
	HandleMan(const HandleMan&) = delete;
	const HandleMan& operator = (const HandleMan&) = delete;

	//-----------------------------------------------------
	// Being strategic on what is expose or not
	//-----------------------------------------------------
	static Handle::Status ActivateHandle(Handle::ID& id, Handle::Index& index);
	static Handle::Status InvalidateHandle(Handle& handle);
	static Handle::Status ValidateHandle(const Handle& handle);

	//-----------------------------------------------------
	// Only for our DEBUG - remove for application
	//-----------------------------------------------------
	static void PrintTable();

private:
	//-----------------------------------------------------
	// Keeping internals... private
	//-----------------------------------------------------
	static HandleMan* privInstance();
	Handle::ID privGetNewID();
	bool privFindNextAvailable(Handle::Index& index);

	//-----------------------------------------------------
	// Raw data
	//-----------------------------------------------------
	HandleTable table[TABLE_SIZE];
	Handle::ID  srcID;
};

#endif

// ---  End of File ---------------
