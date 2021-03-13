#pragma once
#include "XPC_Generic.h"
#include "XPC_Car.h"

class XPC_Top : XPC_Generic
{
public:
	Proxy<unsigned int> entryId;
	Proxy<int> objectType; // Type of object stored
	/*
	* 0 = car
	* 1 = brief
	* 2 = item
	* 3 = ???
	* 4 = world
	* 5 = colliders
	* 6 = world texture
	* 7 = geometry
	* 8 = share
	*/
	Proxy<unsigned int> objectIndex;
	Proxy<char> unknown0;
	Proxy<char> unknown1;
	Proxy<char> unknown2;
	Proxy<char> unknown3;
	Proxy<unsigned int> streamSize;
	Proxy<unsigned int> offset;

	XPC_Car xpcCar;

	XPC_Top();
	XPC_Top(std::vector<unsigned char>&, bool, int);

	void XPC_AddNextTable(int);

	void Update();
};

