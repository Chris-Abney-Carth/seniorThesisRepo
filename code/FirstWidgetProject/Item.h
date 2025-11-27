#ifndef ITEM
#define ITEM
#include <iostream>
#include <string>
using namespace std;

struct Item
{
    int itemId = 0;
    string name = "";
    //Type indicates if it is a consumable or equipment 0 is equip, 1 is consume. int so if more items are needed
    int type = 0;
    int price = 0;
    bool equiped = false;
    int atkBoost = 0;
    int defBoost = 0;
    int speedBoost = 0;
    int agilBoost = 0;
    int gutsBoost = 0;
    int witsBoost = 0;
    //equipType is what slot item is equipable to. 0 = weapon, 1 = body, 2 = accessory, 3 = misc
    int equipType = 0;
    int hpHeal = 0;
    int mpHeal = 0;

};
#endif