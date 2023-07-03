//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------


#ifndef VOICE_CALLBACK_H
#define VOICE_CALLBACK_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"

using namespace ThreadFramework;

// Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	bool   finished = false;
	CircularData *pOut;

	VoiceCallback(CircularData *_pOut)
	{
		assert(_pOut);
		this->pOut = _pOut;
	}

	virtual ~VoiceCallback()
	{

	}

	void STDMETHODCALLTYPE OnStreamEnd()
	{
		//	SetEvent(hBufferEndEvent);

		Debug::out("VoiceCallback::StreamEnd()\n");
		pOut->PushBack(0x1234);

		finished = true;
	}

	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() { }
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) {  }
	void STDMETHODCALLTYPE OnBufferEnd(void *) {  }
	void STDMETHODCALLTYPE OnBufferStart(void *) {  }
	void STDMETHODCALLTYPE OnLoopEnd(void *) {  }
	void STDMETHODCALLTYPE OnVoiceError(void *, HRESULT) {  }
};

#endif

// --- End of File ---