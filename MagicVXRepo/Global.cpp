#include "Global.h"

bool DEV_InstantBoot = false;

std::string verNumber = "0.9.9";

int menuSelect = 0;
bool gearHuntStart = false;
bool gearHuntMakeWorking = false;
bool gearHuntSave = false;
UserSettings mainSettings;
CLSettings customLaunchSettings;
GearHuntManager GH_Manager;
DWORD ProcessID;
XpcStore xpcStore;
GameBoard GB;
bool pipeConnect = false;


int gearHuntMakeDelete = -1;
int gearHuntMakeWarp = -1;
