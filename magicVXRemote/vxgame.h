#pragma once

#include <Windows.h>

// Forward declaration
class Main;
class Vector3D;
class Player;
class Car;
class GameSettings;
class Thing;
class ThingManagerList;
class PlayerManager;
class FileStreaming;
class DataPack;
class DataPackStream;
class DataPackScript;
class WildCardRack;
class World;
class GameData;
class Tile;
class State;

// Stores 3 dimensional position data
class Vector3D {
public:
	float X;
	float Y;
	float Z;

	// Creates an empty Vector
	Vector3D() {
		X = 0;
		Y = 0;
		Z = 0;
	}

	// Creates a Vector with the given coordinates
	Vector3D(float x, float y, float z) {
		X = x;
		Y = y;
		Z = z;
	}
};

class Action {
public:
	static char ActionInterfacePlay(int address)
	{
		return ((_PlayInterface)(0x437890))(address);
	}
	static int ActionLoadInterfacePack(int index) {
		return ((_LoadInterfacePack)(0x4012A0))(index);
	}
	static void ActionPlayInterfacePack(int address) {
		((_PlayInterfacePack)(0x445200))(address);
	}
	
private:
	typedef char(__cdecl* _PlayInterface)(int);
	typedef int(__cdecl* _LoadInterfacePack)(int);
	typedef void(__cdecl* _PlayInterfacePack)(int);
};

// Contains info about a player
class Player {
public:
	// Returns the player car object
	Car* GetCar() {
		return (Car*)(*(DWORD*)(this + 0x2C));
	}

	// Gets the current name value
	char* Name() {
		return (char*)(this + 0x40);
	}

	// Sets the player name
	void SetName(char* newName) {
		strcpy((char*)(this + 0x40), newName);
	}
};

// Contains car world object info
class Car {
public:
	static char ProcessItemPickup(Car *car, DWORD *item) {
		return ((_ProcessItemPickup)(0x412270))(car, item);
	}

	static char CarA_Init(Car *car, DWORD *index)
	{
		return ((_CarA_Init)(0x40D1B0))(car, index);
	}

	// Returns the player object the car is assigned to
	Player* GetPlayer() {
		return (Player*)(*(DWORD*)(this + 0x94));
	}

	// Gets the current health vaue
	int Health() {
		return *(int*)(this + 0x78);
	}

	// Sets the current health value
	void Health(int newHealth) {
		*(int*)(this + 0x78) = newHealth;
	}

	// Gets the current boost value
	char Boost() {
		return *(byte*)(this + 0x3DC);
	}

	// Sets the current boost value
	void Boost(char newBoost) {
		*(byte*)(this + 0x3Dc) = newBoost;
	}

	// Gets the current position
	Vector3D Position() {
		return *(Vector3D*)(this + 0x40);
	}

	// Sets the current position
	void Position(Vector3D newPos) {
		*(Vector3D*)(this + 0x40) = newPos;
	}

	// For use with ThingManagerList::GetByType
	int* ThingIdentifier() {
		return (int*)(this + 0x324);
	}

private:
	typedef char(__cdecl * _ProcessItemPickup)(Car*, DWORD*);
	typedef char(__cdecl* _CarA_Init)(Car*, DWORD*);
};

class GameSettings
{
public:
	static void GameSettings_SetCodeVariable(int variable, int offset, int value)
	{
		((_GameSettings_SetCodeVariable)(0x429FA0))(variable, offset, value);
	}
	static int GameSettings_GetCodeVariable(int variable, int offset)
	{
		return ((_GameSettings_GetCodeVariable)(0x42A680))(variable, offset);
	}
	static int GameSettings_IsCheatEnabled(int index)
	{
		return ((_GameSettings_IsCheatEnabled)(0x42AFB0))(index);
	}
private:
	typedef void(__cdecl* _GameSettings_SetCodeVariable)(int, int, int);
	typedef int(__cdecl* _GameSettings_GetCodeVariable)(int, int);
	typedef int(__cdecl* _GameSettings_IsCheatEnabled)(int);
};

class Interface
{
public:
	static void InterfaceManager_SetObjectText(int address, int text) {
		((_SetObjectText)(0x42EFA0))(address, text);
	}
private:
	typedef void(__cdecl* _SetObjectText)(int, int);
};

class Item {
public:
	static char Item_Init(Item* item, DWORD* index)
	{
		return ((_Item_Init)(0x44D0B0))(item, index);
	}
	static void Item_Release(int address)
	{
		((_Item_Release)(0x438770))(address);
	}
private:
	typedef char(__cdecl* _Item_Init)(Item*, DWORD*);
	typedef void(__cdecl* _Item_Release)(int);
};

class State {
public:
	static State* StateManager_GotoState(int index) {
		return ((_GetByType)(0x447FC0))(index);
	}
private:
	typedef State* (__cdecl* _GetByType)(int);
};

// Contains all thing info and functions
class Thing {
public:
};

// Contains all thing creation tools
class ThingManager
{
public:
	// Assuming thing ptr return type until proven otherwise
	static int ThingManager_DARYL_CreateThing(int type, int base) {
		return ((_ThingManager_DARYL_CreateThing)(0x44D0B0))(type, base);
	}
private:
	typedef int(__cdecl* _ThingManager_DARYL_CreateThing)(int, int);
};

// Not exactly sure what this does lol
class ThingManagerList {
public:
	// Assuming thing ptr return type until proven otherwise
	static Thing* GetByType(int* identifier, int type) {
		return ((_GetByType)(0x44A840))(identifier, type);
	}
private:
	typedef Thing*(__cdecl * _GetByType)(int*, int);
};

// Contains all player and player list info
class PlayerManager {
public:
	// Obtains the number of currently loaded players (including AI)
	static char PlayerCount() {
		return ((_PlayerCount)(0x440160))();
	};

	// Obtains the number of currently loaded players (Humans only)
	static char PlayerHumanCount() {
		return ((_PlayerCount)(0x440130))();
	};

	// Gets the player (AI or Player) with the given index
	static Player* GetPlayerByIndex(char index) {
		return ((_GetPlayerByIndex)(0x440180))(index);
	};

	// Gets the player (Human) with the given index
	static Player* GetHumanPlayerByIndex(char index) {
		return ((_GetPlayerByIndex)(0x4401B0))(index);
	};

private:
	typedef char(__stdcall * _PlayerCount)();
	typedef Player*(__cdecl * _GetPlayerByIndex)(char);
};

// Loads datapacks
class FileStreaming {
public:
	// Loads a datapack by name and index (WIP)
	static DataPackStream* LoadDataPack(const char* name, signed int unk1, int unk2, char unk3) {
		return ((_LoadDataPack)(0x4287E0))(name, unk1, unk2, unk3);
	}

	static DataPack* InitializeDataPack(DataPackStream* stream, int unk1, char unk2) {
		return ((_InitializeDataPack)(0x428C10))(stream, unk1, unk2);
	}

private:
	typedef DataPackStream*(__cdecl * _LoadDataPack)(const char*, signed int, int, char);
	typedef DataPack*(__cdecl * _InitializeDataPack)(DataPackStream*, int, char);
};

// DataPack management
class DataPack {
public:
	static DataPackScript* GetScript(DataPack** pack, int itemId) {
		return ((_GetScript)(0x4216C0))(pack, itemId);
	}
	static char LoadFile(const char* name, int unk1, int unk2, int unk3)
	{
		return ((_LoadFile)(0x420710))(name, unk1, unk2, unk3);
	}
	static void RefreshPtrs(int address) {
		((_RefreshPtrs)(0x421400))(address);
	}
	static void RefreshTextures(int address) {
		((_RefreshPtrs)(0x421320))(address);
	}
private:
	typedef DataPackScript*(__cdecl * _GetScript)(DataPack**, int);
	typedef char(__cdecl* _LoadFile)(const char*, int, int, int);
	typedef void(__cdecl* _RefreshPtrs)(int);
};

// Wildcard/Weapon management
class WildCardRack {
public:
	static char Add(Thing* carThing, int weaponScript, __int16 unk1) {
		return ((_Add)(0x451C80))(carThing, weaponScript, unk1);
	}
private:
	typedef char(__cdecl * _Add)(Thing*, int, __int16);
};

// Level-related functions
class World {
public:
	// Gets the total amount of car tiles in the world data
	static int GetTotalTiles_Car() {
		return ((_GetTotalTiles_Car)(0x4524B0))();
	}

	// Pulls a specific car tile from world data by index (class unimplemented)
	static Tile* GetTileCar(unsigned int index) {
		return ((_GetTileCar)(0x4524D0))(index);
	}

	// Gets world game data (class unimplemented)
	static GameData* GetGameData() {
		return ((_GetGameData)(0x4525A0))();
	}
private:
	typedef int(__stdcall * _GetTotalTiles_Car)();
	typedef Tile*(__cdecl* _GetTileCar)(unsigned int);
	typedef GameData* (__cdecl* _GetGameData)();
};
