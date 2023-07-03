//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_MAN_H
#define SND_MAN_H 

#include "ManBase.h"
#include "DLinkMan.h"
#include "Snd.h"
#include "ASnd.h"
#include "CircularData.h"
#include "Command.h"

class SndMan : public ManBase
{

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
private:
    SndMan(int reserveNum = 3, int reserveGrow = 1);
    ~SndMan();

    //----------------------------------------------------------------------
    // Static Methods
    //----------------------------------------------------------------------
public:
    static void Create(int reserveNum = 3, int reserveGrow = 1);
    static void Destroy();

    static Snd *Add(Snd::ID snd_id);
    static Snd *Find(Snd::ID snd_id);

    static void Remove(Snd *pNode);
    static void Dump();

    static void Update();
    static bool Send(Command *pCmd);
    static bool SendFile(Command *pCmd);
    
    static CircularData *GetGameInQueue();
    static CircularData *GetAudioInQueue();
    static CircularData *GetFileInQueue();

    //----------------------------------------------------------------------
    // Private methods
    //----------------------------------------------------------------------
private:
    static SndMan *privGetInstance();

    //----------------------------------------------------------------------
    // Override Abstract methods
    //----------------------------------------------------------------------
protected:
    DLink *derivedCreateNode() override;


    //----------------------------------------------------------------------
    // Data: unique data for this manager 
    //----------------------------------------------------------------------
private:
    Snd *poNodeCompare;
    static SndMan *posInstance;

    CircularData *poAudioIn; // ---> to Audio
    CircularData *poGameIn;  // ---> to Game
    CircularData *poFileIn;  // ---> to File
};


#endif
