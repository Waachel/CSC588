//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "Game.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{          
	// Run unit tests... future testing
	Test::RunTests();

	START_BANNER_MAIN("--Main--");

	// create Game
	Game *pGame = new Game();    
	assert(pGame);

	// start the game
	pGame->run();                                  

	delete pGame;

	return 0;                                       
}

//---  End of File ---
