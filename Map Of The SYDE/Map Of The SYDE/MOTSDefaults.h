#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include "SYDELabel.h"
struct ColourValues {
	ColourValues(int _r, int _g, int _b) { r = _r; dftr = _r; g = _g; dftg = _g; b = _b; dftb = _b; }
	int r;
	int g;
	int b;

	int dftr;
	int dftg;
	int dftb;

	void operator=(ColourValues other) { r = other.r; g = other.g; b = other.b; }
	void set(int _r, int _g, int  _b) { r = _r; dftr = _r; g = _g; dftg = _g; b = _b; dftb = _b; }

	void toDefault() { r = dftr; g = dftg; b = dftb; }
	DWORD toRGB() { return RGB(r, g, b); }
	std::string toRGBStr() { return std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b); }
};

class MOTSDefaults {
public:
	static bool DEBUG_UI_;
	static bool DEV_ON_;
	static bool HandleCMD;
	static void ColourPalette(HANDLE hOut);

	static void AddLog(string log);

	static ColourValues _BLACK;
	static ColourValues _BLUE;
	static ColourValues _GREEN;
	static ColourValues _AQUA;
	static ColourValues _RED;
	static ColourValues _PURPLE;
	static ColourValues _YELLOW;
	static ColourValues _WHITE;
	static ColourValues _LIGHTGREY;
	static ColourValues _DARKBLUE;
	static ColourValues _BRIGHTGREEN;
	static ColourValues _LIGHTBLUE;
	static ColourValues _BRIGHTRED;
	static ColourValues _LIGHTPURPLE;
	static ColourValues _BRIGHTYELLOW;
	static ColourValues _BRIGHTWHITE;

	static std::vector<std::string> DebugLogs;
	static std::string _CMD;

	static SYDELabel m_fps;
};