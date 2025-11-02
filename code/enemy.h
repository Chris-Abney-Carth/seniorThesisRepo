#pragma once
#include <iostream>
#include <string>
using namespace std;

class Enemy
{
public:
    string name;
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

private:
    void atk1();
    void atk2();
    void hit(int pAgil);
    void mag1();
    void mag2();
    void mag3();
    void defeat();
};