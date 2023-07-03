//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"
#include "Handle.h"

using namespace ThreadFramework;

Handle::Handle()
{
	//Activate
	Status status = HandleMan::ActivateHandle(this->id, this->index);
	assert(status == Status::SUCCESS);

	Debug::out("Handle(): new handle(%x):0x%X\n", this->index, this->id);
}

Handle::~Handle()
{
	// Invalidate handle;
	HandleMan::InvalidateHandle(*this);

	Debug::out("~Handle(): invalidate handle(%x):0x%X\n", this->index, this->id);
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

Handle::Status Handle::ValidateHandle(const Handle& handle)
{
	return HandleMan::ValidateHandle(handle);
}

Handle::Status Handle::InvalidateHandle(Handle& handle)
{
	return HandleMan::InvalidateHandle(handle);
}

// ---  End of File ---------------
