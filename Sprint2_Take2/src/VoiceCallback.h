//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef _VOICE_CALLBACK_H_
#define _VOICE_CALLBACK_H_

#include "XAudio2Wrapper.h"

//  - VoiceCallback.h -
// Sample voice callback

class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	HANDLE hBufferEndEvent;
	bool   finished = false;

	VoiceCallback()
		: hBufferEndEvent(CreateEvent(0, FALSE, FALSE, 0))
	{
	}

	virtual ~VoiceCallback()
	{
		CloseHandle(hBufferEndEvent);
	}

	void STDMETHODCALLTYPE OnStreamEnd()
	{
		finished = true;
	}

	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() { }
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) {  }
	void STDMETHODCALLTYPE OnBufferEnd(void*) {  }
	void STDMETHODCALLTYPE OnBufferStart(void*) {  }
	void STDMETHODCALLTYPE OnLoopEnd(void*) {  }
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) {  }
};

#endif

// --- End of File ---