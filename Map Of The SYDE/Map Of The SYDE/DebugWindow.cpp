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
	return window;
}
