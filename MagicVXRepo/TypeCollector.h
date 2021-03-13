#pragma once

#include "HWVX_Player.h"
#include "HWVX_Vehicle.h"
#include "HWVX_TileCar.h"
#include "FunctionCaller.h"

class TypeCollector
{
protected:
	FunctionCaller* FC;
public:

	std::vector<HWVX_Player> hwvxPlayers;
	std::vector<HWVX_Vehicle> hwvxVehicles;
	std::vector<HWVX_TileCar> hwvxTileCars;

	TypeCollector();
	TypeCollector(FunctionCaller* FC);

	void ResetValues();
	void Update();
	
	void SetUpVehicles();
	void SetUpTileCars();
	void SetUpPlayers();

	void AddPlayer(HWVX_Player);
	void AddVehicle(HWVX_Vehicle);
	void AddTileCar(HWVX_TileCar);

	HWVX_Player* GetPlayer(int);
	HWVX_Vehicle* GetVehicle(int);
	HWVX_TileCar* GetTileCar(int);

	int GetPlayerCount();
	int GetVehicleCount();
	int GetTileCarCount();

	HWVX_Vehicle* GetVehicleByAddress(int);
};