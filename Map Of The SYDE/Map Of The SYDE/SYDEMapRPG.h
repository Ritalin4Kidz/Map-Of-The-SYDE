#pragma once
#include "SYDEstdafx.h"
#include "MOTSDefaults.h"
#include <functional>
#include <ctime>
#include <fstream>
#include <istream>
#include <sstream>
#include "Structures.h"
#include "Player.h"

class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;


	//CUTSCENES
	ConsoleWindow Sailing(ConsoleWindow window, int windowWidth, int windowHeight);
	void setSail(string a_STATE) { sailingTime = 0.0f; _STATESail = a_STATE; _STATE = "Sailing"; }

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
	ConsoleWindow Toplefia_TownHall(ConsoleWindow window, int windowWidth, int windowHeight);

	//OTHER
	ConsoleWindow Enemy_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _EnemAnim);
	ConsoleWindow Wharf_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _NPCAnim);

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
	void enemy_dead();

	vector<string> Split(string a_String, char splitter);

private:
	string _STATE = "MainMenu";
	string _CurentSTATE = "MainMenu";

	string _STATESail = "Toplefia Wharf";
	float sailingTime = 0.0f;
	const float maxSailTime = 5.5f;

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

	//CutScenes
	CustomAnimationAsset m_SAIL; // PLACHOLDER USED ATM

	//ENEMY ANIMATIONS
	CustomAnimationAsset m_ORC;
	CustomAnimationAsset m_PIG; // PLACHOLDER USED ATM
	CustomAnimationAsset m_WOLF; // PLACHOLDER USED ATM

	//NPC
	CustomAnimationAsset m_PLACEHOLDER;

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
