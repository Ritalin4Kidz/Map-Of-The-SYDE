#include "pch.h"
#include "SYDEMapRPG.h"

WildFightAttachment::WildFightAttachment(Vector2 _point, string _wildfightarg)
{
	m_WILD_FIGHT_ARG = _wildfightarg;
	m_Point = _point;
}

Structure::Structure(Vector2 _point, string _structurearg)
{
	m_STRUCT_ARG = _structurearg;
	m_Point = _point;
}

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

void SYDEMapGame::AddAttachmentStructure(Vector2 m_Point, string _arg, int colour)
{
	_LevelAsset.setCharAtPoint(m_Point, StructureChar);
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_structures.push_back(Structure(m_Point, _arg));
}

SYDEMapGame::SYDEMapGame()
{
	AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_list_fight_cases = vector<WildFightAttachment>();
	_list_structures = vector<Structure>();
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	_LevelAsset = CustomAsset(2048, 768, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Level_SYDE.bmp", 1024, 768));
	camera_Pos = Vector2(280,200);

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

		_Town_Square(Vector2(0,		192), Vector2(255,	287), "Northen SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	192), Vector2(511,	287), "Beached Butthole"), // THANKS TRICKS
		_Town_Square(Vector2(512,	192), Vector2(767,	287), "Arcoomer"), // THANKS ARCANA
		_Town_Square(Vector2(768,	192), Vector2(1023,	287), "Djungelskog"), // THANKS JACKSON
		_Town_Square(Vector2(1024,	192), Vector2(1279,	287), "Thrustbowl"), // THANKS TRICKS
		_Town_Square(Vector2(1280,	192), Vector2(1535,	287), "Jonestown"), // THANKS LINDSAY
		_Town_Square(Vector2(1536,	192), Vector2(1791,	287), "Swan Lake"), // THANKS PETE
		_Town_Square(Vector2(1792,	192), Vector2(2047,	287), "Meow Coast Beach"), //THANKS ASHIE

		_Town_Square(Vector2(0,		288), Vector2(255,	383), "Southern SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	288), Vector2(511,	383), "Western Plains"), // THANKS ME
		_Town_Square(Vector2(512,	288), Vector2(767,	383), "Rhofields"), // THANKS ME
		_Town_Square(Vector2(768,	288), Vector2(1023,	383), "Loot Lake"), //MORE LEGO YODA
		_Town_Square(Vector2(1024,	288), Vector2(1279,	383), "Kiffidle Lakes"), // THANKS ME
		_Town_Square(Vector2(1280,	288), Vector2(1535,	383), "Arc Cove"), // THANKS ME
		_Town_Square(Vector2(1536,	288), Vector2(1791,	383), "Faraway"), // THANKS ME
		_Town_Square(Vector2(1792,	288), Vector2(2047,	383), "32x Tile Sea"), // THANKS LEGO YODA (DISCORD)

		_Town_Square(Vector2(0,		384), Vector2(255,	479), "Baffled Coast"), // THANKS ANDREW
		_Town_Square(Vector2(256,	384), Vector2(511,	479), "Zengina"), // THANKS ANDREW
		_Town_Square(Vector2(512,	384), Vector2(767,	479), "Capital Town"), // THANKS ME
		_Town_Square(Vector2(768,	384), Vector2(1023,	479), "Island Centre"), // THANKS ME
		_Town_Square(Vector2(1024,	384), Vector2(1279,	479), "New Xylsdia"), // THANKS ME
		_Town_Square(Vector2(1280,	384), Vector2(1535,	479), "Eastern Plains"), // THANKS ME
		_Town_Square(Vector2(1536,	384), Vector2(1791,	479), "CRT Coast"), //FUCK YOU LEGO YODA
		_Town_Square(Vector2(1792,	384), Vector2(2047,	479), "CRT Island"), //FUCK YOU LEGO YODA

		_Town_Square(Vector2(0,		480), Vector2(255,	575), "Windan"), // THANKS ME
		_Town_Square(Vector2(256,	480), Vector2(511,	575), "Lake Entrance"), // THANKS CENTRAL COAST
		_Town_Square(Vector2(512,	480), Vector2(767,	575), "Western SYDE River"), // THANKS ME
		_Town_Square(Vector2(768,	480), Vector2(1023,	575), "Eastern SYDE River"), // THANKS ME
		_Town_Square(Vector2(1024,	480), Vector2(1279,	575), "Denton"), // THANKS LUKE
		_Town_Square(Vector2(1280,	480), Vector2(1535,	575), "Denton Fields"), // THANKS LUKE
		_Town_Square(Vector2(1536,	480), Vector2(1791,	575), "Jeff Coast"), // THANKS SIMON
		_Town_Square(Vector2(1792,	480), Vector2(2047,	575), "Uncharted Territory"), // THANKS ME

		_Town_Square(Vector2(0,		576), Vector2(255,	671), "Uncharted Territory"), // THANKS ME
		_Town_Square(Vector2(256,	576), Vector2(511,	671), "New SYDE Town"), // THANKS ME
		_Town_Square(Vector2(512,	576), Vector2(767,	671), "North Edgecliffe"), // THANKS ME
		_Town_Square(Vector2(768,	576), Vector2(1023,	671), "Last Bay"), // THANKS ME
		_Town_Square(Vector2(1024,	576), Vector2(1279,	671), "Old Capital Town"), // THANKS ME
		_Town_Square(Vector2(1280,	576), Vector2(1535,	671), "Cyprux"), // THANKS DOM
		_Town_Square(Vector2(1536,	576), Vector2(1791,	671), "Xylsdia Coast"), // FUCK YOU ME
		_Town_Square(Vector2(1792,	576), Vector2(2047,	671), "Useless Sea"), // THANKS ME

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
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}
	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID B:1 - Toplefia Place
	AddAttachmentStructure(Vector2(214, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 173), "Toplefia Wharf", 96);

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

	_Options[0].setText("Play Game");
	_Options[1].setText("--");
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
			enemy_exp_gained = 50;
			enemy_Health = 100;

			_MoveOptions = SYDEMenu(vector<SYDEButton> {
					SYDEButton("Sword", Vector2(1, 2), Vector2(20, 1), WHITE, true),
					SYDEButton(___IfUnlocked(player.getFireSpellUnlocked(), "Fire Spell")  , Vector2(1, 3), Vector2(20, 1), WHITE, true),
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
			//_STATE = "ORC_FIGHT";
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "ORC_FIGHT")
		{
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "BUILDING_TEST")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("--");
			//window = Building_Test(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Building_Test, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Toplefia Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Toplefia_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
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
	window.setTextAtPoint(Vector2(0, 19), "Health: " + std::to_string(player.getHealth()) + ", Lvl: " + std::to_string(player.getLvl()), RED_WHITE_BG);


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
				_STATE = getWFA_STATE(camera_Pos);
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
				_STATE = getWFA_STATE(camera_Pos);
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
				_STATE = getWFA_STATE(camera_Pos);
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
				_STATE = getWFA_STATE(camera_Pos);
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
			_STATE = "MainMap";
		}
		else if (_Options.getSelected().m_Label == "1")
		{
			
		}
		else if (_Options.getSelected().m_Label == "2")
		{
			exit(NULL);
		}
	}
	return window;
}

ConsoleWindow SYDEMapGame::Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	bool enemy_attack = false;
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "ORC_FIGHT", BLACK_WHITE_BG);
	window = m_ORC.draw_asset(window, Vector2(20, 2));

	window.setTextAtPoint(Vector2(20, 11), "    Health: " + std::to_string(enemy_Health) + "     ", BLACK_WHITE_BG);

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
				_FightOptions.setActive(false);
				_MoveOptions.setActive(true);
			}
			else if (_FightOptions.getSelected().m_Label == "1")
			{
				//IF RUN WAS SUCCESSFUL
				_STATE = "MainMap";
			}
		}
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
		player.setXP(player.getXP() + enemy_exp_gained);
		while (player.getXP() >= player.getXPNxtLvl()) {
			player.setLvl(player.getLvl() + 1);
			player.setMaxHealth(player.getMaxHealth() + 5);
			player.setHealth(player.getMaxHealth()); // HEAL ON LVL UP
			player.setXP(player.getXP() - player.getXPNxtLvl());
			player.setXPNxtLvl(player.getXPNxtLvl() * 1.5f);
		}
		_FWindow.clear();
		_STATE = "MainMap";
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

ConsoleWindow SYDEMapGame::Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "Almon Wharf", BLACK_WHITE_BG);

	window = _StructOptions.draw_menu(window);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(214, 173); // Toplefia Wharf
			_STATE = "MainMap";
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

ConsoleWindow SYDEMapGame::Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "Toplefia Wharf", BLACK_WHITE_BG);

	window = _StructOptions.draw_menu(window);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(392, 83); // Almon Island Dock
			_STATE = "MainMap";
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

_Town_Square::_Town_Square(Vector2 boundary1, Vector2 boundary2, string townName)
{
	TopLeft = boundary1;
	BottomRight = boundary2;
	_AREANAME = townName;
}

bool _Town_Square::inBounds(Vector2 point)
{
	return (point.getX() >= TopLeft.getX() && point.getX() <= BottomRight.getX() && point.getY() >= TopLeft.getY() && point.getY() <= BottomRight.getY());
}

void FightWindow::AddFString(string fstring)
{
	if (_fightStrings.size() >= 8)
	{
		for (int i = 1; i <8; i++)
		{
			_fightStrings[i - 1] = _fightStrings[i];
		}
		_fightStrings[7] = fstring;
	}
	else {
		_fightStrings.push_back(fstring);
	}
}
