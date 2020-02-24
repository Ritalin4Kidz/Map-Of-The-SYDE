#include "pch.h"
#include "CheatSettings.h"

bool CHEATCODES_MOTS::SPAMATTACKALLOWED = false;
bool CHEATCODES_MOTS::SPECIAL_ICONS = false;
bool CHEATCODES_MOTS::NOCLIP = false;

void CHEATCODES_MOTS::INIT_CHEATS(std::vector<std::string> cheats)
{
	for (int i = 0; i < cheats.size(); i++)
	{
		MOTSDefaults::AddLog("Cheat -- " + cheats[i]);
		if (cheats[i].compare("spamattkallow") == 0) { SPAMATTACKALLOWED = true; }
		else if (cheats[i].compare("urbanoutfits") == 0) { SPECIAL_ICONS = true; }
		else if (cheats[i].compare("noclip") == 0) { NOCLIP = true; }
	}
}
