#pragma once

#include <string>

template <typename T>
class Proxy
{
public:
	std::string title = "";
	bool lock = false;
	int address;
	T currentValue;
	T gameValue;
	T guiValue;
	void SetValue(T);
	void InitValue(T);
	T GetValue();
	bool CheckUpdate();
};

template <typename T>
void Proxy<T>::SetValue(T value)
{
	gameValue = value;
	if (gameValue != currentValue)
	{
		currentValue = value;
		guiValue = value;
	}

}


template <typename T>
void Proxy<T>::InitValue(T value)
{
	gameValue = value;
	currentValue = value;
	guiValue = value;
}

template <typename T>
T Proxy<T>::GetValue()
{
	return currentValue;
}



template <typename T>
bool Proxy<T>::CheckUpdate()
{
	if (guiValue != currentValue)
	{
		currentValue = guiValue;
		gameValue = guiValue;
		return true;
	}
	return false;
}