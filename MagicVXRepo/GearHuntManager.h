#pragma once
#include <iostream>
#include "SimpleIni.h"
#include "GearHuntObject.h"
#include "Funcs.h"
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ShlObj_core.h>
#include <direct.h>
#include <vector>
#include <atlstr.h>

class GearHuntManager
{
private:
	bool StringToBool(const char* value);
public:
	std::vector<GearHuntObject> objects;
	std::vector<std::string> inFolder;

	std::string Title;
	std::string Creator;
	std::string Description;
	std::string MVX_Version;
	std::string FileName;

	int World = 0;
	int TotalObjects = 0;
	int Gears = 0;
	int Keys = 0;
	int Weapons = 0;
	int PointCapsules = 0;

	bool ForceCar = false;
	int CarChoice = 0;
	bool ForceWeapon = false;
	int WeaponChoice = 0;
	bool ForceDeadWeight = false;
	int DeadWeightChoice = 0;
	int TimeLimit = 0;

	bool ZeroGravity = false;
	bool SimplePhysics = false;

	std::vector<std::string>  CollectGearHunts(std::string);

	void LoadInfo(std::string);
	void SaveInfo(std::string);

	std::string getpath();
	std::string GetExeDirectory();
	
	GearHuntManager();
};

