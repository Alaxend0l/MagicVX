#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include "Proxy.h"


// Typed up by N/A, not exactly up to C standards (since I should be doing local references in functions instead)


// General container documents

struct XpcTableEntry {
	unsigned int entryId;
	unsigned int objectType; // Type of object stored
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
	unsigned int objectIndex;
	short unknown2[2]; // pretty sure it's signed.
	unsigned int streamSize;
	unsigned int offset; //from end of xpc table.
};

struct XpcHeader {
	char unknown1[8]; // I think these are resource id tags
	unsigned int entryId; // Same as in xpc emtry
	unsigned int count; //Number of things in the table
};


//specific file documentation

struct XpcImportThingie {
	char moduleName[12]; // TODO: idk if \x00 is considered. If it's fixed then last 4 bytes is float32 or long int.
	unsigned long int unknown1[2]; // Think 1st index is the entry in the corresponding *.xpc package
};

struct XpcCarEntry {
	unsigned int offset; // offset & 0xf == 0; (from end of table)
	unsigned int size;
	char unknown1[4]; // Seems to be unsigned int as -1 and 0 seen
	int unknown2; // seen values: 0x5622, 0x2b11
	short int unknown3; // Might be wrong. 
	char unknown[12]; // 12 bytes, can't tell if float32 or long int.
};

struct XpcRiffHeader {
	char riffBytes[4]; //Spells RIFF
	unsigned int unknown_size; //Possibly size?
	char sndbBytes[4]; //Spells sndb
	unsigned int unknown1;
	unsigned int count;
	unsigned int unknown2;
	char UninitializedData[8]; //Full of Cs
};

struct XpcThingHeader {
	int offset;
	short textureID;
	short flag;
	
};

struct XpcItemHeader {
	//54 Bytes between start and XpcImportThingie
	char unknown[54];
	XpcImportThingie importLink[2];
};

struct XpcTopHeader {
	unsigned int AddressPtr0;
	unsigned int AddressPtr1;
	unsigned int AddressPtr2;
	unsigned int entryCnt;
	unsigned int unknownInt3;
	unsigned int unknownInt4;
	unsigned int unknownInt5;
	unsigned int AddressPtr6;
	unsigned int textureCnt;
	unsigned int entryCnt2; //same as entryCnt, this might be x2 different structs.
	unsigned int unknownInt8;
	unsigned int unknownInt9;
	unsigned int unknownInt10;
	unsigned int unknownInt11;
	unsigned int unknownInt12;
	unsigned int unknownInt13;
	unsigned int unknownInt14;
	unsigned int unknownInt15;
	unsigned int unknownInt16;
	unsigned int unknownInt17;
	unsigned int musicAddress;
	struct XpcImportThingie importLink[2]; // may also be possible it's empty..
	//unsigned long int OffsetsToEntries[entryCnt];
	//files stary here
};