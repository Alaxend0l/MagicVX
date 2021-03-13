#include "HWVX_TileCar.h"

HWVX_TileCar::HWVX_TileCar()
{

}
HWVX_TileCar::HWVX_TileCar(FunctionCaller* fcReference, int address)
{
    FC = fcReference;

    SetBaseAddress(address);

    InitFloat(spawnX, address + 0x00);
    InitFloat(spawnY, address + 0x04);
    InitFloat(spawnZ, address + 0x08);

    InitInt(carID, address + 0x30);

    InitByte(playerType, address + 0x35);
    InitByte(unknownVal, address + 0xd);

}

void HWVX_TileCar::Update()
{
    UpdateFloat(spawnX);
    UpdateFloat(spawnY);
    UpdateFloat(spawnZ);

    UpdateInt(carID);

    UpdateByte(playerType);
    UpdateByte(unknownVal);
}