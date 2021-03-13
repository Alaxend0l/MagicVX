#pragma once
#include "XPC_Generic.h"
#include "Proxy.h"

class XPC_Car : XPC_Generic
{
public:
	Proxy<unsigned int> AddressPtr0;
	Proxy<unsigned int> AddressPtr1;
	Proxy<unsigned int> entryCnt;
	Proxy<unsigned int> unknownInt3;
	Proxy<unsigned int> unknownInt4;
	Proxy<unsigned int> unknownInt5;
	Proxy<unsigned int> AddressPtr6;
	Proxy<unsigned int> textureCnt;
	Proxy<unsigned int> entryCnt2; //same as entryCnt, this might be x2 different structs.
	Proxy<unsigned int> unknownInt8;
	Proxy<unsigned int> unknownInt9;
	Proxy<unsigned int> unknownInt10;
	Proxy<unsigned int> unknownInt11;
	Proxy<unsigned int> unknownInt12;
	Proxy<unsigned int> unknownInt13;
	Proxy<unsigned int> unknownInt14;
	Proxy<unsigned int> unknownInt15;
	Proxy<unsigned int> unknownInt16;
	Proxy<unsigned int> unknownInt17;
	Proxy<unsigned int> musicAddress;

	XPC_Car();
	XPC_Car(std::vector<unsigned char>&, bool, int);

	void Update();
};

