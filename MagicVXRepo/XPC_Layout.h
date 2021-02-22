#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

// Typed up by N/A, not exactly up to C standards (since I should be doing local references in functions instead)


// General container documents

struct XpcTableEntry {
	unsigned int entryId;
	unsigned int objectType; // Type of object stored
	/*
	* 0 = car
	* 1 = brief
	* 2 = item
	* 3 = texture
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

struct XpcCarStream {
	char unknown1[8];
	unsigned long entryCnt;
	int unknown2[5];
	unsigned long entryCnt2; //same as entryCnt, this might be x2 different structs.
	int unknown3[11];
	struct XpcImportThingie importLink[2]; // may also be possible it's empty..
	//unsigned long int OffsetsToEntries[entryCnt];
	struct XpcCarEntry xpcCarEntries[60];//at least 60 slots, might be hardcoded.
	//files stary here
};
