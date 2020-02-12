#include "pch.h"
#include "SYDEMapRPG.h"
#pragma region LandManipulation

void SYDEMapGame::addLand(Vector2 a_Point)
{
	_LevelAsset.setColourAtPoint(a_Point, 34);
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg)
{
	_LevelAsset.setCharAtPoint(m_Point, WildFightChar);
	_LevelAsset.setColourAtPoint(m_Point, 32);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg));
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour)
{
	_LevelAsset.setCharAtPoint(m_Point, WildFightChar);
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg));
}

void SYDEMapGame::AddAttachmentWildFight(Vector2 m_Point, string _arg, int colour, int a_lvl)
{
	_LevelAsset.setCharAtPoint(m_Point, WildFightChar);
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_fight_cases.push_back(WildFightAttachment(m_Point, _arg, a_lvl));
}

void SYDEMapGame::AddAttachmentStructure(Vector2 m_Point, string _arg, int colour)
{
	_LevelAsset.setCharAtPoint(m_Point, StructureChar);
	_LevelAsset.setColourAtPoint(m_Point, colour);
	_list_structures.push_back(Structure(m_Point, _arg));
}

void SYDEMapGame::AddDragonKeepAttachment(Vector2 m_Point, string _arg, int colour)
{
	_DragonKeepAsset.setCharAtPoint(m_Point, StructureChar);
	_DragonKeepAsset.setColourAtPoint(m_Point, colour);
	_list_structures_dragon_keep.push_back(Structure(m_Point, _arg));
}

void SYDEMapGame::AddDungeonAttachment(CustomAsset _Dungeon, vector<Structure> listAdd, Vector2 m_Point, string _arg, int colour)
{
	_Dungeon.setCharAtPoint(m_Point, StructureChar);
	_Dungeon.setColourAtPoint(m_Point, colour);
	listAdd.push_back(Structure(m_Point, _arg));
}

string SYDEMapGame::getSTRUCT_STATE(Vector2 point, vector<Structure> _list_struct)
{
	for (int i = 0; i < _list_struct.size(); i++)
	{
		if (_list_struct[i].getPoint() == point)
		{
			return _list_struct[i].getStructArg();;
		}
	}
	return "MainMap";
}

#pragma endregion
#pragma region OtherFunc

void SYDEMapGame::setUpFight()
{
	_MoveOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Sword", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getFireSpellUnlocked(), "Fire Spell"), Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getWaterSpellUnlocked(), "Water Spell"), Vector2(1, 4), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getGrassSpellUnlocked(), "Grass Spell"), Vector2(1, 5), Vector2(20, 1), WHITE, true),
			SYDEButton(___IfUnlocked(player.getMoneySpellUnlocked(), "Money Spell"), Vector2(1, 6), Vector2(20, 1), WHITE, true),
			SYDEButton("Back", Vector2(1, 7), Vector2(20, 1), WHITE, true)
	});

	_MoveOptions[0].m_Label = "0";
	_MoveOptions[1].m_Label = ___IfUnlocked(player.getFireSpellUnlocked(), "1");
	_MoveOptions[2].m_Label = ___IfUnlocked(player.getWaterSpellUnlocked(), "2");
	_MoveOptions[3].m_Label = ___IfUnlocked(player.getGrassSpellUnlocked(), "3");
	_MoveOptions[4].m_Label = ___IfUnlocked(player.getMoneySpellUnlocked(), "4");
	_MoveOptions[5].m_Label = "5";

	_MoveOptions.setActive(false);
	_MoveOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _MoveOptions.getSize(); i++)
	{
		_MoveOptions[i].setHighLight(RED);
	}
	_FightOptions.setActive(true);
	enemy_attack = false;
}

void SYDEMapGame::setUpWeaponShop(WeaponStore _store)
{
	if (_store.swordSoldOut())
	{
		_WeaponsMoreOptions[0].setText("SOLD OUT");
		_WeaponsMoreOptions[0].m_Label = "N/A";
	}
	else {
		_WeaponsMoreOptions[0].setText("Sword Upgrade - " + to_string(_store.getSwordCost()));
	}
	_WeaponsMoreOptions[4].setText("Exit Shop");

	if (_store.fireSoldOut())
	{
		_WeaponsMoreOptions[1].setText("SOLD OUT");
		_WeaponsMoreOptions[1].m_Label = "N/A";
	}
	else if (player.getFireSpellUnlocked())
	{
		_WeaponsMoreOptions[1].setText("Fire Upgrade - " + to_string(_store.getFireCost()));
		_WeaponsMoreOptions[1].m_Label = "1";
	}
	else {
		_WeaponsMoreOptions[1].setText("???");
		_WeaponsMoreOptions[1].m_Label = "N/A";
	}

	if (_store.waterSoldOut())
	{
		_WeaponsMoreOptions[2].setText("SOLD OUT");
		_WeaponsMoreOptions[2].m_Label = "N/A";
	}
	else if (player.getWaterSpellUnlocked())
	{
		_WeaponsMoreOptions[2].setText("Water Upgrade - " + to_string(_store.getWaterCost()));
		_WeaponsMoreOptions[2].m_Label = "2";
	}
	else {
		_WeaponsMoreOptions[2].setText("???");
		_WeaponsMoreOptions[2].m_Label = "N/A";
	}

	if (_store.grassSoldOut())
	{
		_WeaponsMoreOptions[3].setText("SOLD OUT");
		_WeaponsMoreOptions[3].m_Label = "N/A";
	}
	else if (player.getGrassSpellUnlocked())
	{
		_WeaponsMoreOptions[3].setText("Grass Upgrade - " + to_string(_store.getGrassCost()));
		_WeaponsMoreOptions[3].m_Label = "3";
	}
	else {
		_WeaponsMoreOptions[3].setText("???");
		_WeaponsMoreOptions[3].m_Label = "N/A";
	}
}

void SYDEMapGame::weaponStoreBody(int storeNo)
{
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_WeaponsMoreOptions.getSelected().m_Label == "0")
		{
			if (player.getMoney() >= _WeaponStores[storeNo].getSwordCost())
			{
				player.spendMoney(_WeaponStores[storeNo].getSwordCost());
				_FWindow.AddFString("Pleasure Doing Business");
				_FWindow.AddFString("");
				_FWindow.AddFString("*Sword Upgraded*");
				_FWindow.AddFString("");
				_FWindow.AddFString("-" + to_string(_WeaponStores[0].getSwordCost()) + " Coins");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				player.setSwordDmg(player.getSwordDmg() + 1);
				_WeaponStores[storeNo].buySword();
				setUpWeaponShop(_WeaponStores[storeNo]);
			}
			else {
				_FWindow.AddFString("I have no time for the poor");
				_FWindow.AddFString("");
				_FWindow.AddFString("Either bring me coins, or");
				_FWindow.AddFString("leave my store");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}

		if (_WeaponsMoreOptions.getSelected().m_Label == "1")
		{
			if (player.getMoney() >= _WeaponStores[storeNo].getFireCost())
			{
				player.spendMoney(_WeaponStores[storeNo].getFireCost());
				_FWindow.AddFString("Pleasure Doing Business");
				_FWindow.AddFString("");
				_FWindow.AddFString("*Fire Spell Upgraded*");
				_FWindow.AddFString("");
				_FWindow.AddFString("-" + to_string(_WeaponStores[storeNo].getFireCost()) + " Coins");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				player.setFireDmg(player.getFireDmg() + 1);
				_WeaponStores[storeNo].buyFire();
				setUpWeaponShop(_WeaponStores[storeNo]);
			}
			else {
				_FWindow.AddFString("I have no time for the poor");
				_FWindow.AddFString("");
				_FWindow.AddFString("Either bring me coins, or");
				_FWindow.AddFString("leave my store");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}

		if (_WeaponsMoreOptions.getSelected().m_Label == "2")
		{
			if (player.getMoney() >= _WeaponStores[storeNo].getWaterCost())
			{
				player.spendMoney(_WeaponStores[storeNo].getWaterCost());
				_FWindow.AddFString("Pleasure Doing Business");
				_FWindow.AddFString("");
				_FWindow.AddFString("*Water Spell Upgraded*");
				_FWindow.AddFString("");
				_FWindow.AddFString("-" + to_string(_WeaponStores[storeNo].getWaterCost()) + " Coins");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				player.setWaterDmg(player.getWaterDmg() + 1);
				_WeaponStores[storeNo].buyWater();
				setUpWeaponShop(_WeaponStores[storeNo]);
			}
			else {
				_FWindow.AddFString("I have no time for the poor");
				_FWindow.AddFString("");
				_FWindow.AddFString("Either bring me coins, or");
				_FWindow.AddFString("leave my store");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}

		if (_WeaponsMoreOptions.getSelected().m_Label == "3")
		{
			if (player.getMoney() >= _WeaponStores[storeNo].getGrassCost())
			{
				player.spendMoney(_WeaponStores[storeNo].getGrassCost());
				_FWindow.AddFString("Pleasure Doing Business");
				_FWindow.AddFString("");
				_FWindow.AddFString("*Grass Spell Upgraded*");
				_FWindow.AddFString("");
				_FWindow.AddFString("-" + to_string(_WeaponStores[storeNo].getGrassCost()) + " Coins");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				player.setGrassDmg(player.getGrassDmg() + 1);
				_WeaponStores[storeNo].buyGrass();
				setUpWeaponShop(_WeaponStores[storeNo]);
			}
			else {
				_FWindow.AddFString("I have no time for the poor");
				_FWindow.AddFString("");
				_FWindow.AddFString("Either bring me coins, or");
				_FWindow.AddFString("leave my store");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}

		else if (_WeaponsMoreOptions.getSelected().m_Label == "4")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
}

void SYDEMapGame::lvlUP()
{
	while (player.getXP() >= player.getXPNxtLvl()) {
		player.setLvl(player.getLvl() + 1);
		player.setMaxHealth(player.getMaxHealth() + 22);
		player.setHealth(player.getMaxHealth()); // HEAL ON LVL UP
		player.setXP(player.getXP() - player.getXPNxtLvl());
		player.setXPNxtLvl(player.getXPNxtLvl() * 1.1f);
	}
	//saveGame(); - Probs introduce fountains of saving or something
}
void SYDEMapGame::saveGame()
{
	json save_file;
	//PlayerStats
	save_file["PlayerLVL"] = player.getLvl();
	save_file["PlayerHP"] = player.getHealth();
	save_file["PlayerHPMax"] = player.getMaxHealth();
	save_file["PlayerXP"] = player.getXP();
	save_file["PlayerXPNxt"] = player.getXPNxtLvl();
	save_file["PlayerColour"] = player.getColour();
	save_file["PlayerIcon"] = player.getIcon();
	save_file["PlayerMoney"] = player.getMoney();
	//PlayerWeapons
	save_file["swordDmg"] = player.getSwordDmg();
	save_file["waterUnlock"] = player.getWaterSpellUnlocked();
	save_file["waterDmg"] = player.getWaterDmg();
	save_file["fireUnlock"] = player.getFireSpellUnlocked();
	save_file["fireDmg"] = player.getFireDmg();
	save_file["grassUnlock"] = player.getGrassSpellUnlocked();
	save_file["grassDmg"] = player.getGrassDmg();
	save_file["moneySpellUnlock"] = player.getMoneySpellUnlocked();
	save_file["moneySpellMulti"] = player.getMoneyDmg();
	//POSITION
	save_file["PosX"] = camera_Pos.getX();
	save_file["PosY"] = camera_Pos.getY();
	//Quests
	for (int i = 0; i < questVec.size(); i++)
	{
		save_file["Quests"][to_string(i)]["Given"] = questVec[i].getGiven();
		save_file["Quests"][to_string(i)]["AmtDone"] = questVec[i].getAmtDone();
		save_file["Quests"][to_string(i)]["Finished"] = questVec[i].getFinished();
	}
	// Weapon Stores
	for (int i = 0; i < _WeaponStores.size(); i++)
	{
		save_file["WeaponStore"][to_string(i)]["swordBought"] = _WeaponStores[i].getSwordBght();
		save_file["WeaponStore"][to_string(i)]["fireBought"] = _WeaponStores[i].getFireBght();
		save_file["WeaponStore"][to_string(i)]["waterBought"] = _WeaponStores[i].getWaterBght();
		save_file["WeaponStore"][to_string(i)]["grassBought"] = _WeaponStores[i].getGrassBght();
	}
	// OTHER
	save_file["STATE_GAME"] = _STATE;
	std::ofstream ofs("EngineFiles\\Settings\\MOTS_SaveFile.sc");
	ofs << save_file;
}

void SYDEMapGame::loadSave()
{
	std::ifstream ifs{ "EngineFiles\\Settings\\MOTS_SaveFile.sc" };
	json save_file = json::parse(ifs);
	//string notes = release_notes["body"];
	try { //PlayerStats
		player.setLvl(save_file["PlayerLVL"]);
		player.setHealth(save_file["PlayerHP"]);
		player.setMaxHealth(save_file["PlayerHPMax"]);
		player.setXP(save_file["PlayerXP"]);
		player.setXPNxtLvl(save_file["PlayerXPNxt"]);
		player.setColour(save_file["PlayerColour"]);
		player.setIcon(save_file["PlayerIcon"]);
		player.setMoney(save_file["PlayerMoney"]);
		MOTSDefaults::DebugLogs.push_back("Player Loaded Successfully");
	}
	catch (exception ex)
	{
		// DO SOMETHING
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
	try { //PlayerWeapons
		player.setSwordDmg(save_file["swordDmg"]);
		player.setWaterSpellUnlocked(save_file["waterUnlock"]);
		player.setWaterDmg(save_file["waterDmg"]);
		player.setFireSpellUnlocked(save_file["fireUnlock"]);
		player.setFireDmg(save_file["fireDmg"]);
		player.setGrassSpellUnlocked(save_file["grassUnlock"]);
		player.setGrassDmg(save_file["grassDmg"]);
		player.setMoneySpellUnlocked(save_file["moneySpellUnlock"]);
		player.setMoneyDmg(save_file["moneySpellMulti"]);
		MOTSDefaults::DebugLogs.push_back("Attack Loaded Successfully");
	}
	catch (exception ex)
	{
		// DO SOMETHING
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
	try { 
		//POSITION
		camera_Pos.setX(save_file["PosX"]);
		camera_Pos.setY(save_file["PosY"]);
		MOTSDefaults::DebugLogs.push_back("Position Loaded Successfully");
	}
	catch (exception ex)
	{
		// DO SOMETHING
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
	try { //QUESTS
		for (int i = 0; i < questVec.size(); i++)
		{
			try {
				questVec[i].setGiven(save_file["Quests"][to_string(i)]["Given"]);
				questVec[i].setAmtDone(save_file["Quests"][to_string(i)]["AmtDone"]);
				questVec[i].setFinished(save_file["Quests"][to_string(i)]["Finished"]);
			}
			catch (exception exc)
			{
				// DO SOMETHING
				MOTSDefaults::DebugLogs.push_back("Quest " + to_string(i) + " Load Failure");
				MOTSDefaults::DebugLogs.push_back(exc.what());
			}
		}
		MOTSDefaults::DebugLogs.push_back("Quests Loaded Successfully");
	}
	catch (exception ex)
	{
		// DO SOMETHING
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
	try {
		for (int i = 0; i < _WeaponStores.size(); i++)
		{
			try {
				_WeaponStores[i].setSwordBght(save_file["WeaponStore"][to_string(i)]["swordBought"]);
				_WeaponStores[i].setFireBght(save_file["WeaponStore"][to_string(i)]["fireBought"]);
				_WeaponStores[i].setWaterBght(save_file["WeaponStore"][to_string(i)]["waterBought"]);
				_WeaponStores[i].setGrassBght(save_file["WeaponStore"][to_string(i)]["grassBought"]);
			}
			catch (exception exc)
			{
				MOTSDefaults::DebugLogs.push_back("WeaponStore " + to_string(i) + " Load Failure");
				MOTSDefaults::DebugLogs.push_back(exc.what());
			}
		}
		MOTSDefaults::DebugLogs.push_back("Weapon Stores Loaded Successfully");
	}
	catch (exception ex)
	{
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
	try {
		setState(save_file["STATE_GAME"]);
	}
	catch (exception ex)
	{
		MOTSDefaults::DebugLogs.push_back("Load Error");
		MOTSDefaults::DebugLogs.push_back(ex.what());
	}
}

void SYDEMapGame::loadDefaults()
{
	camera_Pos = Vector2(214, 173);
	//DEV
	if (MOTSDefaults::DEV_ON_)
	{
		camera_Pos = Vector2(2030, 750);
	}
	player.setLvl(1);
	player.setHealth(100);
	player.setMaxHealth(100);
	player.setXP(0);
	player.setXPNxtLvl(1000);
	player.setColour(BLACK);
	player.setIcon("><");
	player.setMoney(0);

	player.setSwordDmg(5);
	player.setWaterSpellUnlocked(false);
	player.setWaterDmg(5);
	player.setFireSpellUnlocked(false);
	player.setFireDmg(5);
	player.setGrassSpellUnlocked(false);
	player.setGrassDmg(5);

	for (int i = 0; i < questVec.size(); i++)
	{
		questVec[i].setGiven(false);
		questVec[i].setAmtDone(0);
		questVec[i].setFinished(false);				
	}
	for (int i = 0; i < _WeaponStores.size(); i++)
	{
		_WeaponStores[i].setSwordBght(0);
		_WeaponStores[i].setFireBght(0);
		_WeaponStores[i].setWaterBght(0);
		_WeaponStores[i].setGrassBght(0);
	}
}

void SYDEMapGame::enemy_dead()
{
	player.setXP(player.getXP() + enemy_exp_gained);
	lvlUP();
	_FWindow.clear();
	if (!UI_STATE_EVENT)
	{
		_STATE = _FightReturnSTATE;
	}
}

bool SYDEMapGame::fexists(const char * filename)
{
	ifstream ifile(filename);
	return ifile.good();
}

vector<string> SYDEMapGame::Split(string a_String, char splitter)
{
	int arraySize = 1;
	for (int i = 0; i < a_String.length(); i++)
	{
		if (a_String[i] == splitter)
		{
			arraySize++;
		}
	}
	std::vector<std::string> splitString(arraySize);
	int arrayNo = 0;
	while (arrayNo < arraySize - 1)
	{
		for (int i = 0; i < a_String.length(); i++)
		{
			if (a_String[i] == splitter)
			{
				splitString[arrayNo] = a_String.substr(0, i);
				a_String = a_String.substr(i + 1, a_String.length() - i);
				arrayNo++;
				break;
			}
		}
	}
	splitString[arraySize - 1] = a_String;
	return splitString;
}

void SYDEMapGame::setByTag(string tag, bool newState, bool isSettingGiven)
{
	for (int i = 0; i < questVec.size(); i++) 
	{ 
		if (tag.compare(questVec[i].getTag()) == 0) 
		{ 
			if (isSettingGiven)
			{
				questVec[i].setGiven(newState);
			}
			else {
				questVec[i].setFinished(newState);
			}
		} 
	}
}

void SYDEMapGame::setByTag(string tag, int amtDone)
{
	for (int i = 0; i < questVec.size(); i++)
	{
		if (tag.compare(questVec[i].getTag()) == 0)
		{
			questVec[i].setAmtDone(amtDone);
		}
	}
}
#pragma endregion
SYDEMapGame::SYDEMapGame()
{
	AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	_list_fight_cases = vector<WildFightAttachment>();
	_list_structures = vector<Structure>();
	_list_structures_dragon_keep = vector<Structure>();
	m_bg = CustomAsset(60, 30, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\bg.bmp", 30, 30));
	m_crab_bg = CustomAsset(46, 23, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\crab_bg.bmp", 23, 23));
	_LevelAsset = CustomAsset(2048, 768, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Level_SYDE.bmp", 1024, 768));
	_DragonKeepAsset = CustomAsset(200, 100, astVars.get_bmp_as_direct_colour_class_array(L"EngineFiles\\Bitmaps\\Swan Lake Dungeon.bmp", 100, 100));

#pragma region Animations


	//ENEMY ANIMATIONS
	m_ORC.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\TestEnemy.bmp", astVars, 100, 30, 10, 10, 0, 27));
	m_ORC.setLooping(true);

	m_PIG.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\pig.bmp", astVars, 120, 10, 10, 10, 0, 12));
	m_PIG.setLooping(true);

	m_WOLF.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\Wolf.bmp", astVars, 50, 40, 10, 10, 0, 16));
	m_WOLF.setLooping(true);

	m_CRAB.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimation.bmp", astVars, 40, 30, 10, 10, 0, 11));
	m_CRAB.setLooping(true);

	m_BLOOD_GHOST.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BloodGhost.bmp", astVars, 50, 110, 10, 10, 0, 55));
	m_BLOOD_GHOST.setLooping(true);

	m_FLAME_SKULL.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\FlamingSkull.bmp", astVars, 40, 70, 10, 10, 0, 27));
	m_FLAME_SKULL.setLooping(true);

	m_Moves = vector<CustomAnimationAsset>{
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SwordAnimation.bmp", astVars, 100, 100, 20, 20, 0, 25), //0
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\CrabAttack.bmp", astVars, 100, 100, 20, 20, 0, 25),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\SwarmAttack.bmp", astVars, 100, 240, 20, 20, 0, 57),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BiteAttack.bmp", astVars, 100, 60, 20, 20, 0, 15),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\WaveAttack.bmp", astVars, 60, 140, 20, 20, 0, 20), //4
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\GrassAttack.bmp", astVars, 100, 100, 20, 20, 0, 25), //5
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\Fireball.bmp", astVars, 100, 160, 20, 20, 0, 39), //6
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\MoneySpell.bmp", astVars, 100, 160, 20, 20, 0, 39), //7
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\WaterAttack.bmp", astVars, 100, 140, 20, 20, 0, 34), //8
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\BoneAttack.bmp", astVars, 80, 160, 20, 20, 0, 32), //9
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\AttackAnimations\\MudThrow.bmp", astVars, 200, 80, 20, 20, 0, 37), //10
	};

	m_MoveAnimation = m_Moves[0];
	m_MoveAnimation.setLooping(false);

	//FISHIES
	m_Fishies = vector<CustomAnimationAsset>{
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\BlueFish.bmp", astVars, 40, 100, 10, 10, 0, 39),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\RedFish.bmp", astVars, 40, 100, 10, 10, 0, 39),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\YellowFish.bmp", astVars, 40, 100, 10, 10, 0, 39),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\GreenFish.bmp", astVars, 40, 100, 10, 10, 0, 39),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\PurpleFish.bmp", astVars, 40, 100, 10, 10, 0, 39),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\GhostFish.bmp", astVars, 40, 100, 10, 10, 0, 39)
	};
	m_FISH = m_Fishies[0];
	m_FISH.setLooping(true);
	//CUTSCENES
	m_SAIL.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\SailingAnimation.bmp", astVars, 160, 20, 20, 20, 0, 8));
	m_SAIL.setLooping(true);

	m_NIGHT_TO_DAY.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\NightToDay.bmp", astVars, 80, 200, 20, 20, 0, 38));
	m_NIGHT_TO_DAY.setLooping(false);

	m_DunegonWarp.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\Cutscenes\\DungeonWarp_001.bmp", astVars, 200, 100, 20, 20, 0, 45));
	m_DunegonWarp.setLooping(false);

	//NPC
	m_PLACEHOLDER.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Bitmaps\\NPC_Placeholder.bmp", astVars, 10, 10, 10, 10, 0, 1));
	m_PLACEHOLDER.setLooping(true);

	m_NPC = m_PLACEHOLDER;
	m_NPC.setLooping(true);

	m_RED_DRAGON.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\DragonAnimation.bmp", astVars, 150, 30, 15, 10, 0, 30));
	m_RED_DRAGON.setLooping(true);

	m_SMOKING_CRAB.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\EnemAnimations\\CrabAnimationSmoking.bmp", astVars, 40, 130, 10, 10, 0, 51));
	m_SMOKING_CRAB.setLooping(true);

	m_NPCs = vector<CustomAnimationAsset>{
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Bitmaps\\NPC_Placeholder.bmp", astVars, 10, 10, 10, 10, 0, 1),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\NPCAnimations\\TheRetroist.bmp", astVars, 100, 50, 10, 10, 0, 15),
		AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\NPCAnimations\\ScaredMan.bmp", astVars, 10, 10, 10, 10, 0, 1)
	};
	for (int j = 0; j < m_NPCs.size(); j++) {
		m_NPCs[j].setLooping(true);
	}
#pragma endregion

	//camera_Pos = Vector2(1280, 676);
#pragma region TownDeclaration

	// LIST OF ALL TOWNS
	vecTowns = vector<_Town_Square>{
		//A
		_Town_Square(Vector2(0,		0), Vector2(255,	95) , "Dissonant Waved Ocean"), // THANKS ME TRICKS AND DOM
		_Town_Square(Vector2(256,	0), Vector2(511,	95) , "Almon Island"), // THANKS ME
		_Town_Square(Vector2(512,	0), Vector2(767,	95) , "Blankis Island"), // THANKS ME
		_Town_Square(Vector2(768,	0), Vector2(1023,	95) , "Aliran Island"), // SUCK SHIT ALI
		_Town_Square(Vector2(1024,	0), Vector2(1279,	95) , "Daggo Coast"), // FUCK YOU LEGO YODA
		_Town_Square(Vector2(1280,	0), Vector2(1535,	95) , "SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	0), Vector2(1791,	95) , "Taumatawhaka"), // THANKS LEGO YODA (DISCORD)
		_Town_Square(Vector2(1792,	0), Vector2(2047,	95) , "Taumata Beach"), // THANKS LEGO YODA (DISCORD)
		//B
		_Town_Square(Vector2(0,		96), Vector2(255,	191), "Toplefia Place"), // THANKS ME
		_Town_Square(Vector2(256,	96), Vector2(511,	191), "North Muric Coast"), // ALI FUCK YOU
		_Town_Square(Vector2(512,	96), Vector2(767,	191), "Ballistica"), // THANKS ALI
		_Town_Square(Vector2(768,	96), Vector2(1023,	191), "Broken Coast West"), // THANKS ME
		_Town_Square(Vector2(1024,	96), Vector2(1279,	191), "Broken Coast East"), // THANKS ME
		_Town_Square(Vector2(1280,	96), Vector2(1535,	191), "Repaired Coast"), // THANKS ME
		_Town_Square(Vector2(1536,	96), Vector2(1791,	191), "Western Meow Coast"), // THANKS ASHIE
		_Town_Square(Vector2(1792,	96), Vector2(2047,	191), "Eastern Meow Coast"), // THANKS ASHIE
		//C
		_Town_Square(Vector2(0,		192), Vector2(255,	287), "Northen SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	192), Vector2(511,	287), "Beached Butthole"), // THANKS TRICKS
		_Town_Square(Vector2(512,	192), Vector2(767,	287), "Arcoomer"), // THANKS ARCANA
		_Town_Square(Vector2(768,	192), Vector2(1023,	287), "Djungelskog"), // THANKS JACKSON
		_Town_Square(Vector2(1024,	192), Vector2(1279,	287), "Thrustbowl"), // THANKS TRICKS
		_Town_Square(Vector2(1280,	192), Vector2(1535,	287), "Jonestown"), // THANKS LINDSAY
		_Town_Square(Vector2(1536,	192), Vector2(1791,	287), "Swan Lake"), // THANKS PETE
		_Town_Square(Vector2(1792,	192), Vector2(2047,	287), "Meow Coast Beach"), //THANKS ASHIE
		//D
		_Town_Square(Vector2(0,		288), Vector2(255,	383), "Southern SYDE Coast"), // THANKS ME
		_Town_Square(Vector2(256,	288), Vector2(511,	383), "Western Plains"), // THANKS ME
		_Town_Square(Vector2(512,	288), Vector2(767,	383), "Rhofields"), // THANKS ME
		_Town_Square(Vector2(768,	288), Vector2(1023,	383), "Loot Lake"), //MORE LEGO YODA
		_Town_Square(Vector2(1024,	288), Vector2(1279,	383), "Kiffidle Lakes"), // THANKS ME
		_Town_Square(Vector2(1280,	288), Vector2(1535,	383), "Arc Cove"), // THANKS ME
		_Town_Square(Vector2(1536,	288), Vector2(1791,	383), "Faraway"), // THANKS ME
		_Town_Square(Vector2(1792,	288), Vector2(2047,	383), "32x Tile Sea"), // THANKS LEGO YODA (DISCORD)
		//E
		_Town_Square(Vector2(0,		384), Vector2(255,	479), "Baffled Coast"), // THANKS ANDREW
		_Town_Square(Vector2(256,	384), Vector2(511,	479), "Zengina"), // THANKS ANDREW
		_Town_Square(Vector2(512,	384), Vector2(767,	479), "Capital Town"), // THANKS ME
		_Town_Square(Vector2(768,	384), Vector2(1023,	479), "Island Centre"), // THANKS ME
		_Town_Square(Vector2(1024,	384), Vector2(1279,	479), "New Xylsdia"), // THANKS ME
		_Town_Square(Vector2(1280,	384), Vector2(1535,	479), "Eastern Plains"), // THANKS ME
		_Town_Square(Vector2(1536,	384), Vector2(1791,	479), "CRT Coast"), //FUCK YOU LEGO YODA
		_Town_Square(Vector2(1792,	384), Vector2(2047,	479), "CRT Island"), //FUCK YOU LEGO YODA
		//F
		_Town_Square(Vector2(0,		480), Vector2(255,	575), "Windan"), // THANKS ME
		_Town_Square(Vector2(256,	480), Vector2(511,	575), "Lake Entrance"), // THANKS CENTRAL COAST
		_Town_Square(Vector2(512,	480), Vector2(767,	575), "Western SYDE River"), // THANKS ME
		_Town_Square(Vector2(768,	480), Vector2(1023,	575), "Eastern SYDE River"), // THANKS ME
		_Town_Square(Vector2(1024,	480), Vector2(1279,	575), "Denton"), // THANKS LUKE
		_Town_Square(Vector2(1280,	480), Vector2(1535,	575), "Denton Fields"), // THANKS LUKE
		_Town_Square(Vector2(1536,	480), Vector2(1791,	575), "Jeff Coast"), // THANKS SIMON
		_Town_Square(Vector2(1792,	480), Vector2(2047,	575), "Uncharted Territory"), // THANKS ME
		//G
		_Town_Square(Vector2(0,		576), Vector2(255,	671), "Uncharted Territory"), // THANKS ME
		_Town_Square(Vector2(256,	576), Vector2(511,	671), "New SYDE Town"), // THANKS ME
		_Town_Square(Vector2(512,	576), Vector2(767,	671), "North Edgecliffe"), // THANKS ME
		_Town_Square(Vector2(768,	576), Vector2(1023,	671), "Last Bay"), // THANKS ME
		_Town_Square(Vector2(1024,	576), Vector2(1279,	671), "Old Capital Town"), // THANKS ME
		_Town_Square(Vector2(1280,	576), Vector2(1535,	671), "Cyprux"), // THANKS DOM
		_Town_Square(Vector2(1536,	576), Vector2(1791,	671), "Xylsdia Coast"), // FUCK YOU ME
		_Town_Square(Vector2(1792,	576), Vector2(2047,	671), "Useless Sea"), // THANKS ME
		//H
		_Town_Square(Vector2(0,		672), Vector2(255,	767), "Uncharted Territory"), // THANKS ME
		_Town_Square(Vector2(256,	672), Vector2(511,	767), "Edgecliffe"), // THANKS ME
		_Town_Square(Vector2(512,	672), Vector2(767,	767), "Eastcliffe"), // THANKS ME
		_Town_Square(Vector2(768,	672), Vector2(1023,	767), "Broken Beach"), // THANKS ME
		_Town_Square(Vector2(1024,	672), Vector2(1279,	767), "Southern Coast"), // THANKS ME
		_Town_Square(Vector2(1280,	672), Vector2(1535,	767), "Cyprux Beach"), // THANKS DOM
		_Town_Square(Vector2(1536,	672), Vector2(1791,	767), "Haven's Corner"), // THANKS ME
		_Town_Square(Vector2(1792,	672), Vector2(2047,	767), "South East Ocean"), // THANKS ME
	};
#pragma endregion
	for (int ii = 746; ii < 754; ii++)
	{
		for (int i = 2022; i < 2038; i++)
		{
			addLand(Vector2(i, ii));
		}
	}
	//STRUCTURE 1 -- TEST STRUCTURE
	AddAttachmentStructure(Vector2(2030, 747), "BUILDING_TEST", 7);
	AddAttachmentStructure(Vector2(2031, 747), "BUILDING_TEST", 7);

	// WATER TEST: BUILDINGS ON WATER MEAN THAT TILE CAN BE WALKED ON :D
	// AddAttachmentStructure(Vector2(216, 172), "BUILDING_TEST", 7);
	// AddAttachmentStructure(Vector2(217, 172), "BUILDING_TEST", 7);

	//ORC WILD FIGHT 1 -- TEST FIGHT
	for (int ii = 749; ii < 752; ii++)
	{
		for (int i = 2028; i < 2032; i++)
		{
			AddAttachmentWildFight(Vector2(i, ii), "ORC_TEST");
		}
	}

#pragma region Wharfs

	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID A:2 - Almon Island
	AddAttachmentStructure(Vector2(392, 83), "Almon Wharf", 96);
	AddAttachmentStructure(Vector2(393, 83), "Almon Wharf", 96);

	// STRUCTURES && WILD FIGHT AREAS INSIDE Jonestown + Repaired Coast

	for (int ii = 259; ii < 263; ii++)
	{
		for (int i = 1522; i < 1530; i ++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Jonestown Wharf", 96);
		}
	}

	for (int ii = 110; ii < 114; ii++)
	{
		for (int i = 1404; i < 1412; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Repaired Wharf", 96);
		}
	}

	//CRT COAST
	for (int ii = 444; ii < 448; ii++)
	{
		for (int i = 1626; i < 1634; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "CRT Coast Wharf", 96);
		}
	}
	for (int ii = 446; ii < 450; ii++)
	{
		for (int i = 1718; i < 1726; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "CRT Island Wharf", 96);
		}
	}
	//Blankis
	for (int ii = 71; ii < 75; ii++)
	{
		for (int i = 590; i < 598; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "South Blankis Wharf", 96);
		}
	}
	for (int ii = 47; ii < 51; ii++)
	{
		for (int i = 642; i < 650; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "East Blankis Wharf", 96);
		}
	}

	//Taumata
	for (int ii = 73; ii < 77; ii++)
	{
		for (int i = 1502; i < 1510; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Taumata Wharf", 96);
		}
	}

	//BALLISTICA
	for (int ii = 136; ii < 140; ii++)
	{
		for (int i = 602; i < 610; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Ballistica Wharf", 96);
		}
	}
	// NORTHERN SYDE COAST
	//198.261
	for (int ii = 257; ii < 261; ii++)
	{
		for (int i = 190; i < 198; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "North SYDE Wharf", 96);
		}
	}

	for (int ii = 284; ii < 286; ii++)
	{
		for (int i = 90; i < 94; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "West SYDE Wharf", 96);
		}
	}

	//Aliran
	for (int ii = 53; ii < 57; ii++)
	{
		for (int i = 788; i < 796; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Aliran Wharf", 96);
		}
	}

	// SWAN LAKE

	for (int ii = 251; ii < 253; ii++)
	{
		for (int i = 1670; i < 1674; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Swan Lake Wharf", 96);
		}
	}

	for (int ii = 227; ii < 229; ii++)
	{
		for (int i = 1726; i < 1730; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "North Swan Lake Wharf", 96);
		}
	}

	for (int ii = 213; ii < 215; ii++)
	{
		for (int i = 1748; i < 1752; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Dragon Keep Wharf", 96);
		}
	}

	// DENTON
	for (int ii = 559; ii < 563; ii++)
	{
		for (int i = 1286; i < 1294; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Denton Wharf", 96);
		}
	}

	// CYPRUX
	for (int ii = 632; ii < 636; ii++)
	{
		for (int i = 1286; i < 1294; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Cyprux Wharf", 96);
		}
	}

	AddAttachmentStructure(Vector2(210, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(216, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(217, 171), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(216, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(217, 172), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(214, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(215, 173), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(210, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(211, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(212, 174), "Toplefia Wharf", 96);
	AddAttachmentStructure(Vector2(213, 174), "Toplefia Wharf", 96);
#pragma endregion
#pragma region Buildings

	//Houses.push_back
	for (int ii = 191; ii < 195; ii++)
	{
		for (int i = 290; i < 298; i++)
		{
			Houses.push_back(DefaultHouse("Mike", m_NPCs[0], "Default House", Vector2(i,ii)));
			Houses[Houses.size() - 1].setPhrases(vector<string>{
				"What Are You Doing In My House?"
			});
		}
	}
	//Default Homes
	for (int i = 0; i < Houses.size(); i++)
	{
		AddAttachmentStructure(Houses[i]._Struct.getPoint(),Houses[i].getHouseOwner() + "'s House", 64);
		_list_structures[_list_structures.size() - 1].m_TAG = Houses[i]._Struct.m_TAG;
	}
	// BEACHED ****Hole
	for (int ii = 224; ii < 230; ii++)
	{
		for (int i = 356; i < 364; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Jiman's House", 64);
		}
	}

	for (int ii = 181; ii < 184; ii++)
	{
		for (int i = 1344; i < 1360; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Jonestown Hall", 64);
		}
	}

	//Island Centre

	for (int ii = 402; ii < 412; ii++)
	{
		for (int i = 790; i < 816; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Island Fitters", 112);
		}
	}

	// Arcoomer

	for (int ii = 244; ii < 255; ii++)
	{
		for (int i = 602; i < 626; i++)
		{
			AddAttachmentStructure(Vector2(i, ii), "Weapons & More", 112);
		}
	}
	//CRT ISLAND
	for (int ii = 426; ii < 432; ii++)
	{
		for (int i = 1850; i < 1862; i ++)
		{
			AddAttachmentStructure(Vector2(i, ii), "The Retroist", 64);
		}
	}
	// STRUCTURES && WILD FIGHT AREAS INSIDE GRID B:1 - Toplefia Place

	for (int ii = 199; ii < 206; ii++)
	{
		for (int i = 220; i < 232; i += 2)
		{
			AddAttachmentStructure(Vector2(i, ii), "Toplefia Town Hall", 64);
			AddAttachmentStructure(Vector2(i + 1, ii), "Toplefia Town Hall", 64);
		}
	}
	for (int ii = 197; ii < 201; ii++)
	{
		for (int i = 242; i < 252; i += 2)
		{
			AddAttachmentStructure(Vector2(i, ii), "Toplefia Farm", 64);
			AddAttachmentStructure(Vector2(i + 1, ii), "Toplefia Farm", 64);
		}
	}
#pragma endregion

#pragma region Dungeons
	for (int i = 1756; i < 1758; i++)
	{
		AddAttachmentStructure(Vector2(i, 209), "Dragon Keep", 208);
	}
	//Dungeon Keep Stuff
	AddDragonKeepAttachment(Vector2(186, 19), "Red Dragon Fight", 192);
	AddDragonKeepAttachment(Vector2(187, 19), "Red Dragon Fight", 192);
#pragma endregion


#pragma region WildfightAreas
	//ADD WILD AREAS IN BOUUNDARIES 402,85  451,85,  402,68   451,68
	for (int ii = 68; ii < 86; ii++)
	{
		for (int i = 402; i < 452; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 32)
			{
				string wfs = getRandomFromList(Almon_WILD);
				int lvlEnemy = (std::rand() % (almon_max_level - almon_min_level)) + almon_min_level;
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}
	//Toplefia
	for (int ii = 176; ii < 201; ii++)
	{
		for (int i = 242; i < 282; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 32) // If Grass
			{
				string wfs = getRandomFromList(Toplefia_WILD);
				int lvlEnemy = (std::rand() % (toplefia_max_level - toplefia_min_level)) + toplefia_min_level;
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}
	//Beached Butthole
	for (int ii = 225; ii < 233; ii++)
	{
		for (int i = 356; i < 372; i++)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 32)
			{
				int lvlEnemy = 5;
				AddAttachmentWildFight(Vector2(i, ii), "Harmless Pig", wfc, lvlEnemy);
			}
		}
	}
	//North Muric Coast
	for (int ii = 143; ii < 147; ii++)
	{
		for (int i = 292; i < 386; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 224)
			{
				string wfs = getRandomFromList(NORTH_MURIC_BEACH_WILD);
				int lvlEnemy = (std::rand() % (north_muric_beach_max_level - north_muric_beach_min_level)) + north_muric_beach_min_level;
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}

	for (int ii = 38; ii < 51; ii++)
	{
		for (int i = 546; i < 598; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 224)
			{
				string wfs = getRandomFromList(NORTH_MURIC_BEACH_WILD); //BEACH ENEMIES
				int lvlEnemy = (std::rand() % (17 - 14)) + 14; // BETWEEN LVL 14-17
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}

	//ENEMY CODE, ADD WHEN ENEMIES MADE, MAKE DIFFERENT FROM ALMON ISLAND
	for (int ii = 285; ii < 306; ii++)
	{
		for (int i = 50; i < 86; i += 2)
		{
			int wfc = getColourFromLevel(Vector2(i, ii));
			if (wfc == 32)
			{
				string wfs = getRandomFromList(WEST_SYDE_WILD); // NEED TO MAKE DIFFERENT FOR SYDE COAST
				int lvlEnemy = (std::rand() % (west_syde_max_level - west_syde_min_level)) + west_syde_min_level;
				AddAttachmentWildFight(Vector2(i, ii), wfs, wfc, lvlEnemy); // NEED TO DO TWICE
				AddAttachmentWildFight(Vector2(i + 1, ii), wfs, wfc);
			}
		}
	}
#pragma endregion
#pragma region Options/SydeMenus
	//MAIN MENU VARS
	_Options = SYDEMenu(vector<SYDEButton> {	
		SYDEButton("", Vector2(0, 1), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 2), Vector2(20, 1), WHITE, true),
		SYDEButton("", Vector2(0, 3), Vector2(20, 1), WHITE, true),
	});

	_StructOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("--", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton("--", Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton("Leave", Vector2(1, 4), Vector2(20, 1), WHITE, true),
	});

	_StructOptions[0].m_Label = "0";
	_StructOptions[1].m_Label = "1";
	_StructOptions[2].m_Label = "2";

	_StructOptions.setActive(true);
	_StructOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _StructOptions.getSize(); i++)
	{
		_StructOptions[i].setHighLight(RED);
	}

	_StructTestOptions = SYDEMenu(vector<SYDEButton> {
			SYDEButton("Speak", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton("Upgrade Sword", Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton("Toplefia Wharf", Vector2(1, 4), Vector2(20, 1), WHITE, true),
			SYDEButton("Swan Lake Wharf", Vector2(1, 5), Vector2(20, 1), WHITE, true),
			SYDEButton("Leave", Vector2(1, 6), Vector2(20, 1), WHITE, true),
	});

	for (int i = 0; i < _StructTestOptions.getSize(); i++)
	{
		_StructTestOptions[i].m_Label = to_string(i);
		_StructTestOptions[i].setHighLight(RED);
	}

	_StructTestOptions.setActive(true);
	_StructTestOptions.setPos(Vector2(1, 2));

	_FightOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("Fight", Vector2(1, 2), Vector2(20, 1), WHITE, true),
		SYDEButton("Run", Vector2(1, 3), Vector2(20, 1), WHITE, true)
	});
	
	_FightOptions[0].m_Label = "0";
	_FightOptions[1].m_Label = "1";

	_FightOptions.setActive(true);
	_FightOptions.setPos(Vector2(1, 2));

	_WeaponsMoreOptions = SYDEMenu(vector<SYDEButton> {
			SYDEButton("", Vector2(1, 2), Vector2(20, 1), BLACK, true),
			SYDEButton("", Vector2(1, 3), Vector2(20, 1), BLACK, true),
			SYDEButton("", Vector2(1, 4), Vector2(20, 1), BLACK, true),
			SYDEButton("", Vector2(1, 5), Vector2(20, 1), BLACK, true),
			SYDEButton("", Vector2(1, 6), Vector2(20, 1), BLACK, true)
	});

	for (int i = 0; i < _WeaponsMoreOptions.getSize(); i++)
	{
		_WeaponsMoreOptions[i].m_Label = to_string(i);
		_WeaponsMoreOptions[i].setHighLight(RED);
	}

	_WeaponsMoreOptions.setActive(true);
	_WeaponsMoreOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _FightOptions.getSize(); i++)
	{
		_FightOptions[i].setHighLight(RED);
	}

	m_MainMenu_BG.setAsset(AnimationSpriteSheets::load_from_animation_sheet(L"EngineFiles\\Animations\\UIAnimations\\MainMenuAnim.bmp", astVars, 100, 180, 20, 20, 0, 45));
	m_MainMenu_BG.setLooping(true);
	_Options[0].m_Label = "0";
	_Options[1].m_Label = "1";
	_Options[2].m_Label = "2";

	_Options[0].setText("Continue");
	_Options[1].setText("New Game");
	_Options[2].setText("Exit Game");

	_Options.setActive(true);
	_Options.setPos(Vector2(0, 0));
	for (int i = 0; i < _Options.getSize(); i++)
	{
		_Options[i].setHighLight(RED);
	}

	_MenuOptions = SYDEMenu(vector<SYDEButton> {
			SYDEButton("Resume", Vector2(1, 2), Vector2(20, 1), WHITE, true),
			SYDEButton("Save Game", Vector2(1, 3), Vector2(20, 1), WHITE, true),
			SYDEButton("Return To Menu", Vector2(1, 4), Vector2(20, 1), WHITE, true),
	});
	_MenuOptions.setActive(true);
	_MenuOptions.setPos(Vector2(1, 2));
	for (int i = 0; i < _MenuOptions.getSize(); i++)
	{
		_MenuOptions[i].m_Label = to_string(i);
		_MenuOptions[i].setHighLight(RED);
	}

	//CUSTOMIZATION STUFF
	_ColourOptions = SYDEMenu(vector<SYDEButton> {
		SYDEButton("BLACK", Vector2(1, 2), Vector2(20, 1), BLACK, true),
			SYDEButton("BLUE", Vector2(1, 3), Vector2(20, 1), BLACK, true),
			SYDEButton("RED", Vector2(1, 4), Vector2(20, 1), BLACK, true),
			SYDEButton("YELLOW", Vector2(1, 5), Vector2(20, 1), BLACK, true),
			SYDEButton("PURPLE", Vector2(1, 6), Vector2(20, 1), BLACK, true),
			SYDEButton("DARK BLUE", Vector2(1, 7), Vector2(20, 1), BLACK, true),
			SYDEButton("BRIGHT RED", Vector2(1, 8), Vector2(20, 1), BLACK, true),
			SYDEButton("BRIGHT WHITE", Vector2(1, 9), Vector2(20, 1), BLACK, true)
	});

	for (int i = 0; i < _ColourOptions.getSize(); i++)
	{
		_ColourOptions[i].m_Label = to_string(i);
		_ColourOptions[i].setHighLight(RED);
	}

	_ColourOptions.setActive(true);
	_ColourOptions.setPos(Vector2(1, 2));

	for (int i = 0; i < _TextAdvOptions.getSize(); i++)
	{
		_TextAdvOptions[i].m_Label = to_string(i);
		_TextAdvOptions[i].setHighLight(RED);
	}

	_TextAdvOptions.setActive(true);
	_TextAdvOptions.setPos(Vector2(3, 16));

	for (int i = 0; i < _TextAdvOptions.getSize(); i++)
	{
		_TextAdvOptions[i].setHighLight(RED);
	}
#pragma endregion

	loadDefaults();
}

ConsoleWindow SYDEMapGame::window_draw_game(ConsoleWindow window, int windowWidth, int windowHeight)
{
	// IF DIFFERENT STATE, CHANGE THE FUNCTION TO DRAW WHAT WE ACTUALLY WANT IT TO
	if (_CurentSTATE.compare(_STATE) != 0)
	{
		// SO NOW IT IS THE CURRENT STATE
		MOTSDefaults::DebugLogs.push_back(_CurentSTATE + "->" + _STATE);
		_CurentSTATE = _STATE;
		if (_STATE == "MainMap")
		{
			//window = Main_Map_Scene(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Main_Map_Scene, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		}
#pragma region Cutscenes
		else if (_STATE == "Sailing")
		{
			AssignState(std::bind(&SYDEMapGame::Sailing, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Resting")
		{
			AssignState(std::bind(&SYDEMapGame::Rest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Warp")
		{
			AssignState(std::bind(&SYDEMapGame::Warp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
		else if (_STATE == "MainMenu")
		{
			//window = Main_Menu(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Player_Stats")
		{
			//window = Main_Menu(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Player_Stats, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma region FishFight
		else if (_STATE == "FISH_FIGHT")
		{
			//RANDOMIZE WHATEVER FISH COLOUR WE FIGHT
			int random_var = std::rand() % 100;
			if (random_var >= 0 && random_var < 21)
			{
				enemy_Damage = 1.0f * enemy_lvl;
				enemy_exp_gained = 25 * (enemy_lvl);
				enemy_Health = 15 * (enemy_lvl);
				m_FISH = m_Fishies[0];
			}
			else if (random_var >= 21 && random_var < 40)
			{
				enemy_Damage = 3.0f * enemy_lvl;
				enemy_exp_gained = 25 * (enemy_lvl);
				enemy_Health = 5 * (enemy_lvl);
				m_FISH = m_Fishies[1];
			}
			else if (random_var >= 40 && random_var < 55)
			{
				enemy_Damage = 1.10f * enemy_lvl;
				enemy_exp_gained = 45 * (enemy_lvl);
				enemy_Health = 35 * (enemy_lvl);
				m_FISH = m_Fishies[2];
			}
			else if (random_var >= 55 && random_var < 75)
			{
				enemy_Damage = 0.75f * enemy_lvl;
				enemy_exp_gained = 25 * (enemy_lvl);
				enemy_Health = 45 * (enemy_lvl);
				m_FISH = m_Fishies[3];
			}
			else if (random_var >= 75 && random_var < 99)
			{
				enemy_Damage = 0.5f * enemy_lvl;
				enemy_exp_gained = 3 * (enemy_lvl);
				enemy_Health = 15 * (enemy_lvl);
				m_FISH = m_Fishies[4];
			}
			else {
				enemy_Damage = 5.0f * enemy_lvl;
				enemy_exp_gained = 125 * (enemy_lvl);
				enemy_Health = 25 * (enemy_lvl);
				m_FISH = m_Fishies[5];
			}
			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Fish_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
#pragma region Fights

		else if (_STATE == "ORC_TEST")
		{
			//window = Orc_Fight(window, windowWidth, windowHeight);
			//GENERATE ORC FIGHT
			enemy_Damage = 2;
			enemy_exp_gained = 25000;
			enemy_Health = 100;
			setUpFight();
			//_STATE = "ORC_FIGHT";
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Red Dragon Fight")
		{
			enemy_Damage = 50;
			enemy_exp_gained = 100000;
			enemy_Health = 18500;
			enemy_lvl = 100;
			setUpFight();
			AssignState(std::bind(&SYDEMapGame::RED_DRAGON_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//FIGHTS
		else if (_STATE == "ORC_FIGHT")
		{
			enemy_Damage = 2 * (enemy_lvl * 0.5f);
			enemy_exp_gained = 50 * (enemy_lvl * 1.5f);
			enemy_Health = 100 * (enemy_lvl * 1.1f);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Orc_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "PIG_FIGHT")
		{
			enemy_Damage = 0.5f;
			enemy_exp_gained = 10 * (enemy_lvl);
			enemy_Health = 20 * (enemy_lvl);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Pig_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "CRAB_FIGHT")
		{
			enemy_Damage = 1.35f * enemy_lvl;
			enemy_exp_gained = 35 * (enemy_lvl);
			enemy_Health = 30 * (enemy_lvl);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Crab_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "SMOKING_CRAB_FIGHT")
		{
			enemy_Damage = 35;
			enemy_exp_gained = 50000;
			enemy_Health = 10120;
			enemy_lvl = 75;

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Smoking_Crab_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Harmless Pig")
		{
			enemy_Damage = 0;
			enemy_exp_gained = 5 * (enemy_lvl);
			enemy_Health = 15 * (enemy_lvl);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::HarmlessPig_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "WOLF_FIGHT")
		{
			enemy_Damage = 4 * (enemy_lvl * 1.5f);
			enemy_exp_gained = 90 * (enemy_lvl * 1.5f);
			enemy_Health = 60 * (enemy_lvl * 1.5f);

			setUpFight();
			//window = Orc_Fight(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Wolf_Fight, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
		else if (_STATE == "QUEST_PAGE")
		{
			//window = Building_Test(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Quest, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma region Buildings
		//BUILDINGS
		else if (_STATE == "BUILDING_TEST")
		{
			_StructTestOptions[0].setText("Speak");
			_StructTestOptions[1].setText("Upgrade Sword (Test");
			//window = Building_Test(window, windowWidth, windowHeight);
			AssignState(std::bind(&SYDEMapGame::Building_Test, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Toplefia Town Hall")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Toplefia_TownHall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Default House")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("--");
			goToDefault(getHouse_FromPos(camera_Pos).getHouseOwner() + "'s House", getHouse_FromPos(camera_Pos).getNPC(),getHouse_FromPos(camera_Pos).getPhrases());
			AssignState(std::bind(&SYDEMapGame::Default_House, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Toplefia Farm")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("Rest");
			AssignState(std::bind(&SYDEMapGame::Toplefia_Farm, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Island Fitters")
		{
			AssignState(std::bind(&SYDEMapGame::Island_Fitters, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "The Retroist")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("Play The Game");
			AssignState(std::bind(&SYDEMapGame::Retroist, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Weapons & More")
		{
			setUpWeaponShop(_WeaponStores[0]);
			AssignState(std::bind(&SYDEMapGame::Weapons_More, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Jiman's House")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Jiman_House, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Jonestown Hall")
		{
			_StructOptions[0].setText("Speak");
			_StructOptions[1].setText("--");
			AssignState(std::bind(&SYDEMapGame::Jonestown_Hall, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
#pragma region Wharfs

		//TOPLEFIA AREA
		else if (_STATE == "Toplefia Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Toplefia_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//Ballistica
		else if (_STATE == "Ballistica Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Ballistica_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//BLANKIS
		else if (_STATE == "South Blankis Wharf")
		{
			_StructOptions[0].setText("Travel");
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::SouthBlankis_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "East Blankis Wharf")
		{
			_StructOptions[0].setText("Travel");
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::EastBlankis_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//Taumata
		else if (_STATE == "Taumata Wharf")
		{
			_StructOptions[0].setText("Travel");
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Taumata_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//Aliran
		else if (_STATE == "Aliran Wharf")
		{
			_StructOptions[0].setText("Travel");
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Aliran_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//CRT COAST
		else if (_STATE == "CRT Coast Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::CRTCoast_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "CRT Island Wharf")
		{
			_StructOptions[0].setText("Travel");
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::CRTIsland_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//Beached ***hole
		//REPAIRED COAST
		else if (_STATE == "Repaired Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Repaired_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//JONESTOWN
		else if (_STATE == "Jonestown Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Jonestown_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//SWAN LAKE
		else if (_STATE == "Swan Lake Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::SwanLake_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "North Swan Lake Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::NorthSwanLake_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "Dragon Keep Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Dragon_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		// DENTON
		else if (_STATE == "Denton Wharf")
		{
			_StructOptions[0].setText("Travel"); 
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Denton_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//NORTH SYDE COAST
		else if (_STATE == "West SYDE Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::WestSYDE_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "North SYDE Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::NorthSYDE_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		// CYPRUX
		else if (_STATE == "Cyprux Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Cyprux_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		//ALMON ISLAND
		else if (_STATE == "Almon Wharf")
		{
			_StructOptions[0].setText("Travel"); //230,80
			_StructOptions[1].setText("Speak");
			AssignState(std::bind(&SYDEMapGame::Almon_Wharf, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
#pragma region Dungeons
		//DUNGEONS
		else if (_STATE == "Dragon Keep")
		{
			setWarp("Dragon Keep Dungeon", _DragonKeepAsset, Vector2(8, 93));
		}
		else if (_STATE == "Dragon Keep Dungeon")
		{
			AssignState(std::bind(&SYDEMapGame::Dragon_Keep_Dungeon, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else if (_STATE == "TextAdvent")
		{
			setWarp("Text Adventure", m_bg, Vector2(20, 10));
			_TXT_VARS = TxtAdvVars();
			_AdvRoom_ = "Start_Room";
		}
		else if (_STATE == "Text Adventure")
		{
			AssignState(std::bind(&SYDEMapGame::Text_Adventure_Dungeon, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
#pragma endregion
		//ETC
		else if (_STATE == "Customize")
		{
			AssignState(std::bind(&SYDEMapGame::Player_Customization, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
		else {
			//FAILSAFE
			AssignState(std::bind(&SYDEMapGame::Main_Menu, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
	}
	window = DoState(window,windowWidth,windowHeight);

	//IF UI EVENT
	if (UI_STATE_EVENT) {
		window = Animation_UI_EVENT(window, m_MoveAnimation);
	}
	return window;
}
#pragma region Cutscenes

ConsoleWindow SYDEMapGame::Sailing(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_SAIL.draw_asset(window, Vector2(0, 0));
	sailingTime += SYDEDefaults::getDeltaTime();
	window.setTextAtPoint(Vector2(0, 1), "Traveling To '" + _STATESail + "'", BLACK_WHITE_BG);
	if (sailingTime >= maxSailTime)
	{
		_STATE = _STATESail;
	}
	return window;
}

ConsoleWindow SYDEMapGame::Rest(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_NIGHT_TO_DAY.draw_asset(window, Vector2(0, 0));
	window.setTextAtPoint(Vector2(0, 1), "Resting At '" + _STATERest + "'", BLACK_WHITE_BG);
	if (m_NIGHT_TO_DAY.getFrame() >= m_NIGHT_TO_DAY.getFrameSize() - 1)
	{
		_STATE = _STATERest;
	}
	return window;
}

ConsoleWindow SYDEMapGame::Warp(ConsoleWindow window, int windowWidth, int windowHeight)
{
	if (m_DunegonWarp.getFrame() >= 35)
	{
		camera_Pos = _WarpPOS;
		window = m_bg.draw_asset(window, Vector2(0));
		window = _levelWarp.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);
	}
	if (m_DunegonWarp.getFrame() >= m_DunegonWarp.getFrameSize() - 1)
	{
		_STATE = _STATEWarp;
	}
	window = m_DunegonWarp.draw_asset(window, Vector2(0, 0));
	return window;
}

ConsoleWindow SYDEMapGame::Animation_UI_EVENT(ConsoleWindow window, CustomAnimationAsset & _anim)
{
	window = _anim.draw_asset(window, Vector2(0));
	window.setTextAtPoint(Vector2(0,1), _AnimHeader, BLACK_BRIGHTWHITE_BG);
	if (_anim.getFrame() == _anim.getFrameSize() - 1)
	{
		UI_STATE_EVENT = false;
	}
	return window;
}

#pragma endregion
#pragma region MainFunc
ConsoleWindow SYDEMapGame::Main_Map_Scene(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = _LevelAsset.draw_asset(window, Vector2(camera_Pos.getX()-20, camera_Pos.getY()-10), windowWidth, windowHeight);

	//UI
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", RED_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 1), "Area: " + getTown(camera_Pos), RED_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "Health: " + std::to_string(player.getHealth()) + ", Lvl: " + std::to_string(player.getLvl()) + ", XP: " + std::to_string(player.getXP()), RED_WHITE_BG);


	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10) , player.getIcon(), window.determineColourAtPoint(Vector2(20, 10), player.getColour(), true));
	char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
	if (tempChar == StructureChar)
	{
		window.setTextAtPoint(Vector2(0, 19), "'" + getSTRUCT_STATE(camera_Pos, true) + "' Press Space To Enter", BLACK_WHITE_BG);
	}

	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == StructureChar)
		{
			_STATE = getSTRUCT_STATE(camera_Pos);
		}
	}
	if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		_STATE = "QUEST_PAGE";
	}
	if (SYDEKeyCode::get_key('T')._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		_PlayerPage();
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 11)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == WildFightChar)
		{
			if (random_variable == 15 && _STATE == "MainMap")
			{
				// SET ENEMY AND LEVEL
				_FightReturnSTATE = _STATE;
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
				enemy_run_chance = getWFA_RUN(camera_Pos);
			}
		}
		
		// CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(1);
		}
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22, 10)));
		//CASES FOR MOVEMENT NOT ALLOWED
		//window.setTextAtPoint(Vector2(0, 1),temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == WildFightChar)
		{
			if (random_variable == 26 && _STATE == "MainMap")
			{
				// SET ENEMY AND LEVEL
				_FightReturnSTATE = _STATE;
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
				enemy_run_chance = getWFA_RUN(camera_Pos);
			}
		}

		if (temp.compare("17") != 0 && temp.compare("16") != 0) //Note, make from 16 -31
		{
			camera_Pos.addX(2);
		}
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 9)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == WildFightChar)
		{
			if (random_variable == 7 && _STATE == "MainMap")
			{
				// SET ENEMY AND LEVEL
				_FightReturnSTATE = _STATE;
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
				enemy_run_chance = getWFA_RUN(camera_Pos);
			}
		}

		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addY(-1);
		}
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18, 10)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (tempChar == WildFightChar)
		{
			if (random_variable == 30 && _STATE == "MainMap")
			{
				// SET ENEMY AND LEVEL
				_FightReturnSTATE = _STATE;
				_STATE = getWFA_STATE(camera_Pos);
				enemy_lvl = getWFA_LVL(camera_Pos);
				enemy_run_chance = getWFA_RUN(camera_Pos);
			}
		}

		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("17") != 0 && temp.compare("16") != 0)
		{
			camera_Pos.addX(-2);
		}
	}
	if (MOTSDefaults::DEBUG_UI_)
	{
		window.setTextAtPoint(Vector2(0, 2), to_string((int)camera_Pos.getX()) + "," + to_string((int)camera_Pos.getY()), RED_WHITE_BG);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Main_Menu(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_MainMenu_BG.draw_asset(window, Vector2(0,0));
	if (time_passed < 0.15f)
	{
		if (m_MainMenu_BG.getFrame() == 0)
		{
			m_MainMenu_BG.setFrame(m_MainMenu_BG.getFrameSize());
		}
		else {
			m_MainMenu_BG.setFrame(m_MainMenu_BG.getFrame() - 1);
		}
		time_passed += SYDEDefaults::getDeltaTime();
	}
	else
	{
		time_passed = 0.0f;
	}
	window = _Options.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_Options.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_Options.getSelected().m_Label == "0")
		{
			//LOAD SAVE
			if (!fexists("EngineFiles\\Settings\\MOTS_SaveFile.sc"))
			{
				MOTSDefaults::DebugLogs.push_back("Save File Not Found");				
			}
			else {
				_STATE = "MainMap";
				loadSave();
			}
		}
		else if (_Options.getSelected().m_Label == "1")
		{
			// REVERT EVERYTHING TO DEFAULT VARS
			loadDefaults();
			_STATE = "Customize";
		}
		else if (_Options.getSelected().m_Label == "2")
		{
			exit(NULL);
		}
	}
	return window;
}

ConsoleWindow SYDEMapGame::Quest(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	if (SYDEKeyCode::get_key('I')._CompareState(KEYDOWN))
	{
		_STATE = "MainMap";
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEYDOWN))
	{
		questPage--;
		if (questPage < 0)
		{
			questPage = questVec.size() - 1;
		}
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEYDOWN))
	{
		questPage++;
		if (questPage > questVec.size() - 1)
		{
			questPage = 0;
		}
	}
	if (questVec[questPage].getGiven())
	{
		for (int i = 0; i < questVec[questPage].getDetails().size(); i++)
		{
			window.setTextAtPoint(Vector2(0, i + 1), questVec[questPage].getDetails()[i], BLACK_WHITE_BG);
		}
	}
	else{
		window.setTextAtPoint(Vector2(0,  1), "???", BLACK_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 19), to_string(questVec[questPage].getAmtDone()) + "/" + to_string(questVec[questPage].getAmtRequired()), BLACK_WHITE_BG);
	return window;
}

ConsoleWindow SYDEMapGame::Player_Stats(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK_BRIGHTYELLOW_BG);
		}
	}
	if (SYDEKeyCode::get_key('T')._CompareState(KEYDOWN))
	{
		_STATE = _MenuReturnSTATE;
	}

	window = _MenuOptions.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_MenuOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_MenuOptions.getSelected().m_Label == "0")
		{
			_STATE = _MenuReturnSTATE;
		}
		else if (_MenuOptions.getSelected().m_Label == "1")
		{
			//SAVE STATE
			_STATE = _MenuReturnSTATE;
			saveGame();
			_STATE = "Player_Stats";
		}
		else if (_MenuOptions.getSelected().m_Label == "2")
		{
			_STATE = "MainMenu";
		}
	}

	window.setTextAtPoint(Vector2(15, 1), "GAME PAUSED", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 9), "PLAYER STATS", BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 10), "Money: " + to_string(player.getMoney()), BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 11), "Health: " + to_string(player.getHealth()) + "/" + to_string(player.getMaxHealth()), BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 12), "LvL: " + to_string(player.getLvl()), BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 13), "Sword DMG: " + to_string(player.getSwordDmg()), BLACK_BRIGHTYELLOW_BG);
	if (player.getFireSpellUnlocked())
	{
		window.setTextAtPoint(Vector2(0, 13), "Fire DMG: " + to_string(player.getFireDmg()), BLACK_BRIGHTYELLOW_BG);
	}
	else {
		window.setTextAtPoint(Vector2(0, 14), "???", BLACK_BRIGHTYELLOW_BG);
	}
	if (player.getWaterSpellUnlocked())
	{
		window.setTextAtPoint(Vector2(0, 15), "Water DMG: " + to_string(player.getWaterDmg()), BLACK_BRIGHTYELLOW_BG);
	}
	else {
		window.setTextAtPoint(Vector2(0, 15), "???", BLACK_BRIGHTYELLOW_BG);
	}
	if (player.getGrassSpellUnlocked())
	{
		window.setTextAtPoint(Vector2(0, 16), "Grass DMG: " + to_string(player.getGrassDmg()), BLACK_BRIGHTYELLOW_BG);
	}
	else {
		window.setTextAtPoint(Vector2(0, 16), "???", BLACK_BRIGHTYELLOW_BG);
	}
	if (player.getMoneySpellUnlocked())
	{
		window.setTextAtPoint(Vector2(0, 17), "Money Spell Multi: " + to_string(player.getMoneyDmg()), BLACK_BRIGHTYELLOW_BG);
	}
	else {
		window.setTextAtPoint(Vector2(0, 17), "???", BLACK_BRIGHTYELLOW_BG);
	}
	window.setTextAtPoint(Vector2(0, 18), "XP: " + to_string(player.getXP()), BLACK_BRIGHTYELLOW_BG);
	window.setTextAtPoint(Vector2(0, 19), "XP To Next Level: " + to_string(player.getXPNxtLvl() - player.getXP()), BLACK_BRIGHTYELLOW_BG);
	return window;
}

ConsoleWindow SYDEMapGame::Player_Customization(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", WHITE_WHITE_BG);
		}
	}
	window = _ColourOptions.draw_menu(window);
	window.setTextAtPoint(Vector2(0,1),"CUSTOMIZE YOUR CHARACTER", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 17), "TAB: Change Colour", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 18), "A or D: Change Icon", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(0, 19), "Space: Start Game", BLACK_WHITE_BG);
	window.setTextAtPoint(Vector2(25, 10), vecIcons[iconNo], window.determineColourAtPoint(Vector2(25, 10), vecIconCol[_ColourOptions.getSelectedNumber()], true));
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_ColourOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key('A')._CompareState(KEYDOWN)))
	{
		iconNo--;
		if (iconNo < 0)
		{
			iconNo = vecIcons.size() - 1;
		}
	}
	else if ((SYDEKeyCode::get_key('D')._CompareState(KEYDOWN)))
	{
		iconNo++;
		if (iconNo >= vecIcons.size())
		{
			iconNo = 0;
		}
	}
	else if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		player.setColour(vecIconCol[_ColourOptions.getSelectedNumber()]);
		player.setIcon(vecIcons[iconNo]);
		_STATE = "MainMap";
	}
	return window;
}
#pragma endregion

ConsoleWindow SYDEMapGame::Building_Test(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), "BUILDING_TEST", BLACK_WHITE_BG);

	window = _StructTestOptions.draw_menu(window);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructTestOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructTestOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Man: You Poor Lad");
			_FWindow.AddFString("Man: Rest Up My Son");
			_FWindow.AddFString("*HEALTH RESTORED*");
			player.setHealth(player.getMaxHealth());
		}
		else if (_StructTestOptions.getSelected().m_Label == "1")
		{
			player.setSwordDmg(player.getSwordDmg() + 1);
			_FWindow.AddFString("*SWORD UPGRADED*");
		}
		else if (_StructTestOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			camera_Pos = Vector2(214, 173); // Toplefia Wharf
			setSail("Toplefia Wharf");
			_FWindow.clear();
		}
		else if (_StructTestOptions.getSelected().m_Label == "3")
		{
			camera_Pos = Vector2(1670, 251); // Swan Lake Wharf
			setSail("Swan Lake Wharf");
			_FWindow.clear();
		}
		else if (_StructTestOptions.getSelected().m_Label == "4")
		{
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

#pragma region Fights

ConsoleWindow SYDEMapGame::Orc_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_ORC, enemy_run_chance, enemy_attack, true);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 1, 2, 0.5f, 0);		
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Orc Used Bone Club");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		setAnimation_UI_EVENT(m_Moves[9], "Orc Used Bone Club");
		enemy_attack = false;
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Pig_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_PIG, enemy_run_chance, enemy_attack, true);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 2, 2, 0.5f, 0.5f);		
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Pig Used Mud Throw");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		enemy_attack = false;
		setAnimation_UI_EVENT(m_Moves[10], "Pig Used Mud Throw");
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::HarmlessPig_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_PIG, enemy_run_chance, enemy_attack, true);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 2, 2, 0.5f, 0.5f);
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		if (getByTag("Beached_Pigs_Quest").getGiven())
		{
			setByTag("Beached_Pigs_Quest", getByTag("Beached_Pigs_Quest").getAmtDone() + 1);
		}
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Pig Used Roll Around");
		_FWindow.AddFString("It Didn't Do A Thing");
		enemy_attack = false;
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Wolf_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_WOLF, enemy_run_chance, enemy_attack, true);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 1, 2, 0.5f, 0.5f);
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 1.5f;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Wolf Used Bite");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		setAnimation_UI_EVENT(m_Moves[3], "Wolf Used Bite");
		enemy_attack = false;
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::RED_DRAGON_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = DragonKeepBoss_Header(window, windowWidth, windowHeight, enemy_attack);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 2, 0.5f, 1, 0.5f);		
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
		if (getByTag("Jonestown_Main_Quest").getGiven())
		{
			getByTag("Jonestown_Main_Quest").addAmtDone(1);
			getByTag("Jonestown_Main_Quest").setFinished(true);
		}
		//Credits <---Add these to credits scene --->
		camera_Pos = Vector2(1522, 259);
		setSail("Jonestown Wharf");
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 4.5f;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Dragon Used Bite");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		enemy_attack = false;
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Crab_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = m_crab_bg.draw_asset(window,Vector2(0));
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_CRAB, enemy_run_chance, enemy_attack, false);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 3, 2.5f, 0.15f, 2.5f);
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 2.2f;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Crab Used Claw Attack");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		setAnimation_UI_EVENT(m_Moves[1], "Crab Used Claw Attack");
		enemy_attack = false;

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0 && !UI_STATE_EVENT)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Fish_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_FISH, enemy_run_chance, enemy_attack, true);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 3, 0.25f, 0.15f, 5.5f);
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 3.2f;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Fish Used Swarm");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		setAnimation_UI_EVENT(m_Moves[2], "Fish Used Swarm");
		enemy_attack = false;

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0 && !UI_STATE_EVENT)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

ConsoleWindow SYDEMapGame::Smoking_Crab_Fight(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//bool enemy_attack = false;
	window = m_crab_bg.draw_asset(window, Vector2(0));
	window = Enemy_Header(window, windowWidth, windowHeight, _STATE, m_SMOKING_CRAB, enemy_run_chance, enemy_attack, false);
	if (_MoveOptions.getActive() && _FightOptions.getActive())
	{
		_FightOptions.setActive(false); // if both are active, we turn off figt options this fram and allow input next frame
	}
	else if (_MoveOptions.getActive())
	{
		window = _MoveOptions.draw_menu(window);
		fightBody(enemy_Health, enemy_attack, 2.5f, 0.2f, 0.05f, 1.5f);
	}

	if (enemy_Health <= 0)
	{
		enemy_dead();
		enemy_attack = false;
	}
	if (enemy_attack && !UI_STATE_EVENT)
	{
		int dmgAppliedOrc = enemy_Damage * 2;
		player.setHealth(player.getHealth() - dmgAppliedOrc);
		_FWindow.AddFString("Crab Used Smoke");
		_FWindow.AddFString("Hit For " + to_string(dmgAppliedOrc));
		enemy_attack = false;

	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(20, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	window.setTextAtPoint(Vector2(0, 19), "Player Health: " + to_string(player.getHealth()), BRIGHTWHITE);
	if (player.getHealth() <= 0)
	{
		_FWindow.clear();
		player.setHealth(1);
		_STATE = "MainMenu";
	}
	return window;
}

#pragma endregion

#pragma region BuildingsFunc

ConsoleWindow SYDEMapGame::Default_House(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _DefaultHouseName, m_NPC);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{			
			_FWindow.AddFString(getRandomFromList(_DEFAULTPHRASES));
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	return window;
}

ConsoleWindow SYDEMapGame::Jonestown_Hall(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			if (!getByTag("Jonestown_Main_Quest").getGiven())
			{
				//Do Quest Cutscene
				_FWindow.AddFString("Ah, you've arrived");
				_FWindow.AddFString("I'll be blunt");
				_FWindow.AddFString("There's a dragon to the east");
				_FWindow.AddFString("of SYDE island");
				_FWindow.AddFString("I need you to kill it");
				_FWindow.AddFString("Take this pass to travel to");
				_FWindow.AddFString("Swan lake, you can figure");
				_FWindow.AddFString("the rest out from there");
				setByTag("Jonestown_Main_Quest", true, true);
			}
			else if (getByTag("Jonestown_Main_Quest").getFinished())
			{
				//Do Quest Cutscene
				_FWindow.AddFString("I cannot express any further");
				_FWindow.AddFString("gratitude than right now");
				_FWindow.AddFString("");
				_FWindow.AddFString("The island is forever in");
				_FWindow.AddFString("debt to you");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				setByTag("Jonestown_Main_Quest", true, true);
			}
			else
			{
				_FWindow.AddFString("Use that pass I gave you");
				_FWindow.AddFString("to catch the boat to Swan Lake");
				_FWindow.AddFString("");
				_FWindow.AddFString("The island is counting on you");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Jiman_House(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_NPCs[2]);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			if (getByTag("Beached_Pigs_Quest").getFinished())
			{
				//Do Quest Cutscene
				_FWindow.AddFString("I am no longer in need");
				_FWindow.AddFString("of your services kind stranger");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				//setByTag("Beached_Pigs_Quest", true, true);
			}
			else if (!getByTag("Beached_Pigs_Quest").getGiven())
			{
				//Do Quest Cutscene
				_FWindow.AddFString("Help me stranger");
				_FWindow.AddFString("I haven't left home in 3 days");
				_FWindow.AddFString("my place is surrounded by...");
				_FWindow.AddFString("!!MONSTERS!!");
				_FWindow.AddFString("");
				_FWindow.AddFString("if you get rid of them");
				_FWindow.AddFString("i will reward you");
				_FWindow.AddFString("");
				//Do Quest Cutscene
				setByTag("Beached_Pigs_Quest", true, true);
			}
			else if (getByTag("Beached_Pigs_Quest").getGiven() && getByTag("Beached_Pigs_Quest").getAmtDone() < getByTag("Beached_Pigs_Quest").getAmtRequired())
			{
				_FWindow.AddFString("pls kill those monsters");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("i'm running low on food");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
			else if (getByTag("Beached_Pigs_Quest").getGiven() && getByTag("Beached_Pigs_Quest").getAmtDone() >= getByTag("Beached_Pigs_Quest").getAmtRequired())
			{
				_FWindow.AddFString("Thank you kind stranger");
				_FWindow.AddFString("here is your reward");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("*SWORD UPGRADED*");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				setByTag("Beached_Pigs_Quest", true, false);
				player.setSwordDmg(player.getSwordDmg() + 1);
			}
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Retroist(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_NPCs[1]);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Play My Game");
			_FWindow.AddFString("...if you dare");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("hehehehehe");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_STATE = "TextAdvent";
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

#pragma endregion

#pragma region WharfsFunc

ConsoleWindow SYDEMapGame::Jonestown_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			if (!getByTag("Jonestown_Main_Quest").getGiven())
			{
				_FWindow.AddFString("Sorry, Swan Lake Is Blocked");
				_FWindow.AddFString("There are dangers on the");
				_FWindow.AddFString("island");
				_FWindow.AddFString("");
				_FWindow.AddFString("Authorised Access Only");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
			else {
				camera_Pos = Vector2(1670, 251); // Swan Lake Wharf
				setSail("Swan Lake Wharf");
				_FWindow.clear();
			}
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			if (!getByTag("Jonestown_Main_Quest").getGiven())
			{
				_FWindow.AddFString("Sorry, Swan Lake Is Blocked");
				_FWindow.AddFString("There are dangers on the");
				_FWindow.AddFString("island");
				_FWindow.AddFString("");
				_FWindow.AddFString("Authorised Access Only");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
			}
			else {
				_FWindow.AddFString("Ah i see you have");
				_FWindow.AddFString("an access pass");
				_FWindow.AddFString("");
				_FWindow.AddFString("");
				_FWindow.AddFString("We will travel to swan");
				_FWindow.AddFString("lake when you are ready");
				_FWindow.AddFString("");
				_FWindow.AddFString("Be careful out there");
			}
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::SouthBlankis_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(602, 136); // Ballistica
			setSail("Ballistica Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::EastBlankis_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(788, 53);
			setSail("Aliran Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Ballistica_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(590, 71);
			setSail("South Blankis Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Aliran_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(642, 47); // EAST BLANKIS
			setSail("East Blankis Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Repaired_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1502, 73);
			setSail("Taumata Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Taumata_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1404, 110);
			setSail("Repaired Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::CRTCoast_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1718, 447);
			setSail("CRT Island Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::CRTIsland_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1626, 444);
			setSail("CRT Coast Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::SwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1528, 262); // Jonestown Wharf
			setSail("Jonestown Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("Are you ready to head back to");
			_FWindow.AddFString("the mainland yet?");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::NorthSwanLake_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1748, 214);
			setSail("Dragon Keep Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("Oh damn a customer");
			_FWindow.AddFString("");
			_FWindow.AddFString("This ship sails to Dragon");
			_FWindow.AddFString("Keep");
			_FWindow.AddFString("");
			_FWindow.AddFString("I swear nothing of danger");
			_FWindow.AddFString("lies there");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Dragon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1726, 228); 
			setSail("North Swan Lake Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("Are you ready to head back to");
			_FWindow.AddFString("the mainland yet?");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Almon_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(214, 173); // Toplefia Wharf
			setSail("Toplefia Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("Are you ready to head back to");
			_FWindow.AddFString("the mainland yet?");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Toplefia_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(392, 83); // Almon Island Dock
			setSail("Almon Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("We're Going To Almon Island! ");
			_FWindow.AddFString("A lot of dangerous creatures");
			_FWindow.AddFString("over there so you might want");
			_FWindow.AddFString("to make sure you're strong");
			_FWindow.AddFString("enough");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Toplefia_TownHall(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Oh hey it's you.");
			_FWindow.AddFString("The mayor of Jonestown called");
			_FWindow.AddFString("requested I find someone to");
			_FWindow.AddFString("help with some problem they're");
			_FWindow.AddFString("having over there.");
			_FWindow.AddFString("Jonestown is just along the");
			_FWindow.AddFString("north east coast, shouldn't");
			_FWindow.AddFString("take too long to get there.");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Toplefia_Farm(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			_FWindow.AddFString("Welcome To My Farm");
			_FWindow.AddFString("I hope my animals didn't");
			_FWindow.AddFString("give you much trouble");
			_FWindow.AddFString("I love those fellas");
			_FWindow.AddFString("");
			_FWindow.AddFString("Please rest if you need");
			_FWindow.AddFString("to. You look so tired");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			//REST
			player.setHealth(player.getMaxHealth());
			sleepAt(_STATE);
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::WestSYDE_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(190, 260); // Almon Island Dock
			setSail("North SYDE Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	return window;
}

ConsoleWindow SYDEMapGame::NorthSYDE_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(92, 285); //92, 285
			setSail("West SYDE Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Denton_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1286,632); // Almon Island Dock
			setSail("Cyprux Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Cyprux_Wharf(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = Wharf_Header(window, windowWidth, windowHeight, _STATE, m_PLACEHOLDER);
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_StructOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_StructOptions.getSelected().m_Label == "0")
		{
			camera_Pos = Vector2(1286, 559); // Denton Dock
			setSail("Denton Wharf");
			_FWindow.clear();
		}
		else if (_StructOptions.getSelected().m_Label == "1")
		{
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
			_FWindow.AddFString("");
		}
		else if (_StructOptions.getSelected().m_Label == "2")
		{
			// LEAVE BUILDING
			_STATE = "MainMap";
			_FWindow.clear();
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BRIGHTWHITE);
	}
	return window;
}


#pragma endregion

#pragma region Shops

ConsoleWindow SYDEMapGame::Weapons_More(ConsoleWindow window, int windowWidth, int windowHeight)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK_WHITE_BG);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _STATE, BLACK_WHITE_BG);
	window = _WeaponsMoreOptions.draw_menu(window);
	window = m_PLACEHOLDER.draw_asset(window, Vector2(20, 2));
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_WeaponsMoreOptions.nextSelect();
	}
	weaponStoreBody(0);
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(10, 12 + i), _FWindow.getFString(i), BLACK_WHITE_BG);
	}
	return window;
}

ConsoleWindow SYDEMapGame::Island_Fitters(ConsoleWindow window, int windowWidth, int windowHeight)
{
	return Player_Customization(window,windowWidth, windowHeight);
}

#pragma endregion

#pragma region Headers

ConsoleWindow SYDEMapGame::Enemy_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset& _EnemAnim, int _run, bool& enemyAttk, bool bg_needed)
{
	if (bg_needed)
	{
		for (int l = 0; l < windowWidth; l++)
		{
			for (int m = 0; m < windowHeight; m++)
			{
				window.setTextAtPoint(Vector2(l, m), " ", BLACK);
			}
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _STATE, BLACK_WHITE_BG);
	window = _EnemAnim.draw_asset(window, Vector2(20, 2));

	window.setTextAtPoint(Vector2(20, 11), "Health:" + std::to_string(enemy_Health) + ",LVL:" + std::to_string(enemy_lvl), BLACK_WHITE_BG);

	if (_FightOptions.getActive() && !UI_STATE_EVENT)
	{
		window = _FightOptions.draw_menu(window);
		if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_FightOptions.nextSelect();
		}
		if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_FightOptions.getSelected().m_Label == "0")
			{
				//_FightOptions.setActive(false);
				_MoveOptions.setActive(true);
			}
			else if (_FightOptions.getSelected().m_Label == "1")
			{
				//IF RUN WAS SUCCESSFUL
				int _chance = std::rand() % 100;
				if (_chance < _run)
				{
					_FWindow.clear();
					_STATE = _FightReturnSTATE;
				}
				else {
					enemyAttk = true;
					_FWindow.AddFString("Player Failed To Run Away");
				}
			}
		}
	}

	return window;
}

ConsoleWindow SYDEMapGame::DragonKeepBoss_Header(ConsoleWindow window, int windowWidth, int windowHeight, bool &attk)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _STATE, BLACK_WHITE_BG);
	window = m_RED_DRAGON.draw_asset(window, Vector2(15, 2));

	window.setTextAtPoint(Vector2(20, 11), "Health:" + std::to_string(enemy_Health) + ",LVL:" + std::to_string(enemy_lvl), BLACK_WHITE_BG);

	if (_FightOptions.getActive())
	{
		window = _FightOptions.draw_menu(window);
		if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
		{
			_FightOptions.nextSelect();
		}
		if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
		{
			if (_FightOptions.getSelected().m_Label == "0")
			{
				//_FightOptions.setActive(false);
				_MoveOptions.setActive(true);
			}
			else if (_FightOptions.getSelected().m_Label == "1")
			{
				int _chance = std::rand() % 100;
				if (_chance < 0)
				{
					_FWindow.clear();
					_STATE = _FightReturnSTATE;
				}
				else {
					_FWindow.AddFString("Player Failed To Run Away");
					attk = true;
				}
			}
		}
	}

	return window;
}

ConsoleWindow SYDEMapGame::Wharf_Header(ConsoleWindow window, int windowWidth, int windowHeight, string _Name, CustomAnimationAsset& _NPCAnim)
{
	for (int l = 0; l < windowWidth; l++)
	{
		for (int m = 0; m < windowHeight; m++)
		{
			window.setTextAtPoint(Vector2(l, m), " ", BLACK);
		}
	}
	window.setTextAtPoint(Vector2(0, 1), _Name, BLACK_WHITE_BG);
	window = _StructOptions.draw_menu(window);

	window = _NPCAnim.draw_asset(window, Vector2(20, 2));
	return window;
}

void SYDEMapGame::fightBody(int & enemy_hp, bool & enemy_attack, float swordMulti, float fireMulti, float waterMulti, float grassMulti)
{
	if (UI_STATE_EVENT)
	{
		return;
	}
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_MoveOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_MoveOptions.getSelected().m_Label == "0")
		{
			//FIGHT SEQUENCE SWORD
			int dmgApplied = player.getSwordDmg() * swordMulti * player.getLvl();
			enemy_hp -= dmgApplied;
			_FWindow.AddFString("Player Used Sword");
			_FWindow.AddFString("Hit For " + to_string(dmgApplied));
			enemy_attack = true;
			setAnimation_UI_EVENT(m_Moves[0], "Player Used Sword Attack"); // SWORD ANIMATION
		}
		else if (_MoveOptions.getSelected().m_Label == "1")
		{
			int dmgApplied = player.getFireDmg() * fireMulti * player.getLvl();
			enemy_hp -= dmgApplied;
			_FWindow.AddFString("Player Used Fire");
			_FWindow.AddFString("Hit For " + to_string(dmgApplied));
			enemy_attack = true;
			setAnimation_UI_EVENT(m_Moves[6],"Player Casts Fire Spell"); // FIRE ANIMATION
		}
		else if (_MoveOptions.getSelected().m_Label == "2")
		{
			int dmgApplied = player.getWaterDmg() * waterMulti * player.getLvl();
			enemy_hp -= dmgApplied;
			_FWindow.AddFString("Player Used Water");
			_FWindow.AddFString("Hit For " + to_string(dmgApplied));
			enemy_attack = true;
			setAnimation_UI_EVENT(m_Moves[4], "Player Casts Water Spell"); // WATER ANIMATION
		}
		else if (_MoveOptions.getSelected().m_Label == "3")
		{
			int dmgApplied = player.getGrassDmg() * grassMulti * player.getLvl();
			enemy_hp -= dmgApplied;
			_FWindow.AddFString("Player Used Grass");
			_FWindow.AddFString("Hit For " + to_string(dmgApplied));
			enemy_attack = true;
			setAnimation_UI_EVENT(m_Moves[5], "Player Casts Grass Spell"); // GRASS ANIMATION
		}
		else if (_MoveOptions.getSelected().m_Label == "4")
		{
			int cMax = player.getMoneyDmg() * enemy_lvl;
			if (cMax  <= 0) { cMax = 1; }
			int cMin = (player.getMoneyDmg() - 1) * enemy_lvl;
			if (cMin < 0) { cMin = 0; }
			int coinsGained = std::rand() % (cMax- cMin) + cMin;
			_FWindow.AddFString("Player Used Raining Cash");
			_FWindow.AddFString("Player Gained $" + to_string(coinsGained));
			player.addMoney(coinsGained);
			enemy_attack = true;
			setAnimation_UI_EVENT(m_Moves[7], "Player Casts Money Spell"); // MONEY ANIMATION
		}
		else if (_MoveOptions.getSelected().m_Label == "5")
		{
			_FightOptions.setActive(true);
			_MoveOptions.setActive(false);
		}
	}
}

#pragma endregion

#pragma region Dungeons
ConsoleWindow SYDEMapGame::Dragon_Keep_Dungeon(ConsoleWindow window, int windowWidth, int windowHeight)
{
	//NEED DUNGEON IMPLEMENTATION
	window = m_bg.draw_asset(window, Vector2(0, 0));
	window = _DragonKeepAsset.draw_asset(window, Vector2(camera_Pos.getX() - 20, camera_Pos.getY() - 10), windowWidth, windowHeight);

	//UI
	for (int l = 0; l < windowWidth; l++)
	{
		window.setTextAtPoint(Vector2(l, 19), " ", RED_WHITE_BG);
	}
	window.setTextAtPoint(Vector2(0, 19), "Health: " + std::to_string(player.getHealth()) + ", Lvl: " + std::to_string(player.getLvl()) + ", XP: " + std::to_string(player.getXP()), RED_WHITE_BG);
	//PlayerPos
	window.setTextAtPoint(Vector2(20, 10), player.getIcon(), window.determineColourAtPoint(Vector2(20, 10), player.getColour(), true));
	char tempChar = _DragonKeepAsset.getCharAtPoint(camera_Pos);
	if (tempChar == StructureChar)
	{
		window.setTextAtPoint(Vector2(0, 19), "'" + getSTRUCT_STATE(camera_Pos, _list_structures_dragon_keep) + "' Press Space To Enter", BLACK_WHITE_BG);
	}

	if (SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		if (tempChar == StructureChar)
		{
			_STATE = getSTRUCT_STATE(_list_structures_dragon_keep ,camera_Pos);
		}
	}
	if (SYDEKeyCode::get_key('T')._CompareState(KEYDOWN))
	{
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		_PlayerPage();
	}
	if (SYDEKeyCode::get_key('S')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 11)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (random_variable == 15 && _STATE == "Dragon Keep Dungeon")
		{
			_FightReturnSTATE = _STATE;
			_STATE = getRandomFromList(DRAGON_KEEP_WILD);
			enemy_lvl = (std::rand() % (dragon_keep_max_level - dragon_keep_min_level)) + dragon_keep_min_level;
			enemy_run_chance = 15;
		}
		// CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("0") != 0 && temp.compare("1") != 0)
		{
			camera_Pos.addY(1);
		}
	}
	if (SYDEKeyCode::get_key('D')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(22, 10)));
		//CASES FOR MOVEMENT NOT ALLOWED
		//window.setTextAtPoint(Vector2(0, 1),temp, BLACK_WHITE_BG);
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (random_variable == 26 && _STATE == "Dragon Keep Dungeon")
		{
			// SET ENEMY AND LEVEL
			_FightReturnSTATE = _STATE;
			_STATE = getRandomFromList(DRAGON_KEEP_WILD);
			enemy_lvl = (std::rand() % (dragon_keep_max_level - dragon_keep_min_level)) + dragon_keep_min_level;
			enemy_run_chance = 15;
		}
		if (temp.compare("0") != 0 && temp.compare("1") != 0)
		{
			camera_Pos.addX(2);
		}
	}
	if (SYDEKeyCode::get_key('W')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(20, 9)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);
		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;	
		if (random_variable == 7 && _STATE == "Dragon Keep Dungeon")
		{
			// SET ENEMY AND LEVEL
			_FightReturnSTATE = _STATE;
			_STATE = getRandomFromList(DRAGON_KEEP_WILD);
			enemy_lvl = (std::rand() % (dragon_keep_max_level - dragon_keep_min_level)) + dragon_keep_min_level;
			enemy_run_chance = 15;
		}
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("0") != 0 && temp.compare("1") != 0)
		{
			camera_Pos.addY(-1);
		}
	}
	if (SYDEKeyCode::get_key('A')._CompareState(KEY))
	{
		string temp = std::to_string(window.getTextColourAtPoint(Vector2(18, 10)));
		//window.setTextAtPoint(Vector2(0, 1), temp, BLACK_WHITE_BG);

		// CASES FOR WILDFIGHT
		// ADD RANDOM CHANCE
		//char tempChar = _LevelAsset.getCharAtPoint(camera_Pos);
		int random_variable = std::rand() % 33 + 1;
		if (random_variable == 30 && _STATE == "Dragon Keep Dungeon")
		{
			// SET ENEMY AND LEVEL
			_FightReturnSTATE = _STATE;
			_STATE = getRandomFromList(DRAGON_KEEP_WILD);
			enemy_lvl = (std::rand() % (dragon_keep_max_level - dragon_keep_min_level)) + dragon_keep_min_level;
			enemy_run_chance = 15;
		}
		//CASES FOR MOVEMENT NOT ALLOWED
		if (temp.compare("0") != 0 && temp.compare("1") != 0)
		{
			camera_Pos.addX(-2);
		}
	}
	return window;
}
ConsoleWindow SYDEMapGame::Text_Adventure_Dungeon(ConsoleWindow window, int windowWidth, int windowHeight)
{
	window = m_bg.draw_asset(window, Vector2(0));
	if (_CurrentAdvRoom_.compare(_AdvRoom_) != 0)
	{
		MOTSDefaults::DebugLogs.push_back("TextAdv" + _CurrentAdvRoom_ + "->" + _AdvRoom_);
		_CurrentAdvRoom_ = _AdvRoom_;
		if (_AdvRoom_ == "Start_Room")
		{
			_TextWindow.AddFString("You wake up in a cold and damp prison");
			_TextWindow.AddFString("You hear a menacing laugh");
			_TextWindow.AddFString("???: HAHAHA FOOL, WELCOME TO MY DUNGEON");
			_TextWindow.AddFString("???: ");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextAdvOptions[0].setText("Open Cell Door");
			_TextAdvOptions[1].setText("Search For Rock");
			_TextAdvOptions[2].setText("Wait For Death");

			_TextAdvOptions[0].m_Label = "OpenDoor_Cell";
			_TextAdvOptions[1].m_Label = "Rock_Search";
			_TextAdvOptions[2].m_Label = "WaitDie";
		}
		
		else if (_AdvRoom_ == "Guard_Room")
		{
			_TextWindow.AddFString("You enter the room where the guard");
			_TextWindow.AddFString("should be");
			_TextWindow.AddFString("It seems it hasn't been implemented");
			_TextWindow.AddFString("yet");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextAdvOptions[0].setText("Exit Prison");
			_TextAdvOptions[1].setText("Go West");
			_TextAdvOptions[2].setText("Go East");

			_TextAdvOptions[0].m_Label = "Prison_Exit";
			_TextAdvOptions[1].m_Label = "Break_Room";
			_TextAdvOptions[2].m_Label = "Cell_Block";
		}
		
		else if (_AdvRoom_ == "Money_Room")
		{
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextAdvOptions[0].setText("");
			_TextAdvOptions[1].setText("");
			_TextAdvOptions[2].setText("");

			_TextAdvOptions[0].m_Label = "";
			_TextAdvOptions[1].m_Label = "";
			_TextAdvOptions[2].m_Label = "";
		}
	}
	if (SYDEKeyCode::get_key(VK_TAB)._CompareState(KEYDOWN))
	{
		_TextAdvOptions.nextSelect();
	}
	if ((SYDEKeyCode::get_key(VK_SPACE)._CompareState(KEYDOWN)))
	{
		if (_TextAdvOptions.getSelected().m_Label == "OpenDoor_Cell")
		{
			if (_TXT_VARS._ROCK_FOUND)
			{
				_TextWindow.AddFString("You force the door open with the rock");
				_TextWindow.AddFString("You don't know how it worked");
				_TextWindow.AddFString("But you also don't really care");
				_TextWindow.AddFString("");
				_TextWindow.AddFString("The rock crumbles afterwards");
				_TextWindow.AddFString("You say goodbye to your only friend");
				_TextWindow.AddFString("and move onwards");
				_TextWindow.AddFString("");

				_TextAdvOptions[0].setText("Yell 'HA' & Move On");
				_TextAdvOptions[1].setText("Yell 'Get F**Ked' & Move On");
				_TextAdvOptions[2].setText("Say nothing and walk on");

				_TextAdvOptions[0].m_Label = "Move_To_GuardRoom";
				_TextAdvOptions[1].m_Label = "Move_To_GuardRoom";
				_TextAdvOptions[2].m_Label = "Move_To_GuardRoom";
				_TXT_VARS._ROCK_FOUND = false;
			}
			else {
				_TextWindow.AddFString("You try to open the door to the cell");
				_TextWindow.AddFString("Unsuprisingly it doesn't open");
				_TextWindow.AddFString("");
				_TextWindow.AddFString("Like really what did you expect");
				_TextWindow.AddFString("Come on who leaves a door unlocked?");
				_TextWindow.AddFString("");
				_TextWindow.AddFString("");
				_TextWindow.AddFString("");
			}
		}

		else if (_TextAdvOptions.getSelected().m_Label == "Move_To_GuardRoom")
		{
			_AdvRoom_ = "Guard_Room";
		}

		else if (_TextAdvOptions.getSelected().m_Label == "Rock_Throw_Out")
		{
			_TextWindow.AddFString("You throw the rock outside through a");
			_TextWindow.AddFString("small window in the wall");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("Now you don't have a rock anymore");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextAdvOptions[1].setText("Search For Rock");

			_TextAdvOptions[1].m_Label = "Rock_Search";
			_TXT_VARS._ROCK_FOUND = false;
		}
		else if (_TextAdvOptions.getSelected().m_Label == "Rock_Search")
		{
			_TextWindow.AddFString("You find a large rock in the corner");
			_TextWindow.AddFString("You don't know why it was left there");
			_TextWindow.AddFString("but you simply do not care");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextAdvOptions[1].setText("Throw Rock Outside");

			_TextAdvOptions[1].m_Label = "Rock_Throw_Out";
			_TXT_VARS._ROCK_FOUND = true;
		}
		else if (_TextAdvOptions.getSelected().m_Label == "WaitDie")
		{
			_TextWindow.AddFString("You decide to wait for the embrace of death");
			_TextWindow.AddFString("???: Ummm, i haven't programmed starving");
			_TextWindow.AddFString("???: That means you ain't gonna die bud");
			_TextWindow.AddFString("???: May as well try to do something");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
		}
		//GUARD ROOM STUFF
		else if (_TextAdvOptions.getSelected().m_Label == "Prison_Exit")
		{
			//EXIT FOR NOW
			_STATE = "The Retroist";
			camera_Pos = Vector2(1860, 426);
		}
		else if (_TextAdvOptions.getSelected().m_Label == "Break_Room")
		{
			_TextWindow.AddFString("This Feature Hasn't Been Added Into The");
			_TextWindow.AddFString("Game As Of Yet. Please Exit The Prison");
			_TextWindow.AddFString("As Soon As You Can");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
		}
		else if (_TextAdvOptions.getSelected().m_Label == "Cell_Block")
		{
			_TextWindow.AddFString("This Feature Hasn't Been Added Into The");
			_TextWindow.AddFString("Game As Of Yet. Please Exit The Prison");
			_TextWindow.AddFString("As Soon As You Can");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
			_TextWindow.AddFString("");
		}
		else if (_TextAdvOptions.getSelected().m_Label == "---")
		{
		}
	}
	for (int i = 0; i < 8; i++)
	{
		window.setTextAtPoint(Vector2(0, i + 1), _TextWindow.getFString(i), BRIGHTWHITE);
	}
	window = _TextAdvOptions.draw_menu(window);
	return window;
}
#pragma endregion

#pragma region State Stuff

string SYDEMapGame::getWFA_STATE(Vector2 point)
{
	for (int i = 0; i < _list_fight_cases.size(); i++)
	{
		if (_list_fight_cases[i].getPoint() == point)
		{
			return _list_fight_cases[i].getWildFightArg();
		}
	}
	return "MainMap";
}

int SYDEMapGame::getWFA_LVL(Vector2 point)
{
	for (int i = 0; i < _list_fight_cases.size(); i++)
	{
		if (_list_fight_cases[i].getPoint() == point)
		{
			return _list_fight_cases[i].getLvl();
		}
	}
	return 0;
}

int SYDEMapGame::getWFA_RUN(Vector2 point)
{
	for (int i = 0; i < _list_fight_cases.size(); i++)
	{
		if (_list_fight_cases[i].getPoint() == point)
		{
			return _list_fight_cases[i].getRunChance();
		}
	}
	return 100;
}

string SYDEMapGame::getSTRUCT_STATE(Vector2 point)
{
	for (int i = 0; i < _list_structures.size(); i++)
	{
		if (_list_structures[i].getPoint() == point)
		{
			if (_list_structures[i].m_TAG != "") { return _list_structures[i].m_TAG; }
			return _list_structures[i].getStructArg();
		}
	}
	return "MainMap";
}

string SYDEMapGame::getSTRUCT_STATE(Vector2 point, bool display)
{
	for (int i = 0; i < _list_structures.size(); i++)
	{
		if (_list_structures[i].getPoint() == point)
		{
			if (_list_structures[i].m_TAG != "" && !display) { return _list_structures[i].m_TAG; }
			return _list_structures[i].getStructArg();
		}
	}
	return "MainMap";
}

DefaultHouse SYDEMapGame::getHouse_FromPos(Vector2 point)
{
	for (int i = 0; i < Houses.size(); i++)
	{
		if (Houses[i]._Struct.getPoint() == point)
		{
			return Houses[i];
		}
	}
	return DefaultHouse();
}

string SYDEMapGame::getSTRUCT_STATE(vector<Structure> _list, Vector2 point)
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getPoint() == point)
		{
			if (_list_structures[i].m_TAG != "") { return _list_structures[i].m_TAG; }
			return _list[i].getStructArg();
		}
	}
	return "MainMap";
}

string SYDEMapGame::getTown(Vector2 point)
{
	for (int i = 0; i < vecTowns.size(); i++)
	{
		if (vecTowns[i].inBounds(point))
		{
			return vecTowns[i].getAREA();
		}
	}
	return "???";
}

int SYDEMapGame::getColourFromLevel(Vector2 point)
{
	int wf_colour = _LevelAsset.getColourAtPoint(point);
	switch (wf_colour)
	{
	case 16:
		wf_colour = 16;
		break;
	case 32:
		wf_colour = 32;
		break;
	case 34:
		wf_colour = 32;
		break;
	case 224:
		wf_colour = 224;
		break;
	case 238:
		wf_colour = 224;
		break;
	default:
		wf_colour = 16;
		break;
	}

	return wf_colour;
}

string SYDEMapGame::getRandomFromList(vector<string> _list)
{
	int random_var = std::rand() %  _list.size();
	return _list[random_var];
}
#pragma endregion
