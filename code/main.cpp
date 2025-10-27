#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <cctype>
#include <conio.h>
#include "item.cpp"
using namespace std;
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
bool pWeaponEquiped = false;
bool pBodyEquiped = false;
bool pAccEquiped = false;
bool pMiscEquiped = false;
int pWeaponId = 0;
int pBodyId = 0;
int pAccId = 0;
int pMiscId = 0;
//Class for items.
vector<Item*> pItems;
vector<Item*> iLookUp;
void saveFile();
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
            cItem->hpHeal = hpHeal;
            cItem->mpHeal = mpHeal;
            iLookUp.push_back(cItem);
        }

        ss.clear();
        breakDownLine.clear();
        levelLineIndex += 1;
    }
}
bool is_number(const string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
void playerInventory(){
    bool done = false;
    string userInput = "";
    int choiceInt = 0;
    while (done == false){
        if (pItems.size() == 0){
            cout << "No Items" << endl;
        }
        else if (pItems.size() > 0){
            for (int i = 0; i < pItems.size(); i++){
                if (pItems[i]->type == 0){
                    if (pItems[i]->equiped == false){
                        cout << i <<" "<<pItems[i]->name << " [ ]" << endl;
                    }
                    else if (pItems[i]->equiped == true){
                        cout << i <<" "<< pItems[i]->name << " [E]" << endl;
                    }
                } else if (pItems[i]->type == 1){
                    cout << i <<" "<< pItems[i]->name << endl;
                }
            }
        }
        cout << "You can type the number to use an item or equip it.\nType Exit to exit inventory." << endl;
        cin >> userInput;
        if (is_number(userInput) == true){
            choiceInt = stoi(userInput);
            if (choiceInt > pItems.size()){
                cout << "Not a valid item" << endl;
            }
            else if (choiceInt <= pItems.size() && choiceInt >= 0){
                if (pItems[choiceInt]->type == 0){
                    if (pItems[choiceInt]->equiped == false){
                        if (pItems[choiceInt]->equipType == 0){
                            if (pWeaponEquiped == false){
                                pWeaponEquiped = true;
                            }
                            pWeaponId = pItems[choiceInt]->itemId;
                        }
                        if (pItems[choiceInt]->equipType == 1){
                            if (pBodyEquiped == false){
                                pBodyEquiped = true;
                            }
                            pBodyId = pItems[choiceInt]->itemId;
                        }
                        if (pItems[choiceInt]->equipType == 2){
                            if (pAccEquiped == false){
                                pAccEquiped = true;
                            }
                            pAccId = pItems[choiceInt]->itemId;
                        }
                        if (pItems[choiceInt]->equipType == 3){
                            if (pMiscEquiped == false){
                                pMiscEquiped = true;
                            }
                            pMiscId = pItems[choiceInt]->itemId;
                        }
                        pItems[choiceInt]->equiped = true;
                    } else {
                        if (pItems[choiceInt]->equipType == 0){
                            if (pWeaponEquiped == true){
                                pWeaponEquiped = false;
                            }
                            pWeaponId = 0;
                        }
                        if (pItems[choiceInt]->equipType == 1){
                            if (pBodyEquiped == true){
                                pBodyEquiped = false;
                            }
                            pBodyId = 0;
                        }
                        if (pItems[choiceInt]->equipType == 2){
                            if (pAccEquiped == true){
                                pAccEquiped = false;
                            }
                            pAccId = 0;
                        }
                        if (pItems[choiceInt]->equipType == 3){
                            if (pMiscEquiped == true){
                                pMiscEquiped = false;
                            }
                            pMiscId = 0;
                        }
                        pItems[choiceInt]->equiped = false;
                    }
                } else if (pItems[choiceInt]->type == 1){
                    pHP += pItems[choiceInt]->hpHeal;
                    if (pHP > maxHP){
                        pHP = maxHP;
                        cout << "HP Maxed out" << endl;
                    }else{
                        cout << "Healed " << pItems[choiceInt]->hpHeal << " HP!" << endl;
                    }
                    pMP += pItems[choiceInt]->mpHeal;
                    if (pMP > maxMP){
                        pMP = maxMP;
                        cout << "MP Maxed out" << endl;
                    }else{
                        cout << "Recovered " << pItems[choiceInt]->mpHeal << " MP!" << endl;
                    }
                    pItems.erase(pItems.begin()+choiceInt);
                }
            }
        }
        if (userInput == "Exit"){
            done = true;
        }
    }
    
    
}
void waitForEnter() {
    cout << "Press Enter to continue..." << endl;
    getch(); // Wait for the Enter key

    
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
void playerStats(){
    bool done = false;
    string userInput = "";
    int choiceInt = 0;
    int showAtk = pAttack;
    int showDef = pDefense;
    int showSpeed = pSpeed;
    int showAgil = pAgility;
    int showGuts = pGuts;
    int showWits = pWits;
    if (pWeaponEquiped == true || pBodyEquiped == true || pAccEquiped == true || pMiscEquiped == true){
        if (pWeaponEquiped == true){
            for (int i = 0; i < iLookUp.size(); i++){
                if (iLookUp[i]->itemId == pWeaponId){
                    showAtk += iLookUp[i]->atkBoost;
                    showDef += iLookUp[i]->defBoost;
                    showSpeed += iLookUp[i]->speedBoost;
                    showAgil += iLookUp[i]->agilBoost;
                    showGuts += iLookUp[i]->gutsBoost;
                    showWits += iLookUp[i]->witsBoost;
                }
            }
        }
        if (pBodyEquiped == true){
            for (int i = 0; i < iLookUp.size(); i++){
                if (iLookUp[i]->itemId == pBodyId){
                    showAtk += iLookUp[i]->atkBoost;
                    showDef += iLookUp[i]->defBoost;
                    showSpeed += iLookUp[i]->speedBoost;
                    showAgil += iLookUp[i]->agilBoost;
                    showGuts += iLookUp[i]->gutsBoost;
                    showWits += iLookUp[i]->witsBoost;
                }
            }
        }
        if (pAccEquiped == true){
            for (int i = 0; i < iLookUp.size(); i++){
                if (iLookUp[i]->itemId == pAccId){
                    showAtk += iLookUp[i]->atkBoost;
                    showDef += iLookUp[i]->defBoost;
                    showSpeed += iLookUp[i]->speedBoost;
                    showAgil += iLookUp[i]->agilBoost;
                    showGuts += iLookUp[i]->gutsBoost;
                    showWits += iLookUp[i]->witsBoost;
                }
            }
        }
        if (pMiscEquiped == true){
            for (int i = 0; i < iLookUp.size(); i++){
                if (iLookUp[i]->itemId == pMiscId){
                    showAtk += iLookUp[i]->atkBoost;
                    showDef += iLookUp[i]->defBoost;
                    showSpeed += iLookUp[i]->speedBoost;
                    showAgil += iLookUp[i]->agilBoost;
                    showGuts += iLookUp[i]->gutsBoost;
                    showWits += iLookUp[i]->witsBoost;
                }
            }
        }
    }
    while (done != true){
        cout << pName << "'s stats!" << endl;
        cout << pHP << "/" << maxHP << "    " << pMP << "/" << maxMP << endl;
        cout << "Attack: " << showAtk << "   Defence: " << showDef << endl;
        cout << "Speed: " << showSpeed << "    Agility: " << showAgil << endl;
        cout << "Guts: " << showGuts << "    Wits: " << showWits << endl;
        cout << "Gold: " << pGold << "    Exp: " << pExp << endl;
        cout << "Type Exit to exit this screen" << endl;
        cin >> userInput;
        if (userInput == "Exit"){
            done = true;
        }
    }
}
int choiceLoop(int pStoryFlag){
    int choice = 0;
    string playInput = "";
    cout << "Where will " << pName << " go?" << endl;
    cout << "1 Field" << endl;
    cout << "2 Shop" << endl;
    cout << "3 Castle" << endl;
    cout << "4 End Game" << endl;
    cout << "Make Selection" << endl;
    cin >> playInput;
    if (is_number(playInput) == true){
        choice = stoi(playInput);
    }
    else{
        if (playInput == "inv"){
            playerInventory();
        }
        if (playInput == "stat"){
            playerStats();
        }
    }
    return choice;
}
void getItem(int wantItemId){
Item* pItem = new Item;
for (int i = 0; i < iLookUp.size(); i++){
    if (iLookUp[i]->itemId == wantItemId){
        pItem->itemId = wantItemId;
        pItem->type = iLookUp[i]->type;
        pItem->name = iLookUp[i]->name;
        pItem->price = iLookUp[i]->price;
        if (pItem->type == 0){
            pItem->equiped = iLookUp[i]->equiped;
            pItem->atkBoost = iLookUp[i]->atkBoost;
            pItem->defBoost = iLookUp[i]->defBoost;
            pItem->speedBoost = iLookUp[i]->speedBoost;
            pItem->agilBoost = iLookUp[i]->agilBoost;
            pItem->gutsBoost = iLookUp[i]->gutsBoost;
            pItem->witsBoost = iLookUp[i]->witsBoost;
            pItem->equipType = iLookUp[i]->equipType;
        }
        else if (pItem->type == 1){
            pItem->hpHeal = iLookUp[i]->hpHeal;
            pItem->mpHeal = iLookUp[i]->mpHeal;
        }
        pItems.push_back(pItem);
    }
}
}
void startChoices(){
    bool finishedChoosing = false;
    string pInput = "";
    while (finishedChoosing == false){
        int choice = choiceLoop(pStoryFlag);
        switch(choice){
            case 1:
                if(pStoryFlag < 2){
                  cout << "I don't have my Quest yet!" << endl;
                  waitForEnter();
                  break;
                }else {
                    cout << "Going to fight monsters in the Field." << endl;
                    waitForEnter();
                    break;
                }
            case 2:
                cout << "Welcome to the shop!" << endl;
                if(pStoryFlag < 2){
                    cout << "Arn't you that hero? Go visit the castle!" << endl;
                    waitForEnter();
                    break;
                }else {
                    cout << "SHOP NOT IMPLEMENTED YET." << endl;
                    waitForEnter();
                    break;
                }
            case 3:
                if (pStoryFlag == 1){
                    cout << "Welcome " << pName << ". This is the castle." << endl;
                    cout << "Here, you can save your game. You are to adventure out in the field." << endl;
                    cout << "Take this basic sword. Along with 5 gold." << endl;
                    pGold += 5;
                    pStoryFlag = 2;
                    getItem(001);
                    waitForEnter();
                    break;
                }
                else {
                    cout << "Save Game? Type Y for yes. Anything else to exit."<< endl;
                    cin >> pInput;
                    if (pInput == "Y"){
                        cout << "\nSaving Game..." << endl;
                        saveFile();
                    }
                    break;
                }
            case 4:
                finishedChoosing = true;
                break;
        }
    }
    

}
void saveFile() {
    //Saving file setup.
    string filename = "playerSave.txt";
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
	    std::cerr << "Error opening file for reading." << std::endl;
	    //return;
    }
    string line = "";
    vector<std::string> lines;
    while (getline(inputFile, line)) {
        lines.push_back(line);
    }
    inputFile.close();
    /**
    pName Test
    pLevel 1
    pHP 10
    maxHP 10
    pMP 0
    maxMp 0
    pAttack 10
    pDefence 10
    pSpeed 5
    pAgility 5
    pGuts 5
    pWits 5
    pExp 0
    pGold 0
    pStoryFlag 0
    pSaveSpot 0
    pInven 101
     */
    string tempPlayerItems = "";
    lines[0] = "pName " + pName;
    lines[1] = "pLevel " + to_string(pLevel);

    lines[2] = "pHP " + to_string(pHP);
    lines[3] = "maxHP " + to_string(maxHP);

    lines[4] = "pMP " + to_string(pMP);
    lines[5] = "maxMP " + to_string(maxMP);

    lines[6] = "pAttack " + to_string(pAttack);
    lines[7] = "pDefence " + to_string(pDefense);

    lines[8] = "pSpeed " + to_string(pSpeed);
    lines[9] = "pAgility " + to_string(pAgility);

    lines[10] = "pGuts " + to_string(pGuts);
    lines[11] = "pWits " + to_string(pWits);

    lines[12] = "pExp " + to_string(pExp);
    lines[13] = "pGold " + to_string(pGold);

    lines[14] = "pStoryFlag " + to_string(pStoryFlag);
    lines[15] = "pSaveSpot " + to_string(pSaveSpot);
    if (pItems.empty() == false){
        for (int i = 0; i < pItems.size(); i++){
            tempPlayerItems = tempPlayerItems + to_string(pItems[i]->itemId);
            if (i != pItems.size()){
                tempPlayerItems = tempPlayerItems + " ";
            }
        }
    }
    lines[16] = "pInven " + tempPlayerItems;

    fstream saveFile(filename, ios::out);
    if (saveFile.is_open()) {
	    for (const std::string& updatedLine : lines) {
		    saveFile << updatedLine << std::endl;
	    }
    }
    else {
	    cout << "Error Opening File! No changes will be saved." << endl;
    }
    saveFile.close();
    

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
            pHP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "maxHP"){
            maxHP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pMP") {
            pMP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "maxMP"){
            maxMP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAttack") {
            pAttack = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pDefense") {
            pDefense = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSpeed") {
            pSpeed = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAgility") {
            pAgility = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGuts") {
            pGuts = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pWits") {
            pWits = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pExp") {
            pExp = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGold") {
            pGold = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pStoryFlag") {
            pStoryFlag = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSaveSpot") {
            pSaveSpot = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pInven"){
            if (breakDownLine.size() > 1){
                for (int i = 1; i < breakDownLine.size(); i++){
                    int tempId = stoi(breakDownLine[i]);
                    getItem(tempId);
                }
            }
            else{
                cout << "Player Inventory Error" << endl;
            }
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