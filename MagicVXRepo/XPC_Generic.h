#pragma once

#include "Proxy.h"
#include <vector>

class XPC_Generic
{
protected:
	bool xgcFlip;
	int baseAddress = 0;
	std::vector<unsigned char>* FileContents;
public:
	int GetBaseAddress();
	void SetBaseAddress(int);

	template <typename T>
	void InitValue(std::string, Proxy<T>&, int);

	template <typename T>
	T GetValue(Proxy<T>&);

	template <typename T>
	void UpdateValue(Proxy<T>&);

	template <typename T>
	void SwapEndian(T&);

	//void UpdateInt(Proxy<int>&);
	//void UpdateFloat(Proxy<float>&);
	//void UpdateByte(Proxy<byte>&);

	//void InitInt(Proxy<int>&, int);
	//void InitFloat(Proxy<float>&, int);
	//void InitByte(Proxy<byte>&, int);
};

template<typename T>
void XPC_Generic::InitValue(std::string name, Proxy<T>& value, int address)
{
	value.title = name;
	value.address = address;
	value.InitValue(GetValue(value));
}

template<typename T>
T XPC_Generic::GetValue(Proxy<T>& value)
{
	T returnValue;
	unsigned char byteArray[sizeof(T)];
	for (int i = 0; i < sizeof(T); i++)
	{
		byteArray[i] = FileContents->at(value.address + i);
	}
	memcpy(&returnValue, byteArray, sizeof(T));
	if (xgcFlip) SwapEndian(returnValue);
	return returnValue;
}

template<typename T>
void XPC_Generic::UpdateValue(Proxy<T>& value)
{
	if (value.CheckUpdate())
	{
		T returnValue = value.guiValue;
		if (xgcFlip) SwapEndian(returnValue);
		unsigned char byteArray[sizeof(T)];
		memcpy(byteArray, &returnValue, sizeof(T));
		for (int i = 0; i < sizeof(T); i++)
		{
			FileContents->at(value.address + i) = byteArray[i];
		}
	}
}

template <typename T>
void XPC_Generic::SwapEndian(T& val) {
	unsigned char byteArray[sizeof(T)];
	unsigned char finishedByteArray[sizeof(T)];
	memcpy(byteArray, (const char*)&val, sizeof(T));

	for (int i = 0; i < sizeof(byteArray); i++)
	{
		finishedByteArray[(sizeof(byteArray) - 1) - i] = byteArray[i];
	}

	memcpy(&val, finishedByteArray, sizeof(val));
}
