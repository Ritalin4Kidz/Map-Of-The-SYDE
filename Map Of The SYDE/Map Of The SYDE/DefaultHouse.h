#pragma once
#include "SYDEstdafx.h"
#include "Structures.h"
class DefaultHouse {
public:
	DefaultHouse() {}
	DefaultHouse(string _owner, CustomAnimationAsset npc, string TAG, Vector2 _point);
	virtual ~DefaultHouse() {}

	string getHouseOwner() { return m_HouseOwner; }
	void setHouseOwner(string name) { m_HouseOwner = name; }

	CustomAnimationAsset getNPC() { return m_NPC; }
	void setNPC(CustomAnimationAsset npc) { m_NPC = npc; }

	vector<string> getPhrases() { return m_Phrases; }
	string getRandomPhrase();

	void setPhrases(vector<string> _Phrases) { m_Phrases = _Phrases; }

	Structure _Struct = Structure();
private:
	string m_HouseOwner = "";
	CustomAnimationAsset m_NPC = CustomAnimationAsset();
	vector<string> m_Phrases = vector<string>();
};