#ifndef PANNING_H
#define PANNING_H

#include "XAudio2Wrapper.h"

void PanningMain(IXAudio2MasteringVoice* pMasteringVoice, IXAudio2SourceVoice* pSound, HRESULT hr);

#endif