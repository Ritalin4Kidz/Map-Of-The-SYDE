#pragma once
#include "SYDEstdafx.h"
class MOTS_Player {
public:
	MOTS_Player() {}
	virtual ~MOTS_Player() {}

	void setHealth(int newHP) { play_health = newHP; }
	int getHealth() { return play_health; }

	void setMaxHealth(int newHP) { play_max_health = newHP; }
	int getMaxHealth() { return play_max_health; }

	void setLvl(int newlvl) { play_lvl = newlvl; }
	int getLvl() { return play_lvl; }

	void setXP(int newXP) { play_xp = newXP; }
	int getXP() { return play_xp; }

	void setXPNxtLvl(int newXPNxtLvl) { play_xp_to_next_level = newXPNxtLvl; }
	int getXPNxtLvl() { return play_xp_to_next_level; }

	void setSwordDmg(int dmg) { play_sword_dmg = dmg; }
	int getSwordDmg() { return play_sword_dmg; }

	void setFireSpellUnlocked(bool unlocked) { play_fire_spell = unlocked; }
	bool getFireSpellUnlocked() { return play_fire_spell; }
	void setFireDmg(int dmg) { play_fire_dmg = dmg; }
	int getFireDmg() { return play_fire_dmg; }

	void setWaterSpellUnlocked(bool unlocked) { play_water_spell = unlocked; }
	bool getWaterSpellUnlocked() { return play_water_spell; }
	void setWaterDmg(int dmg) { play_water_dmg = dmg; }
	int getWaterDmg() { return play_water_dmg; }

	void setGrassSpellUnlocked(bool unlocked) { play_grass_spell = unlocked; }
	bool getGrassSpellUnlocked() { return play_grass_spell; }
	void setGrassDmg(int dmg) { play_grass_dmg = dmg; }
	int getGrassDmg() { return play_grass_dmg; }
private:
	int play_health = 100;

	int play_max_health = 100;

	int play_lvl = 1;
	int play_xp = 0;
	int play_xp_to_next_level = 1000;

	int play_sword_dmg = 5;

	bool play_fire_spell = false;
	bool play_water_spell = true;
	bool play_grass_spell = false;

	int play_fire_dmg = 5;
	int play_water_dmg = 5;
	int play_grass_dmg = 5;
};

class FightWindow {
public:
	FightWindow() {}
	virtual ~FightWindow() {}

	void AddFString(string fstring);
	string getFString(int index) { if (index >= _fightStrings.size()) { return ""; } return _fightStrings[index]; }

	void clear() { _fightStrings.clear(); }
private:
	vector<string> _fightStrings = vector<string>();
};