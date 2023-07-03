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
#include "SndManager.h"
#include "Snd.h"

// Global varables --- todo remove

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

        //replaced by Snd Manager
	/*// Create an Audio thread...
	pAudioIn = new CircularData();
	assert(pAudioIn);

	pGameIn = new CircularData();
	assert(pGameIn);

	std::thread  t_Audio(AudioMain, std::ref(QuitFlag), pAudioIn, pGameIn);
	Debug::SetName(t_Audio, "--Audio--");
	t_Audio.detach();*/

	// Create the snd system
	SndManager::Create();

	std::thread  t_Audio(AudioMain, std::ref(QuitFlag), SndManager::GetInBuff(), SndManager::GetOutBuff());
	Debug::SetName(t_Audio, "--Audio--");
	Debug::out("--->Audio Thread Created\n");
	t_Audio.detach();

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------


void Game::Update(float)
{
	static bool PanningStart = false;
	// Update the demo application
	GameApp::UpdateDemo();
	// Read from Snd manager
	SndManager::Update();

	// Read Quit Key
	Keyboard *key = InputMan::GetKeyboard();
	if(key->GetKeyState(Keyboard::KEY_Q))
	{
		QuitFlag = true;
	}

	if (key->GetKeyState(Keyboard::KEY_L))
	{
		Snd SndA = Snd(SndId::GUNSHOT_ID);

		// Call the Snd
		assert(SndA.Play() == Handle::Status::SUCCESS);
	}


	// Send data...
	static int count = 0;
	static unsigned int data = 0;
	count++;

	if(count == 10)
	{
		//float Volume = 0.5f;
		//float Pitch = 1.0f;
		//float Panning = 0.0f;
		Snd SndA = Snd(SndId::STRINGS_ID);
		assert(SndA.Play() == Handle::Status::SUCCESS);
	}

	if (count == 100)
	{
		Snd SndA = Snd(SndId::CHANGE_VOLUME_UP_ID);
		Snd SndB = Snd(SndId::CHANGE_PANNING_LEFT_ID);
		Snd SndC = Snd(SndId::CHANGE_PITCH_HIGH_ID);
		// Call the Snd
		assert(SndA.Volume() == Handle::Status::SUCCESS);
		assert(SndB.Panning() == Handle::Status::SUCCESS);
		assert(SndC.Pitch() == Handle::Status::SUCCESS);
	}

	if(count == 300)
	{
		//float Volume = 1.5f;
		//float Pitch = 1024.0f/500.0f;
		//float Panning = -1.0f;
		Snd SndA = Snd(SndId::BASSOON_ID);

		// Call the Snd
		assert(SndA.Play() == Handle::Status::SUCCESS);

	}

	if (count == 400)
	{
		Snd SndA = Snd(SndId::CHANGE_VOLUME_DOWN_ID);
		Snd SndB = Snd(SndId::CHANGE_PANNING_RIGHT_ID);
		Snd SndC = Snd(SndId::CHANGE_PITCH_LOW_ID);
		// Call the Snd
		assert(SndA.Volume() == Handle::Status::SUCCESS);
		assert(SndB.Panning() == Handle::Status::SUCCESS);
		assert(SndC.Pitch() == Handle::Status::SUCCESS);
	}

	if (count == 500)
	{
		//float Volume = 0.1f;
		//float Pitch = 500.0f/1024.0f;
		//float Panning = 1.0f;
		Snd SndA = Snd(SndId::FIDDLE_ID);

		// Call the Snd
		assert(SndA.Play() == Handle::Status::SUCCESS);

	}


	if (count == 600)
	{
		//float Volume = 0.1f;
		//float Pitch = 500.0f/1024.0f;
		//float Panning = 1.0f;
		Snd SndA = Snd(SndId::ELEPHANT_ID);

		// Call the Snd
		assert(SndA.Play() == Handle::Status::SUCCESS);
	}

	if (count == 1000)
	{
		//float Volume = 0.1f;
		//float Pitch = 500.0f/1024.0f;
		//float Panning = 1.0f;
		Snd SndA = Snd(SndId::STOP_ID);

		// Call the Snd
		assert(SndA.Stop() == Handle::Status::SUCCESS);
	}

	//overflow
	if (key->GetKeyState(Keyboard::KEY_O))
	{
		//float Volume = 0.1f;
		//float Pitch = 500.0f/1024.0f;
		//float Panning = 1.0f;
		Snd SndA = Snd(SndId::ELEPHANT_ID);

		// Call the Snd
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
		assert(SndA.Play() == Handle::Status::SUCCESS);
		assert(SndA.Stop() == Handle::Status::SUCCESS);
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
	//delete pAudioIn;
	//delete pGameIn;

        SndManager::Destroy();
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
