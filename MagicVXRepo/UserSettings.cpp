#include "UserSettings.h"
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <ShlObj_core.h>
#include <direct.h>

UserSettings::UserSettings(void)
{

}

std::string UserSettings::TryGetPath()
{
	return getpath();
}

bool UserSettings::LoadSettings()
{
	CSimpleIniA ini;
	ini.SetUnicode();
	std::string path = getpath() + "\\MagicVX";
	std::string path_gearhunts = path + "\\GearHunts";
	_mkdir(path.data());
	_mkdir(path_gearhunts.data());
	std::string pathname = path + "\\config.ini";
	SI_Error rc = ini.LoadFile(pathname.data());
	if (rc < 0)
	{
		gameDirectory = "Click the [...] button to get the HWVX executable!";
		ColorDepth = true;
		VehicleParticles = false;
		AntiAliasing = false;
		WorldParticles = false;
		DrawDistance = false;
		GeometryDetail = false;
		DisableMovies = true;
		TextureFiltering = 5;
		ScreenMode = 1;
		ScreenX = 1920;
		ScreenY = 1080;
		ScreenFOV = 120;
		MusicVol = 5;
		SFXVol = 5;
		return false;
	}
	else
	{
		gameDirectory = ini.GetValue("BasicSettings", "GameDirectory");
		ColorDepth = StringToBool(ini.GetValue("BasicSettings", "ColorDepth"));
		VehicleParticles = StringToBool(ini.GetValue("BasicSettings", "VehicleParticles"));
		AntiAliasing = StringToBool(ini.GetValue("BasicSettings", "AntiAliasing"));
		WorldParticles = StringToBool(ini.GetValue("BasicSettings", "WorldParticles"));
		DrawDistance = StringToBool(ini.GetValue("BasicSettings", "DrawDistance"));
		GeometryDetail = StringToBool(ini.GetValue("BasicSettings", "GeometryDetail"));
		DisableMovies = StringToBool(ini.GetValue("BasicSettings", "DisableMovies"));
		TextureFiltering = atoi(ini.GetValue("BasicSettings", "TextureFiltering"));
		ScreenMode = atoi(ini.GetValue("BasicSettings", "ScreenMode"));
		ScreenX = atoi(ini.GetValue("BasicSettings", "ScreenX"));
		ScreenY = atoi(ini.GetValue("BasicSettings", "ScreenY"));
		ScreenFOV = atoi(ini.GetValue("BasicSettings", "ScreenFOV"));
		MusicVol = atoi(ini.GetValue("BasicSettings", "MusicVol"));
		SFXVol = atoi(ini.GetValue("BasicSettings", "SFXVol"));
		return true;
	}
}

void UserSettings::SaveSettings()
{
	CSimpleIniA ini;
	ini.SetUnicode();
	ini.SetValue("BasicSettings", NULL, NULL);
	ini.SetValue("BasicSettings", "GameDirectory", gameDirectory.c_str());
	ini.SetValue("BasicSettings", "ColorDepth", std::to_string(ColorDepth).c_str());
	ini.SetValue("BasicSettings", "VehicleParticles", std::to_string(VehicleParticles).c_str());
	ini.SetValue("BasicSettings", "AntiAliasing", std::to_string(AntiAliasing).c_str());
	ini.SetValue("BasicSettings", "WorldParticles", std::to_string(WorldParticles).c_str());
	ini.SetValue("BasicSettings", "DrawDistance", std::to_string(DrawDistance).c_str());
	ini.SetValue("BasicSettings", "GeometryDetail", std::to_string(GeometryDetail).c_str());
	ini.SetValue("BasicSettings", "DisableMovies", std::to_string(DisableMovies).c_str());
	ini.SetValue("BasicSettings", "TextureFiltering", std::to_string(TextureFiltering).c_str());
	ini.SetValue("BasicSettings", "ScreenMode", std::to_string(ScreenMode).c_str());
	ini.SetValue("BasicSettings", "ScreenX", std::to_string(ScreenX).c_str());
	ini.SetValue("BasicSettings", "ScreenY", std::to_string(ScreenY).c_str());
	ini.SetValue("BasicSettings", "ScreenFOV", std::to_string(ScreenFOV).c_str());
	ini.SetValue("BasicSettings", "MusicVol", std::to_string(MusicVol).c_str());
	ini.SetValue("BasicSettings", "SFXVol", std::to_string(SFXVol).c_str());
	std::string pathname = getpath() + "\\MagicVX\\config.ini";
	ini.SaveFile(pathname.data());
}

bool UserSettings::StringToBool(const char* value)
{
	int test = atoi(value);
	if (test == 1) return true;
	else return false;
}

std::string UserSettings::getpath() {
	std::string path = getenv("APPDATA");
	return path;
}

std::string UserSettings::GetExeDirectory()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	return std::string(buffer).substr(0, pos);
}

std::string UserSettings::GetDLLPath()
{
	return (GetExeDirectory() + "\\VXR.dll");
}


