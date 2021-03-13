#pragma once
#include "HWVX_Generic.h"

class HWVX_TileCar : public HWVX_Generic
{
public:
    Proxy<float> spawnX;
    Proxy<float> spawnY;
    Proxy<float> spawnZ;

    Proxy<int> carID;

    Proxy<byte> playerType;
    Proxy<byte> unknownVal;

    HWVX_TileCar();
    HWVX_TileCar(FunctionCaller*, int);

    void Update() override;
};

