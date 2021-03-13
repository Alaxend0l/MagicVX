#include "TypeCollector.h"

TypeCollector::TypeCollector()
{

}

TypeCollector::TypeCollector(FunctionCaller* _FC)
{
	FC = _FC;
}

void TypeCollector::ResetValues()
{
	hwvxPlayers.clear();
	hwvxVehicles.clear();
	hwvxTileCars.clear();
}

void TypeCollector::Update()
{
	for (int i = 0; i < GetTileCarCount(); i++) GetTileCar(i)->Update();
	for (int i = 0; i < GetPlayerCount(); i++) GetPlayer(i)->Update();
}

void TypeCollector::SetUpVehicles()
{
	const int MaxOnScreen = 8;
	const int StartAddress = 0x521CC0;
	const int VehicleSize = 0x560;
	hwvxVehicles.clear();
	for (int i = 0; i < MaxOnScreen; i++)
	{
		HWVX_Vehicle newVehicle = HWVX_Vehicle(FC, StartAddress - i * VehicleSize);
		AddVehicle(newVehicle);
	}
}

void TypeCollector::SetUpTileCars()
{
	const int VehicleSize = 0x60;
	int CarsLoaded = FC->ReadInt(0x49DBA0, { 8 });
	hwvxTileCars.clear();
	for (int i = 0; i < CarsLoaded; i++)
	{
		HWVX_TileCar newTileCar = HWVX_TileCar(FC, FC->ReadInt(0x49DBA0, { 0xC }) + i * VehicleSize);
		AddTileCar(newTileCar);
	}
}

void TypeCollector::SetUpPlayers()
{
	int Players = FC->FC_PlayerManager_PlayerCount();
	for (int i = 0; i < Players; i++)
	{
		HWVX_Player newPlayer = HWVX_Player(FC, FC->FC_PlayerManager_GetPlayerByIndex(i));
		newPlayer.playerVehicle = GetVehicleByAddress(FC->ReadInt(newPlayer.GetBaseAddress() + 0x2C));
		AddPlayer(newPlayer);
	}
}



//Getters and Setters

//Add

void TypeCollector::AddPlayer(HWVX_Player player)
{
	hwvxPlayers.push_back(player);
}

void TypeCollector::AddVehicle(HWVX_Vehicle vehicle)
{
	hwvxVehicles.push_back(vehicle);
}

void TypeCollector::AddTileCar(HWVX_TileCar tileCar)
{
	hwvxTileCars.push_back(tileCar);
}

//Get

HWVX_Player* TypeCollector::GetPlayer(int index)
{
	return &hwvxPlayers.at(index);
}

HWVX_Vehicle* TypeCollector::GetVehicle(int index)
{
	return &hwvxVehicles.at(index);
}

HWVX_TileCar* TypeCollector::GetTileCar(int index)
{
	return &hwvxTileCars.at(index);
}

//Get Count

int TypeCollector::GetPlayerCount()
{
	return hwvxPlayers.size();
}

int TypeCollector::GetVehicleCount()
{
	return hwvxVehicles.size();
}

int TypeCollector::GetTileCarCount()
{
	return hwvxTileCars.size();
}

//Get By Address

HWVX_Vehicle* TypeCollector::GetVehicleByAddress(int address)
{
	for (int i = 0; i < GetVehicleCount(); i++)
	{
		if (GetVehicle(i)->GetBaseAddress() == address) return GetVehicle(i);
	}
	return NULL;
}