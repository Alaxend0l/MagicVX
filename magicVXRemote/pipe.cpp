#include <windows.h>
#include <iostream>
#include "vxpipe.h"
#include "vxgame.h"
#include "vxcustom.h"
#include "vxroutes.h"

// Route function type
typedef void(__cdecl * _route)(const char* msg, char* returnData, DWORD* bytesWritten);

// Pipe initialization and loop
void pipe_handler() {
	printf("[magicVX] Initializing named pipe listener...\n");

	HANDLE pipe;
	char buf[1024];
	
	DWORD bytesRead;
	DWORD bytesWritten;

	pipe = CreateNamedPipe(
		PIPE_PATH,
		PIPE_ACCESS_DUPLEX,
		PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
		1,
		sizeof(buf),
		sizeof(buf),
		NMPWAIT_USE_DEFAULT_WAIT,
		NULL
	);

	printf("[magicVX] Initialization complete. Awaiting connections...\n");

	// Main pipe loop
	while (pipe != INVALID_HANDLE_VALUE) {
		if (ConnectNamedPipe(pipe, NULL) != FALSE) {
			printf("Connection successful!\n");
			while (ReadFile(pipe, buf, sizeof(buf), &bytesRead, NULL) != FALSE) {
				printf("Reading file\n");
				handle_message(buf, buf, &bytesRead);
				WriteFile(pipe, buf, bytesRead, &bytesWritten, NULL);
			}
		}

		DisconnectNamedPipe(pipe);
	}
}

// Routes messages to functions
void handle_message(const char* msg, char* returnData, DWORD* bytesWritten) {

	unsigned int route = *(unsigned int*)(msg);
	unsigned int argSize = *(unsigned int*)(msg + 4);
	unsigned int retSize = *(unsigned int*)(msg + 8);

	if (route == 0xFFFF0001)
	{
		MagicVX::EnableMouse();
		*bytesWritten = 0;
	}
	else
	{
		long double arg0 = 0;
		long double arg1 = 0;
		long double arg2 = 0;
		long double arg3 = 0;

		int returnValue = 0;

		printf("[magicVX] Received remote call of function: Enum %d\n", route);

		memcpy(&arg0, msg + 12, 12);
		memcpy(&arg1, msg + 24, 12);
		memcpy(&arg2, msg + 36, 12);
		memcpy(&arg3, msg + 48, 12);

		returnValue = ((_CallFunction)(route))(arg0, arg1, arg2, arg3);

		printf("[magicVX] Function Called - Return Value: %d\n", returnValue);
		memcpy(returnData, &returnValue, retSize);
		*bytesWritten = retSize;
	}

	
}