#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include "PipeFunction.h"
#include "Funcs.h"

class FunctionCaller
{
private:
	HANDLE ProcessHandle;
    HANDLE Pipe;
    int privileges = 0;
public:
    FunctionCaller();
	FunctionCaller(HANDLE ph, std::string);

    void  InitPipe();
    int   GetPrivileges();
    bool  InjectDll(LPCSTR, HANDLE);
    
    int   CallPipeInt(PipeFunction);
    bool  CallPipeBool(PipeFunction);
    float CallPipeFloat(PipeFunction);
    char  CallPipeChar(PipeFunction);
    void  CallPipeVoid(PipeFunction);

    void* AllocateMemory(int);
    void  DeAllocateMemory(void*);

	void  DisableFunction(int);
	void  FunctionReturnZero(int);

    void  PatchMouse();

	int   CU_SpawnGear(float, float, float, int);
	int   CU_SpawnItem(int, float, float, float);
	void  CU_EnableCheats();
	void  CU_DisableCheats();
	void  CU_TeleportCorrection(int);

	int   FC_DataPack_GetScript(int, int);
	int   FC_FileStreaming_LoadDataPack(int, int, int, char);
	int   FC_FileStreaming_InitializeDataPack(int, int, char);
	void  FC_GameSettings_SetCodeVariable(int, int, int);
	int   FC_GameSettings_GetCodeVariable(int, int);
	int   FC_GameSettings_IsCheatEnabled(int);
	void  FC_Item_Release(int);
	bool  FC_Player_IsHuman(int);
	char  FC_PlayerManager_PlayerCount();
	int   FC_PlayerManager_GetPlayerByIndex(char);
	int   FC_PlayerManager_GetHumanPlayerByIndex(char);
	void  FC_StateManager_GotoState(int);
	int   FC_ActionVehicleTeleport(int);
	int   FC_ThingManager_DARYL_CreateThing(int, int);
	void  FC_ViewManager_SetFourPlayer();
	int   FC_GetTotalTiles_Car();
	int   FC_GetTileCar(int);
	void  FC_SubMatrixToQuaternion(int, int);
	void  FC_SetSFXVol(int);

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
};

typedef int(__cdecl* _DataPack_GetScript)(int, int);
typedef int(__cdecl* _FileStreaming_LoadDataPack)(int, signed int, int, char);
typedef int(__cdecl* _FileStreaming_InitializeDataPack)(int, int, char);
typedef void(__cdecl* _GameSettings_SetCodeVariable)(int, int, int);
typedef int(__cdecl* _GameSettings_GetCodeVariable)(int, int);
typedef bool(__cdecl* _GameSettings_IsCheatEnabled)(int);
typedef void(__cdecl* _Item_Release)(int);
typedef bool(__cdecl* _Player_IsHuman)(int);
typedef char(__cdecl* _PlayerManager_PlayerCount)();
typedef int(__cdecl* _PlayerManager_GetPlayerByIndex)(char);
typedef int(__cdecl* _PlayerManager_GetHumanPlayerByIndex)(char);
typedef void(__cdecl* _StateManager_GotoState)(int);
typedef int(__cdecl* _ActionVehicleTeleport)(int);
typedef int(__cdecl* _ThingManager_DARYL_CreateThing)(int, int);
typedef void(__cdecl* _ViewManager_SetFourPlayer)();
typedef int(__cdecl* _GetTotalTiles_Car)();
typedef int(__cdecl* _GetTileCar)(int);
typedef void(__cdecl* _SubMatrixToQuaternion)(int, int);
typedef void(__cdecl* _SetSFXVol)(int);
