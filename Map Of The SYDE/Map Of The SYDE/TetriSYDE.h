#pragma once

#include "SYDEstdafx.h"
#include <functional>
struct TetriSYDEBlockSquare {
	TetriSYDEBlockSquare(Vector2 a) { point = a; }
	Vector2 point;
};

enum TetriSYDEPiece {
	Square,
	LongPiece,
	LShapeOne,
	LShapeTwo,
	TShape,
	ZigZagOne,
	ZigZagTwo
};

struct GRID {
	vector<string> grid = { 
		"*                            *",
		"*                            *", 
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *",
		"*                            *"
	};

};

class TetriSYDEBlock {
public:
	TetriSYDEBlock() {}
	TetriSYDEBlock(TetriSYDEPiece piece);
	virtual ~TetriSYDEBlock() {}

	ConsoleWindow drawBlock(ConsoleWindow window);
	ConsoleWindow drawBlock(ConsoleWindow window, Vector2 _pos);

	void Rotate();

	bool checkhit(GRID window, Vector2 pos);
	void addGrid(GRID &window, Vector2 pos);

	Vector2 pos = SYDEDefaults::v2_Zero;
private:
	vector<TetriSYDEBlockSquare> blocks;

	vector<vector<TetriSYDEBlockSquare>> rotationBlocks;
	ColourClass colour;
	int rotationBlocksNo = 0;
};

class TetriSYDE : public SYDEWindowGame {
public:
	TetriSYDE();
	virtual ~TetriSYDE() {}
	string asScoreString() { string old_string = to_string(score); return std::string(6 - old_string.length(), '0') + old_string; }
	void GridCheck();
	ConsoleWindow window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight) override;
	TetriSYDEPiece returnRandPiece();
private:
	bool placed = true;
	TetriSYDEBlock _BLOCK;
	Vector2 blockPos = Vector2(0);
	GRID game_Grid;
	int score = 0;
	float timePassed = 0.0f;
	const float timeTilNextDrop = 0.75f;

	bool _Playing = true;
};