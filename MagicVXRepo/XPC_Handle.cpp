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

        newHeader.Add0 = ReadInt(newHeader.Address_File + 0x00);
        newHeader.Add1 = ReadInt(newHeader.Address_File + 0x04);
        newHeader.Add2 = ReadInt(newHeader.Address_File + 0x08);
        newHeader.Add3 = ReadInt(newHeader.Address_File + 0x0C);
        newHeader.Add4 = ReadInt(newHeader.Address_File + 0x10);
        newHeader.Add5 = ReadInt(newHeader.Address_File + 0x14);
        newHeader.Add6 = ReadInt(newHeader.Address_File + 0x18);
        newHeader.Add7 = ReadInt(newHeader.Address_File + 0x1C);
        newHeader.Add8 = ReadInt(newHeader.Address_File + 0x20);
        newHeader.Add9 = ReadInt(newHeader.Address_File + 0x24);
        SetUpHeaderMain(newHeader);
        Headers.push_back(newHeader);
    }
}

void XPC_Handle::SetUpHeaderMain(XPC_Header_Main headerMain)
{

}

int XPC_Handle::ReadInt(int address)
{
    int returnValue = 0;
    memcpy(&returnValue, &FileContents[address], sizeof(int));
    return returnValue;
}