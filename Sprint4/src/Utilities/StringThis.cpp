//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"


StringThis::StringThis(Wave::Status status)
{
	switch(status)
	{
	case Wave::Status::EMPTY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::EMPTY));
		break;

	case Wave::Status::PENDING:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::PENDING));
		break;

	case Wave::Status::READY:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(WaveTable::READY));
		break;


	default:
		assert(false);
	}
}

StringThis::StringThis(Handle::Status status)
{
	switch(status)
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

	case Handle::Status::VALID_HANDLE:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::VALID_HANDLE));
		break;

	case Handle::Status::HANDLE_ERROR:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Handle::HANDLE_ERROR));
		break;

	default:
		assert(false);
	}
}

StringThis::StringThis(Wave::ID status)
{
	switch(status)
	{
	case Wave::ID::Bassoon:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Bassoon));
		break;

	case Wave::ID::Calliope:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Calliope));
		break;

	case Wave::ID::Fiddle:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Fiddle));
		break;

	case Wave::ID::Oboe:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Oboe));
		break;

	case Wave::ID::SongA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongA));
		break;

	case Wave::ID::SongB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::SongB));
		break;

	case Wave::ID::Strings:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Strings));
		break;

	case Wave::ID::Intro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Intro));
		break;

	case Wave::ID::A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::A));
		break;

	case Wave::ID::AtoB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::AtoB));
		break;

	case Wave::ID::B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::B));
		break;

	case Wave::ID::BtoC:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::BtoC));
		break;

	case Wave::ID::C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::C));
		break;

	case Wave::ID::CtoA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::CtoA));
		break;

	case Wave::ID::End:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::End));
		break;

	case Wave::ID::Empty:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Wave::Empty));
		break;

	default:
		assert(false);
	}

}

StringThis::StringThis(Snd::ID status)
{
	switch (status)
	{
	case Snd::ID::Bassoon:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Bassoon));
		break;

	case Snd::ID::Calliope:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Calliope));
		break;

	case Snd::ID::Fiddle:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Fiddle));
		break;

	case Snd::ID::Oboe:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Oboe));
		break;

	case Snd::ID::SongA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::SongA));
		break;

	case Snd::ID::SongB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::SongB));
		break;

	case Snd::ID::Strings:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Strings));
		break;

	case Snd::ID::Seinfeld:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Seinfeld));
		break;

	case Snd::ID::Intro:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Intro));
		break;

	case Snd::ID::A:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::A));
		break;

	case Snd::ID::AtoB:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::AtoB));
		break;

	case Snd::ID::B:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::B));
		break;

	case Snd::ID::BtoC:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::BtoC));
		break;

	case Snd::ID::C:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::C));
		break;

	case Snd::ID::CtoA:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::CtoA));
		break;

	case Snd::ID::End:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::End));
		break;

	case Snd::ID::Uninitialized:
		strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Snd::Uninitialized));
		break;

	default:
		assert(false);
	}

}

StringThis::operator char *()
{
	return this->buffer;
}

// --- End of File ---