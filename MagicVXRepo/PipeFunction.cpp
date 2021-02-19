#include "PipeFunction.h"


PipeFunction::PipeFunction()
{
    offset = 0;
}

PipeFunction::PipeFunction(int function)
{
    offset = 0;
    Add(function);
    offset += 8;
}

void PipeFunction::SetArgSizeAndReturnSize(int argSize, int returnSize)
{
    offset = 4;
    Add(argSize);
    Add(returnSize);
    offset = argSize + 12;
}

bool PipeFunction::Add(int value, bool reverse)
{
    unsigned char byteArray[sizeof(value)];
    memcpy(byteArray, (const char*)&value, sizeof(value));

    if (offset + sizeof(value) > 1024) return false;

    int position = offset;

    for (int i = 0; i < sizeof(byteArray); i++)
    {
        if (reverse) buffer[offset + (sizeof(byteArray) - 1) - i] = byteArray[i];
        else buffer[offset + i] = byteArray[i];
    }

    offset += sizeof(value);

    return true;
}

bool PipeFunction::Add(char value, bool reverse)
{
    unsigned char byteArray[sizeof(value)];
    memcpy(byteArray, (const char*)&value, sizeof(value));

    if (offset + sizeof(value) > 1024) return false;

    int position = offset;

    for (int i = 0; i < sizeof(byteArray); i++)
    {
        if (reverse) buffer[offset + (sizeof(byteArray) - 1) - i] = byteArray[i];
        else buffer[offset + i] = byteArray[i];
    }

    offset += sizeof(value);

    return true;
}

bool PipeFunction::Add(float value, bool reverse)
{
    unsigned char byteArray[sizeof(value)];
    memcpy(byteArray, (const char*)&value, sizeof(value));

    if (offset + sizeof(value) > 1024) return false;

    int position = offset;

    for (int i = 0; i < sizeof(byteArray); i++)
    {
        if (reverse) buffer[offset + (sizeof(byteArray) - 1) - i] = byteArray[i];
        else buffer[offset + i] = byteArray[i];
    }

    offset += sizeof(value);

    return true;
}

bool PipeFunction::Add(double value, bool reverse)
{
    unsigned char byteArray[sizeof(value)];
    memcpy(byteArray, (const char*)&value, sizeof(value));

    if (offset + sizeof(value) > 1024) return false;

    int position = offset;

    for (int i = 0; i < sizeof(byteArray); i++)
    {
        if (reverse) buffer[offset + (sizeof(byteArray) - 1) - i] = byteArray[i];
        else buffer[offset + i] = byteArray[i];
    }

    offset += sizeof(value);

    return true;
}

bool PipeFunction::Add(int value)
{
    return Add(value, false);
}

bool PipeFunction::Add(char value)
{
    return Add(value, false);
}

bool PipeFunction::Add(float value)
{
    return Add(value, false);
}

bool PipeFunction::Add(double value)
{
    return Add(value, false);
}
