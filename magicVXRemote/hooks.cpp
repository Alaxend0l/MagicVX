#include "vxhooks.h"

// Initializing MouseHooks
int __stdcall MouseHooks::SetCursorPos(int x, int y) {
	return true;
}

int __stdcall MouseHooks::ShowCursor(int show) {
	return ::ShowCursor(1);
}

bool __stdcall MouseHooks::GetCursorPos(LPPOINT point) {
	point->x = 320;
	point->y = 240;

	return true;
}