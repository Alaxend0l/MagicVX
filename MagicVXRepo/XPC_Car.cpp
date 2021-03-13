#include "XPC_Car.h"

XPC_Car::XPC_Car()
{
	FileContents = NULL;
}

XPC_Car::XPC_Car(std::vector<unsigned char>& contents, bool _endian, int address)
{
	FileContents = &contents;
	xgcFlip = _endian;
	SetBaseAddress(address);

	InitValue("Value00", AddressPtr0, address + 0x00);
	InitValue("Value01", AddressPtr1, address + 0x04);
	InitValue("Entry Count", entryCnt, address + 0x08);
	InitValue("Value03", unknownInt3, address + 0x0C);
	InitValue("Value04", unknownInt4, address + 0x10);
	InitValue("Count For Something", unknownInt5, address + 0x14);
	InitValue("Value06", AddressPtr6, address + 0x18);
	InitValue("Texture Count", textureCnt, address + 0x1C);
	InitValue("Entry Count 2", entryCnt2, address + 0x20);
	InitValue("Value08", unknownInt8, address + 0x24);
	InitValue("Value09", unknownInt9, address + 0x28);
	InitValue("Value10", unknownInt10, address + 0x2C);
	InitValue("Value11", unknownInt11, address + 0x30);
	InitValue("Value12", unknownInt12, address + 0x34);
	InitValue("Value13", unknownInt13, address + 0x38);
	InitValue("Value14", unknownInt14, address + 0x3C);
	InitValue("Value15", unknownInt15, address + 0x40);
	InitValue("Value16", unknownInt16, address + 0x44);
	InitValue("Value17", unknownInt17, address + 0x48);
	InitValue("Music Address", musicAddress, address + 0x4C);


}

void XPC_Car::Update()
{
	UpdateValue(AddressPtr0);
	UpdateValue(AddressPtr1);
	UpdateValue(entryCnt);
	UpdateValue(unknownInt3);
	UpdateValue(unknownInt4);
	UpdateValue(unknownInt5);
	UpdateValue(AddressPtr6);
	UpdateValue(textureCnt);
	UpdateValue(entryCnt2);
	UpdateValue(unknownInt8);
	UpdateValue(unknownInt9);
	UpdateValue(unknownInt10);
	UpdateValue(unknownInt11);
	UpdateValue(unknownInt12);
	UpdateValue(unknownInt13);
	UpdateValue(unknownInt14);
	UpdateValue(unknownInt15);
	UpdateValue(unknownInt16);
	UpdateValue(unknownInt17);
	UpdateValue(musicAddress);
}
