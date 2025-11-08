#include "enemy.h"
#include <iostream>
#include <string>
#include <random>
#include <cmath>
using namespace std;

Enemy::Enemy() {
    enName = "ERR";
    enID = 0;
    enHP = 1;
    enHPM = 1;
    enMP = 0;
    enMPM = 0;
    enAtk = 1;
    enDef = 1;
    enSpe = 1;
    enAgi = 1;
    enGut = 1;
    enWit = 1;
    enEXP = 1;
    enGold = 1;
    //This will determine if enemy is slowed. Will half speed and half dodge chance.
    enSlowStat = false;
    useAtkB = true;
    useIce = false;
    useFire = false;


}

Enemy::Enemy(int id, string name, int hp, int mp, int atk, int def, int spe, int agi, int gut, int wit, int exp, int gold, bool atkB, bool ice, bool fire) {
    enName = name;
    enID = id;
    enHP = hp;
    enHPM = hp;
    enMP = mp;
    enMPM = mp;
    enAtk = atk;
    enDef = def;
    enSpe = spe;
    enAgi = agi;
    enGut = gut;
    enWit = wit;
    enEXP = exp;
    enGold = gold;
    //This will determine if enemy is slowed. Will half speed and half dodge chance.
    enSlowStat = false;
    useAtkB = atkB;
    useIce = ice;
    useFire = fire;

}
bool Enemy::hit(int pAgil, bool pSlowStat) {
    int enSlow = 1;
    int pSlow = 1;
    if (enSlowStat == true) {
        enSlow = 2;
    }
    if (pSlowStat == true) {
        pSlow = 2;
    }
    int chance = (2 * (pAgil / pSlow) - (enAgi / enSlow));
    int min = 1;
    int max = 100;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);

    int hitValue = distrib(gen);

    if (hitValue < chance) {
        return true;
    }
    else {
        return false;
    }

}
int Enemy::atk1(int pDef, int pAgil, bool pSlowStat) {
    //basic attack
    int min = 1;
    int max = 4;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    if (hit(pAgil, pSlowStat) == true) {
        int baseDamageDelt = (enAtk - pDef);
        if (baseDamageDelt <= 0) {
            cout << enName << "'s attack didn't get though defence!" << endl;
            return 0;
        }
        else {
            int randomValue = distrib(gen);
            int damageToAdd = 0;
            if (randomValue <= 2) {
                float lessDamage = baseDamageDelt * 0.25;
                damageToAdd = baseDamageDelt - round(lessDamage);
            }
            else {
                float moreDamage = baseDamageDelt * 0.25;
                damageToAdd = baseDamageDelt + round(moreDamage);
            }
            return damageToAdd;
        }


    }
    else {
        cout << enName << " Attack Missed!" << endl;
        return 0;
    }
}
void Enemy::atk2() {
    //for future use
}

void Enemy::magIce(int pDef, int pAgil, int pSpeed, int pWit, bool pSlowStat) {
    //basic magic attack. This needs to hit but used wit to determine if affect triggers, not use hit to determine. Effect will cause a temperarly lower speed.
    //This will have a 1/8 chacne to paralize, which will half speed and agility. Does no damage. Wit wil determine if one can break out of status affects.
    //Wit can increase odds if wit is 10* target's or greater, or decrease if wit is 1/10 the target's wit.
    int targetValue = 2;
    int min = 1;
    int max = 16;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(min, max);
    int hitValue = distrib(gen);
    if (enWit >= pWit * 10) {
        targetValue += 1;
    }
    if (enWit * 10 <= pWit) {
        targetValue -= 1;
    }
    if (hitValue <= targetValue) {
        pSlowStat = true;
    }
}
int Enemy::magFire(int pDef, int pAgil, int pSpeed, int pWit, bool pSlowStat) {
    //This will use user's damage, target's defence, to determine damage, with wit being a small multiplier. like damage = ((enAtk - pDef) + (enWit*0.25))
    //So magic is more consitant, but does cost mp. This will be managed in battle part.
    int totalDamage = 0;
    if (hit(pAgil, pSlowStat) == true) {
        int baseDamageDelt = (enAtk - pDef);
        if (baseDamageDelt <= 0) {
            cout << enName << "'s attack didn't get though defence!" << endl;
            return 0;
        }
        else {
            float bonusDamage = (enWit * 0.25);
            totalDamage = baseDamageDelt + round(bonusDamage);

            return totalDamage;
        }


    }
    else {
        cout << enName << " Attack Missed!" << endl;
        return 0;
    }
}
void Enemy::mag3() {
    //for future use
}
void Enemy::defeat() {

}