//-----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "AzulCore.h"
#include "HandleMan.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"
#include "AudioThread.h"
#include "TestThreadOne.h"
#include "TestThreadTwo.h"
#include "CircularData.h"
#include "InputMan.h"
#include "SndMan.h"
#include "Snd.h"
#include "Load_WaveCmd.h"
#include "PlaylistMan.h"
#include "PlaylistJukeBox.h"
#include "WaveMan.h"
#include "VoiceMan.h"
#include "AudioEngine.h"
#include "PlaylistData_One.h"
#include "PlaylistData_Stitched.h"
#include "Audio.h"

// Global varables --- todo remove

// Needs to be an atomic
std::atomic_bool QuitFlag = false;
std::atomic_bool AudioReadyFlag = false;

int DemoOne = 0;
int DemoTwo = 0;

using namespace ThreadFramework;
using namespace std::chrono_literals;


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

        HandleMan::Create();
	SndMan::Create();
        InputMan::Create();
	Audio::Create();
        
	//--------------------------------------------------------------------
	// Launch a Thread
	//--------------------------------------------------------------------

	// Spawn Audio thread
	std::thread  t_Audio(AudioMain, std::ref(QuitFlag), std::ref(AudioReadyFlag));
	Debug::SetName(t_Audio, "--Audio--");
	t_Audio.detach();

	// Wait until audio thread is ready.
	while (!AudioReadyFlag);


	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Intro, "Intro_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::A, "A_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::AtoB, "AtoB_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::B, "B_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::BtoC, "BtoC_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::C, "C_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::CtoA, "CtoA_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::End, "End_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Fiddle, "Fiddle_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Bassoon, "Bassoon_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::Oboe2_mono, "Oboe2_mono.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongA, "SongA.wav");
	Audio::Load(Audio::Blocking::LOAD, Wave::ID::SongB, "SongB.wav");

	WaveTable *pWaveTable = Audio::GetWaveTable();
	Trace::out("\n");
	pWaveTable->Dump();
	Trace::out("\n");


	// Create the Playlist

	PlaylistJukeBox::Load(Snd::ID::Fiddle, new PlaylistData_One(Wave::ID::Fiddle));
	PlaylistJukeBox::Load(Snd::ID::Bassoon, new PlaylistData_One(Wave::ID::Bassoon));
	PlaylistJukeBox::Load(Snd::ID::Oboe2_mono, new PlaylistData_One(Wave::ID::Oboe2_mono));
	PlaylistJukeBox::Load(Snd::ID::SongA, new PlaylistData_One(Wave::ID::SongA));
	PlaylistJukeBox::Load(Snd::ID::SongB, new PlaylistData_One(Wave::ID::SongB));
	PlaylistJukeBox::Load(Snd::ID::Seinfeld, new PlaylistData_Stitched(Wave::ID::Intro, Wave::ID::A, Wave::ID::AtoB, Wave::ID::B, Wave::ID::BtoC, Wave::ID::C, Wave::ID::CtoA, Wave::ID::End));
	//PlaylistJukeBox::Load(Snd::ID::Seinfeld, new PlaylistData_Stitched(Wave::ID::Intro, Wave::ID::A, Wave::ID::AtoB, Wave::ID::B));


	// Wait until its loaded...
	//      Hack... future callbacks.
	/*Playlist* pSongB_play = nullptr;

	int count = 0;
	while(pSongB_play == nullptr)
	{
		pSongB_play = PlaylistJukeBox::Find(Snd::ID::Seinfeld);
		Debug::out("Playlist loading: %d ms \n", 200*count++);
		std::this_thread::sleep_for(200ms);
	}*/


	//Snd *pSndA = SndMan::Add(Snd::ID::Seinfeld);
	// *pSndB = SndMan::Add(Snd::ID::Fiddle);
	//Snd *pSndC = SndMan::Add(Snd::ID::Fiddle);
	//Snd *pSndD = SndMan::Add(Snd::ID::Fiddle);

	//Handle::Status status;
	//status = pSndA->Play();

	/*std::this_thread::sleep_for(0.75s);
	status = pSndB->Play();

	std::this_thread::sleep_for(0.75s);
	status = pSndC->Play();

	std::this_thread::sleep_for(0.75s);
	status = pSndD->Play();*/

}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------

void Game::Update(float)
{
	// Update the demo application
	GameApp::UpdateDemo();
	SndMan::Update();

	// Read Quit Key
	Keyboard *key = InputMan::GetKeyboard();
	if(key->GetKeyState(Keyboard::KEY_Q))
	{
		QuitFlag = true;
	}

	if (key->GetKeyState(Keyboard::KEY_1))
	{
		if (DemoOne == 0)
		{
			// Test thread
			std::thread t1(TestThreadOneMain);
			Debug::SetName(t1, "--Demo One--");
			t1.detach();

			DemoOne++;
		}
	}

	if (key->GetKeyState(Keyboard::KEY_2))
	{
		if (DemoTwo == 0)
		{
			// Test thread
			std::thread t2(TestThreadTwoMain);
			Debug::SetName(t2, "--Demo Two--");
			t2.detach();

			DemoTwo++;
			
		}
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
	InputMan::Destroy();
	SndMan::Destroy();
	HandleMan::Destroy();

	Audio::Destroy();
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
