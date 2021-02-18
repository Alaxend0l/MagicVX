#include "GameBoard.h"

GameBoard::GameBoard()
{

}

void GameBoard::Init(HANDLE handle, int address)
{
	ProcessHandle = handle;
	BaseAddress = address;
}

void GameBoard::UpdateAll()
{
	for (int i = 0; i < amount; i++) UpdateKey(i);
}

void GameBoard::UpdateKey(int index)
{
	byte buffer = 0x0;
	ReadProcessMemory(ProcessHandle, (void*)(BaseAddress + index), &buffer, sizeof(byte), NULL);
	switch (state[index])
	{
	case 0: if (buffer != 0) state[index] = 1; break;						  //Key Inactive
	case 1: if (buffer != 0) state[index] = 2; else state[index] = 3; break;  //Key Pressed
	case 2: if (buffer == 0) state[index] = 3; break;						  //Key Held
	case 3: if (buffer == 0) state[index] = 0; else state[index] = 1; break;  //Key Released
	}
}

byte GameBoard::GetKeyState(int index)
{
	return state[index];
}

bool GameBoard::GetIfKeyState(int index, byte _state)
{
	return (state[index] == _state);
}

bool GameBoard::GetKeyDown(int index)
{
	return (state[index] == 1 || state[index] == 2);
}

int GameBoard::GetAnyKeyDown()
{
    for (int i = 0; i < amount; i++)
    {
        if (state[i] == 1) return i;
    }
    return -1;
}
