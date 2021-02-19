#include <iostream>

#include "vxpipe.h"
#include "vxgame.h"
#include "vxcustom.h"
#include "vxroutes.h"

_route Routes::GetRouteFromEnum(int id) {
	switch (id) {
	case METHOD_MAGICVX_ENABLECURSOR: return (_route)Routes::MagicVX_EnableCursor; break;
	case METHOD_MAGICVX_ENABLECHEATS: return (_route)Routes::MagicVX_EnableCheats; break;
	case METHOD_MAGICVX_GIVEITEM: return (_route)Routes::MagicVX_GiveItem; break;
	case METHOD_MAGICVX_LOADCAR: return (_route)Routes::MagicVX_LoadCar; break;
	case METHOD_MAGICVX_LOADITEM: return (_route)Routes::MagicVX_LoadItem; break;
	case METHOD_MAGICVX_PLAYINTERFACE: return (_route)Routes::MagicVX_PlayInterface; break;
	case METHOD_PLAYERMANAGER_PLAYERCOUNT: return (_route)Routes::PlayerManager_PlayerCount; break;
	case METHOD_PLAYERMANAGER_PLAYERHUMANCOUNT: return (_route)Routes::PlayerManager_PlayerHumanCount; break;
	case METHOD_PLAYERMANAGER_GETPLAYERBYINDEX: return (_route)Routes::PlayerManager_GetPlayerByIndex; break;
	case METHOD_PLAYERMANAGER_GETHUMANPLAYERBYINDEX: return (_route)Routes::PlayerManager_GetHumanPlayerByIndex; break;
	case METHOD_PLAYER_GETCAR: return (_route)Routes::Player_GetCar; break;
	case METHOD_WORLD_GETTOTALTILES_CAR: return (_route)Routes::World_GetTotalTiles_Car; break;
	case METHOD_WORLD_GETTILECAR: return (_route)Routes::World_GetTileCar; break;
	case METHOD_STATEMANAGER_GOTOSTATE: return (_route)Routes::StateManager_GotoState; break;
	case METHOD_CARA_INIT: return (_route)Routes::CarA_Init; break;
	case METHOD_ITEM_INIT: return (_route)Routes::Item_Init; break;
	case METHOD_ITEM_RELEASE: return (_route)Routes::Item_Release; break;
	case METHOD_INTERFACEMANAGER_SETOBJECTTEXT: return (_route)Routes::InterfaceManager_SetObjectText; break;
	case METHOD_THINGMANAGER_DARYL_CREATETHING: return (_route)Routes::ThingManager_DARYL_CreateThing; break;
	}

	return [](const char* msg, char* returnData, DWORD* bytesWritten) {
		printf("[magicVX] Invalid route");
	};
}

ROUTE_FUNC_IMPL(Routes::MagicVX_EnableCursor) {
	MagicVX::EnableMouse();
	*bytesWritten = 0;
}

ROUTE_FUNC_IMPL(Routes::MagicVX_EnableCheats) {
	MagicVX::EnableCheats();
	*bytesWritten = 0;
}

ROUTE_FUNC_IMPL(Routes::MagicVX_GiveItem) {
	Car* car;
	int index;
	memcpy(&car, msg + 4, 4);
	memcpy(&index, msg + 8, 4);
	MagicVX::GiveItem(car, index);
	*bytesWritten = 0;
}

ROUTE_FUNC_IMPL(Routes::MagicVX_LoadCar)
{
	int index;
	int loc;
	memcpy(&index, msg + 4, 4);
	memcpy(&loc, msg + 8, 4);
	int address = MagicVX::LoadCar(index, loc);
	memcpy(returnData, &address, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::MagicVX_LoadItem)
{
	int index;
	memcpy(&index, msg + 4, 4);
	int address = MagicVX::LoadItem(index);
	memcpy(returnData, &address, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::MagicVX_PlayInterface)
{
	int index;
	memcpy(&index, msg + 4, 4);
	MagicVX::PlayInterface(index);
	*bytesWritten = 0;
}

ROUTE_FUNC_IMPL(Routes::PlayerManager_PlayerCount) {
	returnData[0] = PlayerManager::PlayerCount();
	*bytesWritten = 1;
}

ROUTE_FUNC_IMPL(Routes::PlayerManager_PlayerHumanCount) {
	returnData[0] = PlayerManager::PlayerHumanCount();
	*bytesWritten = 1;
}

ROUTE_FUNC_IMPL(Routes::PlayerManager_GetPlayerByIndex) {
	char index = msg[4];
	Player* ply = PlayerManager::GetPlayerByIndex(index);
	memcpy(returnData, &ply, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::PlayerManager_GetHumanPlayerByIndex) {
	char index = msg[4];
	Player* ply = PlayerManager::GetHumanPlayerByIndex(index);
	memcpy(returnData, &ply, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::Player_GetCar) {
	Player* player;
	memcpy(&player, msg + 4, 4);
	Car* car = player->GetCar();
	memcpy(returnData, &car, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::World_GetTotalTiles_Car) {
	int tiles = World::GetTotalTiles_Car();
	memcpy(returnData, &tiles, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::World_GetTileCar) {
	int index;

	memcpy(&index, msg + 4, 4);

	Tile* tile = World::GetTileCar(index);

	memcpy(returnData, &tile, 4);

	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::StateManager_GotoState) {
	int index;
	memcpy(&index, msg + 4, 4);
	State* state = State::StateManager_GotoState(index);
	memcpy(returnData, &index, 4);
	*bytesWritten = 4;
}

ROUTE_FUNC_IMPL(Routes::CarA_Init) {
	Car* car;
	DWORD* index;
	memcpy(&car, msg + 4, 4);
	memcpy(&index, msg + 8, 4);
	char testChar = Car::CarA_Init(car, index);
	*bytesWritten = 8;
}

ROUTE_FUNC_IMPL(Routes::Item_Init) {
	Item* item;
	DWORD* index;
	memcpy(&item, msg + 4, 4);
	memcpy(&index, msg + 8, 4);
	char testChar = Item::Item_Init(item, index);
	*bytesWritten = 8;
}

ROUTE_FUNC_IMPL(Routes::Item_Release) {
	int address;
	memcpy(&address, msg + 4, 4);
	Item::Item_Release(address);
	*bytesWritten = 0;
}

ROUTE_FUNC_IMPL(Routes::InterfaceManager_SetObjectText)
{
	int address;
	int text;
	memcpy(&address, msg + 4, 4);
	memcpy(&text, msg + 8, 4);
	Interface::InterfaceManager_SetObjectText(address, text);
	*bytesWritten = 8;
}

ROUTE_FUNC_IMPL(Routes::ThingManager_DARYL_CreateThing)
{
	int type;
	int base;
	memcpy(&type, msg + 4, 4);
	memcpy(&base, msg + 8, 4);
	int returnInt = ThingManager::ThingManager_DARYL_CreateThing(type, base);
	memcpy(returnData, &returnInt, 4);
	*bytesWritten = 8;
}