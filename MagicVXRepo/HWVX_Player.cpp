#include "HWVX_Player.h"

HWVX_Player::HWVX_Player()
{
	Active = false;
	
}

HWVX_Player::HWVX_Player(int startAddress)
{
	Active = true;
	SetBaseAddress(startAddress);
	//playerVehicle = HWVX_Vehicle(startAddress + 0x2C);

}