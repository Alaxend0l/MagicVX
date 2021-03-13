#pragma once
#include <vector>
#include <fstream>
#include "XPC_Layout.h"
#include "XPC_Top.h"

class XPC_Variable
{

};


class XPC_Header_Main
{
public:
	//Personal Values
	int Address_Header;
	int Address_File;
	int Address_SFX;
	int Address_Music;
	int Address_Unknown0;
	int Address_Unknown1;
	int Address_Unknown2;
	int Address_Texture;
	int ID;
	int Size;
	int Offset;
	int Type;

	//Inner Values
	
	XpcTableEntry xpcTableEntry;

	XpcTopHeader xpcTopHeader;
	XpcRiffHeader xpcRiffHeader;
	std::vector<XpcCarEntry> carEntries;
	std::vector<XpcCarEntry> riffEntries;
	std::vector<XpcThingHeader> thingHeaders;
	std::vector<int> entryAddresses;
	std::vector<int> entryAddressesRiff;
	std::vector<int> entryAddressesThings;
	XpcItemHeader xpcItemHeader;
};



class XPC_Handle
{
public:
	//Variables
	int size = 0;
	int entries = 0;
	int address_body = 0;
	int address_tmp = 0;
	int entryID;
	bool xgcFlip = true;
	bool loaded = false;
	std::string filePath = "";
	std::vector<unsigned char> FileContents;
	std::vector<XPC_Header_Main> Headers;
	std::vector<XPC_Top> TopEntries;

	//Functions
	std::vector<unsigned char> ReadFile(std::string);

	void ReadTopHeader(XpcTopHeader&, int);
	void SetUpDatabase();
	int GetTableLength(int);
	int ReadInt(int);
	unsigned int ReadUnsignedInt(int);
	short ReadShort(int);
	char ReadChar(int);

	template <typename T>
	void SwapEndian(T&);
};


template <typename T>
void XPC_Handle::SwapEndian(T& val) {
	unsigned char byteArray[sizeof(val)];
	unsigned char finishedByteArray[sizeof(val)];
	memcpy(byteArray, (const char*)&val, sizeof(val));

	for (int i = 0; i < sizeof(byteArray); i++)
	{
		finishedByteArray[(sizeof(byteArray) - 1) - i] = byteArray[i];
	}

	memcpy(&val, finishedByteArray, sizeof(val));
}
