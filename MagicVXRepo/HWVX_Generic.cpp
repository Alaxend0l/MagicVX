#include "HWVX_Generic.h"

int HWVX_Generic::GetBaseAddress()
{
	return baseAddress;
}

void HWVX_Generic::SetBaseAddress(int address)
{
	baseAddress = address;
}

void HWVX_Generic::SetFunctionCaller(FunctionCaller* fcReference)
{
	FC = fcReference;
}

void HWVX_Generic::UpdateInt(Proxy<int>& value)
{
    if (FC->IsForegroundProcess())
    {
        if (value.lock)
        {
            FC->WriteInt(value.address, value.currentValue);
        }
        else
        {
            value.SetValue(FC->ReadInt(value.address));
        }
    }
    else
    {
        if (value.CheckUpdate())  FC->WriteInt(value.address, value.currentValue);
    }
}

void HWVX_Generic::UpdateFloat(Proxy<float>& value)
{
    if (FC->IsForegroundProcess())
    {
        if (value.lock)
        {
            FC->WriteFloat(value.address, value.currentValue);
        }
        else
        {
            value.SetValue(FC->ReadFloat(value.address));
        }
        
    }
    else
    {
        if (value.CheckUpdate())  FC->WriteFloat(value.address, value.currentValue);
    }
}

void HWVX_Generic::InitInt(Proxy<int>& value, int address)
{
    value.address = address;
    value.SetValue(FC->ReadInt(address));
}

void HWVX_Generic::InitFloat(Proxy<float>& value, int address)
{
    value.address = address;
    value.SetValue(FC->ReadFloat(address));
}