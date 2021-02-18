#pragma once

#include "GamePlayer.h"
#include "GearHuntObject.h"
#include "FunctionCaller.h"
#include "Funcs.h"
#include "Global.h"
#include <windows.h>
#include <vector>


class GameManipulator
{
private:
    FunctionCaller FC;
    
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

	void ClearPlayers();
	void GetAllPlayers();
	void UpdatePlayers();
    void EnableCheats();

	void WriteByte(UINT_PTR address, std::vector<unsigned int> offsets, byte value);
	void WriteFloat(UINT_PTR address, std::vector<unsigned int> offsets, float value);
	void WriteInt(UINT_PTR address, std::vector<unsigned int> offsets, int value);
	void WriteShort(UINT_PTR address, std::vector<unsigned int> offsets, short value);
	void WriteString(UINT_PTR address, std::vector<unsigned int> offsets, std::string value);

	byte ReadByte(UINT_PTR address, std::vector<unsigned int> offsets);
	int ReadInt(UINT_PTR address, std::vector<unsigned int> offsets);
	float ReadFloat(UINT_PTR address, std::vector<unsigned int> offsets);

	void WriteByte(UINT_PTR address, byte value);
	void WriteFloat(UINT_PTR address, float value);
	void WriteInt(UINT_PTR address, int value);
	void WriteShort(UINT_PTR address, short value);
	void WriteString(UINT_PTR address, std::string value);

	byte ReadByte(UINT_PTR address);
	int ReadInt(UINT_PTR address);
	float ReadFloat(UINT_PTR address);

	std::string getPathName(const std::string&);

	bool InjectLibrary(std::string);
	void enableSeDebug();

};
