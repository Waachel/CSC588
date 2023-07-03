//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"


StringThis::StringThis(Handle::Status status)
{
	switch (status)
	{
	case Handle::Status::SUCCESS:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::SUCCESS));
		break;

	case Handle::Status::INSUFFIENT_SPACE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INSUFFIENT_SPACE));
		break;

	case Handle::Status::INVALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::INVALID_HANDLE));
		break;

	case Handle::Status::HANDLE_ERROR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::HANDLE_ERROR));
		break;

	default:
		assert(false);
	}
}

StringThis::operator char* ()
{
	return this->buffer;
}

// --- End of File ---