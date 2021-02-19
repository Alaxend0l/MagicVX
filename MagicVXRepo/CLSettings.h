#pragma once
#include "GearHuntObject.h"
#include <string>
#include <vector>

class CLSettings
{
public:
	//Universal Variables that are used in every custom launch.
	int Mode = 1;
	int Act = 0;
	int Car = 29;
	int Weapon = 8;
	int Difficulty = 0;

	bool U_SimplePhysics = false;
	bool U_ZeroGravity = false;

	//Below are variables used for missions and challenges.

	bool ArmorRepairGlitch = false;

	//Below are variables used for drag races.
	int DragRace_Opponents = 2;
	int DragRace_Rounds = 3;
	int DragRace_Gadgets = 1;
	bool DragRace_ItemReset = false;
	int DragRace_Reset = 0;
	int DragRace_RoundsOrWins = 0;
	int DragRace_Time = 300;

	//Below are variables used for battles.
	int Battle_Opponents = 2;
	int Battle_Rounds = 3;
	int Battle_Gadgets = 1;
	bool Battle_GadgetRespawn = true;
	int Battle_Time = 300;
	int Battle_Kills = 5;
	int Battle_RoundsOrWins = 0;

	//Below are variables used for Score War.
	int Score_Target = 30000;
	int Score_Opponents = 2;
	int Score_Time = 300;
	int Score_Rounds = 3;
	int Score_Gadgets = 1;
	bool Score_GadgetRespawn = 1;
	int Score_PointsPerKill = 3000;
	int Score_RoundsOrWins = 0;

	//Below are variables used for Gear Hunt.
	std::string GearHunt_File = "MagnussFrenzy";
	int GearHunt_Gears = 0;
	int GearHunt_Keys = 0;
	int GearHunt_Objects = 0;
	int GearHunt_Mode = 0; //0 = Make, 1 = Play
	int GearHunt_DeadWeightType = 0;
	int GearHunt_TimeLimit = 0;

	//Below are variables used for Sandbox.
	bool Sandbox_Enabled = false;
	bool Sandbox_PreventCollectablesFromSpawning = false;
	bool Sandbox_EnableAllCheats = true;
	bool Sandbox_SimplifyPhysics = false;
	bool Sandbox_ZeroGravity = false;
};


