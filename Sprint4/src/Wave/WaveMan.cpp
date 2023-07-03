//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WaveMan.h"
#include "Load_WaveCmd.h"
#include "SndMan.h"
#include "WaveTable.h"
#include "Audio.h"
#include "FileLoadCmd.h"

using namespace ThreadFramework;

WaveMan *WaveMan::posInstance = nullptr;

//----------------------------------------------------------------------
// Constructor
//----------------------------------------------------------------------
WaveMan::WaveMan(int reserveNum, int reserveGrow)
    : ManBase(new DLinkMan(), new DLinkMan(), reserveNum, reserveGrow)
{
    // Preload the reserve
    this->proFillReservedPool(reserveNum);

    // initialize derived data here
    this->poNodeCompare = new Wave();
}

WaveMan::~WaveMan()
{
   // Debug::out("~WaveMan()\n");
    delete this->poNodeCompare;
    this->poNodeCompare = nullptr;

    // iterate through the list and delete
    Iterator *pIt = this->baseGetActiveIterator();

    DLink *pNode = pIt->First();

    // Walk through the nodes
    while(!pIt->IsDone())
    {
        Wave *pDeleteMe = (Wave *) pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }

    pIt = this->baseGetReserveIterator();

    pNode = pIt->First();

    // Walk through the nodes
    while(!pIt->IsDone())
    {
        Wave *pDeleteMe = (Wave *) pIt->Curr();
        pNode = pIt->Next();
        delete pDeleteMe;
    }
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void WaveMan::Create(int reserveNum, int reserveGrow)
{
    // make sure values are ressonable 
    assert(reserveNum > 0);
    assert(reserveGrow > 0);

    // initialize the singleton here
    assert(posInstance == nullptr);

    // Do the initialization
    if(posInstance == nullptr)
    {
        posInstance = new WaveMan(reserveNum, reserveGrow);
    }

}

void WaveMan::Destroy()
{
    WaveMan *pMan = WaveMan::privGetInstance();
    assert(pMan != nullptr);

    delete WaveMan::posInstance;
    WaveMan::posInstance = nullptr;
}

Wave * WaveMan::Add(Wave::ID wave_id, const char *const pWaveName, I_File_CB *pIFileCB)
{
    WaveMan *pMan = WaveMan::privGetInstance();

    Wave *pNode = (Wave *) pMan->baseAddToFront();
    assert(pNode != nullptr);

    // Initialize the data    
    assert(pWaveName);
    assert(pIFileCB);
    pNode->SetPending(pWaveName, wave_id, pIFileCB);

    Debug::out("WaveMan::Add() create FileLoadCmd() \n");
    FileLoadCmd *pCmd = new FileLoadCmd(wave_id, pWaveName, pNode);
    assert(pCmd);

    bool status = SndMan::SendFile(pCmd);
    assert(status);


    return pNode;
}

Wave *WaveMan::Find(Wave::ID _id)
{
    WaveMan *pMan = WaveMan::privGetInstance();
    assert(pMan != nullptr);

    // Compare functions only compares two Nodes

    // So:  Use the Compare Node - as a reference
    //      use in the Compare() function
    pMan->poNodeCompare->id = _id;

    Wave *pData = (Wave *) pMan->baseFind(pMan->poNodeCompare);
    return pData;
}

void WaveMan::Remove(Wave *pNode)
{
    assert(pNode != nullptr);

    WaveMan *pMan = WaveMan::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseRemove(pNode);
}

void WaveMan::Dump()
{
    WaveMan *pMan = WaveMan::privGetInstance();
    assert(pMan != nullptr);

    pMan->baseDump();
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
WaveMan *WaveMan::privGetInstance()
{
    // Safety - this forces users to call Create() first before using class
    assert(posInstance != nullptr);

    return posInstance;
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink *WaveMan::derivedCreateNode()
{
    DLink *pNodeBase = new Wave();
    assert(pNodeBase != nullptr);

    return pNodeBase;
}
