//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_CALLBACK_H
#define VOICE_CALLBACK_H

#include "XAudio2Wrapper.h"

class Voice;

using namespace ThreadFramework;

//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	enum class Type
	{
		One,
		Stitched,
		Uninitialized
	};

public:

	VoiceCallback();
	VoiceCallback(const VoiceCallback &);
	VoiceCallback(VoiceCallback &&) = delete;
	VoiceCallback &operator = (const VoiceCallback &) = delete;
	VoiceCallback &operator = (VoiceCallback &&) = delete;
	virtual ~VoiceCallback();

	VoiceCallback(Type type);

	virtual VoiceCallback *CreateCallbackCopy() = 0;
	virtual void SetVoice(Voice *pVoice) = 0;

	Type type;

};

#endif

// --- End of File ---
