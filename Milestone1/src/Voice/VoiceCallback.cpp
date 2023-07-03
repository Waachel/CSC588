//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceCallback.h"

VoiceCallback::~VoiceCallback()
{
	//Debug::out("~VoiceCallback(%p)\n", this);
}

VoiceCallback::VoiceCallback()
	: type(VoiceCallback::Type::Uninitialized)
{

}

VoiceCallback::VoiceCallback(const VoiceCallback &r)
	:type(r.type)
{

}

VoiceCallback::VoiceCallback(Type t)
	:type(t)
{

}

// --- End of File ---
