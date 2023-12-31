//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef AUDIO_ENGINE_H
#define AUDIO_ENGINE_H

#include "XAudio2Wrapper.h"
#include "CircularData.h"
#include "VoiceCallback.h"
#include "Voice.h"

class AudioEngine
{
public:
	// Big 4
	AudioEngine();
	AudioEngine(const AudioEngine &) = delete;
	AudioEngine &operator = (const AudioEngine &) = delete;
	~AudioEngine();
	
	static IXAudio2 *GetXAudio2();
	static IXAudio2MasteringVoice *GetMasterVoice();

	static void StartSound(Voice *pVoice, float volume);
	void PanSound(Voice* pVoice, float snd_pan);
	static void StopSound(Voice *pVoice);

private:
	void privStartCOMThreads();
	void privEndCOMThreads();
	void privCreateXAudio2();
	void privCreateMasterVoice();

private:
	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static AudioEngine *privGetInstance();
	static AudioEngine *psInstance;

	IXAudio2 *poXAudio2;
	IXAudio2MasteringVoice *poMasterVoice;
};


#endif

// --- End of File ---
