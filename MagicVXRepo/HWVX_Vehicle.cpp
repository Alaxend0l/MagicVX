#include "HWVX_Vehicle.h"

HWVX_Vehicle::HWVX_Vehicle()
{

}
HWVX_Vehicle::HWVX_Vehicle(FunctionCaller* fcReference, int address)
{
    FC = fcReference;

    SetBaseAddress(address);

    address_stats = address + 0x24;

    InitFloat(velocityX, address + 0x00);
    InitFloat(velocityY, address + 0x04);
    InitFloat(velocityZ, address + 0x08);

    InitFloat(currentX, address + 0x40);
    InitFloat(currentY, address + 0x44);
    InitFloat(currentZ, address + 0x48);

    InitFloat(rotationX, address + 0x50);
    InitFloat(rotationY, address + 0x54);
    InitFloat(rotationZ, address + 0x58);
    InitFloat(rotationW, address + 0x5C);

    InitInt(currentHealth, address + 0x78);
    InitInt(currentBoost, address + 0x3DC);

}

void HWVX_Vehicle::Update()
{
    UpdateFloat(velocityX);
    UpdateFloat(velocityY);
    UpdateFloat(velocityZ);
    UpdateFloat(currentX);
    UpdateFloat(currentY);
    UpdateFloat(currentZ);
    UpdateFloat(rotationX);
    UpdateFloat(rotationY);
    UpdateFloat(rotationZ);
    UpdateFloat(rotationW);

    UpdateInt(currentHealth);
    UpdateInt(currentBoost);
    
}