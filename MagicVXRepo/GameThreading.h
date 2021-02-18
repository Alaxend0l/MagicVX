#include <thread>
#include "GameManipulator.h"

using namespace std;

class GameThreading
{
public:
	GameManipulator manipulator;
	thread game;

    GameThreading();

	void LaunchThread(bool);
	void LaunchNormal();
	void LaunchCustom();

	void CloseThread();

	
	
};

