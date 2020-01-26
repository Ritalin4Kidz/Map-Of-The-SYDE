#pragma once
#include "SYDEstdafx.h"
#include "MOTSDefaults.h"

class DebugWindow {
public:
	DebugWindow() {}
	DebugWindow(int linesMax) { __linesMax = linesMax; }
	virtual ~DebugWindow() {}

	void AddDebugString(string dstring);
	string getDebugString(int index) { if (index >= _debugStrings.size()) { return ""; } return _debugStrings[index]; }

	void clear() { _debugStrings.clear(); }
private:
	vector<string> _debugStrings = vector<string>();
	int __linesMax;
};

class DebugW : public SYDEWindowGame {
public:
	DebugW() {}
	virtual ~DebugW() {}


	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
private:
	DebugWindow debugger = DebugWindow(15);
};
