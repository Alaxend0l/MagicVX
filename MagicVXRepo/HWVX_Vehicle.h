#pragma once
#include "HWVX_Generic.h"

class HWVX_Vehicle : public HWVX_Generic
{
public:

    bool isLoaded;
    int vehicleID;
    float currentX;
    float currentY;
    float currentZ;
    float rotationX;
    float rotationY;
    float rotationZ;
    float rotationW;
    float velocityX;
    float velocityY;
    float velocityZ;
    float spawnX;
    float spawnY;
    float spawnZ;
    int currentHealth;
    int maxHealth;
    int currentBoost;
    float vehicleMass;
    float vehicleGravity;

    int address_stats = 0x24;
    //int address_vehicleID;
    int address_velocityX;
    int address_velocityY;
    int address_velocityZ;
    int address_currentX;
    int address_currentY;
    int address_currentZ;
    int address_rotationX;
    int address_rotationY;
    int address_rotationZ;
    int address_rotationW;
    
    //int address_spawnX;
    //int address_spawnY;
    //int address_spawnZ;
    int address_currentHealth;
    int address_maxHealth;
    int address_currentBoost;
    int address_vehicleMass;
    int address_vehicleGravity;

    HWVX_Vehicle();
    HWVX_Vehicle(int);
    
    void Update(int) override;
};



