#pragma once
#include "HWVX_Generic.h"

class HWVX_Vehicle : public HWVX_Generic
{
public:

    bool isLoaded;
    int vehicleID;
    Proxy<float> currentX;
    Proxy<float> currentY;
    Proxy<float> currentZ;
    Proxy<float> rotationX;
    Proxy<float> rotationY;
    Proxy<float> rotationZ;
    Proxy<float> rotationW;
    float velocityX;
    float velocityY;
    float velocityZ;
    float spawnX;
    float spawnY;
    float spawnZ;

    Proxy<int> currentHealth;
    Proxy<int> currentBoost;
    int maxHealth;
    float vehicleMass;
    float vehicleGravity;

    int address_stats = 0x24;
    //int address_vehicleID;
    int address_velocityX;
    int address_velocityY;
    int address_velocityZ;
    
    //int address_spawnX;
    //int address_spawnY;
    //int address_spawnZ;
    int address_currentHealth;
    int address_maxHealth;
    int address_currentBoost;
    int address_vehicleMass;
    int address_vehicleGravity;

    HWVX_Vehicle();
    HWVX_Vehicle(FunctionCaller*, int);
    
    void Update() override;
};



