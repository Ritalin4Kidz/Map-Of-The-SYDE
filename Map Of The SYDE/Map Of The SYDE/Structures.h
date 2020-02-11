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
	void setPoint(Vector2 point) { m_Point = point; }
	string getStructArg() { return m_STRUCT_ARG; }
	void setStructArg(string STRUCT_ARG) { m_STRUCT_ARG = STRUCT_ARG; }
	string m_TAG;

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

	void setRunChance(int chance) { run_chance = chance; }
	int getRunChance() { return run_chance; }

	Vector2 getPoint() { return m_Point; }
	string getWildFightArg() { return m_WILD_FIGHT_ARG; }

	int getLvl() { return m_Lvl; }
private:
	string m_WILD_FIGHT_ARG = "";
	int m_Lvl = 0;
	int run_chance = 100;
	Vector2 m_Point = Vector2(0);
};

class WeaponStore {
public:
	WeaponStore() {}
	WeaponStore(vector<int> _swordPrices, vector<int> _firePrices, vector<int> _waterPrices, vector<int> _grassPrices);
	virtual ~WeaponStore() {}

	//get
	int getSwordCost() { return swordPrices[swordBought]; }
	int getSwordBght() { return swordBought; }
	int getSwordMStk() { return swordMaxStock; }

	int getFireCost() { return firePrices[fireBought]; }
	int getFireBght() { return fireBought; }
	int getFireMStk() { return fireMaxStock; }

	int getWaterCost() { return waterPrices[waterBought]; }
	int getWaterBght() { return waterBought; }
	int getWaterMStk() { return waterMaxStock; }

	int getGrassCost() { return grassPrices[grassBought]; }
	int getGrassBght() { return grassBought; }
	int getGrassMStk() { return grassMaxStock; }

	//set
	void setSwordBght(int _NEW) { swordBought = _NEW;}
	void setSwordMStk(int _NEW) { swordMaxStock = _NEW; }
					  			  
	void setFireBght(int _NEW) { fireBought = _NEW; }
	void setFireMStk(int _NEW) { fireMaxStock = _NEW; }
					 			  
	void setWaterBght(int _NEW) { waterBought = _NEW; }
	void setWaterMStk(int _NEW) { waterMaxStock = _NEW; }
					  			  
	void setGrassBght(int _NEW) { grassBought = _NEW; }
	void setGrassMStk(int _NEW) { grassMaxStock = _NEW; }

	void buySword() { swordBought++; }
	void buyFire() { fireBought++; }
	void buyWater() { waterBought++; }
	void buyGrass() { grassBought++; }

	bool swordSoldOut() { return swordBought == swordMaxStock; }
	bool fireSoldOut() { return fireBought == fireMaxStock; }
	bool waterSoldOut() { return waterBought == waterMaxStock; }
	bool grassSoldOut() { return grassBought == grassMaxStock; }

private:
	//  sword
	int swordBought = 0;
	int swordMaxStock;
	vector<int> swordPrices;
	//  fire
	int fireBought = 0;
	int fireMaxStock;
	vector<int> firePrices;
	//  water
	int waterBought = 0;
	int waterMaxStock;
	vector<int> waterPrices;
	//  grass
	int grassBought = 0;
	int grassMaxStock;
	vector<int> grassPrices;
};