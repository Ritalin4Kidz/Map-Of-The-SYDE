#pragma once
#include "SYDEstdafx.h"
#include <ctime>

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
	virtual ~WildFightAttachment() {}

	Vector2 getPoint() { return m_Point; }
	string getWildFightArg() { return m_WILD_FIGHT_ARG; }
private:
	string m_WILD_FIGHT_ARG = "";
	Vector2 m_Point = Vector2(0);
};


class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	ConsoleWindow Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow Building_Test(ConsoleWindow window, int windowWidth, int windowHeight);

	string getWFA_STATE(Vector2 point);
	string getSTRUCT_STATE(Vector2 point);
	string getTown(Vector2 point);

	void AddAttachmentWildFight(Vector2 m_Point, string _arg);
	void AddAttachmentStructure(Vector2 m_Point, string _arg);
private:
	string _STATE = "MainMenu";
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
	int play_health = 100;
	int play_dmg = 5;
	int play_lvl = 1;
	int play_xp = 0;
	int play_xp_to_next_level = 1000;

	//FIGHT
	int enemy_Health = 100;
	int enemy_Damage = 2;
	int enemy_exp_gained = 50;
	SYDEMenu _FightOptions;

	//ENEMY ANIMATIONS
	CustomAnimationAsset m_ORC;

	//ETC
	vector<_Town_Square> vecTowns;

	//STANDARD BUILDING
	SYDEMenu _StructOptions;
 };