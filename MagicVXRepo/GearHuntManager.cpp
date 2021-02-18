#include "GearHuntManager.h"

GearHuntManager::GearHuntManager(void)
{

}

void GearHuntManager::SaveInfo(std::string name)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.SetValue("Base", NULL, NULL);
	ini.SetValue("Base", "Title", Title.c_str());
	ini.SetValue("Base", "Creator", Creator.c_str());
	ini.SetValue("Base", "Description", Description.c_str());
	ini.SetValue("Base", "Version", "0.9.9");

	ini.SetValue("Base", "World", std::to_string(World).c_str());
	ini.SetValue("Base", "ForceCar", std::to_string(ForceCar).c_str());
	ini.SetValue("Base", "ForceWeapon", std::to_string(ForceWeapon).c_str());
	ini.SetValue("Base", "ForceDeadWeight", std::to_string(ForceDeadWeight).c_str());
	ini.SetValue("Base", "CarChoice", std::to_string(CarChoice).c_str());
	ini.SetValue("Base", "WeaponChoice", std::to_string(WeaponChoice).c_str());
	ini.SetValue("Base", "DeadWeightChoice", std::to_string(DeadWeightChoice).c_str());
	ini.SetValue("Base", "TimeLimit", std::to_string(TimeLimit).c_str());

	ini.SetValue("Base", "ZeroGravity", std::to_string(ZeroGravity).c_str());
	ini.SetValue("Base", "SimplePhysics", std::to_string(SimplePhysics).c_str());

	ini.SetValue("Base", "TotalObjects", std::to_string(TotalObjects).c_str());

	for (int i = 0; i < TotalObjects; i++)
	{
		std::string sectionName = "Object" + std::to_string(i);
		ini.SetValue(sectionName.data(), NULL, NULL);
		ini.SetValue(sectionName.data(), "ObjectType", std::to_string(objects[i].ObjectType).c_str());
		ini.SetValue(sectionName.data(), "ObjectTypeIndex", std::to_string(objects[i].ObjectTypeIndex).c_str());
		ini.SetValue(sectionName.data(), "PosX", std::to_string(objects[i].PositionX).c_str());
		ini.SetValue(sectionName.data(), "PosY", std::to_string(objects[i].PositionY).c_str());
		ini.SetValue(sectionName.data(), "PosZ", std::to_string(objects[i].PositionZ).c_str());
	}

	std::string pathname = getpath() + "\\MagicVX\\GearHunts\\" + name + ".ini";
	ini.SaveFile(pathname.data());
}

void GearHuntManager::LoadInfo(std::string name)
{
	CSimpleIniA ini;
	ini.SetUnicode();
	std::string pathToGearHunt = getpath() + "\\MagicVX\\GearHunts\\" + name + ".ini";
	SI_Error rc = ini.LoadFile(pathToGearHunt.data());
	
	if (rc < 0)
	{
		//An error occured.
		return;
	}
	else
	{
		Title = ini.GetValue("Base", "Title", "Error");
		Creator = ini.GetValue("Base", "Creator", "Error");
		Description = ini.GetValue("Base", "Description", "Error");
		MVX_Version = ini.GetValue("Base", "Version", "Error");

		World = atoi(ini.GetValue("Base", "World", "0"));
		ForceCar = StringToBool(ini.GetValue("Base", "ForceCar", "0"));
		ForceWeapon = StringToBool(ini.GetValue("Base", "ForceWeapon", "0"));
		ForceDeadWeight = StringToBool(ini.GetValue("Base", "ForceDeadWeight", "0"));
		CarChoice = atoi(ini.GetValue("Base", "CarChoice", "0"));
		WeaponChoice = atoi(ini.GetValue("Base", "WeaponChoice", "0"));
		DeadWeightChoice = atoi(ini.GetValue("Base", "DeadWeightChoice", "0"));
		TimeLimit = atoi(ini.GetValue("Base", "TimeLimit", "0"));
		
		ZeroGravity = StringToBool(ini.GetValue("Base", "ZeroGravity", "0"));
		SimplePhysics = StringToBool(ini.GetValue("Base", "SimplePhysics", "0"));

		TotalObjects = atoi(ini.GetValue("Base", "TotalObjects", "0"));

		for (int i = 0; i < TotalObjects; i++)
		{
			std::string sectionName = "Object" + std::to_string(i);
			GearHuntObject toAdd;
			toAdd.ObjectType = atoi(ini.GetValue(sectionName.data(), "ObjectType"));
			toAdd.ObjectTypeIndex = atoi(ini.GetValue(sectionName.data(), "ObjectTypeIndex"));
			if (toAdd.ObjectType == 0) //Collectable
			{
				switch (toAdd.ObjectTypeIndex)
				{
				case C_RipperWheels:
				case C_ArmorRepair:
				case C_OilDrum:
				case C_LaserCannon:
				case C_SonicBoom:
				case C_AtomBlaster:
				case C_FreonBomb:
				case C_EnergyShield:
				case C_JetBoosters:
				case C_SuperZapper:
				case C_MagnetMine:
				case C_DoomDisks:
					Weapons++;
					break;
				case C_BlueGear:
				case C_WhiteGear:
				case C_RedGear:
				case C_GreenGear:
				case C_YellowGear:
					Gears++;
					break;
				case C_BlueKey:
				case C_YellowKey:
				case C_GreenKey:
				case C_RedKey:
				case C_WhiteKey:
					Keys++;
					break;
				case C_100PointCapsule:
				case C_200PointCapsule:
				case C_300PointCapsule:
				case C_400PointCapsule:
				case C_500PointCapsule:
				case C_600PointCapsule:
				case C_700PointCapsule:
				case C_800PointCapsule:
					PointCapsules++;
					break;

				}
			}
			toAdd.PositionX = atof(ini.GetValue(sectionName.data(), "PosX"));
			toAdd.PositionY = atof(ini.GetValue(sectionName.data(), "PosY"));
			toAdd.PositionZ = atof(ini.GetValue(sectionName.data(), "PosZ"));
			objects.push_back(toAdd);
		}
	}
}

bool GearHuntManager::StringToBool(const char* value)
{
	int test = atoi(value);
	if (test == 1) return true;
	else return false;
}

std::string GearHuntManager::getpath()
{
	TCHAR documents[MAX_PATH];

	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, documents);
	if (result == S_OK) // SUCCEEDED(result) can be problematic
						// since S_FALSE is a possible return value
	{
		std::stringstream pff;
		pff << documents;
		return pff.str();
	}
	// handle error somehow
	return "";
}
