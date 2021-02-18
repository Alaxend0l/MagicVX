#include "vxcustom.h"
#include "vxhooks.h"
#include "vxgame.h"

// Mouse patch
void MagicVX::EnableMouse() {
	BytePatchFunc((void*)0x456BE3, &MouseHooks::SetCursorPos, 6).patch_hook();
	BytePatchFunc((void*)0x4559CE, &MouseHooks::ShowCursor, 6).patch_hook();
	BytePatchFunc((void*)0x456B78, &MouseHooks::GetCursorPos, 6).patch_hook();
}

void MagicVX::EnableCheats()
{
	GameSettings::GameSettings_SetCodeVariable(0x6B, 0, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 1, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 2, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 3, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 4, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 5, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 6, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 7, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 8, 2);
	GameSettings::GameSettings_SetCodeVariable(0x6B, 9, 2);
}

// Gives item to local car
void MagicVX::GiveItem(Car* car, int weaponIndex) {
	DataPackStream* loadStream = FileStreaming::LoadDataPack("HW_Items", 2, weaponIndex, 0);

	DataPack** pack = (DataPack**)FileStreaming::InitializeDataPack(loadStream, 2, 1);
	if (pack == NULL)
		return;

	DataPackScript* script = DataPack::GetScript(pack, weaponIndex);
	if (script == NULL)
		return;

	Thing* carThing = ThingManagerList::GetByType(car->ThingIdentifier(), 8);
	if (carThing == NULL)
		return;

	DWORD sp1 = *(DWORD*)((DWORD)script + 0x30);
	if (sp1 == NULL)
		return;

	DWORD sp2 = *(DWORD*)(sp1 + 0x20);
	if (sp2 == NULL)
		return;

	WildCardRack::Add(carThing, (int)script, sp2);
}

int MagicVX::LoadCar(int carIndex, int loc)
{
	DataPackStream* loadStream = FileStreaming::LoadDataPack("HW_Cars", 0, carIndex, 0);

	DataPack** pack = (DataPack * *)FileStreaming::InitializeDataPack(loadStream, 0, 1);
	if (pack == NULL)
		return 0;

	DataPackScript* script = DataPack::GetScript(pack, carIndex);
	if (script == NULL)
		return 1;
	
	return (int)script;
}

int MagicVX::LoadItem(int itemIndex)
{
	DataPackStream* loadStream = FileStreaming::LoadDataPack("HW_Items", 2, itemIndex, 0);

	DataPack** pack = (DataPack * *)FileStreaming::InitializeDataPack(loadStream, 2, 1);
	if (pack == NULL)
		return 0;

	DataPackScript* script = DataPack::GetScript(pack, itemIndex);
	if (script == NULL)
		return 1;

	return (int)script;
}

void MagicVX::PlayInterface(int index)
{
	char result = Action::ActionInterfacePlay(index);
}