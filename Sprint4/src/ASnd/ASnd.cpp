//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ASnd.h"
#include "PlaylistJukeBox.h"
#include "PlaylistMan.h"
#include "StringThis.h"

using namespace ThreadFramework;

ASnd::ASnd()
	:pPlaylist(nullptr),
	snd_id(Snd::ID::Uninitialized),
	pSnd(nullptr)
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

ASnd::~ASnd()
{
	//Debug::out("~ASnd()\n");
}


void ASnd::Set(Snd::ID _snd_id, Snd *_pSnd)
{
	this->snd_id = _snd_id;

	assert(_pSnd);
	this->pSnd = _pSnd;

	pSnd->Set(this);

	// Find a reference
	Playlist *pPlayRef = PlaylistJukeBox::Find(this->snd_id);
	assert(pPlayRef);

	// Do a deep copy...
	// Problem: you don't know what type of callback is being used
	// Answer: ask the class to create one itself
	assert(pPlayRef->pVoice);
	assert(pPlayRef->pVoice->porCallback);

	VoiceCallback *pCallback;
	
	pCallback = pPlayRef->pVoice->porCallback->CreateCallbackCopy();
	assert(pCallback);

	this->pPlaylist = PlaylistMan::Add( _snd_id, 
										pPlayRef->pVoice->pWave->id,
										pCallback);

	// Make sure new playlist is TRULY independent
	assert(this->pPlaylist);
	pCallback->SetVoice(this->pPlaylist->pVoice);

	assert(this->pPlaylist->pVoice);
	assert(this->pPlaylist->pVoice != pPlayRef->pVoice);
}

void ASnd::Play()
{
	assert(this->pPlaylist);

	this->pPlaylist->poCmd->Execute();
	
	Debug::out("ASnd::Play(%p)\n",this);
}

void ASnd::Pan(float snd_pan)
{
	assert(this->pPlaylist);
	this->pPlaylist->poPanCmd->SetPan(snd_pan);
	this->pPlaylist->poPanCmd->Execute();

	Debug::out("ASnd::Pan(%p)\n", this);
}

void ASnd::Dump()
{
	// Dump - Print contents to the debug output window
	Trace::out("\t\tASnd(%p) %s Playlist(%p)\n", this, StringMe(this->snd_id), this->pPlaylist);
}

void ASnd::privClear()
{
	this->pPlaylist = nullptr;
	this->snd_id = Snd::ID::Uninitialized;
}

void ASnd::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->privClear();
}

bool ASnd::Compare(DLink *pTarget)
{
	// This is used in ManBase.Find() 
	assert(pTarget != nullptr);

	ASnd *pDataB = (ASnd *) pTarget;

	bool status = false;

	if(this->snd_id == pDataB->snd_id)
	{
		status = true;
	}

	return status;
}





// --- End of File ---