#pragma once
#include "HWVX_Generic.h"

class HWVX_Vehicle : public HWVX_Generic
{
public:

    bool isLoaded;
    int vehicleID;
    Proxy<float> velocityX;
    Proxy<float> velocityY;
    Proxy<float> velocityZ;
    Proxy<float> currentX;
    Proxy<float> currentY;
    Proxy<float> currentZ;
    Proxy<float> rotationX;
    Proxy<float> rotationY;
    Proxy<float> rotationZ;
    Proxy<float> rotationW;
    
    float spawnX;
    float spawnY;
    float spawnZ;

    Proxy<int> currentHealth;
    Proxy<int> currentBoost;
    int maxHealth;
    float vehicleMass;
    float vehicleGravity;

    int address_stats = 0x24;

    HWVX_Vehicle();
    HWVX_Vehicle(FunctionCaller*, int);
    
    void Update() override;
};



