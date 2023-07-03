//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"


HandleMan::HandleMan()
{
	this->srcID = STARTING_ID;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id = INVALID_STATE;
	}
}

HandleMan::~HandleMan()
{
	// safety - nuke it again
	this->srcID = STARTING_ID;

	for (int i = 0; i < TABLE_SIZE; i++)
	{
		this->table[i].id = INVALID_STATE;
	}
}

Handle::ID HandleMan::privGetNewID()
{
	// Increment
	this->srcID++;

	return this->srcID;
}


Handle::Status HandleMan::InvalidateHandle(Handle& handle)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Handle::Status status = Handle::Status::HANDLE_ERROR;

	// before nuking it, is it valid?
	status = HandleMan::ValidateHandle(handle);
	assert(status == Handle::Status::SUCCESS);

	// nuke it
	pMan->table[handle.GetIndex()].id = INVALID_STATE;

	return status;
}


Handle::Status HandleMan::ValidateHandle(const Handle& handle)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Handle::Status status = Handle::Status::HANDLE_ERROR;

	if (handle.GetIndex() < TABLE_SIZE)
	{
		if (pMan->table[handle.GetIndex()].id == handle.GetID())
		{
			status = Handle::Status::SUCCESS;
		}
		else
		{
			status = Handle::Status::INVALID_HANDLE;
		}
	}
	else
	{
		status = Handle::Status::INVALID_HANDLE;
	}

	// trap for Debug
	// assert(status == Handle::Status::SUCCESS);

	return status;
}


Handle::Status HandleMan::ActivateHandle(Handle::ID& id, Handle::Index& index)
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Handle::Status status;

	if (pMan->privFindNextAvailable(index))
	{
		status = Handle::Status::SUCCESS;

		// Set it
		id = pMan->privGetNewID();
		pMan->table[index].id = id;
	}
	else
	{
		status = Handle::Status::INSUFFIENT_SPACE;
	}

	// trap for Debug
	assert(status == Handle::Status::SUCCESS);

	return status;
}

bool HandleMan::privFindNextAvailable(Handle::Index& index)
{
	bool status = false;

	for (Handle::Index i = 0; i < TABLE_SIZE; i++)
	{
		if (this->table[i].id == INVALID_STATE)
		{
			// found one
			index = i;
			status = true;
			break;
		}
	}

	return status;
}

HandleMan* HandleMan::privInstance()
{
	// Here's the singleton
	static HandleMan instance;

	return &instance;
}

void HandleMan::PrintTable()
{
	HandleMan* pMan = HandleMan::privInstance();
	assert(pMan);

	Trace::out("\n");
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		if (pMan->table[i].id == INVALID_STATE)
		{
			Trace::out("[%d]: %s \n", i, STRING_ME(INVALID_STATE));
		}
		else
		{
			Trace::out("[%d]: %x \n", i, pMan->table[i]);
		}
	}
	Trace::out("\n");
}

// ---  End of File ---------------
