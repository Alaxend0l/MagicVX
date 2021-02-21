#include "HWVX_Vehicle.h"

HWVX_Vehicle::HWVX_Vehicle()
{

}
HWVX_Vehicle::HWVX_Vehicle(int address)
{
    SetBaseAddress(address);

    address_stats = address + 0x24;

    address_currentX = address + 0x40;
    address_currentY = address + 0x44;
    address_currentZ = address + 0x48;

    address_rotationX = address + 0x50;
    address_rotationY = address + 0x54;
    address_rotationZ = address + 0x58;
    address_rotationW = address + 0x5C;

    address_currentHealth = address + 0x78;
    address_currentBoost = address + 0x3DC;

}

void HWVX_Vehicle::Update(int handle)
{
    //currentX = *FC->ReadFloat(address_currentX);
}