//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Audio.h"
#include "Load_WaveCmd.h"
#include "SndMan.h"
#include "I_File_CB.h"

Audio *Audio::posInstance = nullptr;

Audio::Audio()
{
    this->poWaveTable = new WaveTable();
    assert(this->poWaveTable);
}

Audio::~Audio()
{
    delete this->poWaveTable;
}

void Audio::Destroy()
{
    Audio *pAudio = Audio::privGetInstance();
    assert(pAudio != nullptr);

    delete Audio::posInstance;
    Audio::posInstance = nullptr;
}

void Audio::Create()
{

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if(posInstance == nullptr)
    {
        posInstance = new Audio();
    }

}

void Audio::WaveTableDump()
{
    Audio *pAudio = Audio::privGetInstance();
    pAudio->poWaveTable->Dump();
}

void Audio::Load(Blocking , Wave::ID wave_id, const char *const pWaveName)
{
    Audio *pAudio = Audio::privGetInstance();

    //Is Wave in the WaveTable?
    WaveTable *pWaveTable = pAudio->poWaveTable;
    assert(pWaveTable);
    WaveTable::Table *pTable = pWaveTable->Find(wave_id);
    
    // Not there...
    if(pTable == nullptr)
    {
        pWaveTable->Register(wave_id, Wave::Status::PENDING);

        assert(pWaveName);

        // Setup the Callback
        bool DoneFlag = false;
        I_File_CB *pFileCB = new I_File_CB(DoneFlag);

        Load_WaveCmd *pCmd = new Load_WaveCmd(wave_id, pWaveName, pFileCB);
        assert(pCmd);

        SndMan::Send(pCmd);


        // Block and spin until Callback
        while(!DoneFlag);

    }
    else
    {
        // its Ready or Pending...
        if(pTable->status == Wave::Status::READY || pTable->status == Wave::Status::PENDING)
        {
            // Do nothing... 
        }
        else
        {
            // bad...
            assert(false);
        }
    }

}

Audio *Audio::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

WaveTable * Audio:: GetWaveTable()
{
    Audio *pAudio = Audio::privGetInstance();
    return pAudio->poWaveTable;
}

// --- End of File ---