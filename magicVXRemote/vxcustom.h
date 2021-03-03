#pragma once

#include "vxgame.h"
#include "vxpatch.h" 

class MagicVX {
public:
	// Disables mouse input and enables the cursor
	static void EnableMouse();

	static void EnableCheats();

	// Gives an item to the local car
	static void GiveItem(Car* car, int weaponIndex);

	static int LoadCar(int carIndex);

	static int LoadItem(int itemIndex);

	static void PlayInterface(int index);
};