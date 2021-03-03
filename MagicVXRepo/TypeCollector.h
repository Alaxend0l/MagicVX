#pragma once

#include "HWVX_Player.h"
#include "HWVX_Vehicle.h"
#include "FunctionCaller.h"

class TypeCollector
{
protected:
	FunctionCaller* FC;
public:

	std::vector<HWVX_Player> hwvxPlayers;
	std::vector<HWVX_Vehicle> hwvxVehicles;

	TypeCollector();
	TypeCollector(FunctionCaller* FC);

	void ResetValues();
	
	void SetUpVehicles();
	void SetUpPlayers();

	void AddPlayer(HWVX_Player);
	void AddVehicle(HWVX_Vehicle);

	HWVX_Player* GetPlayer(int);
	HWVX_Vehicle* GetVehicle(int);

	int GetPlayerCount();
	int GetVehicleCount();

	HWVX_Vehicle* GetVehicleByAddress(int);
};