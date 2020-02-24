#pragma once
#include <vector>
#include <string>
#include "MOTSDefaults.h"
class CHEATCODES_MOTS {
public:
	static bool SPAMATTACKALLOWED;
	static bool SPECIAL_ICONS;
	static bool NOCLIP;

	static void INIT_CHEATS(std::vector<std::string> cheats);
};