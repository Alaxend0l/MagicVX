#pragma once
class GearHuntObject
{
public:
	float PositionX;
	float PositionY;
	float PositionZ;

	//0 = Collectable, 1 = Destructible
	int ObjectType;
	int ObjectTypeIndex;

	int Address;

	bool IsGear = false;
	GearHuntObject();
};

