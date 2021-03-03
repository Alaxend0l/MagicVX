#pragma once
#include "HWVX_Generic.h"
#include "HWVX_Vehicle.h"

class HWVX_Player : public HWVX_Generic
{
public:
	//This is an object representing a player in HWVX. It applies to both human players and AI.
	bool Active = false; //Represents whether the player is currently active.
	int Address_Vehicle = 0x2C; //This is the address of a player's vehicle.
	int Updates = 0; //Every frame, this variable is checked. If changes are made to the player, this number increases, so in-game changes are necessary.

	//TEMP: This is mostly here just to ensure this stuff works.

	int StuntPoints = 0;
	int Kills = 0;

	HWVX_Vehicle* playerVehicle;

	HWVX_Player();
	HWVX_Player(FunctionCaller*, int);

};

