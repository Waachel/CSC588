//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Snd.h"
#include "SndMan.h"
#include "StringThis.h"
#include "Create_ASndCmd.h"
#include "Play_ASndCmd.h"
#include "Pan_ASndCmd.h"

Snd::Snd()
	:snd_id(Snd::ID::Uninitialized),
	pASnd(nullptr)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Snd::~Snd()
{
	//Debug::out("~Snd()\n");
	// check "this" and input
	assert(Handle::IsValid(this->handle) == Handle::Status::VALID_HANDLE);
}


void Snd::Set(Snd::ID _snd_id)
{
	this->snd_id = _snd_id;

	// Send a command to create ASnd
	Create_ASndCmd *pCmd = new Create_ASndCmd(this->snd_id, this);
	assert(pCmd);

	SndMan::Send(pCmd);
}

void Snd::Set(ASnd *_pASnd)
{
	assert(_pASnd);
	this->pASnd = _pASnd;
}

ASnd *Snd::GetASnd()
{
	assert(pASnd);
	return this->pASnd;
}

void Snd::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tSnd(%p) %s  ASnd(%p)\n", this, StringMe(this->snd_id),this->pASnd);
}

void Snd::privClear()
{
	this->snd_id = Snd::ID::Uninitialized;
}

void Snd::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool Snd::Compare(DLink *pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Snd *pDataB = (Snd *) pTarget;

	bool status = false;

	if(this->snd_id == pDataB->snd_id)
	{
		status = true;
	}

	return status;
}

Handle::Status Snd::Play()
{
	Handle::Lock lock(this->handle);

	if(lock)
	{
		Play_ASndCmd *pCmd = new Play_ASndCmd(this->snd_id, this);
		assert(pCmd);
		SndMan::Send(pCmd);
	}

	return lock;
}

Handle::Status Snd::Pan(float snd_pan)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		Pan_ASndCmd* pCmd = new Pan_ASndCmd(this->snd_id, this, snd_pan);
		assert(pCmd);
		SndMan::Send(pCmd);
	}

	return lock;
}



// --- End of File ---
