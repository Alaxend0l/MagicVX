#include "FunctionCaller.h"
#include "Funcs.h"
#include <iostream>

FunctionCaller::FunctionCaller()
{
    Pipe = CreateFile(
        "\\\\.\\pipe\\magicvx_dll",
        GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    ProcessHandle = NULL;
}

FunctionCaller::FunctionCaller(HANDLE ph, std::string path)
{
    ProcessHandle = ph;
    privileges = GetPrivileges() + 1;
    InjectDll(path.c_str(), ProcessHandle);
}

void FunctionCaller::InitPipe()
{
    Pipe = CreateFile(
        "\\\\.\\pipe\\magicvx_dll",
        GENERIC_ALL,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
}

int FunctionCaller::CallPipeInt(PipeFunction pipeFunction)
{
    
    DWORD tempWord;
    int bytes;

    if (Pipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(Pipe,
            pipeFunction.buffer,
            pipeFunction.offset,
            &tempWord,
            NULL);


        LPDWORD lpdWordthing;
        DWORD tempWord2;

        while (ReadFile(Pipe, &bytes, sizeof(int), lpdWordthing, NULL) == FALSE) {}

        CloseHandle(Pipe);
    }

    return bytes;
}

bool FunctionCaller::CallPipeBool(PipeFunction pipeFunction)
{
    
    DWORD tempWord;
    bool bytes;

    if (Pipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(Pipe,
            pipeFunction.buffer,
            pipeFunction.offset,
            &tempWord,
            NULL);


        LPDWORD lpdWordthing;
        DWORD tempWord2;

        while (ReadFile(Pipe, &bytes, sizeof(bool), lpdWordthing, NULL) == FALSE) {}
    }

    return bytes;
}

float FunctionCaller::CallPipeFloat(PipeFunction pipeFunction)
{
    
    DWORD tempWord;
    float bytes;

    if (Pipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(Pipe,
            pipeFunction.buffer,
            pipeFunction.offset,
            &tempWord,
            NULL);


        LPDWORD lpdWordthing;
        DWORD tempWord2;

        while (ReadFile(Pipe, &bytes, sizeof(float), lpdWordthing, NULL) == FALSE) {}
    }

    return bytes;
}

char FunctionCaller::CallPipeChar(PipeFunction pipeFunction)
{
    
    DWORD tempWord;
    char bytes;

    if (Pipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(Pipe,
            pipeFunction.buffer,
            pipeFunction.offset,
            &tempWord,
            NULL);


        LPDWORD lpdWordthing;
        DWORD tempWord2;

        while (ReadFile(Pipe, &bytes, sizeof(char), lpdWordthing, NULL) == FALSE) {}
    }

    return bytes;
}


void  FunctionCaller::CallPipeVoid(PipeFunction pipeFunction)
{
    
    DWORD tempWord;

    if (Pipe != INVALID_HANDLE_VALUE)
    {
        WriteFile(Pipe, pipeFunction.buffer, pipeFunction.offset, &tempWord, NULL);
    }
}

void  FunctionCaller::DisableFunction(int address)
{
    byte value = 0xC3;
    WriteProcessMemory(ProcessHandle, (void*)address, &value, sizeof(byte), NULL);
}
void  FunctionCaller::FunctionReturnZero(int address)
{
    byte v_xor = 0x31;
    byte v_eax = 0xC0;
    byte value = 0xC3;
    WriteProcessMemory(ProcessHandle, (void*)address, &v_xor, sizeof(byte), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(address + 1), &v_eax, sizeof(byte), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(address + 2), &value, sizeof(byte), NULL);
}

int   FunctionCaller::CU_SpawnGear(float x, float y, float z, int address)
{
    //Start by allocating memory for item information.
    void* memoryAllocated;
    memoryAllocated = AllocateMemory(60);
    int memoryAddress = static_cast<int>(reinterpret_cast<std::uintptr_t>(memoryAllocated));

    //Then input all the data necessary.
    int CDCDCDCD = 0xCDCDCDCD;
    int V_42F9EF = 0x42F9EF;
    int zero = 0x0;
    float one = 1;
    float fivehundred = 500;

    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x00), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x04), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x08), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x20), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x24), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x28), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x38), &zero, sizeof(int), NULL);

    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x0C), &one, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x10), &x, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x14), &y, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x18), &z, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x1C), &CDCDCDCD, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x2C), &V_42F9EF, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x30), &address, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x34), &fivehundred, sizeof(float), NULL);

    //Then, spawn the item.
    int result = FC_ThingManager_DARYL_CreateThing(4, memoryAddress);

    //End it off by deallocating the used memory.
    DeAllocateMemory(memoryAllocated);

    return result;
}
int   FunctionCaller::CU_SpawnItem(int type, float x, float y, float z)
{
    //Start by allocating memory for item information.
    void* memoryAllocated;
    memoryAllocated = AllocateMemory(60);
    int memoryAddress = static_cast<int>(reinterpret_cast<std::uintptr_t>(memoryAllocated));

    //Then, let's load in the collectable.
    int loadStream = 0;// FC_FileStreaming_LoadDataPack(LDP_HW_Items, 2, type, 0);
    if (loadStream == 0) { std::cout << "Error Loading Data Pack.\n"; return 0; }

    int pack = 0;// FC_FileStreaming_InitializeDataPack(loadStream, 2, 1);
    if (pack == 0) { std::cout << "Error Initializing Data Pack.\n"; return 0; }

    int script = 0;// FC_DataPack_GetScript(pack, type);
    if (script == 0) { std::cout << "Error Getting Script.\n"; return 0; }

    std::cout << "Script has been initialized.\n";

    //Then input all the data necessary.
    int CDCDCDCD = 0xCDCDCDCD;
    int V_42F9EF = 0x42F9EF;
    int zero = 0x0;
    float one = 1;
    float fivehundred = 500;

    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x00), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x04), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x08), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x20), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x24), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x28), &zero, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x38), &zero, sizeof(int), NULL);

    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x0C), &one, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x10), &x, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x14), &y, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x18), &z, sizeof(float), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x1C), &CDCDCDCD, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x2C), &V_42F9EF, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x30), &script, sizeof(int), NULL);
    WriteProcessMemory(ProcessHandle, (void*)(memoryAddress + 0x34), &fivehundred, sizeof(float), NULL);

    //Then, spawn the item.
    int result = FC_ThingManager_DARYL_CreateThing(4, memoryAddress);

    //End it off by deallocating the used memory.
    DeAllocateMemory(memoryAllocated);

    return result;
}
void  FunctionCaller::CU_EnableCheats()
{
    /*
    FC_GameSettings_SetCodeVariable(0x6B, 0, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 1, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 2, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 3, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 4, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 5, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 6, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 7, 2);
    FC_GameSettings_SetCodeVariable(0x6B, 8, 1);
    FC_GameSettings_SetCodeVariable(0x6B, 9, 1);
    */
    
    //PipeFunction FunctionCall = PipeFunction();
    //FunctionCall.Add(MagicVX_EnableCheats);
    //return CallPipeVoid(FunctionCall);
}
void  FunctionCaller::CU_DisableCheats()
{
    FC_GameSettings_SetCodeVariable(0x6B, 0, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 1, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 2, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 3, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 4, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 5, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 6, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 7, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 8, 0);
    FC_GameSettings_SetCodeVariable(0x6B, 9, 0);
}
void  FunctionCaller::CU_TeleportCorrection(int address)
{
    FC_SubMatrixToQuaternion(address + 0x10, address + 0x50);
}

/*---------------------------------------------------------------------------------*/

void  FunctionCaller::PatchMouse()
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(MagicVX_PatchMouse);
    return CallPipeVoid(FunctionCall);
}


int   FunctionCaller::FC_DataPack_GetScript(int datapack, int index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(DataPack_GetScript);
    FunctionCall.Add(datapack);
    FunctionCall.Add(index);

    return CallPipeInt(FunctionCall);
}

int   FunctionCaller::FC_FileStreaming_LoadDataPack(int filename, int type, int index, char variant)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(FileStreaming_LoadDataPack);
    FunctionCall.Add(filename);
    FunctionCall.Add(type);
    FunctionCall.Add(index);
    FunctionCall.Add(variant);

    return CallPipeInt(FunctionCall);
}

int   FunctionCaller::FC_FileStreaming_InitializeDataPack(int datapackstream, int type, char notsure)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(FileStreaming_InitializeDataPack);
    FunctionCall.Add(datapackstream);
    FunctionCall.Add(type);
    FunctionCall.Add(notsure);

    return CallPipeInt(FunctionCall);
}
void  FunctionCaller::FC_GameSettings_SetCodeVariable(int variable, int offset, int value)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(GameSettings_SetCodeVariable);
    FunctionCall.Add(variable);
    FunctionCall.Add(offset);
    FunctionCall.Add(value);

    return CallPipeVoid(FunctionCall);
}
int   FunctionCaller::FC_GameSettings_GetCodeVariable(int variable, int offset)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(GameSettings_GetCodeVariable);
    FunctionCall.Add(variable);
    FunctionCall.Add(offset);

    return CallPipeInt(FunctionCall);
}
int   FunctionCaller::FC_GameSettings_IsCheatEnabled(int index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(GameSettings_IsCheatEnabled);
    FunctionCall.Add(index);

    return CallPipeInt(FunctionCall);
}
void  FunctionCaller::FC_Item_Release(int address)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(Item_Release);
    FunctionCall.Add(address);

    return CallPipeVoid(FunctionCall);
}
bool  FunctionCaller::FC_Player_IsHuman(int address)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(Player_IsHuman);
    FunctionCall.Add(address);

    return CallPipeBool(FunctionCall);
}
char  FunctionCaller::FC_PlayerManager_PlayerCount()
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(PlayerManager_PlayerCount);

    return CallPipeChar(FunctionCall);
}
int   FunctionCaller::FC_PlayerManager_GetPlayerByIndex(char index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(PlayerManager_GetPlayerByIndex);
    FunctionCall.Add(index);

    return CallPipeInt(FunctionCall);
}
int   FunctionCaller::FC_PlayerManager_GetHumanPlayerByIndex(char index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(PlayerManager_GetHumanPlayerByIndex);
    FunctionCall.Add(index);

    return CallPipeInt(FunctionCall);
}
void  FunctionCaller::FC_StateManager_GotoState(int index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(StateManager_GotoState);
    FunctionCall.Add(index);

    return CallPipeVoid(FunctionCall);
}


int   FunctionCaller::FC_ActionVehicleTeleport(int address)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(ActionVehicleTeleport);
    FunctionCall.Add(address);

    return CallPipeInt(FunctionCall);
}
int   FunctionCaller::FC_ThingManager_DARYL_CreateThing(int type, int address)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(ThingManager_DARYL_CreateThing);
    FunctionCall.Add(type);
    FunctionCall.Add(address);

    return CallPipeInt(FunctionCall);
}
void  FunctionCaller::FC_ViewManager_SetFourPlayer()
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(ViewManager_SetFourPlayer);

    return CallPipeVoid(FunctionCall);
}
int   FunctionCaller::FC_GetTotalTiles_Car()
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(GetTotalTiles_Car);

    return CallPipeInt(FunctionCall);
}
int   FunctionCaller::FC_GetTileCar(int index)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(GetTileCar);
    FunctionCall.Add(index);

    return CallPipeInt(FunctionCall);
}
void  FunctionCaller::FC_SubMatrixToQuaternion(int add1, int add2)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(SubMatrixToQuaternion);
    FunctionCall.Add(add1);
    FunctionCall.Add(add2);

    return CallPipeVoid(FunctionCall);
}
void  FunctionCaller::FC_SetSFXVol(int volume)
{
    PipeFunction FunctionCall = PipeFunction();
    FunctionCall.Add(SetSFXVol);
    FunctionCall.Add(volume);

    return CallPipeVoid(FunctionCall);
}
/*---------------------------------------------------------------------------------*/

void* FunctionCaller::AllocateMemory(int size)
{
    return VirtualAllocEx(ProcessHandle, NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void FunctionCaller::DeAllocateMemory(void* address)
{
    VirtualFreeEx(ProcessHandle, address, 0, MEM_RELEASE);
}

int FunctionCaller::GetPrivileges() {
    HANDLE Token;
    TOKEN_PRIVILEGES tp;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Token))
    {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (AdjustTokenPrivileges(Token, 0, &tp, sizeof(tp), NULL, NULL) == 0) {
            return 1; //FAIL
        }
        else {
            return 0; //SUCCESS
        }
    }
    return 1;
}

bool FunctionCaller::InjectDll(LPCSTR DllPath, HANDLE hProcess) {

    LPVOID LoadLibAddr = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

    if (!LoadLibAddr) {
        printf("Could note locate real address of LoadLibraryA!\n");
        printf("LastError : 0X%x\n", GetLastError());
        system("PAUSE");
        return false;
    }

    printf("LoadLibraryA is located at real address: 0X%p\n", (void*)LoadLibAddr);

    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath), MEM_COMMIT, PAGE_READWRITE);

    if (!pDllPath) {
        printf("Could not allocate Memory in target process\n");
        printf("LastError : 0X%x\n", GetLastError());
        system("PAUSE");
        return false;
    }

    printf("Dll path memory allocated at: 0X%p\n", (void*)pDllPath);

    BOOL Written = WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath), NULL);

    if (!Written) {
        printf("Could not write into the allocated memory\n");
        printf("LastError : 0X%x\n", GetLastError());
        system("PAUSE");
        return false;
    }

    printf("Dll path memory was written at address : 0x%p\n", (void*)pDllPath);

    HANDLE hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddr, pDllPath, 0, NULL);

    if (!hThread) {
        printf("Could not open Thread with CreatRemoteThread API\n");
        printf("LastError : 0X%x\n", GetLastError());
        system("PAUSE");
        return false;
    }

    printf("Thread started with CreateRemoteThread\n");

    return true;
}
