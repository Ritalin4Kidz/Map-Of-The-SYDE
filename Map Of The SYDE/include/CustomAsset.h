#pragma once
#include <vector>
#include "ConsoleWindow.h"

using namespace std;

class CustomAsset {
public:
	CustomAsset() {}
	CustomAsset(int width, int height, vector<ColourClass> colour_array) { setAsset(width, height, colour_array); }


	virtual ~CustomAsset() {}

	void operator=(CustomAsset other);
	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point);
	ConsoleWindow draw_asset(ConsoleWindow window, Vector2 point,int windowWidth, int windowHeight);
	void setAsset(int width, int height, vector<ColourClass> colourClassArray);
	void setAsset(vector<vector<TextItem>> asset) { AssetVector = asset; }

	void setCharAtPoint(Vector2 Point, char m_Text);

private:
	vector<vector<TextItem>> AssetVector;

};