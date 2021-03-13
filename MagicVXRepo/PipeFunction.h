
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>
#include <Windows.h>


class PipeFunction
{
public:
    unsigned char buffer[1024] = "";
    unsigned int offset;
    unsigned int address;

    bool Add(int, bool);
    bool Add(int);
    bool Add(byte, bool);
    bool Add(byte);
    bool Add(float, bool);
    bool Add(float);
    bool Add(double, bool);
    bool Add(double);

    void SetArgSizeAndReturnSize(int, int);

    PipeFunction();
    PipeFunction(int);
};
