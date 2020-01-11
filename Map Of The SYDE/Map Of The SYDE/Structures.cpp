#include "pch.h"
#include "Structures.h"

WildFightAttachment::WildFightAttachment(Vector2 _point, string _wildfightarg)
{
	m_WILD_FIGHT_ARG = _wildfightarg;
	m_Point = _point;
}

WildFightAttachment::WildFightAttachment(Vector2 _point, string _wildfightarg, int a_Lvl)
{
	m_WILD_FIGHT_ARG = _wildfightarg;
	m_Point = _point;
	m_Lvl = a_Lvl;
}

Structure::Structure(Vector2 _point, string _structurearg)
{
	m_STRUCT_ARG = _structurearg;
	m_Point = _point;
}

_Town_Square::_Town_Square(Vector2 boundary1, Vector2 boundary2, string townName)
{
	TopLeft = boundary1;
	BottomRight = boundary2;
	_AREANAME = townName;
}

bool _Town_Square::inBounds(Vector2 point)
{
	return (point.getX() >= TopLeft.getX() && point.getX() <= BottomRight.getX() && point.getY() >= TopLeft.getY() && point.getY() <= BottomRight.getY());
}