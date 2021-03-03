#pragma once

#define ROUTE_FUNC(name) void (name)(const char* msg, char* returnData, DWORD* bytesWritten);
#define ROUTE_FUNC_IMPL(name) void (name)(const char* msg, char* returnData, DWORD* bytesWritten)

typedef void(__cdecl* _route)(const char* msg, char* returnData, DWORD* bytesWritten);

// Network communication enum identifying the pipe route
enum PIPE_METHODS {
	METHOD_MAGICVX_ENABLECURSOR = 0xFFFF0001,
	METHOD_MAGICVX_ENABLECHEATS = 0xFFFF0002,
	METHOD_MAGICVX_GIVEITEM = 0xFFFF0003,
	METHOD_MAGICVX_LOADCAR = 0xFFFF0004,
	METHOD_MAGICVX_LOADITEM = 0xFFFF0005,
	METHOD_MAGICVX_PLAYINTERFACE,
	METHOD_PLAYERMANAGER_PLAYERCOUNT = 0x440160,
	METHOD_PLAYERMANAGER_PLAYERHUMANCOUNT,
	METHOD_PLAYERMANAGER_GETPLAYERBYINDEX = 0x440180,
	METHOD_PLAYERMANAGER_GETHUMANPLAYERBYINDEX = 0x4401B0,
	METHOD_PLAYER_GETCAR,
	METHOD_WORLD_GETTOTALTILES_CAR,
	METHOD_WORLD_GETTILECAR,
	METHOD_STATEMANAGER_GOTOSTATE = 0x447FC0,
	METHOD_CARA_INIT,
	METHOD_ITEM_INIT,
	METHOD_ITEM_RELEASE = 0x438770,
	METHOD_INTERFACEMANAGER_SETOBJECTTEXT,
	METHOD_THINGMANAGER_DARYL_CREATETHING = 0x44D0B0,
};

class Routes {
public:
	static _route GetRouteFromEnum(int id);

	static ROUTE_FUNC(MagicVX_EnableCursor)

	static ROUTE_FUNC(MagicVX_EnableCheats)

	static ROUTE_FUNC(MagicVX_GiveItem)

	static ROUTE_FUNC(MagicVX_LoadCar)

	static ROUTE_FUNC(MagicVX_LoadItem)

	static ROUTE_FUNC(MagicVX_PlayInterface)

	static ROUTE_FUNC(PlayerManager_PlayerCount)

	static ROUTE_FUNC(PlayerManager_PlayerHumanCount)

	static ROUTE_FUNC(PlayerManager_GetPlayerByIndex)

	static ROUTE_FUNC(PlayerManager_GetHumanPlayerByIndex)

	static ROUTE_FUNC(Player_GetCar)

	static ROUTE_FUNC(World_GetTotalTiles_Car)

	static ROUTE_FUNC(World_GetTileCar)

	static ROUTE_FUNC(StateManager_GotoState)

	static ROUTE_FUNC(CarA_Init)

	static ROUTE_FUNC(Item_Init)

	static ROUTE_FUNC(Item_Release)

	static ROUTE_FUNC(InterfaceManager_SetObjectText)

	static ROUTE_FUNC(ThingManager_DARYL_CreateThing)
};