#include "pch.h"
#include "D20Minigame.h"

D20Minigame::D20Minigame()
{
	AssignState(std::bind(&D20Minigame::MainMenu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	diceRolls = vector<CustomAnimationAsset>{
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\D20Anim\\DiceAnimation001.bmp", astVars, 140, 120, 20, 20, 0, 41),
	};

}

ConsoleWindow D20Minigame::MainMenu(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)) {
		_STATE = "DiceRoll";
	}
	window.setTextAtPoint(Vector2(0, 1), "NRL D20 SYDE EDITION", WHITE);
	return window;
}

CustomAnimationAsset D20Minigame::randDiceRoll()
{
	int assetNo = std::rand() % diceRolls.size();
	return diceRolls[assetNo];
}

ConsoleWindow D20Minigame::Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset & _anim)
{
	window = _anim.draw_asset(window, Vector2(0));
	window.setTextAtPoint(Vector2(0, 1), _AnimHeader, BLACK_BRIGHTWHITE_BG);
	if (_anim.getFrame() == _anim.getFrameSize() - 1)
	{
		UI_STATE_EVENT = false;
	}
	return window;
}

ConsoleWindow D20Minigame::DiceRoll(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		if (m_Rolling && !UI_STATE_EVENT)
		{
			if (m_ruleSet == RegularSeasonRoll)
			{
				if (homeTeamRoll){
					int tempHomeTeamScore = (((std::rand() % 3) + 1)*2) + (((std::rand() % 20) + 1) * 2) - 2;
					homeTeamScore += tempHomeTeamScore;
					awayTeamRoll = true;
					homeTeamRoll = false;
					setAnimation_UI_EVENT(randDiceRoll(), HomeTeamName + " Scored: " + to_string(tempHomeTeamScore) + " points!");
				}
				else if (awayTeamRoll) {
					int tempAwayTeamScore = (((std::rand() % 20) + 1) * 2) - 2;
					awayTeamScore += tempAwayTeamScore;
					minsDone += 80;
					awayTeamRoll = false;
					homeTeamRoll = false;
					setAnimation_UI_EVENT(randDiceRoll(), AwayTeamName + " Scored: " + to_string(tempAwayTeamScore) + " points!");
				}
			}
			else if (m_ruleSet == FinalsSimple)
			{

			}
			else if (m_ruleSet == Finals)
			{

			}
		}
	}
	if (minsDone >= 80 && !UI_STATE_EVENT)
	{
		//DETERMINE RESULT
		//DO DISPLAY AND SHIT
	}
	for (int l = 0; l < windowWidth; l++)
	{
			window.setTextAtPoint(Vector2(l, 19), " ", BLACK_BRIGHTWHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 19), HomeTeamName + ": " + to_string(homeTeamScore) + "    " + AwayTeamName + ": " + to_string(awayTeamScore), BLACK_BRIGHTWHITE_BG);
	return window;
}

ConsoleWindow D20Minigame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (_CurentSTATE.compare(_STATE) != 0)
	{
		if (_STATE == "MainMenu")
		{
			AssignState(std::bind(&D20Minigame::MainMenu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "DiceRoll")
		{
			awayTeamRoll = false;
			homeTeamRoll = true;
			m_Rolling = true;
			AssignState(std::bind(&D20Minigame::DiceRoll, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		_CurentSTATE = _STATE;
	}
	window = DoState(window, windowWidth, windowHeight);
	//IF UI EVENT
	if (UI_STATE_EVENT) {
		window = Animation_UI_EVENT(window, m_MoveAnimation);
	}
	return window;
}
