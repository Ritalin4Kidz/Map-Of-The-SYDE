#include "pch.h"
#include "SYDEMapRPG.h"

SYDEMapGame::SYDEMapGame()
{
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	_LevelAsset = CustomAsset(100, 50, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\TestLevel.bmp", 50, 50));
	camera_Pos = Vector2(20, 10);
}

ConsoleWindow SYDEMapGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (_STATE == "MainMap")
	{
		window = Main_Map_Scene(window, windowWidth, windowHeight);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = _LevelAsset.draw_asset(window, Vector2(camera_Pos.getX()-20, camera_Pos.getY()-10));

	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10) , "><", window.determineColourAtPoint(Vector2(20, 10), BLACK, true));
	if (SYDEKeyCode::get('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 9)));
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0)
		{
			camera_Pos.addY(1);
		}
	}
	if (SYDEKeyCode::get('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18, 10)));
		//CASES FOR MOVEMENT NOT ALLOWED
		window.setTextAtPoint(Vector2(0, 1),temp, BLACK_WHITE_BG);
		if (temp.compare("17") != 0)
		{
			camera_Pos.addX(2);
		}
	}
	if (SYDEKeyCode::get('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 11)));
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0)
		{
			camera_Pos.addY(-1);
		}
	}
	if (SYDEKeyCode::get('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22, 10)));
		window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0)
		{
			camera_Pos.addX(-2);
		}
	}
	return window;
}
