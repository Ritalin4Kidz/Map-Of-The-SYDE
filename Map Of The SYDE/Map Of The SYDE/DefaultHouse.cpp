#include "pch.h"
#include "DefaultHouse.h"

DefaultHouse::DefaultHouse(string _owner, CustomAnimationAsset npc, string TAG, Vector2 _point)
{
	m_HouseOwner = _owner;
	m_NPC = npc;
	_Struct.m_TAG = TAG;
	_Struct.setPoint(_point);
	_Struct.setStructArg(_owner + "'s House");
}

string DefaultHouse::getRandomPhrase()
{
	int random_var = std::rand() % m_Phrases.size();
	return m_Phrases[random_var];
}
