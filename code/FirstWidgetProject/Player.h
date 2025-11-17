#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include "Item.h"
using namespace std;


class Player
{
public:
	Player();
	Player(string name, int level, int HP, int mHP, int MP, int mMP, int atk, int def, int spe, int agi, int gut, int wit, int exp, int gold, int storyFlag, int saveSpot, int weaponID, int bodyID, int accID, int miscID);
	string pName = "";
	int pLevel = 1;
	int pHP = 10;
	int maxHP = 10;
	int pMP = 0;
	int maxMP = 0;
	int pAttack = 10;
	int pDefense = 10;
	int pSpeed = 5;
	int pAgility = 5;
	int pGuts = 5;
	int pWits = 5;
	int pExp = 0;
	int pGold = 0;
	int pStoryFlag = 0;
	int pSaveSpot = 0;
	bool playerSpeedEffect = false;
	bool pWeaponEquiped = false;
	bool pBodyEquiped = false;
	bool pAccEquiped = false;
	bool pMiscEquiped = false;
	int pWeaponId = 0;
	int pBodyId = 0;
	int pAccId = 0;
	int pMiscId = 0;
private:
	int getRandom(int rMin, int rMax);
	int statBoost(int gRate, int level, int stat, int rand);
	void levelUP();
	bool pHit(bool enSlowStat, bool pSlowStat, int enAgi, int pAgil);
	bool pCrit();
};

