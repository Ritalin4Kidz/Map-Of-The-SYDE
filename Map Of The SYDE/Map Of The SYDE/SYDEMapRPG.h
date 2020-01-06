#pragma once
#include "SYDEstdafx.h"
class SYDEMapGame : public SYDEWindowGame {
public:
	SYDEMapGame();
	virtual ~SYDEMapGame() {}
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	ConsoleWindow Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight);
private:
	string _STATE = "MainMap";
	CustomAsset m_bg;
	CustomAsset _LevelAsset;

	Vector2 camera_Pos;

	AssetsClass astVars;
 };