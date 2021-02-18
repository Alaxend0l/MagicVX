#pragma once

#include <Windows.h>

class BytePatchFunc {
public:
	void* base_address;
	void* func;
	char original_bytes[128];
	int size_of_patch;

	BytePatchFunc(void* _base_address, void* _func, int _size_of_patch) {
		base_address = _base_address;
		func = _func;
		memcpy(original_bytes, base_address, 6);
		size_of_patch = _size_of_patch;
	}

	void patch_hook() {
		VirtualProtect(base_address, size_of_patch, PAGE_EXECUTE_READWRITE, &old_protect);
		memset(base_address, 0x90, size_of_patch);
		*(char*)(int)base_address = (char)0xE8;
		*(DWORD*)((int)base_address + 0x1) = (DWORD)func - (DWORD)base_address - 0x5;
		VirtualProtect(base_address, size_of_patch, old_protect, &old_protect);
	}

	void patch_original() {
		VirtualProtect(base_address, size_of_patch, PAGE_EXECUTE_READWRITE, &old_protect);
		memcpy(base_address, original_bytes, size_of_patch);
		VirtualProtect(base_address, size_of_patch, old_protect, &old_protect);
	}

private:
	DWORD old_protect;
};

