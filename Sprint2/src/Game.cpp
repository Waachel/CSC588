//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ 
	// Game Window Device setup
	this->setWindowName("CSC 588 Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor( 0.9f, 0.8f, 0.8f, 1.0f );
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	glDisable(GL_DEBUG_OUTPUT);

	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	// Update the demo application
	GameApp::UpdateDemo();

	// Input Testing
	//KeyboardTest();
	//MouseTest();

}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	
}


//---  End of File ---
