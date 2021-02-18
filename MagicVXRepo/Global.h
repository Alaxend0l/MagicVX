#pragma once
#include "CLSettings.h"
#include "GearHuntManager.h"
#include "GearHuntObject.h"
#include "UserSettings.h"
#include "XPC_Layout.h"
#include "GameBoard.h"

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
extern XpcStore xpcStore;
extern bool pipeConnect;
extern GameBoard GB;

extern int gearHuntMakeDelete;
extern int gearHuntMakeWarp;
