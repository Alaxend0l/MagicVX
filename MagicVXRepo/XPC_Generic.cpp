#include "XPC_Generic.h"

int XPC_Generic::GetBaseAddress()
{
	return baseAddress;
}

void XPC_Generic::SetBaseAddress(int address)
{
	baseAddress = address;
}