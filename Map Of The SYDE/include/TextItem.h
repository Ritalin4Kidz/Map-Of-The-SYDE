#pragma once

class TextItem {
public:
	TextItem() { m_char = ' ', m_colour = 0; }
	TextItem(char a_char, int a_colour) { m_char = a_char; m_colour = a_colour; };
	virtual ~TextItem() {}

	void setChar(char text) { m_char = text; }
	void setColour(int color) { m_colour = color; }

	char getChar() { return m_char; }
	int getColour() { return m_colour; }

	void operator=(TextItem other);
private:
	char m_char;
	int m_colour;
};