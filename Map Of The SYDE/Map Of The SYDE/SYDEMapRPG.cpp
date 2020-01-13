#include "pch.h"
#include "SYDEMapRPG.h"

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg)
{
	_LevelAsset.setCharAtPoint(m_Point, 'V');
	_LevelAsset.setColourAtPoint(m_Point, 32);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg));
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour)
{
	_LevelAsset.setCharAtPoint(m_Point, 'V');
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg));
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour, int a_lvl)
{
	_LevelAsset.setCharAtPoint(m_Point, 'V');
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg, a_lvl));
}

void SYDEMapGame::AddAttachmentStructure(Vector2 m_Point, string _arg, int colour)
{
	_LevelAsset.setCharAtPoint(m_Point, StructureChar);
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_structures.push_back(Structure(m_Point, _arg));
}

void SYDEMapGame::setUpFight()
{
	_MoveOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Sword", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getFireSpellUnlocked(), "Fire Spell"), Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getWaterSpellUnlocked(), "Water Spell"), Vector2(1, 4), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getGrassSpellUnlocked(), "Grass Spell"), Vector2(1, 5), Vector2(20, 1), WHITE, true),
			SYDEButton("Back", Vector2(1, 6), Vector2(20, 1), WHITE, true)
	});

	_MoveOptions[0].m_Label = "0";
	_MoveOptions[1].m_Label = ___IfUnlocked(player.getFireSpellUnlocked(), "1");
	_MoveOptions[2].m_Label = ___IfUnlocked(player.getWaterSpellUnlocked(), "2");
	_MoveOptions[3].m_Label = ___IfUnlocked(player.getGrassSpellUnlocked(), "3");
	_MoveOptions[4].m_Label = "4";

	_MoveOptions.setActive(false);
	_MoveOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _MoveOptions.getSize(); i++)
	{
		_MoveOptions[i].setHighLight(RED);
	}
	_FightOptions.setActive(true);
}

void SYDEMapGame::lvlUP()
{
	while (player.getXP() >= player.getXPNxtLvl()) {
		player.setLvl(player.getLvl() + 1);
		player.setMaxHealth(player.getMaxHealth() + 22);
		player.setHealth(player.getMaxHealth()); // HEAL ON LVL UP
		player.setXP(player.getXP() - player.getXPNxtLvl());
		player.setXPNxtLvl(player.getXPNxtLvl() * 1.1f);
	}
	//saveGame(); - Probs introduce fountains of saving or something
}

void SYDEMapGame::saveGame()
{
	ofstream FileOut("EngineFiles\\Settings\\MOTS_SaveFile.sc");
	//LEVELS
	FileOut << "//PLAYERSTATS" << endl;
	FileOut << "PlayerLVL:" + to_string(player.getLvl()) << endl;
	FileOut << "PlayerHP:" + to_string(player.getHealth()) << endl;
	FileOut << "PlayerHPMax:" + to_string(player.getMaxHealth()) << endl;
	FileOut << "PlayerXP:" + to_string(player.getXP()) << endl;
	FileOut << "PlayerXPNxt:" + to_string(player.getXPNxtLvl()) << endl;
	FileOut << "PosX:" + to_string(camera_Pos.getX()) << endl;
	FileOut << "PosY:" + to_string(camera_Pos.getY()) << endl;


	FileOut << "//QUESTS" << endl;
}

void SYDEMapGame::loadSave()
{
	ifstream File("EngineFiles\\Settings\\MOTS_SaveFile.sc", ios::binary | ios::in);
	if (File.is_open())
	{
		string line;
		vector<string> FileLines;
		while (getline(File, line, '\n'))
		{
			FileLines = Split(line, ':');
			if (FileLines[0] == "PlayerLVL")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				player.setLvl(tempVal);
			}
			else if (FileLines[0] == "PlayerHP")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				player.setHealth(tempVal);
			}
			else if (FileLines[0] == "PlayerHPMax")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				player.setMaxHealth(tempVal);
			}
			else if (FileLines[0] == "PlayerXP")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				player.setXP(tempVal);
			}
			else if (FileLines[0] == "PlayerXPNxt")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				player.setXPNxtLvl(tempVal);
			}
			else if (FileLines[0] == "PosX")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				camera_Pos.setX(tempVal);
			}
			else if (FileLines[0] == "PosY")
			{
				int tempVal;
				std::istringstream(FileLines[1]) >> tempVal;
				camera_Pos.setY(tempVal);
			}
		}
	}
}

void SYDEMapGame::enemy_dead()
{
	player.setXP(player.getXP() + enemy_exp_gained);
	lvlUP();
	_FWindow.clear();
	_STATE = "MainMap";
}

vector<string> SYDEMapGame::Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

void SYDEMapGame::setByTag(string tag, bool newState, bool isSettingGiven)
{
	for (int i = 0; i < questVec.size(); i++) 
	{ 
		if (tag.compare(questVec[i].getTag()) == 0) 
		{ 
			if (isSettingGiven)
			{
				questVec[i].setGiven(newState);
			}
			else {
				questVec[i].setFinished(newState);
			}
		} 
	}
}

SYDEMapGame::SYDEMapGame()
{
	AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_list_fight_cases = vector<WildFightAttachment>();
	_list_structures = vector<Structure>();
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	_LevelAsset = CustomAsset(2048, 768, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Level_SYDE.bmp", 1024, 768));
	camera_Pos = Vector2(214,173);

	// LIST OF ALL TOWNS
	vecTowns = vector<_Town_Square>{
		//A
		_Town_Square(Vector2(0,		0), Vector2(255,	95) , "Dissonant Waved Ocean"), // THANKS ME TRICKS AND DOM
		_Town_Square(Vector2(256,	0), Vector2(511,	95) , "Almon Island"), // THANKS ME
		_Town_Square(Vector2(512,	0), Vector2(767,	95) , "Blankis Island"), // THANKS ME
		_Town_Square(Vector2(768,	0), Vector2(1023,	95) , "Aliran Island"), // SUCK SHIT ALI
		_Town_Square(Vector2(1024,	0), Vector2(1279,	95) , "Daggo Coast"), // FUCK YOU LEGO YODA
		_Town_Square(Vector2(1280,	0), Vector2(1535,	95) , "SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	0), Vector2(1791,	95) , "Taumatawhaka"), // THANKS LEGO YODA (DISCORD)
		_Town_Square(Vector2(1792,	0), Vector2(2047,	95) , "Taumata Beach"), // THANKS ME
		//B
		_Town_Square(Vector2(0,		96), Vector2(255,	191), "Toplefia Place"), // THANKS ME
		_Town_Square(Vector2(256,	96), Vector2(511,	191), "North Muric Coast"), // ALI FUCK YOU
		_Town_Square(Vector2(512,	96), Vector2(767,	191), "Ballistica"), // THANKS ALI
		_Town_Square(Vector2(768,	96), Vector2(1023,	191), "Broken Coast West"), // THANKS ME
		_Town_Square(Vector2(1024,	96), Vector2(1279,	191), "Broken Coast East"), // THANKS ME
		_Town_Square(Vector2(1280,	96), Vector2(1535,	191), "Repaired Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	96), Vector2(1791,	191), "Western Meow Coast"), // THANKS ASHIE
		_Town_Square(Vector2(1792,	96), Vector2(2047,	191), "Eastern Meow Coast"), // THANKS ASHIE
		//C
		_Town_Square(Vector2(0,		192), Vector2(255,	287), "Northen SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	192), Vector2(511,	287), "Beached Butthole"), // THANKS TRICKS
		_Town_Square(Vector2(512,	192), Vector2(767,	287), "Arcoomer"), // THANKS ARCANA
		_Town_Square(Vector2(768,	192), Vector2(1023,	287), "Djungelskog"), // THANKS JACKSON
		_Town_Square(Vector2(1024,	192), Vector2(1279,	287), "Thrustbowl"), // THANKS TRICKS
		_Town_Square(Vector2(1280,	192), Vector2(1535,	287), "Jonestown"), // THANKS LINDSAY
		_Town_Square(Vector2(1536,	192), Vector2(1791,	287), "Swan Lake"), // THANKS PETE
		_Town_Square(Vector2(1792,	192), Vector2(2047,	287), "Meow Coast Beach"), //THANKS ASHIE
		//D
		_Town_Square(Vector2(0,		288), Vector2(255,	383), "Southern SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	288), Vector2(511,	383), "Western Plains"), // THANKS ME
		_Town_Square(Vector2(512,	288), Vector2(767,	383), "Rhofields"), // THANKS ME
		_Town_Square(Vector2(768,	288), Vector2(1023,	383), "Loot Lake"), //MORE LEGO YODA
		_Town_Square(Vector2(1024,	288), Vector2(1279,	383), "Kiffidle Lakes"), // THANKS ME
		_Town_Square(Vector2(1280,	288), Vector2(1535,	383), "Arc Cove"), // THANKS ME
		_Town_Square(Vector2(1536,	288), Vector2(1791,	383), "Faraway"), // THANKS ME
		_Town_Square(Vector2(1792,	288), Vector2(2047,	383), "32x Tile Sea"), // THANKS LEGO YODA (DISCORD)
		//E
		_Town_Square(Vector2(0,		384), Vector2(255,	479), "Baffled Coast"), // THANKS ANDREW
		_Town_Square(Vector2(256,	384), Vector2(511,	479), "Zengina"), // THANKS ANDREW
		_Town_Square(Vector2(512,	384), Vector2(767,	479), "Capital Town"), // THANKS ME
		_Town_Square(Vector2(768,	384), Vector2(1023,	479), "Island Centre"), // THANKS ME
		_Town_Square(Vector2(1024,	384), Vector2(1279,	479), "New Xylsdia"), // THANKS ME
		_Town_Square(Vector2(1280,	384), Vector2(1535,	479), "Eastern Plains"), // THANKS ME
		_Town_Square(Vector2(1536,	384), Vector2(1791,	479), "CRT Coast"), //FUCK YOU LEGO YODA
		_Town_Square(Vector2(1792,	384), Vector2(2047,	479), "CRT Island"), //FUCK YOU LEGO YODA
		//F
		_Town_Square(Vector2(0,		480), Vector2(255,	575), "Windan"), // THANKS ME
		_Town_Square(Vector2(256,	480), Vector2(511,	575), "Lake Entrance"), // THANKS CENTRAL COAST
		_Town_Square(Vector2(512,	480), Vector2(767,	575), "Western SYDE River"), // THANKS ME
		_Town_Square(Vector2(768,	480), Vector2(1023,	575), "Eastern SYDE River"), // THANKS ME
		_Town_Square(Vector2(1024,	480), Vector2(1279,	575), "Denton"), // THANKS LUKE
		_Town_Square(Vector2(1280,	480), Vector2(1535,	575), "Denton Fields"), // THANKS LUKE
		_Town_Square(Vector2(1536,	480), Vector2(1791,	575), "Jeff Coast"), // THANKS SIMON
		_Town_Square(Vector2(1792,	480), Vector2(2047,	575), "Uncharted Territory"), // THANKS ME
		//G
		_Town_Square(Vector2(0,		576), Vector2(255,	671), "Uncharted Territory"), // THANKS ME
		_Town_Square(Vector2(256,	576), Vector2(511,	671), "New SYDE Town"), // THANKS ME
		_Town_Square(Vector2(512,	576), Vector2(767,	671), "North Edgecliffe"), // THANKS ME
		_Town_Square(Vector2(768,	576), Vector2(1023,	671), "Last Bay"), // THANKS ME
		_Town_Square(Vector2(1024,	576), Vector2(1279,	671), "Old Capital Town"), // THANKS ME
		_Town_Square(Vector2(1280,	576), Vector2(1535,	671), "Cyprux"), // THANKS DOM
		_Town_Square(Vector2(1536,	576), Vector2(1791,	671), "Xylsdia Coast"), // FUCK YOU ME
		_Town_Square(Vector2(1792,	576), Vector2(2047,	671), "Useless Sea"), // THANKS ME
		//H
		_Town_Square(Vector2(0,		672), Vector2(255,	767), "Uncharted Territory"), // THANKS ME
		_Town_Square(Vector2(256,	672), Vector2(511,	767), "Edgecliffe"), // THANKS ME
		_Town_Square(Vector2(512,	672), Vector2(767,	767), "Eastcliffe"), // THANKS ME
		_Town_Square(Vector2(768,	672), Vector2(1023,	767), "Broken Beach"), // THANKS ME
		_Town_Square(Vector2(1024,	672), Vector2(1279,	767), "Southern Coast"), // THANKS ME
		_Town_Square(Vector2(1280,	672), Vector2(1535,	767), "Cyprux Beach"), // THANKS DOM
		_Town_Square(Vector2(1536,	672), Vector2(1791,	767), "Haven's Corner"), // THANKS ME
		_Town_Square(Vector2(1792,	672), Vector2(2047,	767), "South East Ocean"), // THANKS ME
	};

	//STRUCTURE 1 -- TEST STRUCTURE
	AddAttachmentStructure(Vector2(280, 190), "BUILDING_TEST", 7);
	AddAttachmentStructure(Vector2(281, 190), "BUILDING_TEST", 7);

	// WATER TEST: BUILDINGS ON WATER MEAN THAT TILE CAN BE WALKED ON :D
	// AddAttachmentStructure(Vector2(216, 172), "BUILDING_TEST", 7);
	// AddAttachmentStructure(Vector2(217, 172), "BUILDING_TEST", 7);

	//ORC WILD FIGHT 1 -- TEST FIGHT
	AddAttachmentWildFight(Vector2(280, 199), "ORC_TEST");
	AddAttachmentWildFight(Vector2(280, 198), "ORC_TEST");
	AddAttachmentWildFight(Vector2(280, 197), "ORC_TEST");
	AddAttachmentWildFight(Vector2(281, 199), "ORC_TEST");
	AddAttachmentWildFight(Vector2(281, 198), "ORC_TEST");
	AddAttachmentWildFight(Vector2(281, 197), "ORC_TEST");
	AddAttachmentWildFight(Vector2(282, 199), "ORC_TEST");
	AddAttachmentWildFight(Vector2(282, 198), "ORC_TEST");
	AddAttachmentWildFight(Vector2(282, 197), "ORC_TEST");
	AddAttachmentWildFight(Vector2(283, 199), "ORC_TEST");
	AddAttachmentWildFight(Vector2(283, 198), "ORC_TEST");
	AddAttachmentWildFight(Vector2(283, 197), "ORC_TEST");

	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID A:2 - Almon Island
	AddAttachmentStructure(Vector2(392, 83), "Almon Wharf", 96);
	AddAttachmentStructure(Vector2(393, 83), "Almon Wharf", 96);

	//ADD WILD AREAS IN BOUUNDARIES 402,85  451,85,  402,68   451,68
	for (int ii = 68; ii < 86; ii++)
	{
		for (int i = 402; i < 452; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 32)
			{
				string wfs = getRandomFromList(Almon_WILD);
				int lvlEnemy = (std::rand() % (almon_max_level - almon_min_level)) + almon_min_level;
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}

	// STRUCTURES && WILD FIGHT AREAS INSIDE Jonestown + Repaired Coast

	for (int ii = 181; ii < 184; ii++)
	{
		for (int i = 1344; i < 1360; i ++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Jonestown Hall", 64);
		}
	}

	// BEACHED ****Hole
	for (int ii = 224; ii < 230; ii++)
	{
		for (int i = 356; i < 364; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Jiman's House", 64);
		}
	}

	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID B:1 - Toplefia Place

	for (int ii = 199; ii < 206; ii++)
	{
		for (int i = 220; i < 232; i += 2)
		{
			AddAttachmentStructure(Vector2(i, ii), "Toplefia Town Hall", 64);
			AddAttachmentStructure(Vector2(i + 1, ii), "Toplefia Town Hall", 64);
		}
	}

	AddAttachmentStructure(Vector2(210, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(216, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(217, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(216, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(217, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 174), "Toplefia Wharf", 96);

	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID C:6 - Jonestown

	//MAIN MENU VARS
	_Options = SYDEMenu(vector<SYDEButton> {	
		SYDEButton("", Vector2(0, 1), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 2), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 3), Vector2(20, 1), WHITE, true),
	});

	_StructOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("--", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton("--", Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton("Leave", Vector2(1, 4), Vector2(20, 1), WHITE, true),
	});

	_StructOptions[0].m_Label = "0";
	_StructOptions[1].m_Label = "1";
	_StructOptions[2].m_Label = "2";

	_StructOptions.setActive(true);
	_StructOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _StructOptions.getSize(); i++)
	{
		_StructOptions[i].setHighLight(RED);
	}

	_FightOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Fight", Vector2(1, 2), Vector2(20, 1), WHITE, true),
		SYDEButton("Run", Vector2(1, 3), Vector2(20, 1), WHITE, true)
	});
	
	_FightOptions[0].m_Label = "0";
	_FightOptions[1].m_Label = "1";

	_FightOptions.setActive(true);
	_FightOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _FightOptions.getSize(); i++)
	{
		_FightOptions[i].setHighLight(RED);
	}

	m_MainMenu_BG.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\MainMenuAnim.bmp", astVars, 100, 180, 20, 20, 0, 45));
	m_MainMenu_BG.setLooping(true);
	_Options[0].m_Label = "0";
	_Options[1].m_Label = "1";
	_Options[2].m_Label = "2";

	_Options[0].setText("Continue");
	_Options[1].setText("New Game");
	_Options[2].setText("Exit Game");

	_Options.setActive(true);
	_Options.setPos(Vector2(0, 0));
	for (int i = 0; i < _Options.getSize(); i++)
	{
		_Options[i].setHighLight(RED);
	}

	//ENEMY ANIMATIONS
	m_ORC.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", astVars, 100, 30, 10, 10, 0, 27));
	m_ORC.setLooping(true);

	m_PIG.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", astVars, 100, 30, 10, 10, 0, 27)); // PLACEHOLDER ANIM
	m_PIG.setLooping(true);

	m_WOLF.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", astVars, 100, 30, 10, 10, 0, 27)); // PLACEHOLDER ANIM
	m_WOLF.setLooping(true);

	//CUTSCENES
	m_SAIL.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\SailingAnimation.bmp", astVars, 160, 20, 20, 20, 0, 8));
	m_SAIL.setLooping(true);

	//NPC
	m_PLACEHOLDER.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Bitmaps\\NPC_Placeholder.bmp", astVars, 10, 10, 10, 10, 0, 1));
	m_PLACEHOLDER.setLooping(true);
}

ConsoleWindow SYDEMapGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (_CurentSTATE.compare(_STATE) != 0)
	{
		// SO NOW IT IS THE CURRENT STATE
		_CurentSTATE = _STATE;
		if (_STATE == "MainMap")
		{
			//window = Main_Map_Scene(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Main_Map_Scene, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		}
		else if (_STATE == "Sailing")
		{
			AssignState(std::bind(&SYDEMapGame::Sailing, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "MainMenu")
		{
			//window = Main_Menu(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "ORC_TEST")
		{
			//window = Orc_Fight(window, windowWidth, windowHeight);
			//GENERATE ORC FIGHT
			enemy_Damage = 2;
			enemy_exp_gained = 25000;
			enemy_Health = 100;

			setUpFight();
			//_STATE = "ORC_FIGHT";
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		//FIGHTS
		else if (_STATE == "ORC_FIGHT")
		{
			enemy_Damage = 2 * (enemy_lvl * 0.5f);
			enemy_exp_gained = 50 * (enemy_lvl * 1.5f);
			enemy_Health = 100 * (enemy_lvl * 1.1f);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "PIG_FIGHT")
		{
			enemy_Damage = 0;
			enemy_exp_gained = 10 * (enemy_lvl);
			enemy_Health = 20 * (enemy_lvl);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Pig_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "WOLF_FIGHT")
		{
			enemy_Damage = 4 * (enemy_lvl * 1.5f);
			enemy_exp_gained = 90 * (enemy_lvl * 1.5f);
			enemy_Health = 60 * (enemy_lvl * 1.5f);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Wolf_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "QUEST_PAGE")
		{
			//window = Building_Test(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Quest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//BUILDINGS
		else if (_STATE == "BUILDING_TEST")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("Upgrade Sword (Test");
			//window = Building_Test(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Building_Test, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//TOPLEFIA AREA
		else if (_STATE == "Toplefia Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Toplefia_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Toplefia Town Hall")
		{
			_StructOptions[0].setText("Speak"); //230,80
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Toplefia_TownHall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}

		//Beached ***hole
		else if (_STATE == "Jiman's House")
		{
			_StructOptions[0].setText("Speak"); //230,80
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Jiman_House, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//JONESTOWN
		else if (_STATE == "Jonestown Hall")
		{
			_StructOptions[0].setText("Speak"); //230,80
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Jonestown_Hall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//ALMON ISLAND
		else if (_STATE == "Almon Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Almon_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else {
			//FAILSAFE
			AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
	}
	window = DoState(window,windowWidth,windowHeight);
	return window;
}

ConsoleWindow SYDEMapGame::Sailing(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_SAIL.draw_asset(window, Vector2(0, 0));
	sailingTime += SYDEDefaults::getDeltaTime();
	window.setTextAtPoint(Vector2(0, 1), "Traveling To '" + _STATESail + "'", BLACK_WHITE_BG);
	if (sailingTime >= maxSailTime)
	{
		_STATE = _STATESail;
	}
	return window;
}

ConsoleWindow SYDEMapGame::Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = _LevelAsset.draw_asset(window, Vector2(camera_Pos.getX()-20, camera_Pos.getY()-10), windowWidth, windowHeight);

	//UI
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", RED_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 1), "Area: " + getTown(camera_Pos), RED_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "Health: " + std::to_string(player.getHealth()) + ", Lvl: " + std::to_string(player.getLvl()) + ", XP: " + std::to_string(player.getXP()), RED_WHITE_BG);


	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10) , "><", window.determineColourAtPoint(Vector2(20, 10), BLACK, true));
	char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
	if (tempChar == StructureChar)
	{
		window.setTextAtPoint(Vector2(0, 19), "'" + getSTRUCT_STATE(camera_Pos) + "' Press Space To Enter", BLACK_WHITE_BG);
	}

	if (SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == StructureChar)
		{
			_STATE = getSTRUCT_STATE(camera_Pos);
		}
	}
	if (SYDEKeyCode::get('I')._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		_STATE = "QUEST_PAGE";
	}
	if (SYDEKeyCode::get('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 11)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == 'V')
		{
			if (random_variable == 15)
			{
				// SET ENEMY AND LEVEL
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
			}
		}
		
		// CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(1);
		}
	}
	if (SYDEKeyCode::get('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22, 10)));
		//CASES FOR MOVEMENT NOT ALLOWED
		//window.setTextAtPoint(Vector2(0, 1),temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == 'V')
		{
			if (random_variable == 26)
			{
				// SET ENEMY AND LEVEL
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
			}
		}

		if (temp.compare("17") != 0 && temp.compare("16") != 0) //Note, make from 16 -31
		{
			camera_Pos.addX(2);
		}
	}
	if (SYDEKeyCode::get('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 9)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == 'V')
		{
			if (random_variable == 7)
			{
				// SET ENEMY AND LEVEL
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
			}
		}

		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(-1);
		}
	}
	if (SYDEKeyCode::get('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18, 10)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == 'V')
		{
			if (random_variable == 30)
			{
				// SET ENEMY AND LEVEL
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
			}
		}

		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addX(-2);
		}
	}
	if (MOTSDefaults::DEBUG_UI_)
	{
		window.setTextAtPoint(Vector2(0, 2), to_string((int)camera_Pos.getX()) + "," + to_string((int)camera_Pos.getY()), RED_WHITE_BG);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//for (int l = 0; l < windowWidth; l++)
	//{
	//	for (int m = 0; m < windowHeight; m++)
	//	{
	//		window.setTextAtPoint(Vector2(l, m), " ", BLACK);
	//	}
	//}
	window = m_MainMenu_BG.draw_asset(window, Vector2(0,0));
	if (time_passed < 0.15f)
	{
		if (m_MainMenu_BG.getFrame() == 0)
		{
			m_MainMenu_BG.setFrame(m_MainMenu_BG.getFrameSize());
		}
		else {
			m_MainMenu_BG.setFrame(m_MainMenu_BG.getFrame() - 1);
		}
		time_passed += SYDEDefaults::getDeltaTime();
	}
	else
	{
		time_passed = 0.0f;
	}
	window = _Options.draw_menu(window);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_Options.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_Options.getSelected().m_Label == "0")
		{
			//LOAD SAVE
			loadSave();
			_STATE = "MainMap";
		}
		else if (_Options.getSelected().m_Label == "1")
		{
			// REVERT EVERYTHING TO DEFAULT VARS
			_STATE = "MainMap";
		}
		else if (_Options.getSelected().m_Label == "2")
		{
			exit(NULL);
		}
	}
	return window;
}

ConsoleWindow SYDEMapGame::Quest(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	if (SYDEKeyCode::get('I')._CompareState(KEYDOWN))
	{
		_STATE = "MainMap";
	}
	if (SYDEKeyCode::get('A')._CompareState(KEYDOWN))
	{
		questPage--;
		if (questPage < 0)
		{
			questPage = questVec.size() - 1;
		}
	}
	if (SYDEKeyCode::get('D')._CompareState(KEYDOWN))
	{
		questPage++;
		if (questPage > questVec.size() - 1)
		{
			questPage = 0;
		}
	}
	window.setTextAtPoint(Vector2(0,1),questVec[questPage].getDetails(), BLACK_WHITE_BG);
	return window;
}

ConsoleWindow SYDEMapGame::Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_ORC);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
		{
			_MoveOptions.nextSelect();
		}
		if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_MoveOptions.getSelected().m_Label == "0")
			{
				//FIGHT SEQUENCE SWORD
				int dmgApplied = player.getSwordDmg() * 1 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Sword");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "1")
			{
				int dmgApplied = player.getFireDmg() * 2 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Fire");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "2")
			{
				int dmgApplied = player.getWaterDmg() * 0.5f * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Water");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "3")
			{
				int dmgApplied = player.getGrassDmg() * 0 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Grass");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "4")
			{
				_FightOptions.setActive(true);
				_MoveOptions.setActive(false);
			}
		}
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Orc Used Club");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Building_Test(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "BUILDING_TEST", BLACK_WHITE_BG);

	window = _StructOptions.draw_menu(window);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Man: You Poor Lad");
			_FWindow.AddFString("Man: Rest Up My Son");
			_FWindow.AddFString("*HEALTH RESTORED*");
			player.setHealth(player.getMaxHealth());
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			player.setSwordDmg(player.getSwordDmg() + 1);
			_FWindow.AddFString("*SWORD UPGRADED*");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Pig_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_ORC);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
		{
			_MoveOptions.nextSelect();
		}
		if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_MoveOptions.getSelected().m_Label == "0")
			{
				//FIGHT SEQUENCE SWORD
				int dmgApplied = player.getSwordDmg() * 2 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Sword");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "1")
			{
				int dmgApplied = player.getFireDmg() * 2 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Fire");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "2")
			{
				int dmgApplied = player.getWaterDmg() * 0.5f * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Water");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "3")
			{
				int dmgApplied = player.getGrassDmg() * 0.5f * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Grass");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "4")
			{
				_FightOptions.setActive(true);
				_MoveOptions.setActive(false);
			}
		}
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Pig Used Roll Around");
		_FWindow.AddFString("It Didn't Do Anything");

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Wolf_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_WOLF);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
		{
			_MoveOptions.nextSelect();
		}
		if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_MoveOptions.getSelected().m_Label == "0")
			{
				//FIGHT SEQUENCE SWORD
				int dmgApplied = player.getSwordDmg() * 1 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Sword");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "1")
			{
				int dmgApplied = player.getFireDmg() * 2 * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Fire");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "2")
			{
				int dmgApplied = player.getWaterDmg() * 0.5f * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Water");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "3")
			{
				int dmgApplied = player.getGrassDmg() * 0.5f * player.getLvl();
				enemy_Health -= dmgApplied;
				_FWindow.AddFString("Player Used Grass");
				_FWindow.AddFString("Hit For " + to_string(dmgApplied));
				enemy_attack = true;
			}
			else if (_MoveOptions.getSelected().m_Label == "4")
			{
				_FightOptions.setActive(true);
				_MoveOptions.setActive(false);
			}
		}
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack)
	{
		int dmgAppliedOrc = enemy_Damage * 1.5f;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Wolf Used Bite");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Jonestown_Hall(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			if (!getByTag("Jonestown_Main_Quest").getGiven())
			{
				//Do Quest Cutscene
				setByTag("Jonestown_Main_Quest", true, true);
			}
			else
			{
				_FWindow.AddFString("Use that pass I gave you");
				_FWindow.AddFString("to catch the boat to Swan Lake");
				_FWindow.AddFString("");
				_FWindow.AddFString("The island is counting on you");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(214, 173); // Toplefia Wharf
			setSail("Toplefia Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("Are you ready to head back to");
			_FWindow.AddFString("the mainland yet?");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Jiman_House(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			if (!getByTag("Beached_Pigs_Quest").getFinished())
			{
				//Do Quest Cutscene
				//setByTag("Beached_Pigs_Quest", true, true);
			}
			else if (!getByTag("Beached_Pigs_Quest").getGiven())
			{
				//Do Quest Cutscene
				setByTag("Beached_Pigs_Quest", true, true);
			}
			else if (getByTag("Beached_Pigs_Quest").getGiven() && jimans_house_pigs_killed < 5)
			{
				_FWindow.AddFString("pls kill those pig");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
			else if (getByTag("Beached_Pigs_Quest").getGiven() && jimans_house_pigs_killed >= 5)
			{
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				setByTag("Beached_Pigs_Quest", true, false);
			}
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(392, 83); // Almon Island Dock
			setSail("Almon Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("We're Going To Almon Island! ");
			_FWindow.AddFString("A lot of dangerous creatures");
			_FWindow.AddFString("over there so you might want");
			_FWindow.AddFString("to make sure you're strong");
			_FWindow.AddFString("enough");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Toplefia_TownHall(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Oh hey it's you.");
			_FWindow.AddFString("The mayor of Jonestown called");
			_FWindow.AddFString("requested I find someone to");
			_FWindow.AddFString("help with some problem they're");
			_FWindow.AddFString("having over there.");
			_FWindow.AddFString("Jonestown is just along the");
			_FWindow.AddFString("north east coast, shouldn't");
			_FWindow.AddFString("take too long to get there.");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Enemy_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _EnemAnim)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _STATE, BLACK_WHITE_BG);
	window = _EnemAnim.draw_asset(window, Vector2(20, 2));

	window.setTextAtPoint(Vector2(20, 11), "Health:" + std::to_string(enemy_Health) + ",LVL:" + std::to_string(enemy_lvl), BLACK_WHITE_BG);

	if (_FightOptions.getActive())
	{
		window = _FightOptions.draw_menu(window);
		if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
		{
			_FightOptions.nextSelect();
		}
		if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_FightOptions.getSelected().m_Label == "0")
			{
				//_FightOptions.setActive(false);
				_MoveOptions.setActive(true);
			}
			else if (_FightOptions.getSelected().m_Label == "1")
			{
				//IF RUN WAS SUCCESSFUL
				_FWindow.clear();
				_STATE = "MainMap";
			}
		}
	}

	return window;
}

ConsoleWindow SYDEMapGame::Wharf_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset _NPCAnim)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _Name, BLACK_WHITE_BG);
	window = _StructOptions.draw_menu(window);

	window = _NPCAnim.draw_asset(window, Vector2(20, 2));
	return window;
}

string SYDEMapGame::getWFA_STATE(Vector2 point)
{
	for (int i = 0; i < _list_fight_cases.size(); i++)
	{
		if (_list_fight_cases[i].getPoint() == point)
		{
			return _list_fight_cases[i].getWildFightArg();
		}
	}
	return "MainMap";
}

int SYDEMapGame::getWFA_LVL(Vector2 point)
{
	for (int i = 0; i < _list_fight_cases.size(); i++)
	{
		if (_list_fight_cases[i].getPoint() == point)
		{
			return _list_fight_cases[i].getLvl();
		}
	}
	return 0;
}

string SYDEMapGame::getSTRUCT_STATE(Vector2 point)
{
	for (int i = 0; i < _list_structures.size(); i++)
	{
		if (_list_structures[i].getPoint() == point)
		{
			return _list_structures[i].getStructArg();
		}
	}
	return "MainMap";
}

string SYDEMapGame::getTown(Vector2 point)
{
	for (int i = 0; i < vecTowns.size(); i++)
	{
		if (vecTowns[i].inBounds(point))
		{
			return vecTowns[i].getAREA();
		}
	}
	return "???";
}

int SYDEMapGame::getColourFromLevel(Vector2 point)
{
	int wf_colour = _LevelAsset.getColourAtPoint(point);
	switch (wf_colour)
	{
	case 32:
		wf_colour = 32;
		break;
	case 34:
		wf_colour = 32;
		break;
	case 224:
		wf_colour = 224;
		break;
	case 238:
		wf_colour = 224;
	default:
		wf_colour = 224;
		break;
	}

	return wf_colour;
}

string SYDEMapGame::getRandomFromList(vector<string> _list)
{
	int random_var = std::rand() %  _list.size();
	return _list[random_var];
}
