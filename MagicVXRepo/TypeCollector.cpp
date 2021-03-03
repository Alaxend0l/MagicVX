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

void TypeCollector::AddPlayer(HWVX_Player player)
{
	hwvxPlayers.push_back(player);
}

void TypeCollector::AddVehicle(HWVX_Vehicle vehicle)
{
	hwvxVehicles.push_back(vehicle);
}

HWVX_Player* TypeCollector::GetPlayer(int index)
{
	return &hwvxPlayers.at(index);
}

HWVX_Vehicle* TypeCollector::GetVehicle(int index)
{
	return &hwvxVehicles.at(index);
}

int TypeCollector::GetPlayerCount()
{
	return hwvxPlayers.size();
}

int TypeCollector::GetVehicleCount()
{
	return hwvxVehicles.size();
}

HWVX_Vehicle* TypeCollector::GetVehicleByAddress(int address)
{
	for (int i = 0; i < GetVehicleCount(); i++)
	{
		if (GetVehicle(i)->GetBaseAddress() == address) return GetVehicle(i);
	}
	return NULL;
}