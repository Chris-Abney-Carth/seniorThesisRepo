#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Player
{
public:
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
};

