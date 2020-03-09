#include "pch.h"
#include "TetriSYDE.h"


TetriSYDE::TetriSYDE()
{
}

ConsoleWindow TetriSYDE::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < 30; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	for (int l = 30; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK_BRIGHTWHITE_BG);
		}
	}
	window.setTextAtPoint(Vector2(32, 5), "Score:", BLACK_BRIGHTWHITE_BG);
	window.setTextAtPoint(Vector2(32, 6), asScoreString(), BLACK_BRIGHTWHITE_BG);
	if (_Playing)
	{
		Vector2 blockMove = Vector2(0);
		if (placed) {
			_BLOCK = TetriSYDEBlock(returnRandPiece());
			placed = false;
			blockPos = Vector2(((std::rand() % 15) + 5), 0);
		}

		if (SYDEKeyCode::get_key('R')._CompareState(KEYDOWN)) {
			//ROTATE
			_BLOCK.Rotate();
		}

		if (SYDEKeyCode::get_key('A')._CompareState(KEY)) {
			//BLOCK MOVE
			blockMove.addX(-1);
		}
		if (SYDEKeyCode::get_key('D')._CompareState(KEY)) {
			//BLOCK MOVE
			blockMove.addX(1);
		}
		if (SYDEKeyCode::get_key('S')._CompareState(KEY)) {
			//BLOCK MOVE
			if (blockPos.getY() < 17)
			{
				blockMove.addY(1);
			}
		}
		timePassed += SYDEDefaults::getDeltaTime();
		for (int i = 0; i < game_Grid.grid.size(); i++) {
			window.setTextAtPoint(Vector2(0, i), game_Grid.grid[i], WHITE);
		}
		if (!_BLOCK.checkhit(game_Grid, blockPos + blockMove)) {
			blockPos += blockMove;
		}
		window = _BLOCK.drawBlock(window, blockPos);
		if (timePassed >= timeTilNextDrop)
		{
			blockPos.addY(1);
			timePassed = 0;
		}
		if (_BLOCK.checkhit(game_Grid, blockPos) || blockPos.getY() >= 18) {
			blockPos.addY(-1);
			placed = true;
			if (blockPos.getY() < 0)
			{
				//placed oout of limit
				_Playing = false;
			}
			else {
				_BLOCK.addGrid(game_Grid, blockPos);
				GridCheck();
			}
		}
	}
	else {
		if (SYDEKeyCode::get_key('R')._CompareState(KEY)) {
			//Restart
		}
		for (int i = 0; i < game_Grid.grid.size(); i++) {
			window.setTextAtPoint(Vector2(0, i), game_Grid.grid[i], WHITE);
		}
		window.setTextAtPoint(Vector2(11, 10), "GAME OVER", RED);
	}
	return window;
}

TetriSYDEPiece TetriSYDE::returnRandPiece()
{
	int a = std::rand() % 7;
	switch (a) {
	case 0:
		return Square;
	case 1:
		return LongPiece;
	case 2:
		return ZigZagOne;
	case 3:
		return LShapeOne;
	case 4:
		return TShape;
	case 5:
		return LShapeTwo;
	case 6:
		return ZigZagTwo;
	default:
		return Square;
	}
}

TetriSYDEBlock::TetriSYDEBlock(TetriSYDEPiece piece)
{
	if (piece == Square)
	{
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,0)),
			TetriSYDEBlockSquare(Vector2(1,0)),
			TetriSYDEBlockSquare(Vector2(0,1)),
			TetriSYDEBlockSquare(Vector2(1,1)),
		};
		rotationBlocks = { blocks };
		colour = LIGHTBLUE;
	}
	else if (piece == LongPiece) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,0)),
			TetriSYDEBlockSquare(Vector2(0,1)),
			TetriSYDEBlockSquare(Vector2(0,2)),
			TetriSYDEBlockSquare(Vector2(0,3)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(0,2)),
				TetriSYDEBlockSquare(Vector2(0,3))
			},
			{
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(2,1)),
				TetriSYDEBlockSquare(Vector2(3,1))
			}
		};
		colour = BRIGHTRED;
	}
	else if (piece == LShapeOne) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,0)),
			TetriSYDEBlockSquare(Vector2(0,1)),
			TetriSYDEBlockSquare(Vector2(0,2)),
			TetriSYDEBlockSquare(Vector2(1,2)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(0,2)),
				TetriSYDEBlockSquare(Vector2(1,2)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(2,0)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(1,2)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(2,1)),
				TetriSYDEBlockSquare(Vector2(2,0)),
			}
		};
		colour = PURPLE;
	}
	else if (piece == LShapeTwo) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(1,0)),
			TetriSYDEBlockSquare(Vector2(1,1)),
			TetriSYDEBlockSquare(Vector2(1,2)),
			TetriSYDEBlockSquare(Vector2(0,2)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(1,2)),
				TetriSYDEBlockSquare(Vector2(0,2)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(2,1)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(0,2)),
				TetriSYDEBlockSquare(Vector2(1,0)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(2,0)),
				TetriSYDEBlockSquare(Vector2(2,1)),
			}
		};
		colour = GREEN;
	}
	else if (piece == TShape) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,1)),
			TetriSYDEBlockSquare(Vector2(1,1)),
			TetriSYDEBlockSquare(Vector2(2,1)),
			TetriSYDEBlockSquare(Vector2(1,0)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(2,1)),
				TetriSYDEBlockSquare(Vector2(1,0)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(0,2)),
				TetriSYDEBlockSquare(Vector2(1,1)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(2,0)),
				TetriSYDEBlockSquare(Vector2(1,1)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(1,2)),
			}
		};
		colour = YELLOW;
	}
	else if (piece == ZigZagOne) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,0)),
			TetriSYDEBlockSquare(Vector2(1,0)),
			TetriSYDEBlockSquare(Vector2(1,1)),
			TetriSYDEBlockSquare(Vector2(2,1)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(2,1)),
			},
			{
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(0,2)),
				TetriSYDEBlockSquare(Vector2(1,1)),
			},
		};
		colour = DARKBLUE;
	}
	else if (piece == ZigZagTwo) {
		blocks = {
			TetriSYDEBlockSquare(Vector2(0,1)),
			TetriSYDEBlockSquare(Vector2(1,1)),
			TetriSYDEBlockSquare(Vector2(1,0)),
			TetriSYDEBlockSquare(Vector2(2,0)),
		};
		rotationBlocks = {
			{
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,1)),
				TetriSYDEBlockSquare(Vector2(1,0)),
				TetriSYDEBlockSquare(Vector2(2,0)),
			},
			{
				TetriSYDEBlockSquare(Vector2(0,0)),
				TetriSYDEBlockSquare(Vector2(0,1)),
				TetriSYDEBlockSquare(Vector2(1,2)),
				TetriSYDEBlockSquare(Vector2(1,1)),
			},
		};
		colour = BRIGHTYELLOW;
	}
}


ConsoleWindow TetriSYDEBlock::drawBlock(ConsoleWindow window)
{
	for (int i = 0; i < blocks.size(); i++) {
		window.setTextAtPoint(blocks[i].point + pos, "*", colour);
	}
	return window;
}

ConsoleWindow TetriSYDEBlock::drawBlock(ConsoleWindow window, Vector2 _pos)
{
	for (int i = 0; i < blocks.size(); i++) {
		window.setTextAtPoint(blocks[i].point + _pos, "*", colour);
	}
	return window;
}

void TetriSYDEBlock::Rotate()
{
		//Vector2 temp = blocks[0].point;
		//blocks[0].point = blocks[3].point;
		//blocks[3].point = temp;
		//
		//temp = blocks[1].point;
		//blocks[1].point = blocks[2].point;
		//blocks[2].point = temp;
		//for (int i = 0; i < 4; i++)
		//{
		//	float temp = blocks[i].point.getX();
		//	blocks[i].point.setX(blocks[i].point.getY());
		//	blocks[i].point.setY(temp);
		//}
	rotationBlocksNo++;
	if (rotationBlocksNo >= rotationBlocks.size()) {
		rotationBlocksNo = 0;
	}
	blocks = rotationBlocks[rotationBlocksNo];
}

bool TetriSYDEBlock::checkhit(GRID window, Vector2 pos)
{
	for (int i = 0; i < blocks.size(); i++) {
		if (blocks[i].point.getY() + pos.getY() < 0)
		{
		}
		else if (blocks[i].point.getY() + pos.getY() >= window.grid.size())
		{
			return true;
		}
		else if (window.grid[blocks[i].point.getY() + pos.getY()][blocks[i].point.getX() + pos.getX()] == '*')
		{
			return true;
		}
	}
	return false;
}

void TetriSYDEBlock::addGrid(GRID & window, Vector2 pos)
{
	for (int i = 0; i < blocks.size(); i++) {
		window.grid[blocks[i].point.getY() + pos.getY()][blocks[i].point.getX() + pos.getX()] = '*';			
	}

}

void TetriSYDE::GridCheck()
{
	int bonus = 0;
	for (int i = 0; i < game_Grid.grid.size(); i++) {
		if (game_Grid.grid[i] == "******************************")
		{
			for (int j = i; j > 0; j--)
			{
				game_Grid.grid[j] = game_Grid.grid[j - 1];
			}
			game_Grid.grid[0] = "*                            *";
			i = 0;
			if (bonus == 0)
			{
				bonus = 1;
			}
			else
			{
				bonus *= 2;
			}
		}
	}
	score += (100 * bonus);
}

