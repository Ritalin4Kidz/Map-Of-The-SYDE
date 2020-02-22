#include "pch.h"
#include "MOTSDefaults.h"

bool MOTSDefaults::DEBUG_UI_ = false;
bool MOTSDefaults::DEV_ON_ = false;
bool MOTSDefaults::HandleCMD = false;

std::string MOTSDefaults::_CMD = "";

ColourValues MOTSDefaults::_BLACK = ColourValues(12, 12, 12);
ColourValues MOTSDefaults::_BLUE = ColourValues(0, 55, 218);
ColourValues MOTSDefaults::_GREEN = ColourValues(19, 161, 14);
ColourValues MOTSDefaults::_AQUA = ColourValues(58, 150, 221);
ColourValues MOTSDefaults::_RED = ColourValues(197, 15, 31);
ColourValues MOTSDefaults::_PURPLE = ColourValues(136, 23, 152);
ColourValues MOTSDefaults::_YELLOW = ColourValues(193, 156, 0);
ColourValues MOTSDefaults::_WHITE = ColourValues(204, 204, 204);
ColourValues MOTSDefaults::_LIGHTGREY = ColourValues(118, 118, 118);
ColourValues MOTSDefaults::_DARKBLUE = ColourValues(59, 120, 255);
ColourValues MOTSDefaults::_BRIGHTGREEN = ColourValues(22, 198, 12);
ColourValues MOTSDefaults::_LIGHTBLUE = ColourValues(97, 214, 214);
ColourValues MOTSDefaults::_BRIGHTRED = ColourValues(231, 72, 86);
ColourValues MOTSDefaults::_LIGHTPURPLE = ColourValues(180, 0, 158);
ColourValues MOTSDefaults::_BRIGHTYELLOW = ColourValues(249, 241, 165);
ColourValues MOTSDefaults::_BRIGHTWHITE = ColourValues(242, 242, 242);

std::vector<std::string> MOTSDefaults::DebugLogs = std::vector<std::string>();

SYDELabel MOTSDefaults::m_fps = SYDELabel("", Vector2(35, 1), Vector2(5, 1), BRIGHTGREEN, true);;

void MOTSDefaults::ColourPalette(HANDLE hOut)
{
	CONSOLE_SCREEN_BUFFER_INFOEX pInfo;
	pInfo.cbSize = sizeof(pInfo);
	GetConsoleScreenBufferInfoEx(hOut, &pInfo);
	pInfo.ColorTable[0] = COLORREF(MOTSDefaults::_BLACK.toRGB());
	pInfo.ColorTable[1] = COLORREF(MOTSDefaults::_BLUE.toRGB());
	pInfo.ColorTable[2] = COLORREF(MOTSDefaults::_GREEN.toRGB());
	pInfo.ColorTable[3] = COLORREF(MOTSDefaults::_AQUA.toRGB());
	pInfo.ColorTable[4] = COLORREF(MOTSDefaults::_RED.toRGB());
	pInfo.ColorTable[5] = COLORREF(MOTSDefaults::_PURPLE.toRGB());
	pInfo.ColorTable[6] = COLORREF(MOTSDefaults::_YELLOW.toRGB());
	pInfo.ColorTable[7] = COLORREF(MOTSDefaults::_WHITE.toRGB());
	pInfo.ColorTable[8] = COLORREF(MOTSDefaults::_LIGHTGREY.toRGB());
	pInfo.ColorTable[9] = COLORREF(MOTSDefaults::_DARKBLUE.toRGB());
	pInfo.ColorTable[10] = COLORREF(MOTSDefaults::_BRIGHTGREEN.toRGB());
	pInfo.ColorTable[11] = COLORREF(MOTSDefaults::_LIGHTBLUE.toRGB());
	pInfo.ColorTable[12] = COLORREF(MOTSDefaults::_BRIGHTRED.toRGB());
	pInfo.ColorTable[13] = COLORREF(MOTSDefaults::_LIGHTPURPLE.toRGB());
	pInfo.ColorTable[14] = COLORREF(MOTSDefaults::_BRIGHTYELLOW.toRGB());
	pInfo.ColorTable[15] = COLORREF(MOTSDefaults::_BRIGHTWHITE.toRGB());
	SetConsoleScreenBufferInfoEx(hOut, &pInfo);
}

void MOTSDefaults::AddLog(string log)
{
	if (DEV_ON_)
	{
		DebugLogs.push_back(log);
	}
}
