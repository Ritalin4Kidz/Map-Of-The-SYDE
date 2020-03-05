#pragma once
#include "SYDEstdafx.h"
#include <functional>

enum RuleSet {
	RegularSeasonRoll = 0,
	FinalsSimple,
	Finals,
	GoldenPoint
};

class D20Minigame : public SYDEWindowGame {
public:
	D20Minigame();
	virtual ~D20Minigame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;

	ConsoleWindow MainMenu(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow DiceRoll(ConsoleWindow window, int windowWidth, int windowHeight);

	std::function<ConsoleWindow(ConsoleWindow, int, int)> m_State;

	void AssignState(std::function<ConsoleWindow(ConsoleWindow, int, int)> newState) { m_State = newState; }

	ConsoleWindow DoState(ConsoleWindow window, int windowWidth, int windowHeight) { return m_State(window, windowWidth, windowHeight); }

	CustomAnimationAsset randDiceRoll();

	ConsoleWindow Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset& _anim);
	void setAnimation_UI_EVENT(CustomAnimationAsset _Anim, string _Header) { m_MoveAnimation = _Anim; m_MoveAnimation.setFrame(0); UI_STATE_EVENT = true; _AnimHeader = _Header; }
private:
	string _STATE = "MainMenu";
	string _CurentSTATE = "MainMenu";

	bool m_Rolling = false;

	bool homeTeamRoll = false;
	bool awayTeamRoll = false;

	CustomAnimationAsset m_MoveAnimation;
	AssetsClass astVars;
	vector<CustomAnimationAsset> diceRolls;

	int homeTeamScore = 0;
	int awayTeamScore = 0;

	bool UI_STATE_EVENT = false;
	string _AnimHeader = "";

	string HomeTeamName = "Home Team";
	string AwayTeamName = "Away Team";
	int minsDone = 0;
	RuleSet m_ruleSet = RegularSeasonRoll;
};