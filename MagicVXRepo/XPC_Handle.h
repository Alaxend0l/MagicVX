#pragma once
#include <vector>
#include <fstream>
#include "XPC_Layout.h"

class XPC_Variable
{

};


class XPC_Header_Main
{
public:
	//Personal Values
	int Address_Header;
	int Address_File;
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

	XpcCarHeader xpcCarHeader;
	XpcWorldHeader xpcWorldHeader;
	std::vector<XpcCarEntry> carEntries;
	std::vector<int> entryAddresses;
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
	bool loaded = false;
	std::string filePath = "";
	std::vector<unsigned char> FileContents;
	std::vector<XPC_Header_Main> Headers;

	//Functions
	std::vector<unsigned char> ReadFile(std::string);

	void SetUpDatabase();
	int ReadInt(int);
	unsigned int ReadUnsignedInt(int);
	short ReadShort(int);
	char ReadChar(int);
};