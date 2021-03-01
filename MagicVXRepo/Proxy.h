#pragma once

template <typename T>
class Proxy
{
public:
	bool lock = false;
	int address;
	T currentValue;
	T gameValue;
	T guiValue;
	void SetValue(T);
	T GetValue();
	bool CheckUpdate();
};

template <typename T>
T Proxy<T>::GetValue()
{
	return currentValue;
}

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