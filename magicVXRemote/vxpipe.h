#pragma once

#include <Windows.h>

// Named pipe path
#define PIPE_PATH TEXT("\\\\.\\pipe\\magicvx_dll")

// Main thread to handle pipe requests
void pipe_handler();

// Routes network messages
void handle_message(const char* msg, char* returnData, DWORD* bytesWritten);