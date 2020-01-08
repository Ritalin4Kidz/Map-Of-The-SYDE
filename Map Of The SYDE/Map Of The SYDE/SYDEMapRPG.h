#pragma once
#include "SYDEstdafx.h"

class WildFightAttachment {
public:
	WildFightAttachment() {}
	WildFightAttachment(Vector2 _point, string _wildfightarg);
	virtual ~WildFightAttachment() {}

	string getWildFightArg() { return m_WILD_FIGHT_ARG; }
private:
	string m_WILD_FIGHT_ARG = "";
	Vector2 m_Point = Vector2(0);
};


class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	ConsoleWindow Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight);

	ConsoleWindow Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight);

	void AddAttachmentWildFight(Vector2 m_Point, string _arg);
private:
	string _STATE = "MainMenu";
	CustomAsset m_bg;
	CustomAsset _LevelAsset;

	Vector2 camera_Pos;

	AssetsClass astVars;

	//MainMenu Vars
	CustomAnimationAsset m_MainMenu_BG;
	float time_passed = 0.0f;
	SYDEMenu _Options;

	vector<WildFightAttachment> _list_fight_cases;

	//FIGHT
	int enemy_Health = 100;
	int enemy_Damage = 2;
	int enemy_exp_gained = 50;

	//ENEMY ANIMATIONS
	CustomAnimationAsset m_ORC;
 };