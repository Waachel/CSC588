//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Playlist.h"
#include "StringThis.h"
#include "VoiceMan.h"
#include "SndMan.h"
#include "Playlist_Start_Cmd.h"
#include "Playlist_Pan_Cmd.h"
#include "VoiceCallback_Stitched.h"

Playlist::Playlist()
	: pVoice(nullptr),
	poCmd(nullptr), poPanCmd(nullptr),
	id(Snd::ID::Uninitialized),
	type(Playlist::Type::Uninitialized)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Playlist::~Playlist()
{
	//Debug::out("~Playlist()\n");
	if(this->pVoice)
	{
		VoiceMan::Remove(this->pVoice);
		this->pVoice = nullptr;
	}
	delete poPanCmd;
	this->poPanCmd = nullptr;

	delete poCmd;
	this->poCmd = nullptr;

}

void Playlist::SetId(Snd::ID _id)
{
	this->id = _id;
}

Snd::ID Playlist::GetId() const
{
	return this->id;
}

void Playlist::Set(Snd::ID snd_id, Wave::ID wave_id, VoiceCallback *pCallback)
{
	this->id = snd_id;
	this->type = Playlist::Type::Uninitialized;

	assert(pCallback);

	this->pVoice = VoiceMan::Add(wave_id, pCallback);
	assert(this->pVoice);

	pCallback->SetVoice(pVoice);

	this->poCmd = new Playlist_Start_Cmd(this->pVoice);
	this->poPanCmd = new Playlist_Pan_Cmd(this->pVoice);
	assert(this->poCmd);
}


void Playlist::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tPlaylist(%p) %s Voice(%p) src:%p\n", this, StringMe(this->id), this->pVoice, this->pVoice->poSourceVoice);
}

void Playlist::privClear()
{
	// This method... is used in wash to reuse 
	// If its alive... remove the data
	if(this->pVoice)
	{
		VoiceMan::Remove(this->pVoice);
		this->pVoice = nullptr;
	}

	delete this->poCmd;
	this->poCmd = nullptr;


	this->id = Snd::ID::Uninitialized;

}

void Playlist::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool Playlist::Compare(DLink *pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	Playlist *pDataB = (Playlist *) pTarget;

	bool status = false;

	if(this->id == pDataB->id)
	{
		status = true;
	}

	return status;
}





// --- End of File ---