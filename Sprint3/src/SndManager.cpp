//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SndManager.h"

using namespace ThreadFramework;

SndManager::SndManager()
{
	this->pIn = new CircularData();
	assert(pIn);

	this->pOut = new CircularData();
	assert(pOut);
}

SndManager::~SndManager()
{
	delete this->pIn;
	delete this->pOut;
}

CircularData *SndManager::GetInBuff()
{
	SndManager *pMan = SndManager::privGetInstance();
	return pMan->pIn;
}

CircularData *SndManager::GetOutBuff()
{
	SndManager *pMan = SndManager::privGetInstance();
	return pMan->pOut;
}

bool SndManager::SendData(int data)
{
	SndManager *pMan = SndManager::privGetInstance();

	Debug::out("-->Audio: %x \n", data);
	bool status = pMan->pIn->PushBack(data);

	return status;
}

void SndManager::Update()
{
	SndManager *pMan = SndManager::privGetInstance();

	int val;

	if (pMan->pOut->PopFront(val) == true)
	{
		if (val == 0x1234)
		{
			Debug::out("-->Game: %x  Snd Ended callback\n", val);
		}
	}
}

void SndManager::Create()
{
	Debug::out("SndManager::Create()\n");
	SndManager *pMan = SndManager::privGetInstance();
	assert(pMan);
}

void SndManager::Destroy()
{

	Debug::out("SndManager::Destroy()\n");
}


SndManager *SndManager::privGetInstance()
{
	static SndManager sndMan;
	return &sndMan;
}


// --- End of File ---
