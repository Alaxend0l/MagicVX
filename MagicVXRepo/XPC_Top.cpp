#include "XPC_Top.h"

XPC_Top::XPC_Top()
{
	FileContents = NULL;
}

XPC_Top::XPC_Top(std::vector<unsigned char>& contents, bool _endian, int address)
{
	FileContents = &contents;
	xgcFlip = _endian;
	SetBaseAddress(address);

	InitValue("Entry ID", entryId, address + 0x00);
	InitValue("Object Type", objectType, address + 0x04);
	InitValue("Object Index", objectIndex, address + 0x08);

	InitValue("Unknown0", unknown0, address + 0x0C);
	InitValue("Unknown1", unknown1, address + 0x0D);
	InitValue("Unknown2", unknown2, address + 0x0E);
	InitValue("Unknown3", unknown3, address + 0x0F);

	InitValue("StreamSize", streamSize, address + 0x10);
	InitValue("Offset", offset, address + 0x14);

	
}

void XPC_Top::XPC_AddNextTable(int tableAddress)
{
	xpcCar = XPC_Car(*FileContents, xgcFlip, tableAddress);
}

void XPC_Top::Update()
{
	UpdateValue(entryId);
	UpdateValue(objectType);
	UpdateValue(objectIndex);
	UpdateValue(unknown0);
	UpdateValue(unknown1);
	UpdateValue(unknown2);
	UpdateValue(unknown3);
	UpdateValue(streamSize);
	UpdateValue(offset);
}