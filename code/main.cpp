#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include "item.cpp"
using namespace std;
string pName = "";
int pLevel = 1;
int pHP = 10;
int pMP = 0;
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
//Class for items.
vector<Item*> pItems;
vector<Item*> iLookUp;
void setUpLookup(){
    //setup for lookUp Table
    int itemID = 000;
    string itemName = "";
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
    int levelLineIndex = 0;
    string filePath = "";
    string word = "";
    string levelLine = "";
    string filename = "itemLookUp.txt";
    vector<string> breakDownLine;
    ifstream readSavefile(filename);
    while (getline(readSavefile, levelLine)) {
        stringstream ss(levelLine);
        while (!ss.eof()) {
            ss >> word;
            breakDownLine.push_back(word);
        }
        if (breakDownLine[0] == "0") {
            type = stoi(breakDownLine[0]);
            itemID = stoi(breakDownLine[1]);
            itemName = breakDownLine[2];
            price = stoi(breakDownLine[3]);
            equiped = stoi(breakDownLine[4]);
            atkBoost = stoi(breakDownLine[5]);
            defBoost = stoi(breakDownLine[6]);
            speedBoost = stoi(breakDownLine[7]);
            agilBoost = stoi(breakDownLine[8]);
            gutsBoost = stoi(breakDownLine[9]);
            witsBoost = stoi(breakDownLine[10]);
            equipType = stoi(breakDownLine[11]);

            Item* eItem = new Item();
            eItem->itemId = itemID;
            eItem->type = type;
            eItem->name = itemName;
            eItem->price = price;
            eItem->equiped = equiped;
            eItem->atkBoost = atkBoost;
            eItem->defBoost = defBoost;
            eItem->speedBoost = speedBoost;
            eItem->agilBoost = agilBoost;
            eItem->gutsBoost = gutsBoost;
            eItem->witsBoost = witsBoost;
            eItem->equipType = equipType;
            iLookUp.push_back(eItem);

        }
        if (breakDownLine[0] == "1") {
            type = stoi(breakDownLine[0]);
            itemID = stoi(breakDownLine[1]);
            itemName = breakDownLine[2];
            price = stoi(breakDownLine[3]);
            hpHeal = stoi(breakDownLine[4]);
            mpHeal = stoi(breakDownLine[5]);
            Item* cItem = new Item();
            cItem->itemId = itemID;
            cItem->type = type;
            cItem->name = itemName;
            cItem->price = price;
            cItem->equiped = hpHeal;
            cItem->atkBoost = mpHeal;
            iLookUp.push_back(cItem);
        }

        ss.clear();
        breakDownLine.clear();
        levelLineIndex += 1;
    }
}
void eLookTable(int itemID){
    
}
void waitForEnter() {
    cout << "Press Enter to continue..." << endl;
    cin.get(); // Wait for the Enter key
}
bool isValidName(string& playName) {
    //reject for certan Characts
    for (char c : playName) {
        if (isdigit(c) || c == '!' || c == '@' || c == '#') {
            return false; // Invalid character found
        }
    }
    if (playName.empty() || playName.length() < 1 || playName.length() > 20) {
        return false;
    }
    return true;
}
string namePlayer() {
    string playName = "";
    cout << "You Begin your Adventure. Please Name yourself." << endl;
    bool nameAccepted = false;

    while (!nameAccepted) {
        cout << "Enter your player name" << endl;
        cin >> playName;
        cout << endl;
        if (isValidName(playName)) {
            return playName;
        }
        else {
            cout << "Invalid name. Please try again. (Names cannot contain numbers or symbols like !, @, #, and must be at least 1 to 20 characters long)." << endl;
        }
    }
    return "ERR";
}
int choiceLoop(int pStoryFlag){
    int choice = 0;
    cout << "Where will " << pName << " go?" << endl;
    cout << "1 Field" << endl;
    cout << "2 Shop" << endl;
    cout << "3 Castle" << endl;
    cout << "4 End Game" << endl;
    cout << "Make Selection" << endl;
    cin >> choice;
    return choice;
}
void startChoices(){
    bool finishedChoosing = false;
    while (finishedChoosing == false){
        int choice = choiceLoop(pStoryFlag);
        switch(choice){
            case 1:
                if(pStoryFlag < 2){
                  cout << "I don't have my Quest yet!" << endl;
                }else {
                    cout << "Going to fight monsters in the Field." << endl;
                }
                break;
            case 2:
                cout << "Welcome to the shop!" << endl;
                if(pStoryFlag < 2){
                    cout << "Arn't you that hero? Go visit the castle!" << endl;
                }else {
                    cout << "SHOP NOT IMPLEMENTED YET." << endl;
                }
                break;
            case 3:
                if (pStoryFlag == 1){
                    cout << "Welcome " << pName << ". This is the castle." << endl;
                    cout << "Here, you can save your game. You are to adventure out in the field." << endl;
                    cout << "Take this basic sword. Along with 5 gold." << endl;
                }
                else {
                    cout << "This worked!";
                }
                break;
            case 4:
                finishedChoosing = true;
                break;
        }
    }
    

}
void readFile() {
    //setup for file
    /**
    string pName = "";
    int plevel = 1;
    int pHP = 10;
    int pMP = 0;
    int pAttack = 10;
    int pDefense = 10;
    int pSpeed = 5;
    int pAgility = 5;
    int pGuts = 5;
    int pWits = 5;
    int pStoryFlag = 0;
    int pSaveSpot = 0;
    **/
    int levelLineIndex = 0;
    string filePath = "";
    string word = "";
    string levelLine = "";
    string filename = "playerSave.txt";
    vector<string> breakDownLine;
    ifstream readSavefile(filename);
    while (getline(readSavefile, levelLine)) {
        stringstream ss(levelLine);
        while (!ss.eof()) {
            ss >> word;
            breakDownLine.push_back(word);
        }
        if (breakDownLine[0] == "pName") {
            pName = breakDownLine[1];
        }
        if (breakDownLine[0] == "pLevel") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pHP") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pMP") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAttack") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pDefense") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSpeed") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAgility") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGuts") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pWits") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pExp") {
            pExp = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGold") {
            pGold = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pStoryFlag") {
            pLevel = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSaveSpot") {
            pLevel = stoi(breakDownLine[1]);
        }
        ss.clear();
        breakDownLine.clear();
        levelLineIndex += 1;
    }
    readSavefile.close();
    if (pStoryFlag == 0) {
        //cout << "DEBUG PLAYER NAME IS: " <<pName << endl;
        pName = namePlayer();
        pStoryFlag = 1;
    }
    cout << "Welcome " << pName << endl;
}
int main() {
    cout << "TBRPG" << endl;
    cout << "By Christopher J Abney" << endl;
    waitForEnter();
    cout << "Building GAME!" << endl;
    setUpLookup();
    readFile();
    cout << "After File" << endl;
    startChoices();
    return 0;
}