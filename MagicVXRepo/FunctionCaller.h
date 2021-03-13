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
	DWORD ProID;
    int privileges = 0;
public:
    FunctionCaller();
	FunctionCaller(HANDLE ph, DWORD pid, std::string);

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
	int   Pipe_LoadCar(int);

	int   CU_SpawnGear(float, float, float, int);
	int   CU_SpawnItem(int, float, float, float);
	int   CU_SpawnCar(int, float, float, float);
	void  CU_EnableCheats();
	void  CU_DisableCheats();
	void  CU_TeleportCorrection(int);
	void  CU_ChangeCameraView(int);

	int   FC_CameraManager_GetActiveCameras();
	int   FC_CameraManager_GetCameraByIndex(int);
	int   FC_CameraManager_GetNewCamera();
	void  FC_Camera_SetPlayer(int, int);
	int   FC_DataPack_RefreshTextures(int);
	int   FC_DataPack_GetScript(int, int);
	int   FC_FileStreaming_LoadDataPack(int, int, int, byte);
	int   FC_FileStreaming_GetPackID(int, int, int);
	int   FC_FileStreaming_InitializeDataPack(int, int, byte);
	int   FC_GameSettings_GetMCP();
	void  FC_GameSettings_SetCodeVariable(int, int, int);
	int   FC_GameSettings_GetCodeVariable(int, int);
	int   FC_GameSettings_IsCheatEnabled(int);
	void  FC_Item_Release(int);
	bool  FC_Player_IsHuman(int);
	void  FC_Player_RefreshInterface(int);
	void  FC_Player_SetThing(int, int);
	int   FC_PlayerManager_NewHumanPlayer();
	int   FC_PlayerManager_NewAIPlayer();
	char  FC_PlayerManager_PlayerHumanCount();
	char  FC_PlayerManager_PlayerCount();
	int   FC_PlayerManager_GetPlayerByIndex(char);
	int   FC_PlayerManager_GetHumanPlayerByIndex(char);
	void  FC_PlayerManager_RemovePlayer(int);
	void  FC_InterfaceInputAnimator_Initialize();
	void  FC_StateProgressionManager_RestartCurrentLevel();
	void  FC_StateManager_GotoState(int);
	int   FC_ActionVehicleTeleport(int);
	int   FC_ThingManager_DARYL_CreateThing(int, int);
	void  FC_ViewManager_SetCamera(int, int);
	void  FC_ViewManager_EnableView(int, int);
	void  FC_Gfx_SetRenderWindowSize(int, int, int, int, int);
	void  FC_ViewManager_SetSinglePlayer();
	void  FC_ViewManager_SetTwoPlayerHorizontal();
	void  FC_ViewManager_SetThreePlayer();
	void  FC_ViewManager_SetFourPlayer();
	int   FC_GetTotalTiles_Car();
	int   FC_GetTileCar(int);
	void  FC_SubMatrixToQuaternion(int, int);
	void  FC_SetSFXVol(int);

	void  FC_ArmageddonDropShip();

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

	bool IsForegroundProcess();
};
