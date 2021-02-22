#include "XPC_Handle.h"


std::vector<unsigned char> XPC_Handle::ReadFile(std::string filename)
{
    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<unsigned char> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
        std::istream_iterator<unsigned char>(file),
        std::istream_iterator<unsigned char>());

    filePath = filename;
    loaded = true;
    size = fileSize;
    return vec;
}

void XPC_Handle::SetUpDatabase()
{
    address_tmp = 0xC;
    entryID = ReadInt(0x8);
    entries = ReadInt(address_tmp);
    address_body = address_tmp + (entries * 0x18);
    address_tmp = 0x10;

    Headers.clear();
    
    for (int i = 0; i < entries; i++)
    {
        XPC_Header_Main newHeader;
        newHeader.Address_Header = address_tmp + (i * 0x18);
        newHeader.ID = ReadInt(newHeader.Address_Header + 0x8);
        newHeader.Size = ReadInt(newHeader.Address_Header + 0x10);
        newHeader.Offset = ReadInt(newHeader.Address_Header + 0x14);

        newHeader.Address_File = address_body + newHeader.Offset;

        newHeader.xpcTableEntry.entryId = ReadUnsignedInt(newHeader.Address_Header + 0x0);
        newHeader.xpcTableEntry.objectType = ReadUnsignedInt(newHeader.Address_Header + 0x4);
        newHeader.xpcTableEntry.objectIndex = ReadUnsignedInt(newHeader.Address_Header + 0x8);
        newHeader.xpcTableEntry.unknown2[0] = ReadShort(newHeader.Address_Header + 0xC);
        newHeader.xpcTableEntry.unknown2[1] = ReadShort(newHeader.Address_Header + 0xE);
        newHeader.xpcTableEntry.streamSize = ReadUnsignedInt(newHeader.Address_Header + 0x10);
        newHeader.xpcTableEntry.offset = ReadUnsignedInt(newHeader.Address_Header + 0x14);
        
        Headers.push_back(newHeader);
    }
}

int XPC_Handle::ReadInt(int address)
{
    int returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    return returnValue;
}

unsigned int XPC_Handle::ReadUnsignedInt(int address)
{
    unsigned int returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    return returnValue;
}

short XPC_Handle::ReadShort(int address)
{
    short returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    return returnValue;
}