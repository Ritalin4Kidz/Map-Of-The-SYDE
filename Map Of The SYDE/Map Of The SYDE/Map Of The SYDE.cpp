#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include "SYDEstdafx.h"
#include "SYDEMapRPG.h"
#include "DebugWindow.h"
#include <fstream>
#include <istream>
#include <sstream>
#include "CheatSettings.h"
#include "D20Minigame.h"
#include "TetriSYDE.h"

using namespace std;
using namespace Gdiplus;
//INITIALIZING VARIABLES
int windowWidth = 40;
const int windowHeight = 20;
const string dir = "BrainFiles\\";
Settings config("EngineFiles\\Settings\\configSettings.sc");
ConsoleWindow window(windowHeight);
//DRAWING SETTINGS
BackgroundClass bgVars;
Characters charVars;
Artwork artVars;
//OTHER ASSETS
AssetsClass astVars;
//DECLARE CUSTOM ASSETS HERE
COORD start = { (SHORT)0, (SHORT)0 };
static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
CustomAnimationAsset testAnimation;
//CHEATS
vector<string> cheatCodes;
static ULONG_PTR gdiplusToken;
static GdiplusStartupInput startupInput;

DWORD VOLUME_LOW = DWORD(858993459);
DWORD VOLUME_NML = DWORD(1717986918);
DWORD VOLUME_MED = DWORD(-1717986918);
DWORD VOLUME_HIG = DWORD(-858993459);
DWORD VOLUME_OFF = DWORD(0);

bool _Debug_Window = false;

void volumeControl(int volume){
	switch (volume)
	{
	case 0:
		waveOutSetVolume(0, VOLUME_OFF);
		break;
	case 1:
		waveOutSetVolume(0, VOLUME_LOW);
		break;
	case 2:
		waveOutSetVolume(0, VOLUME_NML);
		break;
	case 3:
		waveOutSetVolume(0, VOLUME_MED);
		break;
	case 4:
		waveOutSetVolume(0, VOLUME_HIG);
		break;
	default:
		waveOutSetVolume(0, VOLUME_NML);
		volume = 2;
		break;
	}
}


int main(int argc, char* argv[])
{
	MOTSDefaults::ColourPalette(hOut);
	volumeControl(1);
	//CHEAT CODES
	CHEATCODES_MOTS::INIT_CHEATS(config.ReturnCheats());
	std::srand(std::time(nullptr));
	LPCWSTR title = L"Map Of The SYDE";
	SYDECredits::_GAMETITLE = "Map Of The SYDE";
	SYDECredits::_ORGANISATION = "Callum Hands \nIn Association With Freebee Games";
	//CONSOLE SETTINGS
	//SYDE ENGINE SETTINGS
	GdiplusStartup(&gdiplusToken, &startupInput, 0);
	SetConsoleTitleW(title);
	SYDETIME deltaTime;
	deltaTime.initialise(std::chrono::high_resolution_clock::now());
	SYDEGamePlay::initialize_window(hOut, window);
	for (int i = 0; i < windowWidth; i++)
	{
		for (int j = 0; j < windowHeight; j++)
		{
			window.setTextAtPoint(Vector2(i, j), " ", BRIGHTWHITE_BRIGHTWHITE_BG);
		}
	}

	for (int i = 0; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg == "--dev_mode")
		{
			MOTSDefaults::DEV_ON_ = true;
		}
		else if (arg == "--debug_ui")
		{
			MOTSDefaults::DEBUG_UI_ = true;
		}
	}

	SYDEMapGame m_MapSYDE;
	TetriSYDE d20;
	DebugW m_DEBUGGER;

	//KEYS
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('A'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('W'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('S'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('D'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('R')); //TETRIS
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_TAB));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SHIFT));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_SPACE));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('T'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey(VK_BACK));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('I'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('M'));
	SYDEKeyCode::KeyCodes_Optimized.push_back(SYDEKey('K'));

	if (MOTSDefaults::DEV_ON_)
	{
		SYDEGamePlay::activate_bySplashscreen(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	}
	else
	{
		SYDEGamePlay::opening_splashscreens(astVars.get_electronic_chime_file_path(), start, hOut, window, windowWidth, windowHeight, artVars);
	}

	//MAIN GAMEPLAY LOOP
	while (true)
	{
		window = SYDEGamePlay::play(&d20, start, hOut, window, windowWidth, windowHeight, deltaTime);
		//window = SYDEGamePlay::play(&m_MapSYDE, start, hOut, window, windowWidth, windowHeight, deltaTime);
		if (MOTSDefaults::DEV_ON_)
		{
			if ((SYDEKeyCode::get_key(VK_SHIFT)._CompareState(KEYDOWN)))
			{
				_Debug_Window = !_Debug_Window;
			}
			if (_Debug_Window)
			{
				window = m_DEBUGGER.window_draw_game(window, windowHeight, windowWidth);
			}
			if (MOTSDefaults::HandleCMD)
			{
				MOTSDefaults::HandleCMD = false;
				MOTSDefaults::AddLog("CMD: " + MOTSDefaults::_CMD);
				if (MOTSDefaults::_CMD.compare("savegame") == 0)
				{
					m_MapSYDE.saveGame();
				}
				if (MOTSDefaults::_CMD.compare("logclear") == 0)
				{
					MOTSDefaults::DebugLogs.clear();
				}
			}
		}
		//else if (MOTSDefaults::DebugLogs.size() >= 50)
		//{
		//	// DOn't Fuck UP THE RAMMMM
		//	MOTSDefaults::DebugLogs.clear();
		//}
		if (MOTSDefaults::DEBUG_UI_)
		{
			float fps = 1.0f / SYDEDefaults::getDeltaTime();
			MOTSDefaults::m_fps.setText(std::to_string((int)fps) + "fps");
			window = MOTSDefaults::m_fps.draw_ui(window);
		}
		window.writeConsole();
		SYDEFunctions::SYDESleep(30, SYDEDefaults::getDeltaTime());
	}
	system("cls");
	return NULL;

}
