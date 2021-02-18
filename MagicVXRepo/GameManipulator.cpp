#pragma once
#include "GameManipulator.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <windows.h>
#include <shellapi.h>
#include <atlstr.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <thread>
#include <stdio.h>      /* printf, fopen */
#include <stdlib.h>     /* exit, EXIT_FAILURE */

HANDLE ProcessHandle;
bool DevMode = true;
bool Sandbox = false;
bool Mouse = true;

bool CustomLaunch = false;
bool GearHuntLaunch = false;
bool MakeGearHuntLaunch = false;

bool MakeGearHunt_UpdateCount = false;

bool CL_Disclaimer = false;
bool CL_LoadStart = false;
bool CL_LoadWorldData = false;
bool CL_LoadObjectData = false;
bool CL_GamePlayStart = false;

bool SL_Disclaimer = false;

bool JustWarped = false;
int JustWarpedCounter = 0;
float JustWarpedFloatX = 0;
float JustWarpedFloatY = 0;
float JustWarpedFloatZ = 0;
float JustWarpedFloatW = 0;
GamePlayer player[8];


std::vector<int> GH_ObjectTypes;

int GHRedGearAddress;
int GH_TotalGears;
int GH_LastCount;

bool GH_Timer_Started = false;
int GH_TotalTimeMs = 0;
int GH_StartingTimeValue = 0;

int KeyPress_1 = 0;

int IDEA_ScoreCountUp = 0;

bool startsFalse = 0;

std::thread hb;

//Test values to test function calling
char playerCount;

GameManipulator::GameManipulator()
{

}

void GameManipulator::BootGame(bool custom)
{
    ResetValues();
    enableSeDebug();
    mainSettings.LoadSettings();
    CustomLaunch = custom;
    if (CustomLaunch)
    {
        if (customLaunchSettings.Sandbox_Enabled) Sandbox = true;
    }
    GameLaunch();
    Heartbeat();
}

void GameManipulator::ResetValues()
{
    CL_Disclaimer = false;
    CL_LoadStart = false;
    CL_LoadWorldData = false;
    CL_LoadObjectData = false;
    CL_GamePlayStart = false;

    SL_Disclaimer = false;
}
void GameManipulator::GameLaunch()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CString path = mainSettings.gameDirectory.data();
    CString directory = getPathName(mainSettings.gameDirectory).data();
    CString args = ((std::string)"-w").data();
    CString open = "open";

    LPSTR pszText;
    pszText = args.GetBuffer(args.GetLength());

    CreateProcessA(
        path,   // No module name (use command line)
        pszText,        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        0,              // No creation flags
        NULL,           // Use parent's environment block
        directory,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure
        &pi);           // Pointer to PROCESS_INFORMATION structure

    ProcessHandle = pi.hProcess;
    ProcessID = GetProcessId(ProcessHandle);
    FC = FunctionCaller(ProcessHandle, mainSettings.GetDLLPath());
    GB.Init(ProcessHandle, 0x68DF20);
    
}

void GameManipulator::Heartbeat()
{
	//The game is booting! Prepare everything below.
	AddToLog("Booting!");

	//First, let's skip the config window.
	FC.DisableFunction(CreateConfigWindow); //Starts OpenConfigMenu's function with a 'ret', effectively stopping execution.


	//The below code stops Heartbeat until all variables are loaded in.
	int holdUp = 0; while (holdUp != 1) holdUp = ReadInt(0x0049D7DC);

	//Next, let's load in all the settings the user added in.
	WriteInt(0x0068DEE0, mainSettings.Resolution[0]);
	WriteInt(0x0068DEE4, mainSettings.Resolution[1]);
	WriteInt(0x0068DEF8, mainSettings.AntiAliasing);
	WriteInt(0x0068DEE8, mainSettings.ColorDepth*16 + 16);

	WriteByte(0x0068DEFC, mainSettings.TextureFiltering);
	WriteByte(0x0068DF04, (!mainSettings.ScreenMode));
	WriteByte(0x0068DF05, (!mainSettings.VehicleParticles));
	WriteByte(0x0068DEF4, (!mainSettings.WorldParticles));
	WriteByte(0x0068DF00, (!mainSettings.DrawDistance));
	WriteByte(0x0068DEEC, (!mainSettings.GeometryDetail));
	WriteByte(0x0068DF06, (mainSettings.DisableMovies));
	WriteByte(0x0068DF04, (!mainSettings.ScreenMode));

	for (;;)
	{
		if (WaitForSingleObject(ProcessHandle, 0) != WAIT_TIMEOUT)
		{
			return;
		}
		else
		{
			GB.UpdateAll();
			if (CustomLaunch)
			{
				if (!CL_Disclaimer) CustomLaunch_Disclaimer();
				else if (!CL_LoadStart) CustomLaunch_LoadStart();
				else if (!CL_LoadWorldData) CustomLaunch_LoadWorldData();
				else if (!CL_LoadObjectData) CustomLaunch_LoadObjectData();
				else if (!CL_GamePlayStart) CustomLaunch_GamePlayStart();
				else CustomLaunch_GamePlayHeartbeat();
			}
			else
			{
				if (!SL_Disclaimer) StandardLaunch_Disclaimer();
			}
		}
		Sleep(10);
	}
}

void GameManipulator::PatchMouse()
{
	//Let's patch out all the mouse-related functions in the game.

}

void GameManipulator::CustomLaunch_Disclaimer()
{
	//A lot of the game's base values are loaded at this point, so they can be modified.
	if (ReadFloat(0x005E7678, {}) != 0)
	{
        FC.InitPipe();
        if (Mouse) FC.PatchMouse();
        if (customLaunchSettings.Sandbox_EnableAllCheats) EnableCheats();

		WriteByte(0x0065E332, {}, 0x1); //Set game to demo mode.

		if (DevMode) AddToLog("Mode: " + std::to_string(customLaunchSettings.Mode));
		switch (customLaunchSettings.Mode) //Change the Prog Script to load the appropriate game mode.
		{
		case 0: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x0 })); break; //Changes Demo Prog Script to Mission
		case 1: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x4 })); break; //Changes Demo Prog Script to Challenge
		case 2: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x8 })); break; //Changes Demo Prog Script to Drag Race
		case 3: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0xC })); break; //Changes Demo Prog Script to Battle
		case 4: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x10 })); break; //Changes Demo Prog Script to Joyride
		case 5: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0xC })); break; //Changes Demo Prog Script to Battle
		case 6: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x10 })); break; //Changes Demo Prog Script to Joyride
		case 7: WriteInt(0x0048D7C0, { 0x24, 0x8 }, ReadInt(0x0048D7C0, { 0x38, 0x10 })); break; //Changes Demo Prog Script to Joyride
		}
		WriteInt(0x0048D920, customLaunchSettings.Act);
		WriteInt(0x0064D3EC, customLaunchSettings.Car);
		WriteInt(0x0065E2B0, customLaunchSettings.Weapon);
		WriteInt(0x0064D160, customLaunchSettings.Difficulty);

		//Below is more specific setup for each game mode.
		switch (customLaunchSettings.Mode)
		{
		case 0:
		case 1:
			WriteByte(0x0065E32C, customLaunchSettings.ArmorRepairGlitch); //Sets whether or not gadgets respawn.
			break;
		case 2: //Drag Race
			WriteInt(0x0065E2A0, customLaunchSettings.Car); //Forces the game to use the proper vehicle.
			WriteInt(0x0065E310, 3); //Makes the game believe it's in drag race.
			WriteInt(0x0065E314, customLaunchSettings.DragRace_Time * 1000); //Sets the time limit.
			WriteInt(0x0065E320, customLaunchSettings.DragRace_Rounds); //Sets the amount of rounds to play.
			WriteInt(0x0065E324, customLaunchSettings.DragRace_RoundsOrWins); //Sets the game to either wins or rounds.
			WriteInt(0x0065E328, customLaunchSettings.DragRace_Opponents); //Sets the number of players.
			WriteInt(0x0065E32C, customLaunchSettings.DragRace_Gadgets); //Sets gadget mode.
			WriteByte(0x0065E338, customLaunchSettings.DragRace_ItemReset); //Sets whether or not items reset

			break;
		case 3: //Battle
			WriteInt(0x0065E2A0, customLaunchSettings.Car); //Forces the game to use the proper vehicle.
			WriteInt(0x0065E310, 2); //Makes the game believe it's in battle mode.
			WriteInt(0x0065E314, customLaunchSettings.Battle_Time * 1000); //Sets the time limit.
			WriteInt(0x0065E318, customLaunchSettings.Battle_Kills); //Sets the kill target.
			WriteInt(0x0065E320, customLaunchSettings.Battle_Rounds); //Sets the amount of rounds to play.
			WriteInt(0x0065E324, customLaunchSettings.Battle_RoundsOrWins); //Sets the game to either wins or rounds.
			WriteInt(0x0065E328, customLaunchSettings.Battle_Opponents); //Sets the number of players.
			WriteInt(0x0065E32C, customLaunchSettings.Battle_Gadgets); //Sets gadget mode.
			WriteByte(0x0065E330, customLaunchSettings.Battle_GadgetRespawn); //Sets whether or not gadgets respawn.
			break;
		case 5: //Score War
			WriteInt(0x0065E2A0, customLaunchSettings.Car); //Forces the game to use the proper vehicle.
			WriteInt(0x0065E310, 1); //Makes the game believe it's in score attack.
			WriteInt(0x0065E314, customLaunchSettings.Score_Time * 1000); //Sets the time limit.
			WriteInt(0x0065E31C, customLaunchSettings.Score_Target); //Sets the target score for Score War.
			WriteInt(0x0065E320, customLaunchSettings.Score_Rounds); //Sets the amount of rounds to play.
			WriteInt(0x0065E324, customLaunchSettings.Score_RoundsOrWins); //Sets the game to either wins or rounds.
			WriteInt(0x0065E328, customLaunchSettings.Score_Opponents); //Sets the number of players.
			WriteInt(0x0065E32C, customLaunchSettings.Score_Gadgets); //Sets gadget mode.
			WriteByte(0x0065E330, customLaunchSettings.Score_GadgetRespawn); //Sets whether or not gadgets respawn.

			//The below bytes patch the code to allow enemies to get points from point capsules.
			WriteByte(0x00412507, 0x90);
			WriteByte(0x00412508, 0x90);
			WriteByte(0x00412509, 0x90);
			WriteByte(0x0041250A, 0x90);
			WriteByte(0x0041250B, 0x90);
			WriteByte(0x0041250C, 0x90);
			WriteByte(0x0041250D, 0x90);
			WriteByte(0x0041250E, 0x90);
			break;
		case 6: //Play Gear Hunt
			GearHuntLaunch = true;
			break;
		case 7: //Make Gear Hunt
			MakeGearHuntLaunch = true;
			break;
		}

		WriteShort(0x00499228, (short)(mainSettings.MusicVol * 327));
		WriteShort(0x00497150, (short)(mainSettings.SFXVol * 327));

		PatchFOV(); //Don't forget about this!

		WriteFloat(0x005E7678, {}, 1); //Set the disclaimer timer to 1, so it finishes nearly instantly.
		CL_Disclaimer = true;
		if (DevMode) AddToLog("Found Disclaimer!");
		
	}
}
void GameManipulator::CustomLaunch_LoadStart() 
{
	if (ReadInt(0x0048D970, { 0xD0 }) != 12)
	{
		WriteByte(0x0065E332, {}, 0x0);
		ClearPlayers();
		CL_LoadStart = true;
		if (DevMode) AddToLog("Found Start of Load!");
		if (Sandbox) Sandbox_Init();
	}
}
void GameManipulator::CustomLaunch_LoadWorldData()
{
	if (ReadInt(0x0049DBA0, {}) != 0)
	{
		CL_LoadWorldData = true;
		if (DevMode) AddToLog("Found World Load Data!");
	}
}
void GameManipulator::CustomLaunch_LoadObjectData()
{
	if (ReadInt(0x0048D92C, {}) == 5 && ReadInt(0x0048D900, {}) > 1)
	{
		CL_LoadObjectData = true;
		if (gearHuntMakeWorking) MakeGearHunt_PrepareObjectTypes();
		else if (GearHuntLaunch) GearHuntLaunch_PrepareObjectTypes();
		if (DevMode) AddToLog("Found Object Load Data!");
	}
}
void GameManipulator::CustomLaunch_GamePlayStart()
{
	if (ReadInt(0x0048D970, { 0xD0 }) == 5)
	{
		GetAllPlayers();
		switch (customLaunchSettings.Mode)
		{
		case 5:
			WriteString(0x005F2300, { 0x480 }, " " + std::to_string(customLaunchSettings.Score_Target));
			break;
		}
		CL_GamePlayStart = true;
		if (DevMode) AddToLog("Found Gameplay Start!");
		if (customLaunchSettings.Sandbox_SimplifyPhysics) FC.DisableFunction(CarA_ComputeSuspensionForces_Aux1);
		if (customLaunchSettings.Sandbox_ZeroGravity)
		{
			WriteFloat(0x0053BB04, { 0xA0, 0x20 }, 50);
			WriteFloat(0x0053BB04, { 0xA0, 0x24 }, -0.001);
		}
		if (GearHuntLaunch)
		{
			GH_Manager.objects = GearHuntLaunch_PrepareGears();
			GearHuntLaunch_SpawnGears();
		}
		if (gearHuntMakeWorking)
		{
			WriteFloat(0x00496D80, { 0x0,0x4,0xC }, 99); //Set gear target to 99, AKA impossible to get to.
			
			GH_Manager.ZeroGravity = customLaunchSettings.U_ZeroGravity;
			GH_Manager.SimplePhysics = customLaunchSettings.U_SimplePhysics;
		}
	}
}
void GameManipulator::CustomLaunch_GamePlayHeartbeat()
{
	//Watch to see if the game restarts!
	if (ReadInt(0x0048D970, { 0xD0 }) != 5)
	{
		//If the code gets here, the player has restarted.
		CL_LoadStart = false;
		CL_LoadWorldData = false;
		CL_LoadObjectData = false;
		CL_GamePlayStart = false;
		if (DevMode) AddToLog("Player has restarted!");
	}
	else
	{
		//The player has not restarted, all clear!
		UpdatePlayers();

		if (GB.GetIfKeyState(GB_1, GBS_Pressed))
		{
            printf("Pressed the 1 button!");
            FC.CU_EnableCheats();
			//playerCount = FC.FC_PlayerManager_PlayerCount();
			MakeGearHunt_UpdateCount = false;
		}

        if (GB.GetIfKeyState(GB_2, GBS_Pressed))
        {
            //startsFalse = FC.TestInject();
            //
            
            
            MakeGearHunt_UpdateCount = false;
        }

		if (gearHuntMakeWorking) //Making Gear Hunt
		{
			WriteInt(0x0047A934, {}, 1); //Prevent other collectables from spawning

			int amountOfCollectables = GH_Manager.objects.size(); //Get the amount of gears spawned.

			if (MakeGearHunt_UpdateCount)
			{
				WriteFloat(0x0049DBA0, { 0x4C, 0x0, 0x4 }, (float)(amountOfCollectables)); //Set gears collected.
				MakeGearHunt_UpdateCount = false;
			}

			for (int i = 0; i < amountOfCollectables; i++) //Prevent gear hunt collectables from being collectable.
			{
				WriteShort(GH_Manager.objects[i].Address + 0xCC, 5000);
			}

			if (GB.GetIfKeyState(GB_1, GBS_Pressed))
			{
				if (amountOfCollectables < 95)
				{
					GearHuntObject newObject;
					newObject.PositionX = ReadFloat(0x0053BAF4, { 0x40 });
					newObject.PositionY = ReadFloat(0x0053BAF4, { 0x44 }) + 5;
					newObject.PositionZ = ReadFloat(0x0053BAF4, { 0x48 });
					newObject.ObjectType = 0;
					newObject.ObjectTypeIndex = 21;

					newObject.Address = FC.CU_SpawnGear(newObject.PositionX, newObject.PositionY, newObject.PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x8, 0x1C }));

					GH_Manager.objects.push_back(newObject);

					MakeGearHunt_UpdateCount = true;
				}
			}
			if (GB.GetIfKeyState(GB_0, GBS_Pressed))
			{
				if (amountOfCollectables > 0) MakeGearHunt_RemoveObject(amountOfCollectables);
			}
			if (GB.GetIfKeyState(GB_2, GBS_Pressed))
			{
			}

			if (gearHuntMakeDelete != -1)
			{
				if (amountOfCollectables > 0 && amountOfCollectables > gearHuntMakeDelete) MakeGearHunt_RemoveObject(gearHuntMakeDelete + 1);
				gearHuntMakeDelete = -1;
			}
			if (gearHuntMakeWarp != -1)
			{
				if (amountOfCollectables > 0 && amountOfCollectables > gearHuntMakeWarp)
				{
					WriteFloat(0x0053BAF4, { 0x00 }, 0);
					WriteFloat(0x0053BAF4, { 0x04 }, 0);
					WriteFloat(0x0053BAF4, { 0x08 }, 0);
					WriteFloat(0x0053BAF4, { 0x40 }, GH_Manager.objects[gearHuntMakeWarp].PositionX);
					WriteFloat(0x0053BAF4, { 0x44 }, GH_Manager.objects[gearHuntMakeWarp].PositionY + 8);
					WriteFloat(0x0053BAF4, { 0x48 }, GH_Manager.objects[gearHuntMakeWarp].PositionZ);
					WriteFloat(0x0053BAF4, { 0x50 }, 0);
					FC.CU_TeleportCorrection(ReadInt(0x0053BAF4));
					JustWarped = true;
					JustWarpedCounter = ReadInt(0x0048D978);
					JustWarpedFloatX = ReadInt(0x0053BAF4, { 0x50 });
					JustWarpedFloatY = ReadInt(0x0053BAF4, { 0x54 });
					JustWarpedFloatZ = ReadInt(0x0053BAF4, { 0x58 });
					JustWarpedFloatW = ReadInt(0x0053BAF4, { 0x5C });
				}
				gearHuntMakeWarp = -1;
			}

			if (gearHuntSave) MakeGearHunt_Save();
		}
		else if (GearHuntLaunch) //Playing Gear Hunt
		{
			WriteInt(0x0047A934, {}, 1); //Prevent other collectables from spawning
			int totalObjects = GH_Manager.objects.size();
			float totalCollected = 0;
			for (int i = 0; i < totalObjects; i++)
			{
				if (ReadByte(GH_Manager.objects[i].Address + 0x75, {}) != 0)
				{
					switch (GH_Manager.objects[i].ObjectTypeIndex)
					{
					case C_RedGear:
					case C_BlueGear:
					case C_WhiteGear:
					case C_YellowGear:
					case C_GreenGear:
						totalCollected++;
					}
					
				}
			}
			if (int(totalCollected) != GH_LastCount)
			{
				Sleep(50);
				WriteFloat(0x0049DBA0, { 0x4C, 0x0, 0x4 }, totalCollected); //Set gears collected.
				WriteString(0x00496D6C, { 0x4, 0x4, 0x18, 0x1C, 0x560 }, "Gears Collected: " + std::to_string(int(totalCollected)) + "/" + std::to_string(GH_TotalGears));
				WriteInt(0x005EF2CC, ReadInt(0x00496D6C, { 0x4, 0x4, 0x18, 0x1C }) + 0x560);
				GH_LastCount = int(totalCollected);
			}
			if (GH_Manager.TimeLimit != 0) GearHuntLaunch_Timer();
		}

		if (Sandbox) Sandbox_Heartbeat();
		if (JustWarped)
		{
			if (ReadInt(0x48D978) != JustWarpedCounter)
			{
				WriteFloat(0x0053BAF4, { 0x35C }, 0);
				WriteFloat(0x0053BAF4, { 0x360 }, 0);
				WriteFloat(0x0053BAF4, { 0x364 }, 0);
				WriteFloat(0x0053BAF4, { 0x50 }, 0);
				WriteFloat(0x0053BAF4, { 0x54 }, 0);
				WriteFloat(0x0053BAF4, { 0x58 }, 0);
				WriteFloat(0x0053BAF4, { 0x5C }, 1);
				JustWarped = false;
			}
		}
	}
}

void GameManipulator::StandardLaunch_Disclaimer()
{
	if (ReadFloat(0x005E7678, {}) != 0)
	{
		WriteShort(0x00499228, (short)(mainSettings.MusicVol * 327));
		WriteShort(0x00497150, (short)(mainSettings.SFXVol * 327));

		PatchFOV(); //Don't forget about this!

		SL_Disclaimer = true;
		if (DevMode) AddToLog("Found Disclaimer!");
	}
}

void GameManipulator::MakeGearHunt_PrepareObjectTypes()
{
	WriteInt(0x00496D6C, { 0x4,0x4,0x8,0x30 }, C_WhiteGear);
}
void GameManipulator::MakeGearHunt_Save()
{
	GH_Manager.TotalObjects = GH_Manager.objects.size();
	for (int i = 0; i < GH_Manager.TotalObjects; i++)
	{
		GH_Manager.objects[i] = GH_Manager.objects[i];
	}
	GH_Manager.World = customLaunchSettings.Act;
	GH_Manager.CarChoice = customLaunchSettings.Car;
	GH_Manager.WeaponChoice = customLaunchSettings.Weapon;
	GH_Manager.SaveInfo(GH_Manager.FileName);
	gearHuntSave = false;
}
void GameManipulator::MakeGearHunt_RemoveObject(int index)
{
	int _index = index - 1;
	FC.FC_Item_Release(GH_Manager.objects[_index].Address);
	GH_Manager.objects.erase(GH_Manager.objects.begin() + (_index));
	MakeGearHunt_UpdateCount = true;
}

void GameManipulator::GearHuntLaunch_PrepareObjectTypes()
{
	GH_Manager.LoadInfo(customLaunchSettings.GearHunt_File);
	std::vector<int> types;
	int j = 0;
	for (int i = 0; i < GH_Manager.TotalObjects; i++)
	{
		std::vector<int>::iterator it = std::find(types.begin(), types.end(), GH_Manager.objects[i].ObjectTypeIndex);
		if (it == types.end())
		{
			types.push_back(GH_Manager.objects[i].ObjectTypeIndex);
			GH_ObjectTypes.push_back(j);
			j++;
		}
		else
		{
			GH_ObjectTypes.push_back(std::distance(types.begin(), it));
		}

		
	}
	switch (GH_Manager.DeadWeightChoice) //Set the key to a deadweight
	{
	case 1: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_MoneyBag); break;
	case 2: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_Uranium); break;
	case 3: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_TimeBomb); break;
	case 4: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_DataDisk); break;
	case 5: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_TemporalTransmission); break;
	case 6: WriteInt(0x00496D6C, { 0x0,0x4,0x4,0x30 }, C_VolcanicGasCollector); break;
	}
	if (types.size() < 11)
	{
		for (int i = 0; i < types.size(); i++)
		{
			byte offset = (4 + (i * 4));
			WriteInt(0x00496D6C, { 0x4,0x4,offset,0x30 }, types[i]);
		}
	}
}
std::vector<GearHuntObject> GameManipulator::GearHuntLaunch_PrepareGears()
{
	std::vector<GearHuntObject> prep;

	for (int i = 0; i < GH_Manager.TotalObjects; i++)
	{
		prep.push_back(GH_Manager.objects[i]);
	}

	return prep;
}
void GameManipulator::GearHuntLaunch_SpawnGears()
{
	float totalGears = 0;
	for (int i = 0; i < GH_Manager.objects.size(); i++)
	{
		switch (GH_ObjectTypes[i])
		{
		case 0: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x4, 0x1C })); break;
		case 1: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x8, 0x1C })); break;
		case 2: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0xC, 0x1C })); break;
		case 3: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x10, 0x1C })); break;
		case 4: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x14, 0x1C })); break;
		case 5: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x18, 0x1C })); break;
		case 6: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x1C, 0x1C })); break;
		case 7: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x20, 0x1C })); break;
		case 8: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x24, 0x1C })); break;
		case 9: FC.CU_SpawnGear(GH_Manager.objects[i].PositionX, GH_Manager.objects[i].PositionY, GH_Manager.objects[i].PositionZ, ReadInt(0x00496D6C, { 0x4, 0x4, 0x28, 0x1C })); break;
		}
		GH_Manager.objects[i].Address = 0x4F9530 - (i * 0xF0);
		if (GH_Manager.objects[i].ObjectTypeIndex == C_BlueGear || GH_Manager.objects[i].ObjectTypeIndex == C_WhiteGear || GH_Manager.objects[i].ObjectTypeIndex == C_RedGear || GH_Manager.objects[i].ObjectTypeIndex == C_GreenGear || GH_Manager.objects[i].ObjectTypeIndex == C_YellowGear)
		{
			GH_Manager.objects[i].IsGear = true;
			totalGears++;
		}
	}
	if (GH_Manager.ForceDeadWeight) FC.CU_SpawnGear(ReadFloat(0x0053BAF4, { 0x40 }), ReadFloat(0x0053BAF4, { 0x44 }) + 5, ReadFloat(0x0053BAF4, { 0x48 }), ReadInt(0x00496D6C, { 0x0, 0x4, 0x4, 0x1C }));
	WriteFloat(0x00496D80, { 0x0,0x4,0xC }, totalGears); //Set gear target
	GH_TotalGears = (int)totalGears;
}
void GameManipulator::GearHuntLaunch_Timer()
{
	if (GH_Timer_Started)
	{
		std::string timerString = "";
		int timePassed = ReadInt(0x0049DBA4) - GH_StartingTimeValue;
		int timePassedCorrected = (int)((double)timePassed * (double)0.666667);
		int timeLeft = GH_TotalTimeMs - timePassedCorrected;
		int seconds = timeLeft / 1000;
		int remainingSeconds = seconds % 60;
		int minutes = (seconds - remainingSeconds) / 60;
		if (minutes < 10) timerString += "0";
		timerString += std::to_string(minutes);
		timerString += ":";
		if (remainingSeconds < 10) timerString += "0";
		timerString += std::to_string(remainingSeconds);
		WriteString(0x005EDE04, { 0x0 }, timerString);
	}
	else
	{
		if (ReadInt(0x005E7794) == 9 && ReadInt(0x0049DBA4) > 1000) // If true, player has control of their vehicle.
		{
			GH_Timer_Started = true;
			GH_StartingTimeValue = ReadInt(0x0049DBA4);
			GH_TotalTimeMs = GH_Manager.TimeLimit * 1000;
		}
	}
}

void GameManipulator::Sandbox_Init()
{
	//Basically, the dev sandbox is where I test new features I want to add to the new MagicVX.
	if (customLaunchSettings.Sandbox_EnableAllCheats) FC.CU_EnableCheats();
	if (customLaunchSettings.Sandbox_SimplifyPhysics) FC.DisableFunction(CarA_ComputeSuspensionForces_Aux1);
	if (customLaunchSettings.Sandbox_ZeroGravity)
	{
		WriteFloat(0x0053BB04, { 0xA0, 0x20 }, 50);
		WriteFloat(0x0053BB04, { 0xA0, 0x24 }, -0.001);
	}
	
	//FC.FunctionReturnZero(ThingManager_DARYL_CreateThing);

	//Then, execute the desired features.
	//Execute(ProcessHandle);
	/*
	int players = FC.PlayerManager_PlayerCount();
	AddToLog("Players = " + std::to_string(players));
	for (int i = 0; i < players; i++)
	{
		int newPlayer = FC.GetPlayerByIndex(i);
		AddToLog("Player " + std::to_string(i) + ": " + std::to_string(newPlayer));
		if (FC.Player_IsHuman(newPlayer)) AddToLog("Player is Human!"); else AddToLog("Player is AI!");
	}
	*/
	
	/*
	AddToLog("Battle Type: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x12D,0)));
	AddToLog("Battle Time Limit: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x12E,0)));
	AddToLog("Battle Kill Target: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x12F,0)));
	AddToLog("Battle Attack Target: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x130,0)));
	AddToLog("Battle Amount Of Rounds Or Wins: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x131,0)));
	AddToLog("Battle Rounds Or Wins: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x132,0)));
	AddToLog("Battle Amount Of Opponents: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x133,0)));

	AddToLog(" ");
	//AddToLog(" ");

	AddToLog("Unlimited Ammo: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x6B, 0)));
	AddToLog("Unlock All Cars: " + std::to_string(FC.FC_GameSettings_GetCodeVariable(0x6B, 1)));
	*/
	
}
void GameManipulator::Sandbox_Heartbeat()
{
	if (customLaunchSettings.Sandbox_PreventCollectablesFromSpawning) WriteInt(0x0047A934, {}, 1);
}

void GameManipulator::PatchFOV()
{
	WriteFloat(0x006D40F0, (float)mainSettings.ScreenFOV); //Set the FOV to the desired value.

	//Patch the game's code so it can't be changed anymore.
	WriteByte(0x00460B82, 0x90);
	WriteByte(0x00460B83, 0x90);
	WriteByte(0x00460B84, 0x90);
	WriteByte(0x00460B85, 0x90);
	WriteByte(0x00460B86, 0x90);
	WriteByte(0x00460B87, 0x90);
	
}

void GameManipulator::EnableCheats()
{
    WriteByte(0x0065E350, 0x01);
    WriteByte(0x0065E351, 0x01);
    WriteByte(0x0065E352, 0x01);
    WriteByte(0x0065E353, 0x01);
    WriteByte(0x0065E354, 0x01);
    WriteByte(0x0065E355, 0x01);
    WriteByte(0x0065E356, 0x01);
    WriteByte(0x0065E357, 0x02);
    WriteByte(0x0065E358, 0x01);
}

void GameManipulator::ClearPlayers()
{
	for (int i = 0; i < 8; i++)
	{
		player[i] = GamePlayer();
	}
}
void GameManipulator::GetAllPlayers()
{
	int Players = ReadInt(0x0065E328, {}) + 1;
	for (int i = 0; i < Players; i++)
	{
		if (i == 0) player[i] = GamePlayer(0x0053BAC8);
		else player[i] = GamePlayer(ReadInt(0x005423A8) + (i - 1) * 0x654);
		if (DevMode) AddToLog("Added Player " + std::to_string(i));
	}
}
void GameManipulator::UpdatePlayers()
{
	for (int i = 0; i < 8; i++)
	{
		if (player[i].Active)
		{
			//First, get all the information that matters in all modes.

			//Then, get all information that only matters in specific modes.
			switch (customLaunchSettings.Mode)
			{
			case 5:
				int CurrentKills = player[i].Kills;
				player[i].Kills = ReadInt(player[i].Address + 0x78);
				player[i].StuntPoints = ReadInt(player[i].Address + 0x7C);
				if (CurrentKills < player[i].Kills)
				{
					if (i == 0)
					{
						IDEA_ScoreCountUp += customLaunchSettings.Score_PointsPerKill * (player[i].Kills - CurrentKills);
					}
					else
					{
						player[i].StuntPoints += customLaunchSettings.Score_PointsPerKill * (player[i].Kills - CurrentKills);
						WriteInt(player[i].Address + 0x7C, player[i].StuntPoints);
					}
				}
				break;
			}

			//Just as an idea, I'm going to make a sort-of count-up effect to the score increasing after a kill.
			
			
		}
		if (i == 0)
		{
			if (IDEA_ScoreCountUp > 0)
			{
				int countFraction = IDEA_ScoreCountUp / 5 + 1;
				player[i].StuntPoints += countFraction;
				WriteInt(player[i].Address + 0x7C, player[i].StuntPoints);
				WriteString(0x005EE118, std::to_string(player[i].StuntPoints));
				WriteString(0x005FE068, std::to_string(player[i].StuntPoints));
				IDEA_ScoreCountUp -= countFraction;

				//Debugging something and seeing if it works!

				//StateProgressionManager_RestartCurrentLevel(ProcessHandle);
			}
		}
	}
}

void GameManipulator::WriteByte(UINT_PTR address, std::vector<unsigned int> offsets, byte value)
{
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	WriteProcessMemory(ProcessHandle, (void*)addr, &value, sizeof(byte), NULL);
}
void GameManipulator::WriteInt(UINT_PTR address, std::vector<unsigned int> offsets, int value)
{
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (LPCVOID)(addr), &addr, 4, 0);
		addr += offsets[i];
	}
	WriteProcessMemory(ProcessHandle, (void*)addr, &value, sizeof(int), NULL);
}
void GameManipulator::WriteFloat(UINT_PTR address, std::vector<unsigned int> offsets, float value)
{
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	WriteProcessMemory(ProcessHandle, (void*)addr, &value, sizeof(float), NULL);
}
void GameManipulator::WriteShort(UINT_PTR address, std::vector<unsigned int> offsets, short value)
{
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	WriteProcessMemory(ProcessHandle, (void*)addr, &value, sizeof(short), NULL);
}
void GameManipulator::WriteString(UINT_PTR address, std::vector<unsigned int> offsets, std::string value)
{
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	for (int i = 0; i < value.length(); i++)
	{
		char character = value.at(i);
		WriteProcessMemory(ProcessHandle, (void*)(addr + i), &character, 1, NULL);
	}
	WriteByte((addr + value.length()), {}, 0x0);
	
}

byte GameManipulator::ReadByte(UINT_PTR address, std::vector<unsigned int> offsets)
{
	byte toReturn = 0x0;
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	ReadProcessMemory(ProcessHandle, reinterpret_cast<void*>(addr), &toReturn, sizeof(byte), nullptr);
	return toReturn;
}
int GameManipulator::ReadInt(UINT_PTR address, std::vector<unsigned int> offsets)
{
	int toReturn = 0;
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (BYTE*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	ReadProcessMemory(ProcessHandle, reinterpret_cast<void*>(addr), &toReturn, sizeof(int), nullptr);
	return toReturn;
}
float GameManipulator::ReadFloat(UINT_PTR address, std::vector<unsigned int> offsets)
{
	float toReturn = 0;
	UINT_PTR addr = address;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(ProcessHandle, (float*)addr, &addr, 4, 0);
		addr += offsets[i];
	}
	ReadProcessMemory(ProcessHandle, reinterpret_cast<void*>(addr), &toReturn, sizeof(float), nullptr);
	return toReturn;
}

void GameManipulator::AddToLog(std::string textToAdd)
{
	/*
	* std::cout << textToAdd;
	std::cout << "\n";
	*/
	
}

void GameManipulator::CreateBackgroundThread()
{
	hb = std::thread(&GameManipulator::Heartbeat, this);
}

bool GameManipulator::InjectLibrary(std::string path)
{

	
	return true;
}

void GameManipulator::enableSeDebug()
{

}

std::string GameManipulator::getPathName(const std::string& s) {

	char sep = '/';

#ifdef _WIN32
	sep = '\\';
#endif

	size_t i = s.rfind(sep, s.length());
	if (i != std::string::npos) {
		return(s.substr(0, i));
	}

	return("");
}

void GameManipulator::WriteByte(UINT_PTR address, byte value)
{
	std::vector<unsigned int> offsets;
	WriteByte(address, offsets, value);
}
void GameManipulator::WriteFloat(UINT_PTR address, float value)
{
	std::vector<unsigned int> offsets;
	WriteFloat(address, offsets, value);
}
void GameManipulator::WriteInt(UINT_PTR address, int value)
{
	std::vector<unsigned int> offsets;
	WriteInt(address, offsets, value);
}
void GameManipulator::WriteShort(UINT_PTR address, short value)
{
	std::vector<unsigned int> offsets;
	WriteShort(address, offsets, value);
}
void GameManipulator::WriteString(UINT_PTR address, std::string value)
{
	std::vector<unsigned int> offsets;
	WriteString(address, offsets, value);
}

byte GameManipulator::ReadByte(UINT_PTR address)
{
	std::vector<unsigned int> offsets;
	return ReadByte(address, offsets);
}
int GameManipulator::ReadInt(UINT_PTR address)
{
	std::vector<unsigned int> offsets;
	return ReadInt(address, offsets);
}
float GameManipulator::ReadFloat(UINT_PTR address)
{
	std::vector<unsigned int> offsets;
	return ReadFloat(address, offsets);
}

