//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "TestThread.h"

using namespace ThreadFramework;

void Test_Main(CircularData *pIn_TestQueue, CircularData *pOut_TestQueue, bool &QuitFlag)
{
	SimpleBanner b;

	int val;

	while(!QuitFlag)
	{
		if(pIn_TestQueue->PopFront(val) == true)
	{
			Debug::out("<--- Test(): %x \n", val);

			// echo back the complement
			unsigned int data = (unsigned int)(~val & 0xff);

			Debug::out("Test() ---> send: %x \n", data);
			bool status = pOut_TestQueue->PushBack((int)data);
			assert(status);
	}
	}


}

//---  End of File ---
