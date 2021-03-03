#pragma once

enum Funcs
{
	CarA_Extract_Keyframes = 0x40CC90,
	CarA_PreMove = 0x40E8D0,
	CarA_Move = 0x40F270,
	CarA_ComputeSuspensionForces_Aux1 = 0x4160C0,
	DataPack_RefreshTextures = 0x421320,
	DataPack_GetScript = 0x4216C0,
	FileStreaming_LoadDataPack = 0x4287E0,
	FileStreaming_GetPackID = 0x4289E0,
	FileStreaming_InitializeDataPack = 0x428C10,
	GameSettings_GetMCP = 0x429EC0,
	GameSettings_SetCodeVariable = 0x429FA0,
	GameSettings_GetCodeVariable = 0x42A680,
	GameSettings_IsCheatEnabled = 0x42AFB0,
	Item_Release = 0x438770,
	Player_IsHuman = 0x43E9F0,
	PlayerManager_PlayerCount = 0x440160,
	PlayerManager_GetPlayerByIndex = 0x440180,
	PlayerManager_GetHumanPlayerByIndex = 0x4401B0,
	ArmageddonDropShip = 0x4453E0,
	StateManager_GotoState = 0x447FC0,
	ActionVehicleTeleport = 0x4498B0,
	ThingManager_DARYL_CreateThing = 0x44D0B0,
	ViewManager_SetFourPlayer = 0x450B80,
	GetTotalTiles_Car = 0x4524B0,
	GetTileCar = 0x4524D0,
	SubMatrixToQuaternion = 0x4540C0,
	CreateConfigWindow = 0x455F70,
	SetSFXVol = 0x4596C0,
	MagicVX_PatchMouse = 0xFFFF0001,
    MagicVX_EnableCheats = 0xFFFF0002,
	MagicVX_GiveItem = 0xFFFF0003,
	MagicVX_LoadCar = 0xFFFF0004,
	MagicVX_LoadItem = 0xFFFF0005,
};

enum LoadDataPackNames
{
    LDP_HW_Items = 0x48A49C,
    LDP_HW_Cars = 0x489A9C,
};

//case DataPack_GetScript: return ((_DataPack_GetScript)(p->func))(p->argInt0, p->argInt1); break;
//case FileStreaming_LoadDataPack: return ((_FileStreaming_LoadDataPack)(p->func))(p->argInt0, p->argSInt1, p->argInt2, p->argChar3); break;
//case FileStreaming_InitializeDataPack: return ((_FileStreaming_InitializeDataPack)(p->func))(p->argInt0, p->argInt1, p->argChar2); break;
//case GameSettings_SetCodeVariable: ((_GameSettings_SetCodeVariable)(p->func))(p->argInt0, p->argInt1, p->argInt2); break;
//case GameSettings_GetCodeVariable: return ((_GameSettings_GetCodeVariable)(p->func))(p->argInt0, p->argInt1); break;
//case GameSettings_IsCheatEnabled: return ((_GameSettings_IsCheatEnabled)(p->func))(p->argInt0); break;
//case Item_Release: ((_Item_Release)(p->func))(p->argInt0); break;
//case Player_IsHuman: return ((_Player_IsHuman)(p->func))(p->argInt0); break;
//case PlayerManager_PlayerCount: return ((_PlayerManager_PlayerCount)(p->func))(); break;
//case PlayerManager_GetPlayerByIndex: return ((_PlayerManager_GetPlayerByIndex)(p->func))(p->argChar0); break;
//case PlayerManager_GetHumanPlayerByIndex: return ((_PlayerManager_GetHumanPlayerByIndex)(p->func))(p->argChar0); break;
//case StateManager_GotoState: ((_StateManager_GotoState)(p->func))(p->argInt0); break;
//case ActionVehicleTeleport: return ((_ActionVehicleTeleport)(p->func))(p->argInt0); break;
//case ThingManager_DARYL_CreateThing: return ((_ThingManager_DARYL_CreateThing)(p->func))(p->argInt0, p->argInt1); break;
//case ViewManager_SetFourPlayer: ((_ViewManager_SetFourPlayer)(p->func))(); break;
//case GetTotalTiles_Car: return ((_GetTotalTiles_Car)(p->func))(); break;
//case GetTileCar: return ((_GetTileCar)(p->func))(p->argInt0); break;
//case SubMatrixToQuaternion: ((_SubMatrixToQuaternion)(p->func))(p->argInt0, p->argInt1); break;
//case SetSFXVol: ((_SetSFXVol)(p->func))(p->argInt0); break;

enum Collectables
{
	C_RipperWheels = 0,
	C_ArmorRepair = 1,
	C_OilDrum = 2,
	C_LaserCannon = 3,
	C_SonicBoom = 4,
	C_AtomBlaster = 5,
	C_FreonBomb = 6,
	C_EnergyShield = 7,
	C_JetBoosters = 8,
	C_SuperZapper = 9,
	C_MagnetMine = 10,
	C_DoomDisks = 11,
	C_MoneyBag = 16,
	C_Uranium = 17,
	C_BlueGear = 19,
	C_WhiteGear = 20,
	C_RedGear = 21,
	C_GreenGear = 22,
	C_YellowGear = 23,
	C_TimeBomb = 51,
	C_BlueKey = 52,
	C_YellowKey = 53,
	C_GreenKey = 54,
	C_RedKey = 55,
	C_WhiteKey = 56,
	C_600PointCapsule = 57,
	C_700PointCapsule = 58,
	C_200PointCapsule = 59,
	C_400PointCapsule = 60,
	C_100PointCapsule = 61,
	C_500PointCapsule = 62,
	C_300PointCapsule = 63,
	C_800PointCapsule = 64,
	C_DataDisk = 65,
	C_TemporalTransmission = 68,
	C_VolcanicGasCollector = 69,
};

enum GameBoardKeys
{
	GB_Backspace = 8,
	GB_Tab = 9,
	GB_Enter = 13,
	GB_Shift = 16,
	GB_Alt = 18,
	GB_CapsLock = 20,
	GB_Escape = 27,
	GB_Space = 32,
	GB_PageUp = 33,
	GB_PageDown = 34,
	GB_End = 35,
	GB_Home = 36,
	GB_Left = 37,
	GB_Up = 38,
	GB_Right = 39,
	GB_Down = 40,
	GB_Insert = 45,
	GB_Delete = 46,
	GB_0 = 48,
	GB_1 = 49,
	GB_2 = 50,
	GB_3 = 51,
	GB_4 = 52,
	GB_5 = 53,
	GB_6 = 54,
	GB_7 = 55,
	GB_8 = 56,
	GB_9 = 57,
	GB_A = 65,
	GB_B = 66,
	GB_C = 67,
	GB_D = 68,
	GB_E = 69,
	GB_F = 70,
	GB_G = 71,
	GB_H = 72,
	GB_I = 73,
	GB_J = 74,
	GB_K = 75,
	GB_L = 76,
	GB_M = 77,
	GB_N = 78,
	GB_O = 79,
	GB_P = 80,
	GB_Q = 81,
	GB_R = 82,
	GB_S = 83,
	GB_T = 84,
	GB_U = 85,
	GB_V = 86,
	GB_W = 87,
	GB_X = 88,
	GB_Y = 89,
	GB_Z = 90,
	GB_Windows = 91,
	GB_Context = 93,
	GB_NumPad0 = 96,
	GB_NumPad1 = 97,
	GB_NumPad2 = 98,
	GB_NumPad3 = 99,
	GB_NumPad4 = 100,
	GB_NumPad5 = 101,
	GB_NumPad6 = 102,
	GB_NumPad7 = 103,
	GB_NumPad8 = 104,
	GB_NumPad9 = 105,
	GB_NumPadStar = 106,
	GB_NumPadPlus = 107,
	GB_NumPadMinus = 109,
	GB_NumPadPeriod = 110,
	GB_NumPadForwardSlash = 111,
	GB_F1 = 112,
	GB_F2 = 113,
	GB_F3 = 114,
	GB_F4 = 115,
	GB_F5 = 116,
	GB_F6 = 117,
	GB_F7 = 118,
	GB_F8 = 119,
	GB_F9 = 120,
	GB_F10 = 121,
	GB_F11 = 122,
	GB_F12 = 123,
	GB_F13 = 124,
	GB_F14 = 125,
	GB_F15 = 126,
	GB_F16 = 127,
	GB_Semicolon = 186,
	GB_Equals = 187,
	GB_Comma = 188,
	GB_Dash = 189,
	GB_Period = 190,
	GB_ForwardSlash = 191,
	GB_Tilde = 192,
};

enum GameBoardStates
{
	GBS_Inactive = 0,
	GBS_Pressed = 1,
	GBS_Held = 2,
	GBS_Released = 3
};

