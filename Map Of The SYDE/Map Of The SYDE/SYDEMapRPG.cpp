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
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		if (tempChar == 'V')
		{
			if (true)
			{
				//change to if random number, then make fight happen
				_STATE = "ORC_TEST";
			}
		}
		
		// CASES FOR MOVEMENT NOT ALLOWED
		else if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(1);
		}
	}
	if (SYDEKeyCode::get('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22, 10)));
		//CASES FOR MOVEMENT NOT ALLOWED
		window.setTextAtPoint(Vector2(0, 1),temp, BLACK_WHITE_BG);
		if (temp.compare("17") != 0 && temp.compare("16") != 0) //Note, make from 16 -31
		{
			camera_Pos.addX(2);
		}
	}
	if (SYDEKeyCode::get('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 9)));
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(-1);
		}
	}
	if (SYDEKeyCode::get('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18, 10)));
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addX(-2);
		}
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
	window = m_ORC.draw_asset(window, Vector2(20, 1));

	window.setTextAtPoint(Vector2(20, 11), "    Health: " + std::to_string(enemy_Health) + "     ", BLACK_WHITE_BG);
	return window;
}
