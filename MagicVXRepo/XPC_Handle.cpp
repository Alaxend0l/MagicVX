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
        newHeader.Type = ReadInt(newHeader.Address_Header + 0x4);
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

        int baseAddress = 0;
        int tableOffset = 0;
        int offset = 0;
        int finalAddress = 0;
        switch (newHeader.Type)
        {
        case 0: //Car
            baseAddress = newHeader.Address_File + 0x7C;
            tableOffset = 0x20;

            newHeader.xpcCarHeader.AddressPtr0 = ReadInt(newHeader.Address_File + 0x0);
            newHeader.xpcCarHeader.AddressPtr1 = ReadInt(newHeader.Address_File + 0x4);
            newHeader.xpcCarHeader.AddressPtr2 = ReadInt(newHeader.Address_File + 0x8);
            newHeader.xpcCarHeader.entryCnt = ReadUnsignedInt(newHeader.Address_File + 0xC);
            newHeader.xpcCarHeader.unknownInt3 = ReadInt(newHeader.Address_File + 0x10);
            newHeader.xpcCarHeader.unknownInt4 = ReadInt(newHeader.Address_File + 0x14);
            newHeader.xpcCarHeader.unknownInt5 = ReadInt(newHeader.Address_File + 0x18);
            newHeader.xpcCarHeader.AddressPtr6 = ReadInt(newHeader.Address_File + 0x1C);
            newHeader.xpcCarHeader.textureCnt = ReadInt(newHeader.Address_File + 0x20); 
            newHeader.xpcCarHeader.entryCnt2 = ReadUnsignedInt(newHeader.Address_File + 0x24);
            newHeader.xpcCarHeader.unknownInt8 = ReadInt(newHeader.Address_File + 0x28);
            newHeader.xpcCarHeader.unknownInt9 = ReadInt(newHeader.Address_File + 0x2C);
            newHeader.xpcCarHeader.unknownInt10 = ReadInt(newHeader.Address_File + 0x30);
            newHeader.xpcCarHeader.unknownInt11 = ReadInt(newHeader.Address_File + 0x34);
            newHeader.xpcCarHeader.unknownInt12 = ReadInt(newHeader.Address_File + 0x38);
            newHeader.xpcCarHeader.unknownInt13 = ReadInt(newHeader.Address_File + 0x3C);
            newHeader.xpcCarHeader.unknownInt14 = ReadInt(newHeader.Address_File + 0x40);
            newHeader.xpcCarHeader.unknownInt15 = ReadInt(newHeader.Address_File + 0x44);
            newHeader.xpcCarHeader.unknownInt16 = ReadInt(newHeader.Address_File + 0x48);
            newHeader.xpcCarHeader.unknownInt17 = ReadInt(newHeader.Address_File + 0x4C);
            newHeader.xpcCarHeader.unknownInt18 = ReadInt(newHeader.Address_File + 0x50);

            
            newHeader.carEntries.clear();
            newHeader.entryAddresses.clear();
            for (int j = 0; j < newHeader.xpcCarHeader.entryCnt; j++)
            {
                //Base Header
                offset = ReadInt(baseAddress + j * 4);
                XpcCarEntry xpcCarEntry;
                xpcCarEntry.offset = ReadInt(baseAddress + offset + tableOffset + 0x0);
                xpcCarEntry.size = ReadInt(baseAddress + offset + tableOffset + 0x4);
                finalAddress = baseAddress + 0x20 + xpcCarEntry.offset;
                newHeader.carEntries.push_back(xpcCarEntry);
                newHeader.entryAddresses.push_back(finalAddress);
            }
            
            newHeader.Address_Unknown0 = (baseAddress + tableOffset) + newHeader.xpcCarHeader.AddressPtr0;
            newHeader.Address_Unknown1 = (baseAddress + tableOffset) + newHeader.xpcCarHeader.AddressPtr1;
            newHeader.Address_Unknown2 = (baseAddress + tableOffset) + newHeader.xpcCarHeader.AddressPtr2;
            newHeader.Address_Texture = (baseAddress + tableOffset) + newHeader.xpcCarHeader.AddressPtr6;
            break;
        case 4: //World
            baseAddress = newHeader.Address_File + 0x7C;
            tableOffset = 0x120;

            newHeader.xpcWorldHeader.AddressPtr0 = ReadInt(newHeader.Address_File + 0x0);
            newHeader.xpcWorldHeader.AddressPtr1 = ReadInt(newHeader.Address_File + 0x4);
            newHeader.xpcWorldHeader.AddressPtr2 = ReadInt(newHeader.Address_File + 0x8);
            newHeader.xpcWorldHeader.entryCnt = ReadUnsignedInt(newHeader.Address_File + 0xC);
            newHeader.xpcWorldHeader.unknownInt3 = ReadInt(newHeader.Address_File + 0x10);
            newHeader.xpcWorldHeader.unknownInt4 = ReadInt(newHeader.Address_File + 0x14);
            newHeader.xpcWorldHeader.unknownInt5 = ReadInt(newHeader.Address_File + 0x18);
            newHeader.xpcWorldHeader.AddressPtr6 = ReadInt(newHeader.Address_File + 0x1C);
            newHeader.xpcWorldHeader.textureCnt = ReadInt(newHeader.Address_File + 0x20);
            newHeader.xpcWorldHeader.entryCnt2 = ReadUnsignedInt(newHeader.Address_File + 0x24);
            newHeader.xpcWorldHeader.unknownInt8 = ReadInt(newHeader.Address_File + 0x28);
            newHeader.xpcWorldHeader.unknownInt9 = ReadInt(newHeader.Address_File + 0x2C);
            newHeader.xpcWorldHeader.unknownInt10 = ReadInt(newHeader.Address_File + 0x30);
            newHeader.xpcWorldHeader.unknownInt11 = ReadInt(newHeader.Address_File + 0x34);
            newHeader.xpcWorldHeader.unknownInt12 = ReadInt(newHeader.Address_File + 0x38);
            newHeader.xpcWorldHeader.unknownInt13 = ReadInt(newHeader.Address_File + 0x3C);
            newHeader.xpcWorldHeader.unknownInt14 = ReadInt(newHeader.Address_File + 0x40);
            newHeader.xpcWorldHeader.unknownInt15 = ReadInt(newHeader.Address_File + 0x44);
            newHeader.xpcWorldHeader.unknownInt16 = ReadInt(newHeader.Address_File + 0x48);
            newHeader.xpcWorldHeader.unknownInt17 = ReadInt(newHeader.Address_File + 0x4C);
            newHeader.xpcWorldHeader.unknownInt18 = ReadInt(newHeader.Address_File + 0x50);

            newHeader.carEntries.clear();
            newHeader.entryAddresses.clear();
            for (int j = 0; j < newHeader.xpcWorldHeader.entryCnt; j++)
            {
                //Base Header
                offset = ReadInt(baseAddress + j * 4);
                XpcCarEntry xpcCarEntry;
                xpcCarEntry.offset = ReadInt(baseAddress + offset + tableOffset + 0x0);
                xpcCarEntry.size = ReadInt(baseAddress + offset + tableOffset + 0x4);
                finalAddress = baseAddress + 0x20 + xpcCarEntry.offset;
                newHeader.carEntries.push_back(xpcCarEntry);
                newHeader.entryAddresses.push_back(finalAddress);
            }

            newHeader.Address_Unknown0 = (baseAddress + tableOffset) + newHeader.xpcWorldHeader.unknownInt18;
            newHeader.Address_Unknown1 = (baseAddress + tableOffset) + newHeader.xpcWorldHeader.AddressPtr1;
            newHeader.Address_Unknown2 = (baseAddress + tableOffset) + newHeader.xpcWorldHeader.AddressPtr2;
            newHeader.Address_Texture = (baseAddress + tableOffset) + newHeader.xpcWorldHeader.AddressPtr6;


            break;
        }
        
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

char XPC_Handle::ReadChar(int address)
{
    char returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    return returnValue;
}