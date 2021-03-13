#include "HWVX_Player.h"

HWVX_Player::HWVX_Player()
{
	Active = false;
	
}

HWVX_Player::HWVX_Player(FunctionCaller* fcReference, int startAddress)
{
	FC = fcReference;
	Active = true;
	SetBaseAddress(startAddress);
	//playerVehicle = HWVX_Vehicle(fcReference, startAddress + 0x2C);
	InitInt(PlayerType, startAddress + 0x20);
}

void HWVX_Player::Update()
{
	//UpdateInt(PlayerType);

}