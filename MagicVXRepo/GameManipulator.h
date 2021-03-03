#pragma once

#include "Global.h"
#include "GearHuntObject.h"
#include "Funcs.h"

#include <windows.h>
#include <vector>


class GameManipulator
{
public:
	GameManipulator();

    void BootGame(bool);

    void ResetValues();
	void AddToLog(std::string);
	void GameLaunch();
	void CreateBackgroundThread();

	void Heartbeat();

	void PatchMouse();

	void CustomLaunch_Disclaimer();
	void CustomLaunch_LoadStart();
	void CustomLaunch_LoadWorldData();
	void CustomLaunch_LoadObjectData();
	void CustomLaunch_GamePlayStart();
	void CustomLaunch_GamePlayHeartbeat();

	void StandardLaunch_Disclaimer();

	void MakeGearHunt_PrepareObjectTypes();
	void MakeGearHunt_Save();
	void MakeGearHunt_RemoveObject(int index);
	
	void GearHuntLaunch_PrepareObjectTypes();
	std::vector<GearHuntObject> GearHuntLaunch_PrepareGears();
	void GearHuntLaunch_SpawnGears();
	void GearHuntLaunch_Timer();

	void Sandbox_Init();
	void Sandbox_Heartbeat();

	void PatchFOV();

	void UpdatePlayers();
    void EnableCheats();

	

	std::string IntToHexString(int);

	std::string getPathName(const std::string&);

	bool InjectLibrary(std::string);
	void enableSeDebug();

};
