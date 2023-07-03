//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

using namespace ThreadFramework;

void ThreadA()
{
	SimpleBanner b;

	Debug::out("sample 3\n");
	Debug::out("sample 4\n");
}

class Functor : public BannerBase
{
public:
	Functor(const char *const pName)
		: BannerBase(pName)
	{

	}

	void operator() ()
	{
		START_BANNER

		Debug::out("sample 9 \n");
		Debug::out("sample 10 \n");
	}
};

int main()
{
	START_BANNER_MAIN("--Main--");

	Debug::out("sample 1 \n");
	Debug::out("sample 2 \n");

	std::thread tA = std::thread(ThreadA);
	Debug::SetName(tA, "--A--");

	tA.join();

	Functor func("--B--");
	std::thread tB = std::thread(func);	
	
	tB.join();

	Debug::out("sample 5 \n");
	Debug::out("sample 6 \n");
}

// ---  End of File ---------------
