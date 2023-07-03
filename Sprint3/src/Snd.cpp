//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CircularData.h"
#include "SndManager.h"
#include "Snd.h"


Snd::Snd(SndId snd)
	: sndID(snd)
{
	// generates -> new handle automatically 
}

Snd::Snd(const Snd& tmp)
	: sndID(tmp.sndID)
{
	// generates -> new handle automatically 
}

const Snd& Snd::operator=(const Snd& tmp)
{
	// QUESTION: copy handle?  --> I say NO, its the data not the handle
	//           to prevent anyone, I deleted the copy operator in handle
	//           this->handle = r.handle;   <----- I say its a no no

	this->sndID = tmp.sndID;

	return *this;
}

Snd::~Snd()
{
	// Kill the Handle
	// Gets automagically killed by the ~Handle()
}


Handle::Status Snd::Play()
{
	HANDLE_CHECK_BEGIN

		// Send a play command to the Audio thread
		SndManager::SendData((int)this->sndID);

	HANDLE_CHECK_END
}

Handle::Status Snd::Volume()
{
	HANDLE_CHECK_BEGIN

		// Send a play command to the Audio thread
		SndManager::SendData((int)this->sndID);

	HANDLE_CHECK_END
}

Handle::Status Snd::Panning()
{
	HANDLE_CHECK_BEGIN

		// Send a play command to the Audio thread
		SndManager::SendData((int)this->sndID);

	HANDLE_CHECK_END
}

Handle::Status Snd::Pitch()
{
	HANDLE_CHECK_BEGIN

		// Send a play command to the Audio thread
		SndManager::SendData((int)this->sndID);

	HANDLE_CHECK_END
}

Handle::Status Snd::Stop()
{
	HANDLE_CHECK_BEGIN

		// Send a play command to the Audio thread
		SndManager::SendData((int)this->sndID);

	HANDLE_CHECK_END
}

// End of File 
