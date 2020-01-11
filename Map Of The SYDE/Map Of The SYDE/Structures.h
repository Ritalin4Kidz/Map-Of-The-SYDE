#pragma once
#include "SYDEstdafx.h"
class _Town_Square {
public:
	_Town_Square() {}
	_Town_Square(Vector2 boundary1, Vector2 boundary2, string townName);
	virtual ~_Town_Square() {}

	string getAREA() { return _AREANAME; }
	bool inBounds(Vector2 point);

private:
	Vector2 TopLeft;
	Vector2 BottomRight;

	string _AREANAME = "???";
};

class Structure {
public:
	Structure() {}
	Structure(Vector2 _point, string _structurearg);
	virtual ~Structure() {}

	Vector2 getPoint() { return m_Point; }
	string getStructArg() { return m_STRUCT_ARG; }

private:
	string m_STRUCT_ARG = "";
	Vector2 m_Point = Vector2(0);
};

class WildFightAttachment {
public:
	WildFightAttachment() {}
	WildFightAttachment(Vector2 _point, string _wildfightarg);
	WildFightAttachment(Vector2 _point, string _wildfightarg, int a_Lvl);
	virtual ~WildFightAttachment() {}

	Vector2 getPoint() { return m_Point; }
	string getWildFightArg() { return m_WILD_FIGHT_ARG; }

	int getLvl() { return m_Lvl; }
private:
	string m_WILD_FIGHT_ARG = "";
	int m_Lvl = 0;
	Vector2 m_Point = Vector2(0);
};