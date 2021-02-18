
#include <array>
#include <memory>
#include <type_traits>
#include <iostream>
#include <iomanip>


class PipeFunction
{
public:
    unsigned char buffer[1024];
    unsigned int offset;

    bool Add(int, bool);
    bool Add(int);
    bool Add(char, bool);
    bool Add(char);
    bool Add(float, bool);
    bool Add(float);
    bool Add(double, bool);
    bool Add(double);

    PipeFunction();
};
