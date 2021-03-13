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
    char endianTest = ReadChar(0);
    xgcFlip = (endianTest == 2);

    entryID = ReadInt(0x8);
    entries = ReadInt(0xC);
    address_body = 0x10 + (entries * 0x18);
    

    Headers.clear();
    TopEntries.clear();

    /*
    */
    
    for (int i = 0; i < entries; i++)
    {
        XPC_Top newTop = XPC_Top(FileContents, xgcFlip, 0x10 + (i * 0x18));
        newTop.XPC_AddNextTable(address_body + newTop.offset.currentValue);
        TopEntries.push_back(newTop);
        /*
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

        baseAddress = newHeader.Address_File + 0x7C;

        ReadTopHeader(newHeader.xpcTopHeader, newHeader.Address_File);

        tableOffset = GetTableLength(newHeader.xpcTopHeader.entryCnt);
        newHeader.Address_SFX = baseAddress;

        newHeader.carEntries.clear();
        newHeader.entryAddresses.clear();
        for (int j = 0; j < newHeader.xpcTopHeader.entryCnt; j++)
        {
            //Base Header
            offset = ReadInt(baseAddress + j * 4);
            XpcCarEntry xpcCarEntry;
            xpcCarEntry.offset = ReadInt(baseAddress + offset + tableOffset + 0x0);
            xpcCarEntry.size = ReadInt(baseAddress + offset + tableOffset + 0x4);
            finalAddress = baseAddress + tableOffset + xpcCarEntry.offset;
            newHeader.carEntries.push_back(xpcCarEntry);
            newHeader.entryAddresses.push_back(finalAddress);
        }

        switch (newHeader.Type)
        {
        case 0: //Car
            
            
            newHeader.Address_Unknown0 = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr0;
            newHeader.Address_Unknown1 = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr1;
            newHeader.Address_Texture = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr6;
            break;
        case 4: //World
            

            newHeader.Address_Music = (baseAddress + tableOffset) + newHeader.xpcTopHeader.musicAddress;
            newHeader.Address_Unknown0 = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr0;
            newHeader.Address_Unknown1 = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr1;
            newHeader.Address_Unknown2 = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr2;
            newHeader.Address_Texture = (baseAddress + tableOffset) + newHeader.xpcTopHeader.AddressPtr6;

            //Address_Unknown0 points to something
            newHeader.riffEntries.clear();
            newHeader.entryAddressesRiff.clear();

            newHeader.xpcRiffHeader.unknown_size = ReadInt(newHeader.Address_Music + 0x4);
            newHeader.xpcRiffHeader.count = ReadInt(newHeader.Address_Music + 0x10);

            int dataStart = newHeader.Address_Music + 0x20 + newHeader.xpcRiffHeader.count * 0x20;

            for (int j = 0; j < newHeader.xpcRiffHeader.count; j++)
            {
                //Riff Header
                int entryStart = newHeader.Address_Music + 0x20 + j * 0x20;
                XpcCarEntry xpcCarEntry;
                xpcCarEntry.offset = ReadInt(entryStart + 0x0);
                xpcCarEntry.size = ReadInt(entryStart + 0x4);
                finalAddress = dataStart + xpcCarEntry.offset;
                newHeader.riffEntries.push_back(xpcCarEntry);
                newHeader.entryAddressesRiff.push_back(finalAddress);
            }

            dataStart = newHeader.Address_Unknown2;
            for (int j = 0; j < newHeader.xpcTopHeader.unknownInt4; j++)
            {
                //CollectableHeader
                int entryStart = dataStart + j * 0x8;
                XpcThingHeader xpcThingHeader;
                xpcThingHeader.offset = ReadInt(entryStart + 0x0);
                xpcThingHeader.textureID = ReadShort(entryStart + 0x4);
                xpcThingHeader.flag = ReadShort(entryStart + 0x6);
                finalAddress = dataStart + xpcThingHeader.offset;
                newHeader.thingHeaders.push_back(xpcThingHeader);
                newHeader.entryAddressesThings.push_back(finalAddress);
            }
            break;
        }
        
        Headers.push_back(newHeader);
        */

    }
}

void XPC_Handle::ReadTopHeader(XpcTopHeader& header, int fileOffset)
{
    header.AddressPtr0 = ReadInt(fileOffset + 0x0);
    header.AddressPtr1 = ReadInt(fileOffset + 0x4);
    header.AddressPtr2 = ReadInt(fileOffset + 0x8);
    header.entryCnt = ReadUnsignedInt(fileOffset + 0xC);
    header.unknownInt3 = ReadInt(fileOffset + 0x10);
    header.unknownInt4 = ReadInt(fileOffset + 0x14);
    header.unknownInt5 = ReadInt(fileOffset + 0x18);
    header.AddressPtr6 = ReadInt(fileOffset + 0x1C);
    header.textureCnt = ReadInt(fileOffset + 0x20);
    header.entryCnt2 = ReadUnsignedInt(fileOffset + 0x24);
    header.unknownInt8 = ReadInt(fileOffset + 0x28);
    header.unknownInt9 = ReadInt(fileOffset + 0x2C);
    header.unknownInt10 = ReadInt(fileOffset + 0x30);
    header.unknownInt11 = ReadInt(fileOffset + 0x34);
    header.unknownInt12 = ReadInt(fileOffset + 0x38);
    header.unknownInt13 = ReadInt(fileOffset + 0x3C);
    header.unknownInt14 = ReadInt(fileOffset + 0x40);
    header.unknownInt15 = ReadInt(fileOffset + 0x44);
    header.unknownInt16 = ReadInt(fileOffset + 0x48);
    header.unknownInt17 = ReadInt(fileOffset + 0x4C);
    header.musicAddress = ReadInt(fileOffset + 0x50);
}

int XPC_Handle::ReadInt(int address)
{
    int returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    if (xgcFlip) SwapEndian(returnValue);
    return returnValue;
}

unsigned int XPC_Handle::ReadUnsignedInt(int address)
{
    unsigned int returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    if (xgcFlip) SwapEndian(returnValue);
    return returnValue;
}

short XPC_Handle::ReadShort(int address)
{
    short returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    if (xgcFlip) SwapEndian(returnValue);
    return returnValue;
}

char XPC_Handle::ReadChar(int address)
{
    char returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(returnValue));
    if (xgcFlip) SwapEndian(returnValue);
    return returnValue;
}

int XPC_Handle::GetTableLength(int count)
{
    /*
    * Memory for the tables in HWVX seem to be allocated in chunks of 0x20 bytes.
    * If not filled, it's filled with zeros.
    * If filled but short, it shifts the offsets up
    */

    const int chunkSize = 0x20;
    int countSize = count * 0x4;
    int returnSize = 0;
    for (; returnSize < countSize; returnSize += chunkSize) {}
    return returnSize;
}
