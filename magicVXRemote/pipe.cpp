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
// TODO: Change entirely
void handle_message(const char* msg, char* returnData, DWORD* bytesWritten) {
	int route = *(int*)(msg);

	printf("[magicVX] Received remote call of function: Enum %d\n", route);

	Routes::GetRouteFromEnum(route)(msg, returnData, bytesWritten);
}