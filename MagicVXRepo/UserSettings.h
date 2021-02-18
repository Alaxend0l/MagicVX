#pragma once
#include <iostream>
#include "SimpleIni.h"

class UserSettings
{
private:
	const char* BoolToString(bool value);
	std::string IntToString(int value);
	const char* FloatToString(float value);
	bool StringToBool(const char* value);
	int StringToInt(const char* value);
	float StringToFloat(const char* value);
	std::string getpath();
public:
	std::string gameDirectory;
	bool ColorDepth;
	bool VehicleParticles;
	bool AntiAliasing;
	bool WorldParticles;
	bool DrawDistance;
	bool GeometryDetail;
	bool DisableMovies;
	int TextureFiltering;
	int ScreenMode;
	int Resolution[2];
	int ScreenFOV;
	int MusicVol;
	int SFXVol;

	UserSettings();

	bool LoadSettings();
	void SaveSettings();

	std::string GetExeDirectory();
	std::string GetDLLPath();

	std::string TryGetPath();
};

