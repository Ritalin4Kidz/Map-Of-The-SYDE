#include "pch.h"
#include "CheatSettings.h"

bool CHEATCODES_MOTS::SPAMATTACKALLOWED = false;

void CHEATCODES_MOTS::INIT_CHEATS(std::vector<std::string> cheats)
{
	for (int i = 0; i < cheats.size(); i++)
	{
		MOTSDefaults::AddLog("Cheat -- " + cheats[i]);
		if (cheats[i].compare("spamattkallow") == 0) { SPAMATTACKALLOWED = true; }
	}
}
