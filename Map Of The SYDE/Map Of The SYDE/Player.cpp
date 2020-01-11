#include "pch.h"
#include "Player.h"

void FightWindow::AddFString(string fstring)
{
	if (_fightStrings.size() >= 8)
	{
		for (int i = 1; i < 8; i++)
		{
			_fightStrings[i - 1] = _fightStrings[i];
		}
		_fightStrings[7] = fstring;
	}
	else {
		_fightStrings.push_back(fstring);
	}
}