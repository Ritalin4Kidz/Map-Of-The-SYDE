#pragma once
#include "SYDEstdafx.h"
#include "MOTSDefaults.h"
#include "CheatSettings.h"
#include <functional>
#include <ctime>
#include <fstream>
#include <istream>
#include <sstream>
#include "Structures.h"
#include "Player.h"
#include "Quest.h"
#include "TxtAdvVars.h"
#include "DefaultHouse.h"
#include "json.hpp"
#include "Pong.h"
using json = nlohmann::json;

class MapTile {
public:
	MapTile() {}
	MapTile(Vector2 pos, string name) { Pos = pos; TileName = name; }
	virtual ~MapTile() {}

	Vector2 Pos;
	string TileName;
};

class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;


	//CUTSCENES
	ConsoleWindow Sailing(ConsoleWindow window, int windowWidth, int windowHeight);
	void setSail(string a_STATE) { sailingTime = 0.0f; _STATESail = a_STATE; _STATE = "Sailing"; }
	ConsoleWindow Rest(ConsoleWindow window, int windowWidth, int windowHeight);
	void sleepAt(string a_STATE) { _STATERest = a_STATE; _STATE = "Resting"; m_NIGHT_TO_DAY.setFrame(0); }
	ConsoleWindow Warp(ConsoleWindow window, int windowWidth, int windowHeight);
	void setWarp(string a_STATE, CustomAsset _Level, Vector2 pos) { _STATEWarp = a_STATE; _STATE = "Warp"; m_DunegonWarp.setFrame(0); _levelWarp = _Level; _WarpPOS = pos; }
	ConsoleWindow Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset& _anim);
	void setAnimation_UI_EVENT(CustomAnimationAsset _Anim, string _Header) { m_MoveAnimation = _Anim; m_MoveAnimation.setFrame(0); UI_STATE_EVENT = true; _AnimHeader = _Header; }
	void goToDefault(string house, CustomAnimationAsset npc, vector<string> phrases) { m_NPC = npc; _DefaultHouseName = house; _DEFAULTPHRASES = phrases; }

	//ARCADE STUFF

	ConsoleWindow playPong(ConsoleWindow window, int windowWidth, int windowHeight) { if ((SYDEKeyCode::get_key(VK_BACK)._CompareState(KEYDOWN))) { _STATE = "CRT Arcade"; } return pongGame.draw_game(window, windowWidth, windowHeight); }

	//MAIN
	ConsoleWindow Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Controls(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Quest(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Map(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Player_Stats(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Player_Inventory(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Player_Customization(ConsoleWindow window, int windowWidth, int windowHeight);

	//TEST
	ConsoleWindow Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Building_Test(ConsoleWindow window, int windowWidth, int windowHeight);

	//ENEMIES
	ConsoleWindow Pig_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow HarmlessPig_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Wolf_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow RED_DRAGON_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Crab_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Fish_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Smoking_Crab_Fight(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Slimekeeper_Fight(ConsoleWindow window, int windowWidth, int windowHeight);

	//Jonestown//Repaired Coast
	ConsoleWindow Jonestown_Hall(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Jonestown_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//Blankis Island 2 wharfs
	ConsoleWindow SouthBlankis_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow EastBlankis_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//Ballistica
	ConsoleWindow Ballistica_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//Aliran Island
	ConsoleWindow Aliran_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//Repaired Coast
	ConsoleWindow Repaired_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//Taumatawhaka
	ConsoleWindow Taumata_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//CRT COAST 2 wharfs
	ConsoleWindow CRTCoast_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow CRTIsland_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	//SWAN LAKE
	ConsoleWindow SwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow NorthSwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Dragon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//Default
	ConsoleWindow Default_House(ConsoleWindow window, int windowWidth, int windowHeight);

	//Almon Island
	ConsoleWindow Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	// BEACHED ****Hole
	ConsoleWindow Jiman_House(ConsoleWindow window, int windowWidth, int windowHeight);

	//CRT ISLAND
	ConsoleWindow Retroist(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow CRT_Arcade(ConsoleWindow window, int windowWidth, int windowHeight);

	//Arcoomer
	ConsoleWindow Weapons_More(ConsoleWindow window, int windowWidth, int windowHeight);

	//Island Centre
	ConsoleWindow Island_Fitters(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Your_House(ConsoleWindow window, int windowWidth, int windowHeight);

	//TOPLEFIA PLACE
	ConsoleWindow Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Toplefia_TownHall(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Toplefia_Farm(ConsoleWindow window, int windowWidth, int windowHeight);

	//NORTHERN SYDE COAST
	ConsoleWindow WestSYDE_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow NorthSYDE_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//DENTON
	ConsoleWindow Denton_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//Cyprux
	ConsoleWindow Cyprux_Wharf(ConsoleWindow window, int windowWidth, int windowHeight);

	//OTHER
	ConsoleWindow Enemy_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset& _EnemAnim, int _run, bool& enemyAttk, bool bg_needed);
	ConsoleWindow DragonKeepBoss_Header(ConsoleWindow window, int windowWidth, int windowHeight, bool& enemyAttk);
	ConsoleWindow Wharf_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset& _NPCAnim);

	void fightBody(int& enemy_hp, bool& enemy_attack, float swordMulti, float fireMulti, float waterMulti, float grassMulti);

	//DUNGEONS
	ConsoleWindow Dragon_Keep_Dungeon(ConsoleWindow window, int windowWidth, int windowHeight);
	ConsoleWindow Text_Adventure_Dungeon(ConsoleWindow window, int windowWidth, int windowHeight);

	string ___IfUnlocked(bool unlocked, string use) { if (unlocked) { return use; } return "???"; }

	string getWFA_STATE(Vector2 point);
	int getWFA_LVL(Vector2 point);
	int getWFA_RUN(Vector2 point);
	string getSTRUCT_STATE(Vector2 point);
	string getSTRUCT_STATE(Vector2 point, bool display);
	DefaultHouse getHouse_FromPos(Vector2 point);
	string getSTRUCT_STATE(vector<Structure> _list, Vector2 point);
	string getTown(Vector2 point);

	int getColourFromLevel(Vector2 point);
	string getRandomFromList(vector<string> _list);

	void addLand(Vector2 a_Point);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour);
	void AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour, int a_lvl);

	void AddAttachmentStructure(Vector2 m_Point, string _arg, int colour);

	void AddDragonKeepAttachment(Vector2 m_Point, string _arg, int colour);
	void AddDungeonAttachment(CustomAsset _Dungeon, vector<Structure> listAdd, Vector2 m_Point, string _arg, int colour);
	string getSTRUCT_STATE(Vector2 point, vector<Structure> _list_struct);


	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) {m_State = newState;}

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight) { return m_State(window, windowWidth, windowHeight); }

	//OTHER VOIDS
	void setUpFight();
	void setUpWeaponShop(WeaponStore _store);
	void weaponStoreBody(int storeNo);
	void lvlUP();
	void saveGame();
	void loadSave();
	void loadDefaults();
	void enemy_dead();
	bool fexists(const char *filename);

	vector<string> Split(string a_String, char splitter);
	__Quest getByTag(string tag) { for (int i = 0; i < questVec.size(); i++) { if (tag.compare(questVec[i].getTag()) == 0) { return questVec[i]; } } return __Quest(); }

	void setByTag(string tag, bool newState, bool isSettingGiven);
	void setByTag(string tag, int amtDone);

	void setState(string newS) { _STATE = newS; }

	void _PlayerPage() {
		_MenuReturnSTATE = _STATE;
		_STATE = "Player_Stats";
	}

private:
#pragma region state
	string _STATE = "MainMenu";
	string _CurentSTATE = "MainMenu";
	string _MenuReturnSTATE = "MainMap";
	string _FightReturnSTATE = "MainMap";

	string _STATESail = "Toplefia Wharf";
	float sailingTime = 0.0f;
	const float maxSailTime = 5.5f;

	string _STATERest = "Toplefia Farm";

	//WARP
	string _STATEWarp = "Dragon Keep";
	CustomAsset _levelWarp = CustomAsset();
	Vector2 _WarpPOS = Vector2(0);

	bool UI_STATE_EVENT = false;
	string _AnimHeader = "";
#pragma endregion

	CustomAsset m_bg;
	CustomAsset m_crab_bg;
	CustomAsset _LevelAsset;
	CustomAsset _DragonKeepAsset;

	Vector2 camera_Pos;

	AssetsClass astVars;

	//MainMenu Vars
	CustomAnimationAsset m_MainMenu_BG;
	float time_passed = 0.0f;

	vector<WildFightAttachment> _list_fight_cases;
	vector<Structure> _list_structures;
	vector<Structure> _list_structures_dragon_keep;

	const char StructureChar = '-';
	const char WildFightChar = 'V';

	// PLAYER VALUES (GET LOADING FROM CONFIG FILE
	MOTS_Player player;

	//FIGHT
	int enemy_Health = 100;
	float enemy_Damage = 2;
	int enemy_exp_gained = 50;
	int enemy_lvl = 1;
	int enemy_run_chance = 100;
	bool enemy_attack = false;

	//MENUS
	SYDEMenu _Options;
	SYDEMenu _FightOptions;
	SYDEMenu _MoveOptions;
	SYDEMenu _MenuOptions;
	SYDEMenu _ColourOptions;

	FightWindow _FWindow;

	//CutScenes
	CustomAnimationAsset m_SAIL; // PLACHOLDER USED ATM
	CustomAnimationAsset m_NIGHT_TO_DAY;
	CustomAnimationAsset m_DunegonWarp;

	//MOVES
	CustomAnimationAsset m_MoveAnimation;
	vector<CustomAnimationAsset> m_Moves;


	//ENEMY ANIMATIONS
	CustomAnimationAsset m_ORC;
	CustomAnimationAsset m_PIG; // PLACHOLDER USED ATM
	CustomAnimationAsset m_WOLF; // PLACHOLDER USED ATM
	CustomAnimationAsset m_CRAB;
	CustomAnimationAsset m_FISH;

	vector<CustomAnimationAsset> m_Fishies;

	CustomAnimationAsset m_FLAME_SKULL;
	CustomAnimationAsset m_BLOOD_GHOST;

	CustomAnimationAsset m_RED_DRAGON; // PLACHOLDER USED ATM
	CustomAnimationAsset m_SMOKING_CRAB;

	//NPC
	CustomAnimationAsset m_PLACEHOLDER;

	//DEFAULTS
	vector<DefaultHouse> Houses = vector<DefaultHouse>();
	string _DefaultHouseName = "";
	vector<string> _DEFAULTPHRASES = vector<string>();
	vector<CustomAnimationAsset> m_NPCs;
	CustomAnimationAsset m_NPC;

	//ETC
	vector<_Town_Square> vecTowns;
	vector<string> vecIcons = {
		"><",	"//",	"nn",	":|",	"][",	"/\\",
		"[]",	"XX",	"ii",	":)",	")(",	"\\/",
		"()",	"$$",	"ll",	":(",	"}{",	"\\\\",
		"<>",	"!!",	"00",	";)",	"S2",	"\"\"",
		"{}",	"AA",	"96",	";(",	"2S",	":\\",
		"**",	"VV",	"bd",	";|",	"<3",	";\\",
		"##",	"--",	"''",	");",	":3",	"pi",
		"++",	"ZZ",	"YY",	"(;",	":D",	"..",
		"::",	"TT",	"xx",	"|;",	"D:",	";:",
		"HH",	"~~",	"pq",	"(:",	":C",	"db",
		"@@",	"GG",	",,",	"):",	"C:",	"vv",
		"??",	"JK",	"^^",	"|:",	"3:",	"uu",
		";;",	"WP",	"hi",	"/:",	"<:",	"UU",
		"II",	"MM",	":;",	"/;",	">:",	"zz",
		"WW",	"NN",	"ww",	"qp",	":>",	"yy",
		"||",	"OO",	"oo",	"tt",	":<",	"``",
		"%%",	"Pq",	"ae",	"bb",	":O",	"  ",
	};
	int iconNo = 0;
	vector<ColourClass> vecIconCol = {
		BLACK,
		BLUE,
		RED,
		YELLOW,
		PURPLE,
		DARKBLUE,
		BRIGHTRED, 
		BRIGHTWHITE
	};
#pragma region WILD AREAS
	vector<string> Toplefia_WILD = {
		"PIG_FIGHT",
	};
	int toplefia_min_level = 1;
	int toplefia_max_level = 3;
	vector<string> Almon_WILD = {
		"ORC_FIGHT",
		"WOLF_FIGHT",
		"PIG_FIGHT",
	};
	int almon_min_level = 4;
	int almon_max_level = 10;

	vector<string> WEST_SYDE_WILD = {
		"ORC_FIGHT",
		"WOLF_FIGHT",
		"PIG_FIGHT",
	};
	int west_syde_min_level = 2;
	int west_syde_max_level = 5;

	vector<string> NORTH_MURIC_BEACH_WILD = {
		"CRAB_FIGHT",
		"FISH_FIGHT"
	};
	int north_muric_beach_min_level = 1;
	int north_muric_beach_max_level = 4;

	vector<string> DRAGON_KEEP_WILD = {
	"ORC_FIGHT",
	};
	int dragon_keep_min_level = 35;
	int dragon_keep_max_level = 43;

#pragma endregion

	//STANDARD BUILDING
	SYDEMenu _StructOptions;
	SYDEMenu _StructTestOptions;
	//Special Buildings
	SYDEMenu _WeaponsMoreOptions;

	//INV
	SYDEMenu _InventoryMenu;

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
			"'monsters' surrounding his house"}, "Beached_Pigs_Quest", 5),
		__Quest(vector<string> {
			"HOME IS WHERE THE HEART IS",
			"",
			"I've rented you out a place in",
			"the Island Centre. The world is",
			"Depending on you to complete",
			"your mission, even if it doesn't",
			"seem like it",
			" ",
			"- Anonymous"}, "Find_Home_Quest")
	};

	vector<WeaponStore> _WeaponStores = vector<WeaponStore>{ 
	WeaponStore( //WEAPON & MORE
		vector<int>{1000, 1500, 2500},
		vector<int>{2500, 4500, 6500},
		vector<int>{3000, 6500, 9500},
		vector<int>{5000, 7500, 12500}
	) };
	int questPage = 0;

	//TEXT ADVENTURE DUNGEON
	SYDEMenu _TextAdvOptions = SYDEMenu(vector<SYDEButton>{
		SYDEButton("", Vector2(3, 16), Vector2(36, 1), WHITE, true),
		SYDEButton("", Vector2(3, 17), Vector2(36, 1), WHITE, true),
		SYDEButton("", Vector2(3, 18), Vector2(36, 1), WHITE, true),
	});
	string _CurrentAdvRoom_ = "NULL";
	string _AdvRoom_ = "Room1";
	FightWindow _TextWindow;
	TxtAdvVars _TXT_VARS = TxtAdvVars();

	//TROPHIES
	vector<CustomAsset> m_Trophies;
	CustomAsset m_PlayerHouse_BG;
	bool allQuestsDone = false;
	bool checkQuests();


	//CRT ARCADE
	SYDEMenu _ArcadeOptions;
	Pong pongGame;

	//MAP
	CustomAsset blueBg;
	CustomAsset yellowBg;
	CustomAsset _Map;
	CustomAsset _Cursor;
#pragma region Tiles
	vector<MapTile> tiles__ = vector<MapTile>{
		MapTile(Vector2( 4,2), "Dissonant Waved Ocean"), // THANKS ME TRICKS AND), 
		MapTile(Vector2(8,2), "Almon Island"), // THANKS ME), 
		MapTile(Vector2(12,2), "Blankis Island"), // THANKS ME), 
		MapTile(Vector2(16,2), "Aliran Island"), // SUCK SHIT ALI),
		MapTile(Vector2(20,2), "Daggo Coast"), // FUCK YOU LEGO YODA), 
		MapTile(Vector2(24,2), "SYDE Coast"), // THANKS ME), 
		MapTile(Vector2(28,2), "Taumatawhaka"), // THANKS LEGO YODA (DISCORD)), 
		MapTile(Vector2(32,2), "Taumata Beach"), // THANKS LEGO YODA (DISCORD)),

		MapTile(Vector2(4, 4), "Toplefia Place"), // THANKS ME), 
		MapTile(Vector2(8, 4), "North Muric Coast"), // ALI FUCK YOU), 
		MapTile(Vector2(12,4), "Ballistica"), // THANKS ALI), 
		MapTile(Vector2(16,4), "Broken Coast West"), // THANKS ME),
		MapTile(Vector2(20,4), "Broken Coast East"), // THANKS ME), 
		MapTile(Vector2(24,4), "Repaired Coast"), // THANKS ME), 
		MapTile(Vector2(28,4), "Western Meow Coast"), // THANKS ASHIE), 
		MapTile(Vector2(32,4), "Eastern Meow Coast"), // THANKS ASHIE),

		MapTile(Vector2(4, 6), "Northen SYDE Coast"), // THANKS ME), 
		MapTile(Vector2(8, 6), "Beached Butthole"), // THANKS TRICKS), 
		MapTile(Vector2(12,6), "Arcoomer"), // THANKS ARCANA), 
		MapTile(Vector2(16,6), "Djungelskog"), // THANKS JACKSON),
		MapTile(Vector2(20,6), "Thrustbowl"), // THANKS TRICKS), 
		MapTile(Vector2(24,6), "Jonestown"), // THANKS LINDSAY), 
		MapTile(Vector2(28,6), "Swan Lake"), // THANKS PETE), 
		MapTile(Vector2(32,6), "Meow Coast Beach"), //THANKS ASHIE),

		MapTile(Vector2(4, 8), "Southern SYDE Coast"), // THANKS ME), 
		MapTile(Vector2(8, 8), "Western Plains"), // THANKS ME), 
		MapTile(Vector2(12,8), "Rhofields"), // THANKS ME),
		MapTile(Vector2(16,8), "Loot Lake"), //MORE LEGO YODA),
		MapTile(Vector2(20,8), "Kiffidle Lakes"), // THANKS ME), 
		MapTile(Vector2(24,8), "Arc Cove"), // THANKS ME),
		MapTile(Vector2(28,8), "Faraway"), // THANKS ME), 
		MapTile(Vector2(32,8), "32x Tile Sea"), // THANKS LEGO YODA (DISCORD)),

		MapTile(Vector2(4, 10), "Baffled Coast"), // THANKS ANDREW),
		MapTile(Vector2(8, 10), "Zengina"), // THANKS ANDREW), 
		MapTile(Vector2(12,10), "Capital Town"), // THANKS ME), 
		MapTile(Vector2(16,10), "Island Centre"), // THANKS ME),
		MapTile(Vector2(20,10), "New Xylsdia"), // THANKS ME), 
		MapTile(Vector2(24,10), "Eastern Plains"), // THANKS ME),
		MapTile(Vector2(28,10), "CRT Coast"), //FUCK YOU LEGO YODA), 
		MapTile(Vector2(32,10), "CRT Island"), //FUCK YOU LEGO YODA),

		MapTile(Vector2(4, 12), "Windan"), // THANKS ME), 
		MapTile(Vector2(8, 12), "Lake Entrance"), // THANKS CENTRAL COAST), 
		MapTile(Vector2(12,12), "Western SYDE River"), // THANKS ME), 
		MapTile(Vector2(16,12), "Eastern SYDE River"), // THANKS ME),
		MapTile(Vector2(20,12), "Denton"), // THANKS LUKE),
		MapTile(Vector2(24,12), "Denton Fields"), // THANKS LUKE), 
		MapTile(Vector2(28,12), "Jeff Coast"), // THANKS SIMON), 
		MapTile(Vector2(32,12), "Uncharted Territory"), // THANKS ME),

		MapTile(Vector2(4, 14), "Uncharted Territory"), // THANKS ME),
		MapTile(Vector2(8, 14), "New SYDE Town"), // THANKS ME), 
		MapTile(Vector2(12,14), "North Edgecliffe"), // THANKS ME),
		MapTile(Vector2(16,14), "Last Bay"), // THANKS ME),
		MapTile(Vector2(20,14), "Old Capital Town"), // THANKS ME), 
		MapTile(Vector2(24,14), "Cyprux"), // THANKS DOM),
		MapTile(Vector2(28,14), "Xylsdia Coast"), // FUCK YOU ME), 
		MapTile(Vector2(32,14), "Useless Sea"), // THANKS ME),

		MapTile(Vector2(4, 16), "Uncharted Territory"), // THANKS ME),
		MapTile(Vector2(8, 16), "Edgecliffe"), // THANKS ME), 
		MapTile(Vector2(12,16), "Eastcliffe"), // THANKS ME), 
		MapTile(Vector2(16,16), "Broken Beach"), // THANKS ME),
		MapTile(Vector2(20,16), "Southern Coast"), // THANKS ME),
		MapTile(Vector2(24,16), "Cyprux Beach"), // THANKS DOM), 
		MapTile(Vector2(28,16), "Haven's Corner"), // THANKS ME), 
		MapTile(Vector2(32,16), "South East Ocean"), // THANKS ME),
	};

	int getIndexOfTown(string name);

#pragma endregion
	int selectedIndex = 0;


#pragma region Items
	void potionFunc();
	eItem potion = eItem(std::bind(&SYDEMapGame::potionFunc,this), "Potion");
#pragma endregion
 };
