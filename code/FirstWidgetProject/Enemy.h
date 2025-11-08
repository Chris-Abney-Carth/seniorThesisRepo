#pragma once
#ifndef ENEMY
#define ENEMY
#include <iostream>
#include <string>
using namespace std;

class Enemy
{
public:
    Enemy();
    Enemy(int id, string name, int hp, int mp, int atk, int def, int spe, int agi, int gut, int wit, int exp, int gold, bool atkB, bool ice, bool fire);
    string enName;
    int enID;
    int enHP;
    int enHPM;
    int enMP;
    int enMPM;
    int enAtk;
    int enDef;
    int enSpe;
    int enAgi;
    int enGut;
    int enWit;
    int enEXP;
    int enGold;
    bool enSlowStat;
    bool useAtkB;
    bool useIce;
    bool useFire;

private:
    bool hit(int pAgil, bool pSlowStat);
    int atk1(int pDef, int pAgilt, bool pSlowStat);
    void atk2();
    void magIce(int pDef, int pAgil, int pSpeed, int pWit, bool pSlowStat);
    int magFire(int pDef, int pAgil, int pSpeed, int pWit, bool pSlowStat);
    void mag3();
    void defeat();
};
#endif