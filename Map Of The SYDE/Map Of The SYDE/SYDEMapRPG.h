#pragma once
#include "SYDEstdafx.h"
#include "MOTSDefaults.h"
#include <functional>
#include <ctime>
#include <fstream>
#include <istream>
#include <sstream>

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

class _Town_Square {
public:
	_Town_Square() {}
	_Town_Square(Vector2 boundary1, Vector2 boundary2, string townName);
	virtual ~_Town_Square() {}

	string getAREA() { return _AREANAME; }
	bool inBounds(Vector2 point);

private:
	Vector2 TopLeft;
	Vector2 BottomRight;

	string _AREANAME = "???";
};

class Structure {
public:
	Structure() {}
	Structure(Vector2 _point, string _structurearg);
	virtual ~Structure() {}

	Vector2 getPoint() { return m_Point; }
	string getStructArg() { return m_STRUCT_ARG; }

private:
	string m_STRUCT_ARG = "";
	Vector2 m_Point = Vector2(0);
};

class WildFightAttachment {
public:
	WildFightAttachment() {}
	WildFightAttachment(Vector2 _point, string _wildfightarg);
	WildFightAttachment(Vector2 _point, string _wildfightarg, int a_Lvl);
	virtual ~WildFightAttachment() {}

	Vector2 getPoint() { return m_Point; }
	string getWildFightArg() { return m_WILD_FIGHT_ARG; }

	int getLvl() { return m_Lvl; }
private:
	string m_WILD_FIGHT_ARG = "";
	int m_Lvl = 0;
	Vector2 m_Point = Vector2(0);
};


class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	//MAIN
	ConsoleWindow Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight);

	//TEST
	ConsoleWindow Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Building_Test(ConsoleWindow window, int windowWidth, int windowHeight);

	//ENEMIES
	ConsoleWindow Pig_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Wolf_Fight(ConsoleWindow window, int windowWidth, int windowHeight);


	//Almon Island
	ConsoleWindow Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//TOPLEFIA PLACE
	ConsoleWindow Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	string ___IfUnlocked(bool unlocked, string use) { if (unlocked) { return use; } return "???"; }

	string getWFA_STATE(Vector2 point);
	int getWFA_LVL(Vector2 point);
	string getSTRUCT_STATE(Vector2 point);
	string getTown(Vector2 point);

	int getColourFromLevel(Vector2 point);
	string getRandomFromList(vector<string> _list);

	void AddAttachmentWildFight(Vector2 m_Point, string _arg);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour, int a_lvl);

	void AddAttachmentStructure(Vector2 m_Point, string _arg, int colour);

	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) {m_State = newState;}

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight) { return m_State(window, windowWidth, windowHeight); }

	//OTHER VOIDS
	void setUpFight();
	void lvlUP();
	void saveGame();
	void loadSave();

	vector<string> Split(string a_String, char splitter);

private:
	string _STATE = "MainMenu";
	string _CurentSTATE = "MainMenu";
	CustomAsset m_bg;
	CustomAsset _LevelAsset;

	Vector2 camera_Pos;

	AssetsClass astVars;

	//MainMenu Vars
	CustomAnimationAsset m_MainMenu_BG;
	float time_passed = 0.0f;
	SYDEMenu _Options;

	vector<WildFightAttachment> _list_fight_cases;
	vector<Structure> _list_structures;

	const char StructureChar = '0';

	// PLAYER VALUES (GET LOADING FROM CONFIG FILE
	MOTS_Player player;

	//FIGHT
	int enemy_Health = 100;
	int enemy_Damage = 2;
	int enemy_exp_gained = 50;
	int enemy_lvl = 1;

	SYDEMenu _FightOptions;
	SYDEMenu _MoveOptions;

	FightWindow _FWindow;

	//ENEMY ANIMATIONS
	CustomAnimationAsset m_ORC;
	CustomAnimationAsset m_PIG; // PLACHOLDER USED ATM
	CustomAnimationAsset m_WOLF; // PLACHOLDER USED ATM

	//ETC
	vector<_Town_Square> vecTowns;

	//WILD AREAS
	vector<string> Almon_WILD = {
		"ORC_FIGHT",
		"WOLF_FIGHT",
		"PIG_FIGHT",
	};
	int almon_min_level = 4;
	int almon_max_level = 10;

	//STANDARD BUILDING
	SYDEMenu _StructOptions;

	// SAVED VARIABLES (e.g. quest booleans)
 };
