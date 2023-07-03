//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"
#include "AudioThread.h"
#include "TestThread.h"
#include "CircularData.h"
#include "InputMan.h"
#include "Panning.h"

// Global varables --- todo remove

// Game to Audio: 
CircularData *pAudioIn;
CircularData *pGameIn;

bool QuitFlag = false;

using namespace ThreadFramework;

//-----------------------------------------------------------------------------
//  Game::Game()
//		Game Engine Constructor
//-----------------------------------------------------------------------------
Game::Game(const char *const pWindowName, const int Width, const int Height)
	:Engine(pWindowName, Width, Height)
{
	assert(pWindowName);
	this->globalTimer.tic();
	this->intervalTimer.tic();
}

//-----------------------------------------------------------------------------
//  Game::~Game()
//		Game Engine destructor
//-----------------------------------------------------------------------------
Game::~Game()
{
}

//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{

}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	// Load up the demo application
	GameApp::LoadDemo(this->info.windowWidth, this->info.windowHeight);

	InputMan::Create();

	//---------------------------------------------------------------------------------------------------------
	// Launch a Thread
	//---------------------------------------------------------------------------------------------------------

	// Create an Audio thread...
	pAudioIn = new CircularData();
	assert(pAudioIn);

	pGameIn = new CircularData();
	assert(pGameIn);

	std::thread  t_Audio(AudioMain, std::ref(QuitFlag), pAudioIn, pGameIn);
	Debug::SetName(t_Audio, "--Audio--");
	t_Audio.detach();

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

int count = 0;
int data = 0;
void Game::Update(float)
{
	static bool PanningStart = false;
	// Update the demo application
	GameApp::UpdateDemo();


	// Read Quit Key
	Keyboard *key = InputMan::GetKeyboard();
	if(key->GetKeyState(Keyboard::KEY_Q))
	{
		QuitFlag = true;
	}

	
	// Send data...
	count++;
	if(count == 120)
	{
		count = 0;
		data += 0x11;

		bool status = pAudioIn->PushBack(data);
		assert(status == true);
	}

	// Receive data...
	int val;
	if(pGameIn->PopFront(val) == true)
	{
		Debug::out("receive: %x <--- \n", val);
	}

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
	delete pAudioIn;
	delete pGameIn;

	InputMan::Destroy();
	
}

//------------------------------------------------------------------
// Game::ClearBufferFunc()
// Allows user to change the way the clear buffer function works
//------------------------------------------------------------------
void Game::ClearBufferFunc()
{
	const GLfloat grey[] = { 0.9f, 0.8f, 0.8f, 1.0f };
	constexpr GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}

//---  End of File ---
