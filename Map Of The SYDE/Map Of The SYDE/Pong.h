#pragma once
#include "SYDEstdafx.h"

class Pong {
public:

	Pong();
	virtual ~Pong() {}

	ConsoleWindow draw_game(ConsoleWindow window, int windowWidth, int windowHeight);

private:

	CustomAsset m_PADDLE_1;
	CustomAsset m_PADDLE_2;
	CustomAsset m_BALL;

	AssetsClass astVars;

	Vector2 player1Pos;
	Vector2 player2Pos;
	Vector2 ballPos;

	float ballDirectionHorizontal = 1;
	float ballDirectionVertical = 0;

	int Player1Points = 0;
	int Player2Points = 0;
};