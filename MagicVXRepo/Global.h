#pragma once
#include "CLSettings.h"
#include "GearHuntManager.h"
#include "GearHuntObject.h"
#include "UserSettings.h"
#include "XPC_Layout.h"
#include "GameBoard.h"
#include "HWVX_Player.h"
#include "FunctionCaller.h"
#include "XPC_Handle.h"
#include "TypeCollector.h"

#include <string>
#include <vector>


extern bool DEV_InstantBoot;

extern int menuSelect;
extern bool gearHuntStart;
extern bool gearHuntMakeWorking;
extern bool gearHuntSave;

extern UserSettings mainSettings;
extern CLSettings customLaunchSettings;
extern GearHuntManager GH_Manager;

extern std::string verNumber;
extern DWORD ProcessID;
extern bool pipeConnect;
extern GameBoard GB;
extern FunctionCaller FC;
extern XPC_Handle xpcHandle;

extern TypeCollector TC;

extern int gearHuntMakeDelete;
extern int gearHuntMakeWarp;
