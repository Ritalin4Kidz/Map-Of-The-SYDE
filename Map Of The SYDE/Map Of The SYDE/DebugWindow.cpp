#include "pch.h"
#include "DebugWindow.h"

void DebugWindow::AddDebugString(string dstring)
{
	if (_debugStrings.size() >= __linesMax)
	{
		for (int i = 1; i < __linesMax; i++)
		{
			_debugStrings[i - 1] = _debugStrings[i];
		}
		_debugStrings[__linesMax - 1] = dstring;
	}
	else {
		_debugStrings.push_back(dstring);
	}
}


ConsoleWindow DebugW::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int i = 0; i < MOTSDefaults::DebugLogs.size(); i++)
	{
		debugger.AddDebugString(MOTSDefaults::DebugLogs[i]);
	}
	MOTSDefaults::DebugLogs.clear();
	for (int i = 0; i < 15; i++)
	{
		window.setTextAtPoint(Vector2(0, 19 - i), debugger.getDebugString(i), BRIGHTGREEN);
	}
	if ((SYDEKeyCode::get_key(VK_BACK)._CompareState(KEYDOWN)))
	{
		string cmd;
		cin.clear();
		cin >> cmd;
		system("cls");
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, WHITE);
		CONSOLE_SCREEN_BUFFER_INFOEX pInfo;
		pInfo.cbSize = sizeof(pInfo);
		GetConsoleScreenBufferInfoEx(hOut, &pInfo);
		SetConsoleScreenBufferInfoEx(hOut, &pInfo);
		CONSOLE_SCREEN_BUFFER_INFO SBInfo;
		GetConsoleScreenBufferInfo(hOut, &SBInfo);
		COORD removebuffer = {
			SBInfo.srWindow.Right - SBInfo.srWindow.Left + 10,
			SBInfo.srWindow.Bottom - SBInfo.srWindow.Top + 10
		};
		SetConsoleScreenBufferSize(hOut, removebuffer);
		SYDEGamePlay::initialize_window(hOut, window);
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", BLACK);
			}
		}

		//HANDLE COMMAND
		if (cmd.compare("savegame") == 0)
		{
			MOTSDefaults::_CMD = "savegame";
			MOTSDefaults::HandleCMD = true;
		}
		if (cmd.compare("logclear") == 0)
		{
			MOTSDefaults::_CMD = "logclear";
			MOTSDefaults::HandleCMD = true;
		}
	}
	return window;
}
