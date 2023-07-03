//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

using namespace ThreadFramework;
#include <Xaudio2.h>

#ifdef _XBOX //Big-Endian
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX //Little-Endian
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

//data
HRESULT hr, load, play;

//declare variable used when creating instance of XAudio2 engine
IXAudio2* pXAudio2;

//declare variable used when creating mastering voice
IXAudio2MasteringVoice* pMasterVoice;

WAVEFORMATEXTENSIBLE wfx;

//declare buffer variables
XAUDIO2_BUFFER buffer;
BYTE* pDataBuffer;

//declare variables for find chunk function
DWORD dwChunkSize;
DWORD dwChunkPosition;
DWORD filetype;

//declare variable for Source Voice
IXAudio2SourceVoice* pSourceVoice;


//load data
//find chunk in RIFF file - helper function
HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkDataPosition)
{
    hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());

    DWORD dwChunkType;
    DWORD dwChunkDataSize;
    DWORD dwRIFFDataSize = 0;
    DWORD dwFileType;
    DWORD bytesRead = 0;
    DWORD dwOffset = 0;

    while (hr == S_OK)
    {
        DWORD dwRead;
        if (0 == ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        if (0 == ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
            hr = HRESULT_FROM_WIN32(GetLastError());

        switch (dwChunkType)
        {
        case fourccRIFF:
            dwRIFFDataSize = dwChunkDataSize;
            dwChunkDataSize = 4;
            if (0 == ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
                hr = HRESULT_FROM_WIN32(GetLastError());
            break;

        default:
            if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
                return HRESULT_FROM_WIN32(GetLastError());
        }

        dwOffset += sizeof(DWORD) * 2;

        if (dwChunkType == fourcc)
        {
            dwChunkSize = dwChunkDataSize;
            dwChunkDataPosition = dwOffset;
            return S_OK;
        }

        dwOffset += dwChunkDataSize;

        if (bytesRead >= dwRIFFDataSize) return S_FALSE;

    }

    return S_OK;

}


//read data in chunk - helper function
HRESULT ReadChunkData(HANDLE hFile, void* bufferParam, DWORD buffersize, DWORD bufferoffset)
{
    hr = S_OK;
    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());
    DWORD dwRead;
    if (0 == ReadFile(hFile, bufferParam, buffersize, &dwRead, NULL))
        hr = HRESULT_FROM_WIN32(GetLastError());
    return hr;
}

//Initialize helper function
HRESULT Initialize()
{
    //creates the COM
    hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr))
        return hr;
    
    //creates an Xaudio2 to handler
    pXAudio2 = nullptr;
    hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
    if (FAILED(hr = XAudio2Create(&pXAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR)))
        return hr;

    //create master voice using xaudio2
    pMasterVoice = nullptr;
    hr = pXAudio2->CreateMasteringVoice(&pMasterVoice);
    if (FAILED(hr = pXAudio2->CreateMasteringVoice(&pMasterVoice)))
        return hr;

    return hr;
}

//Fill XAudio2 container with data from RIFF chunks
HRESULT PopulateWithChunks(LPCSTR wavFile)
{
    wfx = { { 0 } };
    buffer = { { 0 } };

    // Open the file
    HANDLE hFile1 = CreateFile(wavFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

    if (INVALID_HANDLE_VALUE == hFile1)
        return HRESULT_FROM_WIN32(GetLastError());

    if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile1, 0, NULL, FILE_BEGIN))
        return HRESULT_FROM_WIN32(GetLastError());


    //check the file type, should be fourccWAVE or 'XWMA'
    FindChunk(hFile1, fourccRIFF, dwChunkPosition);
    
    ReadChunkData(hFile1, &filetype, sizeof(DWORD), dwChunkPosition);
    if (filetype != fourccWAVE)
        return S_FALSE;

    //read format
    FindChunk(hFile1, fourccFMT, dwChunkPosition);
    ReadChunkData(hFile1, &wfx, dwChunkSize, dwChunkPosition);

    //read data
    //fill out the audio data buffer with the contents of the fourccDATA chunk
    FindChunk(hFile1, fourccDATA, dwChunkPosition);
    pDataBuffer = new BYTE[dwChunkSize];
    ReadChunkData(hFile1, pDataBuffer, dwChunkSize, dwChunkPosition);

    //populate and prepare play structure
    buffer.AudioBytes = dwChunkSize;  //size of the audio buffer in bytes
    buffer.pAudioData = pDataBuffer;  //buffer containing audio data
    buffer.Flags = XAUDIO2_END_OF_STREAM; // tell the source voice not to expect any data after this buffer

    return hr;
}

HRESULT PlaySound()
{
    //check CreateSourceVoice
    if (FAILED(hr = pXAudio2->CreateSourceVoice(&pSourceVoice, (WAVEFORMATEX*)&wfx))) return hr;

    //Submit buffer to pSourceVoice
    if (FAILED(hr = pSourceVoice->SubmitSourceBuffer(&buffer)))
        return hr;

    //set volume
    pSourceVoice->SetVolume(0.3f);

    //play audio
    if (FAILED(hr = pSourceVoice->Start(0)))
        return hr;

    //hacky - should change but for now it keeps audio going
    //plays audio for 30 seconds
    Sleep(20000);

    //stop audio
    pSourceVoice->Stop();
    return hr;
}

//unallocate - delete
void Delete(IXAudio2SourceVoice* pSourceVoiceParam)
{
    //delete Buffer - delete new
    delete[] pDataBuffer;

    //delete what was created
    pSourceVoiceParam->DestroyVoice();

    pMasterVoice->DestroyVoice();

    pXAudio2->Release();

    CoUninitialize();
}


int main()
{
    
    START_BANNER_MAIN("--Main--");

    //Initialize XAudio2
    hr = Initialize();
    
    //Load first wav file
    load = PopulateWithChunks("LRMonoPhase4.wav");

    //Call function to play sound
    play = PlaySound();

    //Unallocate and Uninitialize
    Delete(pSourceVoice);
   
    //Initialize XAudio2
    hr = Initialize();

    //Load second wav file
    load = PopulateWithChunks("audio-stereo-32bit-48KHz.wav");

    //Call function to play sound
    play = PlaySound();

    //Unallocate and Uninitialize
    Delete(pSourceVoice);



}

// ---  End of File ---------------
