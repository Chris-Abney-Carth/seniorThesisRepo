#include "Player.h"
#include <random>
#include <iostream>

using namespace std;

Player::Player() {
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
}
Player::Player(string name, int level, int HP, int mHP, int MP, int mMP, int atk, int def, int spe, int agi, int gut, int wit, int exp, int gold, int storyFlag, int saveSpot, int weaponID, int bodyID, int accID, int miscID) {
    pName = name;
    pLevel = level;
    pHP = HP;
    maxHP = mHP;
    pMP = MP;
    maxMP = mMP;
    pAttack = atk;
    pDefense = def;
    pSpeed = spe;
    pAgility = agi;
    pGuts = gut;
    pWits = wit;
    pExp = exp;
    pGold = gold;
    pStoryFlag = storyFlag;
    pSaveSpot = saveSpot;
    playerSpeedEffect = false;
    pWeaponId = weaponID;
    pBodyId = bodyID;
    pAccId = accID;
    pMiscId = miscID;
    //This is determining if something is equiped. 0 in ID means nothing is there.
    if (pWeaponId == 0) {
        pWeaponEquiped = false;
    }
    else {
        pWeaponEquiped = true;
    }
    if (pBodyId == 0) {
        pBodyEquiped = false;
    }
    else {
        pBodyEquiped = true;
    }
    if (pAccId == 0) {
        pAccEquiped = false;
    }
    else {
        pAccEquiped = true;
    }
    if (pMiscId == 0) {
        pMiscEquiped = false;
    }
    else {
        pMiscEquiped = true;
    }
    


}
int Player::getRandom(int rMin, int rMax) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(rMin, rMax);
	int randomValue = distrib(gen);
	return randomValue;
}
int Player::statBoost(int gRate, int level, int stat, int rand) {
    int statGain = ((gRate * level) - ((stat - 2) * 10)) * rand / 50;
    return statGain;
}
void Player::levelUP() {
    //stat growth rate
    //atk = 10
    //def = 6
    //speed = 5
    //agil = 5
    //gut = 4
    //wit = 3
    cout << "LEVEL UP!" << endl;
    int hpToAdd = pGuts * 15;
    maxHP += hpToAdd;
    pHP += hpToAdd;
    cout << "HP went up by " << hpToAdd << endl;
    int mpToAdd = pWits * 10;
    maxMP += mpToAdd;
    pMP = mpToAdd;
    cout << "MP went up by " << mpToAdd << endl;
    int min = 0;
    int max = 0;
    if ((pLevel + 1) % 4 == 0) {
        min = 7;
        max = 10;
    }
    else {
        min = 3;
        max = 10;
    }
    int atkRand = getRandom(min, max);
    int attackBoost = statBoost(10, pLevel, pAttack, atkRand);
    pAttack += attackBoost;
    cout << "Attack went up by " << attackBoost << endl;

    int defRand = getRandom(min, max);
    int defenseBoost = statBoost(6, pLevel, pDefense, defRand);
    pDefense += defenseBoost;
    cout << "Defense went up by " << defenseBoost << endl;

    int speRand = getRandom(min, max);
    int speedBoost = statBoost(6, pLevel, pSpeed, speRand);
    pSpeed += speedBoost;
    cout << "Speed went up by " << speedBoost << endl;

    int agiRand = getRandom(min, max);
    int agilityBoost = statBoost(6, pLevel, pAgility, agiRand);
    pAgility += agilityBoost;
    cout << "Agility went up by " << agilityBoost << endl;

    int gutRand = getRandom(min, max);
    if ((pLevel + 1) <= 10) {
        gutRand = 5;
    }
    int gutBoost = statBoost(6, pLevel, pGuts, gutRand);
    pGuts += gutBoost;
    cout << "Guts went up by " << gutBoost << endl;

    int witRand = getRandom(min, max);
    if ((pLevel + 1) <= 10) {
        witRand = 5;
    }
    int witBoost = statBoost(6, pLevel, pWits, gutRand);
    pWits += witBoost;
    cout << "Wits went up by " << witBoost << endl;

    pLevel += 1;
    pExp = 0;
}

bool Player::pHit(bool enSlowStat, bool pSlowStat, int enAgi, int pAgil) {

    int enSlow = 1;
    int pSlow = 1;
    if (enSlowStat == true) {
        enSlow = 2;
    }
    if (pSlowStat == true) {
        pSlow = 2;
    }
    int chance = (2 * (pAgil / pSlow) - (enAgi / enSlow));

    int hitValue = getRandom(1, 100);

    if (hitValue <= chance) {
        return true;
    }
    else {
        return false;
    }
}
bool Player::pCrit() {
    int baseCritChance = 25;
    int critChance = 0;
    if (baseCritChance >= pGuts) {
        critChance = baseCritChance;
    }
    else {
        critChance = pGuts;
    }
    int critRandom = getRandom(1, 500);
    if (critRandom <= critChance) {
        return true;
    }
    else {
        return false;
    }
}
