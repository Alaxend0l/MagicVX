#include <windows.h>
#include <iostream>
#include <time.h>
#include "vxpipe.h"
#include "vxgame.h"

// Main routine jump type
typedef void(__stdcall* _main_routine)();

// DLL Entrypoint
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
		// Open console if built in debug mode
		#ifdef _DEBUG
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		printf("[magicVX] This console will only appear when the project is built in debug mode\n");
		#endif


		// Run DLL thread
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)pipe_handler, 0, 0, 0);
		break;
	}
	return true;
}