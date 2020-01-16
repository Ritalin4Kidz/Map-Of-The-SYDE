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
#include "Quest.h"

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
	ConsoleWindow Quest(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Player_Stats(ConsoleWindow window, int windowWidth, int windowHeight);

	//TEST
	ConsoleWindow Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Building_Test(ConsoleWindow window, int windowWidth, int windowHeight);

	//ENEMIES
	ConsoleWindow Pig_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow HarmlessPig_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Wolf_Fight(ConsoleWindow window, int windowWidth, int windowHeight);

	//Jonestown//Repaired Coast
	ConsoleWindow Jonestown_Hall(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Jonestown_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//SWAN LAKE
	ConsoleWindow SwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow NorthSwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Dragon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//Almon Island
	ConsoleWindow Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	// BEACHED ****Hole
	ConsoleWindow Jiman_House(ConsoleWindow window, int windowWidth, int windowHeight);

	//TOPLEFIA PLACE
	ConsoleWindow Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Toplefia_TownHall(ConsoleWindow window, int windowWidth, int windowHeight);

	//DENTON
	ConsoleWindow Denton_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//Cyprux
	ConsoleWindow Cyprux_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//OTHER
	ConsoleWindow Enemy_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _EnemAnim);
	ConsoleWindow Wharf_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _NPCAnim);


	//DUNGEONS
	ConsoleWindow Dragon_Keep_Dungeon(ConsoleWindow window, int windowWidth, int windowHeight);

	string ___IfUnlocked(bool unlocked, string use) { if (unlocked) { return use; } return "???"; }

	string getWFA_STATE(Vector2 point);
	int getWFA_LVL(Vector2 point);
	string getSTRUCT_STATE(Vector2 point);
	string getTown(Vector2 point);

	int getColourFromLevel(Vector2 point);
	string getRandomFromList(vector<string> _list);

	void addLand(Vector2 a_Point);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour, int a_lvl);

	void AddAttachmentStructure(Vector2 m_Point, string _arg, int colour);

	void AddDungeonAttachment(CustomAsset _Dungeon, vector<Structure> listAdd, Vector2 m_Point, string _arg, int colour);
	string getSTRUCT_STATE(Vector2 point, vector<Structure> _list_struct);


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
	__Quest getByTag(string tag) { for (int i = 0; i < questVec.size(); i++) { if (tag.compare(questVec[i].getTag()) == 0) { return questVec[i]; } } return __Quest(); }

	void setByTag(string tag, bool newState, bool isSettingGiven);
	void setByTag(string tag, int amtDone);

	void _PlayerPage() {
		_MenuReturnSTATE = _STATE;
		_STATE = "Player_Stats";
	}

private:
	string _STATE = "MainMenu";
	string _CurentSTATE = "MainMenu";
	string _MenuReturnSTATE = "MainMap";

	string _STATESail = "Toplefia Wharf";
	float sailingTime = 0.0f;
	const float maxSailTime = 5.5f;

	CustomAsset m_bg;
	CustomAsset _LevelAsset;
	CustomAsset _DragonKeepAsset;

	Vector2 camera_Pos;

	AssetsClass astVars;

	//MainMenu Vars
	CustomAnimationAsset m_MainMenu_BG;
	float time_passed = 0.0f;
	SYDEMenu _Options;

	vector<WildFightAttachment> _list_fight_cases;
	vector<Structure> _list_structures;
	vector<Structure> _list_structures_dragon_keep;

	const char StructureChar = '0';

	// PLAYER VALUES (GET LOADING FROM CONFIG FILE
	MOTS_Player player;

	//FIGHT
	int enemy_Health = 100;
	float enemy_Damage = 2;
	int enemy_exp_gained = 50;
	int enemy_lvl = 1;

	SYDEMenu _FightOptions;
	SYDEMenu _MoveOptions;
	SYDEMenu _MenuOptions;

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
	SYDEMenu _StructTestOptions;

	// SAVED VARIABLES (e.g. quest booleans)
	vector<__Quest> questVec = vector<__Quest>
	{
		__Quest(vector<string>{
			"DRAGON KEEPER",
			"",
			"SYDE Island is under the threat",
			"of attack by a dragon roosting",
			"in the middle of dragon keep.",
			"Travel to Swan Lake and kill",
			"the dragon before it's too late!"}, "Jonestown_Main_Quest"),
		__Quest(vector<string> {
			"HOUSE SAVIOUR",
			"",
			"Jiman wants you to get rid of the",
			"'monsters' surrounding his house"}, "Beached_Pigs_Quest", 5)
	};
	int questPage = 0;
 };
