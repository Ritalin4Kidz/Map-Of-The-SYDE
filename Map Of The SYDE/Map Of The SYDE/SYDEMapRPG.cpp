#include "pch.h"
#include "SYDEMapRPG.h"

WildFightAttachment::WildFightAttachment(Vector2 _point, string _wildfightarg)
{
	m_WILD_FIGHT_ARG = _wildfightarg;
	m_Point = _point;
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg)
{
	_LevelAsset.setCharAtPoint(m_Point, 'V');
	_LevelAsset.setColourAtPoint(m_Point, 32);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg));
}

SYDEMapGame::SYDEMapGame()
{
	_list_fight_cases = vector<WildFightAttachment>();
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	_LevelAsset = CustomAsset(2048, 768, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Level_SYDE.bmp", 1024, 768));
	camera_Pos = Vector2(280,200);

	vecTowns = vector<_Town_Square>{
		_Town_Square(Vector2(0,		0), Vector2(255,	95) , "Dissonant Waved Ocean"), // THANKS ME TRICKS AND DOM
		_Town_Square(Vector2(256,	0), Vector2(511,	95) , "Almon Island"), // THANKS ME
		_Town_Square(Vector2(512,	0), Vector2(767,	95) , "Blankis Island"), // THANKS ME
		_Town_Square(Vector2(768,	0), Vector2(1023,	95) , "Aliran Island"), // SUCK SHIT ALI
		_Town_Square(Vector2(1024,	0), Vector2(1279,	95) , "Daggo Coast"), // FUCK YOU LEGO YODA
		_Town_Square(Vector2(1280,	0), Vector2(1535,	95) , "SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	0), Vector2(1791,	95) , "Taumatawhaka"), // THANKS LEGO YODA (DISCORD)
		_Town_Square(Vector2(1792,	0), Vector2(2047,	95) , "Taumata Beach"), // THANKS ME

		_Town_Square(Vector2(0,		96), Vector2(255,	191), "Toplefia Place"), // THANKS ME
		_Town_Square(Vector2(256,	96), Vector2(511,	191), "North Muric Coast"), // ALI FUCK YOU
		_Town_Square(Vector2(512,	96), Vector2(767,	191), "Ballistica"), // THANKS ALI
		_Town_Square(Vector2(768,	96), Vector2(1023,	191), "Broken Coast West"), // THANKS ME
		_Town_Square(Vector2(1024,	96), Vector2(1279,	191), "Broken Coast East"), // THANKS ME
		_Town_Square(Vector2(1280,	96), Vector2(1535,	191), "Repaired Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	96), Vector2(1791,	191), "Western Meow Coast"), // THANKS ASHIE
		_Town_Square(Vector2(1792,	96), Vector2(2047,	191), "Eastern Meow Coast"), // THANKS ASHIE

		_Town_Square(Vector2(0,		192), Vector2(255,	287), "Hidden Ocean"),
		_Town_Square(Vector2(256,	192), Vector2(511,	287), "Beached Butthole"), // THANKS TRICKS
		_Town_Square(Vector2(512,	192), Vector2(767,	287), "Arcoomer"), // THANKS ARCANA
		_Town_Square(Vector2(768,	192), Vector2(1023,	287), "Hidden Ocean"),
		_Town_Square(Vector2(1024,	192), Vector2(1279,	287), "Thrustbowl"), // THANKS TRICKS
		_Town_Square(Vector2(1280,	192), Vector2(1535,	287), "Jonestown"), // THANKS LINDSAY
		_Town_Square(Vector2(1536,	192), Vector2(1791,	287), "Swan Lake"), // THANKS PETE
		_Town_Square(Vector2(1792,	192), Vector2(2047,	287), "Hidden Ocean"),

		_Town_Square(Vector2(0,		288), Vector2(255,	383), "Hidden Ocean"),
		_Town_Square(Vector2(256,	288), Vector2(511,	383), "Hidden Ocean"),
		_Town_Square(Vector2(512,	288), Vector2(767,	383), "Hidden Ocean"),
		_Town_Square(Vector2(768,	288), Vector2(1023,	383), "Loot Lake"), //MORE LEGO YODA
		_Town_Square(Vector2(1024,	288), Vector2(1279,	383), "Hidden Ocean"),
		_Town_Square(Vector2(1280,	288), Vector2(1535,	383), "Hidden Ocean"),
		_Town_Square(Vector2(1536,	288), Vector2(1791,	383), "Hidden Ocean"),
		_Town_Square(Vector2(1792,	288), Vector2(2047,	383), "32x Tile Sea"), // THANKS LEGO YODA (DISCORD)

		_Town_Square(Vector2(0,		384), Vector2(255,	479), "Baffled Coast"), // THANKS ANDREW
		_Town_Square(Vector2(256,	384), Vector2(511,	479), "Zengina"), // THANKS ANDREW
		_Town_Square(Vector2(512,	384), Vector2(767,	479), "Hidden Ocean"),
		_Town_Square(Vector2(768,	384), Vector2(1023,	479), "Hidden Ocean"),
		_Town_Square(Vector2(1024,	384), Vector2(1279,	479), "Hidden Ocean"),
		_Town_Square(Vector2(1280,	384), Vector2(1535,	479), "Hidden Ocean"),
		_Town_Square(Vector2(1536,	384), Vector2(1791,	479), "CRT Coast"), //FUCK YOU LEGO YODA
		_Town_Square(Vector2(1792,	384), Vector2(2047,	479), "CRT Island"), //FUCK YOU LEGO YODA

		_Town_Square(Vector2(0,		480), Vector2(255,	575), "Hidden Ocean"),
		_Town_Square(Vector2(256,	480), Vector2(511,	575), "Hidden Ocean"),
		_Town_Square(Vector2(512,	480), Vector2(767,	575), "Hidden Ocean"),
		_Town_Square(Vector2(768,	480), Vector2(1023,	575), "Hidden Ocean"),
		_Town_Square(Vector2(1024,	480), Vector2(1279,	575), "Denton"), // THANKS LUKE
		_Town_Square(Vector2(1280,	480), Vector2(1535,	575), "Hidden Ocean"),
		_Town_Square(Vector2(1536,	480), Vector2(1791,	575), "Jeff Coast"), // THANKS SIMON
		_Town_Square(Vector2(1792,	480), Vector2(2047,	575), "Hidden Ocean"),

		_Town_Square(Vector2(0,		576), Vector2(255,	671), "Hidden Ocean"),
		_Town_Square(Vector2(256,	576), Vector2(511,	671), "Hidden Ocean"),
		_Town_Square(Vector2(512,	576), Vector2(767,	671), "Hidden Ocean"),
		_Town_Square(Vector2(768,	576), Vector2(1023,	671), "Hidden Ocean"),
		_Town_Square(Vector2(1024,	576), Vector2(1279,	671), "Hidden Ocean"),
		_Town_Square(Vector2(1280,	576), Vector2(1535,	671), "Cyprux"), // THANKS DOM
		_Town_Square(Vector2(1536,	576), Vector2(1791,	671), "Hidden Ocean"),
		_Town_Square(Vector2(1792,	576), Vector2(2047,	671), "Hidden Ocean"),

		_Town_Square(Vector2(0,		672), Vector2(255,	767), "Hidden Ocean"),
		_Town_Square(Vector2(256,	672), Vector2(511,	767), "Hidden Ocean"),
		_Town_Square(Vector2(512,	672), Vector2(767,	767), "Hidden Ocean"),
		_Town_Square(Vector2(768,	672), Vector2(1023,	767), "Hidden Ocean"),
		_Town_Square(Vector2(1024,	672), Vector2(1279,	767), "Hidden Ocean"),
		_Town_Square(Vector2(1280,	672), Vector2(1535,	767), "Hidden Ocean"),
		_Town_Square(Vector2(1536,	672), Vector2(1791,	767), "Hidden Ocean"),
		_Town_Square(Vector2(1792,	672), Vector2(2047,	767), "Hidden Ocean"),
	};

	//ORC WILD FIGHT 1
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

	//MAIN MENU VARS
	_Options = SYDEMenu(vector<SYDEButton> {	
		SYDEButton("", Vector2(0, 1), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 2), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 3), Vector2(20, 1), WHITE, true),
	});

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
	if (_STATE == "MainMap")
	{
		window = Main_Map_Scene(window, windowWidth, windowHeight);
	}
	if (_STATE == "MainMenu")
	{
		window = Main_Menu(window, windowWidth, windowHeight);
	}
	if (_STATE == "ORC_TEST")
	{
		//window = Orc_Fight(window, windowWidth, windowHeight);
		//GENERATE ORC FIGHT
		enemy_Damage = 2;
		enemy_exp_gained = 50;
		enemy_Health = 100;
		_STATE = "ORC_FIGHT";
	}
	if (_STATE == "ORC_FIGHT")
	{
		window = Orc_Fight(window, windowWidth, windowHeight);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = _LevelAsset.draw_asset(window, Vector2(camera_Pos.getX()-20, camera_Pos.getY()-10), windowWidth, windowHeight);

	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10) , "><", window.determineColourAtPoint(Vector2(20, 10), BLACK, true));
	if (SYDEKeyCode::get('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 11)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
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
		char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
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
		char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
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
		char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
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
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", RED_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 1), "Area: " + getTown(camera_Pos), RED_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "Health: " + std::to_string(play_health) + ", Lvl: " + std::to_string(play_lvl), RED_WHITE_BG);
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

	window = _FightOptions.draw_menu(window);
	if (SYDEKeyCode::get(VK_TAB)._CompareState(KEYDOWN))
	{
		_FightOptions.nextSelect();
	}
	if ((SYDEKeyCode::get(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_FightOptions.getSelected().m_Label == "0")
		{
			//FIGHT SEQUENCE
		}
		else if (_FightOptions.getSelected().m_Label == "1")
		{
			//IF RUN WAS SUCCESSFUL
			_STATE = "MainMap";
		}
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
