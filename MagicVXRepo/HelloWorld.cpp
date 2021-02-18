/*
* #include "GameManipulator.h"
#include "UserSettings.h"
#include <thread>
#include <Windows.h>
#include "Global.h"

GameManipulator manipulator;

void LaunchThread(bool);
void LaunchNormal();
void LaunchCustom();

void HideConsole();
void ShowConsole();

void WatchGlobal();
void WatchGearHunt();

UserSettings userSettings;

void HelloWorld()
{
	//_wchdir(GetModuleFileName());
	if (userSettings.LoadSettings())
	{
		menuSelect = 1; //If settings file is found, set menuSelect to 1.
	}
	else
	{
		menuSelect = 2; //If settings file is not found, set menuSelect to 2.
	}
	if (DEV_InstantBoot) menuSelect = 13;
	std::thread heartbeat(WatchGlobal);
	std::thread gearhunt(WatchGearHunt);

	Sleep(10);
}

void WatchGlobal()
{
	for (;;)
	{
		/*
		* switch (menuSelect)
		{
		case 1: //Show Menu Screen
			HideConsole();
			title.show();
			settings.hide();
			title.events().unload([](const nana::arg_unload& arg)
			{
				arg.cancel = true; // this line prevents the form from closing!
				menuSelect = 5;
			});
			menuSelect = 0;
			break;
		case 2: //Show Settings Screen
			settings.show();
			title.hide();
			settings.events().unload([](const nana::arg_unload& arg)
			{
				arg.cancel = true; // this line prevents the form from closing!
				menuSelect = 1;
			});
			menuSelect = 0;
			break;
		case 3: //Launch Game in normal mode
			ShowConsole();
			//settings.show();
			title.hide();
			LaunchNormal();
			menuSelect = 0;
			break;
		case 4: //Launch Game with custom settings
			ShowConsole();
			//settings.show();
			custom.hide();
			LaunchCustom();
			menuSelect = 0;
			break;
		case 5: //Quit
			title.hide();
			ShowConsole();
			HideConsole();
			_Exit(EXIT_SUCCESS);
			break;
		case 6: //Exit settings screen while saving settings.
			userSettings.LoadSettings();
			title.show();
			settings.hide();
			menuSelect = 0;
			break;
		case 7: //Enter custom launch menu.
			custom.show();
			title.hide();
			custom.events().unload([](const nana::arg_unload& arg)
			{
				arg.cancel = true; // this line prevents the form from closing!
				menuSelect = 8;
			});
			menuSelect = 0;
			break;
		case 8: //Exit custom launch menu and return to title
			title.show();
			custom.hide();
			menuSelect = 0;
			break;
		case 9: //Launch Gear Hunt Menu
			gearHuntScreen.show();
			title.hide();
			gearHuntScreen.events().unload([](const nana::arg_unload& arg)
				{
					arg.cancel = true; // this line prevents the form from closing!
					menuSelect = 10;
				});
			menuSelect = 0;
			break;
		case 10: //Exit Gear Hunt Menu and return to title
			title.show();
			gearHuntScreen.hide();
			menuSelect = 0;
			break;
		case 11: //Start playing made gear hunt.
			ShowConsole();
			gearHuntScreen.hide();
			LaunchCustom();
			menuSelect = 0;
			break;
		case 12: //Create a gear hunt!
			gearHuntStart = true;
			ShowConsole();
			gearHuntScreen.hide();
			LaunchCustom();
			menuSelect = 0;
			break;
		case 13: //Instantly boot into gameplay, dev feature
			ShowConsole();
			LaunchCustom();
			menuSelect = 0;
			break;
		}
		

		
		
		
Sleep(10);
	}
}

void WatchGearHunt()
{
	for (;;)
	{
		if (gearHuntStart)
		{
			//gearHuntMakeScreen.show();
			gearHuntMakeWorking = true;
			gearHuntStart = false;
		}
		if (gearHuntMakeWorking)
		{

		}
		Sleep(10);
	}
}

void LaunchThread(bool custom)
{
	if (!custom) std::thread game(LaunchNormal);
	else std::thread game(LaunchCustom);
}

void LaunchNormal()
{
	manipulator = GameManipulator(false);
}

void LaunchCustom()
{
	manipulator = GameManipulator(true);
}

void HideConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

void ShowConsole()
{
	::ShowWindow(::GetConsoleWindow(), SW_SHOW);
}

bool IsConsoleVisible()
{
	return ::IsWindowVisible(::GetConsoleWindow()) != FALSE;
}
*/
