#pragma once
#include <vector>
#include <fstream>

struct XPC_Header_Interior
{
	int Address_Header;
	int Count;
};

struct XPC_Header_Main
{
	int Address_Header;
	int Address_File;
	int ID;
	int Size;
	int Offset;
	int Add0;
	int Add1;
	int Add2;
	int Add3;
	int Add4;
	int Add5;
	int Add6;
	int Add7;
	int Add8;
	int Add9;
	std::vector<XPC_Header_Interior> InteriorHeaders;
};



class XPC_Handle
{
public:
	//Variables
	int size = 0;
	int entries = 0;
	int address_body = 0;
	int address_tmp = 0;
	bool loaded = false;
	std::string filePath = "";
	std::vector<unsigned char> FileContents;
	std::vector<XPC_Header_Main> Headers;

	//Functions
	std::vector<unsigned char> ReadFile(std::string);

	void SetUpDatabase();
	void SetUpHeaderMain(XPC_Header_Main);
	int ReadInt(int);
};