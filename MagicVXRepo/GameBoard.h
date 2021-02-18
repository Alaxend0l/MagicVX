#pragma once
#include <Windows.h>
class GameBoard
{
private:
	HANDLE ProcessHandle;
	int BaseAddress;
	const int amount = 256;
	byte state[256];

public:
	GameBoard();

	void Init(HANDLE handle, int address);

	void UpdateAll();
	void UpdateKey(int index);
	byte GetKeyState(int index);
	bool GetIfKeyState(int index, byte _state);
	bool GetKeyDown(int index);
    int GetAnyKeyDown();
};

