//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceCallback_One.h"

VoiceCallback_One::~VoiceCallback_One()
{
	//Debug::out("~VoiceCallback_One(%p) \n",this);
}

VoiceCallback_One::VoiceCallback_One()
	: VoiceCallback(Type::One),
	finished(false),
	pVoice(nullptr)
{

}

VoiceCallback_One::VoiceCallback_One(const VoiceCallback_One &r)
	: VoiceCallback(r.type),
	finished(r.finished),
	pVoice(nullptr)
{
	assert(r.type == Type::One);
	assert(r.finished == false);
	// pVoice should be null its externally set
	assert(this->pVoice == nullptr);
}

VoiceCallback * VoiceCallback_One::CreateCallbackCopy()
{
	// copy constructor
	return new VoiceCallback_One(*this);
}

void VoiceCallback_One::SetVoice(Voice *_pVoice)
{
	assert(_pVoice);
	this->pVoice = _pVoice;
}

void VoiceCallback_One::OnStreamEnd()
{
	finished = true;
}

void VoiceCallback_One::OnVoiceProcessingPassEnd()
{
}

void VoiceCallback_One::OnVoiceProcessingPassStart(UINT32)
{
}

void VoiceCallback_One::OnBufferEnd(void *)
{
}

void VoiceCallback_One::OnBufferStart(void *)
{
}

void VoiceCallback_One::OnLoopEnd(void *)
{
}

void VoiceCallback_One::OnVoiceError(void *, HRESULT)
{
}

// --- End of File ---