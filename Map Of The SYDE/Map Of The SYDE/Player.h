#pragma once
#include "SYDEstdafx.h"
#include "Inventory.h"
class MOTS_Player {
public:
	MOTS_Player() {}
	virtual ~MOTS_Player() {}

	Inventory _Inventory = Inventory();

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
	int  getGrassDmg() { return play_grass_dmg; }

	void setMoneySpellUnlocked(bool unlocked) { play_money_spell = unlocked; }
	bool getMoneySpellUnlocked() { return play_money_spell; }
	void setMoneyDmg(int dmg) { play_money_multi = dmg; }
	int  getMoneyDmg() { return play_money_multi; }

	//etc values
	void setMoney(int coins) { player_money = coins; }
	void addMoney(int coins) { player_money += coins; }
	int getMoney() { return player_money; }
	void spendMoney(int coins) { player_money -= coins; }

	void setIcon(string _ICON) { player_icon = _ICON; }
	string getIcon() { return player_icon; }

	void setColour(ColourClass colour) { player_colour = colour; }
	ColourClass getColour() { return player_colour; }
private:
	int play_health = 100;

	int play_max_health = 100;

	int play_lvl = 1;
	int play_xp = 0;
	int play_xp_to_next_level = 1000;

	int play_sword_dmg = 5;

	bool play_fire_spell = false;
	bool play_water_spell = false;
	bool play_grass_spell = false;
	bool play_money_spell = false;

	int play_fire_dmg = 5;
	int play_water_dmg = 5;
	int play_grass_dmg = 5;
	int play_money_multi = 2;

	// etc values
	int player_money = 0;

	string player_icon = "><";
	ColourClass player_colour = BLACK;
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