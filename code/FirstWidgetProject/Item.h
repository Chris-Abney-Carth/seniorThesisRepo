#ifndef ITEM
#define ITEM
#include <iostream>
#include <string>
using namespace std;

struct Item
{
    int itemId;
    string name;
    //Type indicates if it is a consumable or equipment 0 is equip, 1 is consume. int so if more items are needed
    int type;
    int price;
    bool equiped;
    int atkBoost;
    int defBoost;
    int speedBoost;
    int agilBoost;
    int gutsBoost;
    int witsBoost;
    //equipType is what slot item is equipable to. 0 = weapon, 1 = body, 2 = accessory, 3 = misc
    int equipType;
    int hpHeal;
    int mpHeal;

};
#endif