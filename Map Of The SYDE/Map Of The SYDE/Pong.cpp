#include "pch.h"
#include "Pong.h"

Pong::Pong()
{
	m_PADDLE_1 = CustomAsset(10, 5, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Objects\\Paddle.bmp", 5, 5));
	m_PADDLE_2 = CustomAsset(10, 5, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Objects\\Paddle.bmp", 5, 5));
	m_BALL = CustomAsset(10, 5, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Objects\\Ball.bmp", 5, 5));

	player1Pos = Vector2(0, 7);
	player2Pos = Vector2(34, 7);
	ballPos = Vector2(17, 7);
}

ConsoleWindow Pong::draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}

	window = m_PADDLE_1.draw_asset(window, player1Pos);
	window = m_PADDLE_2.draw_asset(window, player2Pos);
	window = m_BALL.draw_asset(window, ballPos);

	if ((SYDEKeyCode::get_key('W')._CompareState(KEY)) && player1Pos.getY() > 0) {
		player1Pos.addY(-1);
	}
	else if ((SYDEKeyCode::get_key('S')._CompareState(KEY)) && player1Pos.getY() < 15) {
		player1Pos.addY(1);
	}

	if ((SYDEKeyCode::get_key('I')._CompareState(KEY)) && player1Pos.getY() > 0) {
		player2Pos.addY(-1);
	}
	else if ((SYDEKeyCode::get_key('K')._CompareState(KEY)) && player1Pos.getY() < 15) {
		player2Pos.addY(1);
	}

	// BALL MOVING
	ballPos.addX(ballDirectionHorizontal);
	ballPos.addY(ballDirectionVertical);

	if (ballPos.getX() == 34)
	{
		if ((int)player2Pos.getY() == (int)ballPos.getY())
		{
			ballDirectionHorizontal = -1;
			ballDirectionVertical = 0;
		}
		else if ((int)player2Pos.getY() == (int)ballPos.getY() - 1)
		{
			ballDirectionHorizontal = -1;
			ballDirectionVertical = 0.25f;
		}
		else if ((int)player2Pos.getY() == (int)ballPos.getY() + 1)
		{
			ballDirectionHorizontal = -1;
			ballDirectionVertical = -0.25f;
		}
	}
	else if (ballPos.getX() == 0)
	{
		if ((int)player1Pos.getY() == (int)ballPos.getY())
		{
			ballDirectionHorizontal = 1;
			ballDirectionVertical = 0;
		}
		else if ((int)player1Pos.getY() == (int)ballPos.getY() - 1)
		{
			ballDirectionHorizontal = 1;
			ballDirectionVertical = 0.25f;
		}
		else if ((int)player1Pos.getY() == (int)ballPos.getY() + 1)
		{
			ballDirectionHorizontal = 1;
			ballDirectionVertical = -0.25f;
		}
	}
	else if (ballPos.getX() > 34)
	{
		Player1Points++;
		player1Pos = Vector2(0, 7);
		player2Pos = Vector2(34, 7);
		ballPos = Vector2(17, 7);
		ballDirectionHorizontal = -1;
		ballDirectionVertical = 0;
	}
	else if (ballPos.getX() < 0)
	{
		Player2Points++;
		player1Pos = Vector2(0, 7);
		player2Pos = Vector2(34, 7);
		ballPos = Vector2(17, 7);
		ballDirectionHorizontal = 1;
		ballDirectionVertical = 0;
	}

	if ((int)ballPos.getY() <= 0 || (int)ballPos.getY() >= 15) {
		ballDirectionVertical = -ballDirectionVertical;
	}
	

	window.setTextAtPoint(Vector2(0, 19), "W,S,I,K - Move, BACK - Leave, 1:" + to_string(Player1Points) + "," + "2:" + to_string(Player2Points) + "             ", BLACK_WHITE_BG);
	return window;

}
