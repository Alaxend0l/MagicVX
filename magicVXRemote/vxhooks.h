#pragma once

#include <Windows.h>

// Intercept mouse functions to enable mouse
class MouseHooks {
public:
	static int __stdcall SetCursorPos(int x, int y);

	static int __stdcall ShowCursor(int show);

	static bool __stdcall GetCursorPos(LPPOINT point);
};