#include "MainFrame.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <cctype>
#include <conio.h>
#include <random>
#include "Item.h"
#include "Enemy.h"
#include "Player.h"
#include <wx/wx.h>

using namespace std;

enum {
	ID_BUTTON_A = 101,
	ID_BUTTON_B,
	ID_BUTTON_C
};
enum {
    //This will give panel IDs. Panels will have 1001 as begining
    ID_PANEL_A = 1001,
    ID_PANEL_B,
    ID_PANEL_C,
    ID_PANEL_D,
    ID_PANEL_E,
    ID_PANEL_F,
    ID_PANEL_G,
    ID_PANEL_H
};

enum {
    ID_LIST_A = 2001
};

enum {
    ID_INVENTORY_BUTTON_A = 2101,
    ID_INVENTORY_BUTTON_B,
    ID_INVENTORY_BUTTON_C
};

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {

	savePaths.push_back("playerSave1.txt");
	savePaths.push_back("playerSave2.txt");
	savePaths.push_back("playerSave3.txt");

    choiceOptions.Add("Open Menu");
    choiceOptions.Add("Go to Castle");
    choiceOptions.Add("Go to Shop");
    choiceOptions.Add("Go to Field");

    choiceMenuOverworld.Add("Inventory");
    choiceMenuOverworld.Add("Stats");
    choiceMenuOverworld.Add("Magic");
    choiceMenuOverworld.Add("Exit Menu");
    choiceMenuOverworld.Add("Quit Game");
    
    choiceCastle.Add("Open Menu");
    choiceCastle.Add("Save Game");
    choiceCastle.Add("Exit Castle");

    choiceMenuFight.Add("Attack");
    choiceMenuFight.Add("Magic");
    choiceMenuFight.Add("Inventory");
    choiceMenuFight.Add("Run");

    fightOverMenu.Add("Continue");
    fightOverMenu.Add("Go Back");

    battleLostMenu.Add("Continue?");
    battleLostMenu.Add("Quit");

	startPanel = new wxPanel(this, ID_PANEL_A);
	startPanel->SetBackgroundColour(*wxBLACK);

	savePanel = new wxPanel(this, ID_PANEL_B);
	savePanel->SetBackgroundColour(*wxBLUE);
	savePanel->Hide();

    namePanel = new wxPanel(this, ID_PANEL_C);
    namePanel->SetBackgroundColour(*wxBLUE);
    namePanel->Hide();

    choicePanel = new wxPanel(this, ID_PANEL_D);
    choicePanel->SetBackgroundColour(*wxBLACK);
    choicePanel->Hide();

    menuPanel = new wxPanel(this, ID_PANEL_E);
    menuPanel->SetBackgroundColour(*wxBLACK);
    menuPanel->Hide();
    
    inventoryPanel = new wxPanel(this, ID_PANEL_F);
    inventoryPanel->SetBackgroundColour(*wxBLACK);
    inventoryPanel->Hide();

    statPanel = new wxPanel(this, ID_PANEL_G);
    statPanel->SetBackgroundColour(*wxBLACK);
    statPanel->Hide();

    fightPanel = new wxPanel(this, ID_PANEL_H);
    fightPanel->SetBackgroundColour(*wxBLACK);
    fightPanel->Hide();

	wxStaticText* gameTitle = new wxStaticText(startPanel, wxID_ANY, "BITQUEST", wxPoint(300, 175), wxSize(200, 50), wxALIGN_CENTER_HORIZONTAL);
	gameTitle->SetForegroundColour(*wxGREEN);
	wxFont titleFont = gameTitle->GetFont();
	titleFont.SetPointSize(20);
	gameTitle->SetFont(titleFont);
	gameTitle->GetParent()->Layout();

	//This will be for the name Panel
    wxStaticText* namingText = new wxStaticText(namePanel, wxID_ANY, "Welcome to BITQUEST. Please name yourself.", wxPoint(300, 75), wxSize(200, 100), wxALIGN_CENTER_HORIZONTAL | wxST_NO_AUTORESIZE);
    namingText->SetForegroundColour(*wxWHITE);
    wxFont basicFont = namingText->GetFont();
    basicFont.SetPointSize(12);
    namingText->SetFont(basicFont);
    wxTextCtrl* nameMe = new wxTextCtrl(namePanel, wxID_ANY, "", wxPoint(300, 275), wxSize(200, 50), wxTE_PROCESS_ENTER);
    Bind(wxEVT_TEXT_ENTER, &MainFrame::namePlayer, this);
    namingText->GetParent()->Layout();

	switchButton = new wxButton(this, wxID_ANY, "Switch View");
	wxButton* startButton = new wxButton(startPanel, wxID_ANY, "START", wxPoint(300, 275), wxSize(200, 50));

	switchButton->Bind(wxEVT_BUTTON, &MainFrame::switchViewButton, this);
	startButton->Bind(wxEVT_BUTTON, &MainFrame::startButtonClicked, this);

	wxButton* saveOneButton = new wxButton(savePanel, ID_BUTTON_A, "Save 1", wxPoint(300, 175), wxSize(200, 50));
	wxButton* saveTwoButton = new wxButton(savePanel, ID_BUTTON_B, "Save 2", wxPoint(300, 275), wxSize(200, 50));
	wxButton* saveThreeButton = new wxButton(savePanel, ID_BUTTON_C, "Save 3", wxPoint(300, 375), wxSize(200, 50));
	
	Bind(wxEVT_BUTTON, &MainFrame::saveFileChosen, this, ID_BUTTON_A, ID_BUTTON_C);
    //For Scenes
    //1 = town square;
    //2 = castle;
    //3 = shop;
    infoBox = new wxListBox(choicePanel, wxID_ANY, wxPoint(50, 375), wxSize(700,125), choiceOptions, wxLB_SINGLE | wxWANTS_CHARS);
    infoBox->SetForegroundColour(*wxWHITE);
    infoBox->SetBackgroundColour(*wxBLACK);
    wxFont infoFont = infoBox->GetFont();
    infoFont.SetPointSize(16);
    infoBox->SetFont(infoFont);
    infoBox->GetParent()->Layout();
    infoBox->Bind(wxEVT_KEY_DOWN, &MainFrame::choiceBoxSelect, this);
    sceneText = new wxTextCtrl(choicePanel, wxID_ANY, "Test", wxPoint(50, 50), wxSize(700, 225), wxTE_READONLY);
    sceneText->SetBackgroundColour(*wxBLACK);
    sceneText->SetForegroundColour(*wxWHITE);
    sceneText->SetFont(infoFont);
    sceneText->GetParent()->Layout();
    sceneCurrent = 1;
    //For menu
    menuBox = new wxListBox(menuPanel, wxID_ANY, wxPoint(50, 175), wxSize(700, 225), choiceMenuOverworld, wxLB_SINGLE | wxWANTS_CHARS);
    menuBox->SetForegroundColour(*wxWHITE);
    menuBox->SetBackgroundColour(*wxBLACK);
    wxFont menuFont = menuBox->GetFont();
    menuFont.SetPointSize(16);
    menuBox->SetFont(menuFont);
    menuBox->GetParent()->Layout();
    menuBox->Bind(wxEVT_KEY_DOWN, &MainFrame::menuBoxSelect, this);
    //Inventory
    //Need to be able to secect item.
    inventoryList = new wxListCtrl(inventoryPanel, 2001, wxPoint(50, 75), wxSize(700, 225), wxLC_REPORT | wxLC_SINGLE_SEL);
    inventoryList->InsertColumn(0, "Name", wxLIST_FORMAT_LEFT, 150);
    inventoryList->InsertColumn(1, "Equiped", wxLIST_FORMAT_RIGHT, 60);
    inventoryList->InsertColumn(2, "Item ID", wxLIST_FORMAT_RIGHT, 80);
    inventoryList->Bind(wxEVT_LIST_ITEM_SELECTED, &MainFrame::itemSelect, this);
    describeText = new wxTextCtrl(inventoryPanel, wxID_ANY, "TEST", wxPoint(50, 300), wxSize(700, 50), wxTE_READONLY);
    describeText->SetBackgroundColour(*wxBLACK);
    describeText->SetForegroundColour(*wxWHITE);
    wxButton* exitInventory = new wxButton(inventoryPanel, ID_INVENTORY_BUTTON_A, "Exit", wxPoint(300, 475), wxSize(200, 50));
    wxButton* infoButton = new wxButton(inventoryPanel, ID_INVENTORY_BUTTON_B, "Info", wxPoint(75, 475), wxSize(200, 50));
    wxButton* useButton = new wxButton(inventoryPanel, ID_INVENTORY_BUTTON_C, "Use", wxPoint(525, 475), wxSize(200, 50));
    useButton->Bind(wxEVT_BUTTON, &MainFrame::useItem, this);
    exitInventory->Bind(wxEVT_BUTTON, &MainFrame::exitInventory, this);
    
    //Stats
    statGrid = new wxPropertyGrid(statPanel, wxID_ANY, wxPoint(325, 75), wxSize(150, 325), wxPG_DEFAULT_STYLE);
    

    wxButton* exitStats = new wxButton(statPanel, wxID_ANY, "Exit", wxPoint(300, 450), wxSize(200, 50));

    exitStats->Bind(wxEVT_BUTTON, &MainFrame::exitStats, this);
    //Fight This will be specific becuase I want to do things with it.
    fightBox = new wxListBox(fightPanel, wxID_ANY, wxPoint(50, 375), wxSize(700, 125), choiceMenuFight, wxLB_SINGLE | wxWANTS_CHARS);
    fightBox->SetForegroundColour(*wxWHITE);
    fightBox->SetBackgroundColour(*wxBLACK);
    wxFont battleFont = fightBox->GetFont();
    battleFont.SetPointSize(16);
    fightBox->SetFont(battleFont);
    fightBox->GetParent()->Layout();
    fightBox->Bind(wxEVT_KEY_DOWN, &MainFrame::fightChoiceSelect, this);
    fightText = new wxTextCtrl(fightPanel, wxID_ANY, "Test", wxPoint(50, 50), wxSize(700, 225), wxTE_READONLY | wxTE_MULTILINE | wxTE_WORDWRAP);
    fightText->SetBackgroundColour(*wxBLACK);
    fightText->SetForegroundColour(*wxWHITE);
    fightText->SetFont(battleFont);
    fightText->GetParent()->Layout();

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(startPanel, 1, wxEXPAND);
	mainSizer->Add(savePanel, 1, wxEXPAND); // Add both panels to the sizer
    mainSizer->Add(namePanel, 1, wxEXPAND);
    mainSizer->Add(choicePanel, 1, wxEXPAND);
    mainSizer->Add(menuPanel, 1, wxEXPAND);
    mainSizer->Add(inventoryPanel, 1, wxEXPAND);
    mainSizer->Add(statPanel, 1, wxEXPAND);
    mainSizer->Add(fightPanel,1, wxEXPAND);
	mainSizer->Add(switchButton, 0, wxALIGN_CENTER | wxALL, 5);
	SetSizerAndFit(mainSizer);
	CreateStatusBar();
}

void MainFrame::setUpLookUp() {
    //setup for lookUp Table
    int itemID = 000;
    wxString itemName = "";
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
    ifstream readItem(filename);
    while (getline(readItem, levelLine)) {
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
    readItem.close();
    iLookUpMade = true;
}
void MainFrame::setUpEnenmyLookup() {
    int enID = 0;
    string enName = "";
    int enHP = 0;
    int enMP = 0;
    int enAtk = 0;
    int enDef = 0;
    int enSpe = 0;
    int enAgi = 0;
    int enGut = 0;
    int enWit = 0;
    int enExp = 0;
    int enGold = 0;
    bool enAtkB = false;
    bool enIce = false;
    bool enFire = false;
    int levelLineIndex = 0;
    string filePath = "";
    string word = "";
    string levelLine = "";
    string filename = "enemyLookUp.txt";
    vector<string> breakDownLine;
    ifstream readEnemyFile(filename);
    while (getline(readEnemyFile, levelLine)) {
        stringstream ss(levelLine);
        while (!ss.eof()) {
            ss >> word;
            breakDownLine.push_back(word);
        }
        enID = stoi(breakDownLine[0]);
        enName = breakDownLine[1];
        enHP = stoi(breakDownLine[2]);
        enMP = stoi(breakDownLine[3]);
        enAtk = stoi(breakDownLine[4]);
        enDef = stoi(breakDownLine[5]);
        enSpe = stoi(breakDownLine[6]);
        enAgi = stoi(breakDownLine[7]);
        enGut = stoi(breakDownLine[8]);
        enWit = stoi(breakDownLine[9]);
        enExp = stoi(breakDownLine[10]);
        enGold = stoi(breakDownLine[11]);
        enAtkB = stoi(breakDownLine[12]);
        enIce = stoi(breakDownLine[13]);
        enFire = stoi(breakDownLine[14]);
        Enemy* newEnemy = new Enemy(enID, enName, enHP, enMP, enAtk, enDef, enSpe, enAgi, enGut, enWit, enExp, enGold, enAtkB, enIce, enFire);
        eLookUP.push_back(newEnemy);
        numOEn += 1;
        wxLogStatus("EnemyBuilt!");

        ss.clear();
        breakDownLine.clear();
        levelLineIndex += 1;
    }
    readEnemyFile.close();
    eLookUpMade = true;
}
void MainFrame::getItem(int wantItemId) {
    Item* pItem = new Item;
    for (int i = 0; i < iLookUp.size(); i++) {
        if (iLookUp[i]->itemId == wantItemId) {
            pItem->itemId = wantItemId;
            pItem->type = iLookUp[i]->type;
            pItem->name = iLookUp[i]->name;
            pItem->price = iLookUp[i]->price;
            if (pItem->type == 0) {
                pItem->equiped = iLookUp[i]->equiped;
                pItem->atkBoost = iLookUp[i]->atkBoost;
                pItem->defBoost = iLookUp[i]->defBoost;
                pItem->speedBoost = iLookUp[i]->speedBoost;
                pItem->agilBoost = iLookUp[i]->agilBoost;
                pItem->gutsBoost = iLookUp[i]->gutsBoost;
                pItem->witsBoost = iLookUp[i]->witsBoost;
                pItem->equipType = iLookUp[i]->equipType;
            }
            else if (pItem->type == 1) {
                pItem->hpHeal = iLookUp[i]->hpHeal;
                pItem->mpHeal = iLookUp[i]->mpHeal;
            }
            pItems.push_back(pItem);
        }
    }
}
bool MainFrame::isValidName(string& playName) {
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
void MainFrame::namePlayer(wxCommandEvent& evt) {
    wxString str = wxString::Format("%s", evt.GetString());
    wxString messageString = wxT("");
    string testingString = str.ToStdString();
    if (isValidName(testingString)) {
        playerChar.pName = testingString;
        messageString = wxT("Name accepted!");
        namePanel->Hide();
        choicePanel->Show();
        sceneText->SetLabelText("You are in the town square. Select where you want to go.");
        GetSizer()->Layout();
    }
    else {
        messageString = wxT("Err. Name not accepted. Name must be between 1 and 20 characters, and must not have #, ! or @");
    }
    wxLogStatus(messageString);
}
void MainFrame::savePlayerSave(string curFile) {
    //Saving file setup.
    ifstream inputFile(curFile);
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
    pWeaponId 0
    pBodyId 0
    pAccId 0
    pMiscId 0
     */
    string tempPlayerItems = "";
    lines[0] = "pName " + playerChar.pName;
    lines[1] = "pLevel " + to_string(playerChar.pLevel);

    lines[2] = "pHP " + to_string(playerChar.pHP);
    lines[3] = "maxHP " + to_string(playerChar.maxHP);

    lines[4] = "pMP " + to_string(playerChar.pMP);
    lines[5] = "maxMP " + to_string(playerChar.maxMP);

    lines[6] = "pAttack " + to_string(playerChar.pAttack);
    lines[7] = "pDefence " + to_string(playerChar.pDefense);

    lines[8] = "pSpeed " + to_string(playerChar.pSpeed);
    lines[9] = "pAgility " + to_string(playerChar.pAgility);

    lines[10] = "pGuts " + to_string(playerChar.pGuts);
    lines[11] = "pWits " + to_string(playerChar.pWits);

    lines[12] = "pExp " + to_string(playerChar.pExp);
    lines[13] = "pGold " + to_string(playerChar.pGold);

    lines[14] = "pStoryFlag " + to_string(playerChar.pStoryFlag);
    lines[15] = "pSaveSpot " + to_string(playerChar.pSaveSpot);
    if (pItems.empty() == false) {
        for (int i = 0; i < pItems.size(); i++) {
            tempPlayerItems = tempPlayerItems + to_string(pItems[i]->itemId);
            if (i != pItems.size() - 1) {
                tempPlayerItems = tempPlayerItems + " ";
            }
        }
    }
    lines[16] = "pInven " + tempPlayerItems;

    lines[17] = "pWeaponId " + to_string(playerChar.pWeaponId);
    lines[18] = "pBodyId " + to_string(playerChar.pBodyId);

    lines[19] = "pAccId " + to_string(playerChar.pAccId);
    lines[20] = "pMiscId " + to_string(playerChar.pMiscId);

    fstream saveFile(curFile, ios::out);
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
void MainFrame::loadPlayerSave(string saveFile) {
    //setup for file
    currSavePath = saveFile;
    string name = "";
    int level = 1;
    int HP = 10;
    int maxHP = 10;
    int MP = 0;
    int maxMP = 0;
    int attack = 10;
    int defense = 10;
    int speed = 5;
    int agility = 5;
    int guts = 5;
    int wits = 5;
    int exp = 0;
    int gold = 0;
    int storyFlag = 0;
    int saveSpot = 0;
    int weaponID = 0;
    int bodyID = 0;
    int accID = 0;
    int miscID = 0;
    
    int levelLineIndex = 0;
    string filePath = "";
    string word = "";
    string levelLine = "";
    vector<string> breakDownLine;
    ifstream readSavefile(saveFile);
    while (getline(readSavefile, levelLine)) {
        stringstream ss(levelLine);
        while (!ss.eof()) {
            ss >> word;
            breakDownLine.push_back(word);
        }
        if (breakDownLine[0] == "pName") {
            name = breakDownLine[1];
        }
        if (breakDownLine[0] == "pLevel") {
            level = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pHP") {
            HP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "maxHP") {
            maxHP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pMP") {
            MP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "maxMP") {
            maxMP = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAttack") {
            attack = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pDefense") {
            defense = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSpeed") {
            speed = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAgility") {
            agility = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGuts") {
            guts = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pWits") {
            wits = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pExp") {
            exp = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pGold") {
            gold = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pStoryFlag") {
            storyFlag = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pSaveSpot") {
            saveSpot = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pInven") {
            if (breakDownLine.size() > 1) {
                for (int i = 1; i < breakDownLine.size(); i++) {
                    int tempId = stoi(breakDownLine[i]);
                    getItem(tempId);
                }
            }
            else {
                cout << "Player Inventory Error" << endl;
            }
        }
        if (breakDownLine[0] == "pWeaponId") {
            weaponID = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pBodyId") {
            bodyID = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pAccId") {
            accID = stoi(breakDownLine[1]);
        }
        if (breakDownLine[0] == "pMiscId") {
            miscID = stoi(breakDownLine[1]);
        }
        ss.clear();
        breakDownLine.clear();
        levelLineIndex += 1;
    }
    playerChar = Player(name, level, HP, maxHP, MP, maxMP, attack, defense, speed, agility, guts, wits, exp, gold, storyFlag, saveSpot, weaponID, bodyID, accID, miscID);
    readSavefile.close();
    for (int i = 0; i < pItems.size(); i++) {
        if (pItems[i]->itemId == playerChar.pWeaponId|| pItems[i]->itemId == playerChar.pBodyId|| pItems[i]->itemId == playerChar.pAccId || pItems[i]->itemId == playerChar.pBodyId){
            pItems[i]->equiped = true;
        }
    }
    if (playerChar.pStoryFlag == 0) {
        //cout << "DEBUG PLAYER NAME IS: " <<pName << endl;
        if (savePanel->IsShown()) {
            savePanel->Hide();
            namePanel->Show();
            GetSizer()->Layout();
        }
        playerChar.pStoryFlag = 1;
    }
    else {
        if (savePanel->IsShown()) {
            savePanel->Hide();
            choicePanel->Show();
            sceneText->SetLabelText("You are in the town square. Select where you want to go.");
            GetSizer()->Layout();
        }
    }
    cout << "Welcome " << playerChar.pName << endl;
}
int MainFrame::getRandom(int rMin, int rMax) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(rMin, rMax);
	int randomValue = distrib(gen);
	return randomValue;
}
void MainFrame::getPlayerStatsSimple(Player player, int& simAtk, int& simDef, int& simSpe, int& simAgi, int& simGut, int& simWit) {
    //Stats that will need to be simple
    simAtk = player.pAttack;
    simDef = player.pDefense;
    simSpe = player.pSpeed;
    simAgi = player.pAgility;
    simGut = player.pGuts;
    simWit = player.pWits;
    if (player.pWeaponEquiped == true || player.pBodyEquiped == true || player.pAccEquiped == true || player.pMiscEquiped == true) {
        if (player.pWeaponEquiped == true) {
            for (int i = 0; i < iLookUp.size(); i++) {
                if (iLookUp[i]->itemId == player.pWeaponId) {
                    simAtk += iLookUp[i]->atkBoost;
                    simDef += iLookUp[i]->defBoost;
                    simSpe += iLookUp[i]->speedBoost;
                    simAgi += iLookUp[i]->agilBoost;
                    simGut += iLookUp[i]->gutsBoost;
                    simWit += iLookUp[i]->witsBoost;
                }
            }
        }
        if (player.pBodyEquiped == true) {
            for (int i = 0; i < iLookUp.size(); i++) {
                if (iLookUp[i]->itemId == player.pBodyId) {
                    simAtk += iLookUp[i]->atkBoost;
                    simDef += iLookUp[i]->defBoost;
                    simSpe += iLookUp[i]->speedBoost;
                    simAgi += iLookUp[i]->agilBoost;
                    simGut += iLookUp[i]->gutsBoost;
                    simWit += iLookUp[i]->witsBoost;
                }
            }
        }
        if (player.pAccEquiped == true) {
            for (int i = 0; i < iLookUp.size(); i++) {
                if (iLookUp[i]->itemId == player.pAccId) {
                    simAtk += iLookUp[i]->atkBoost;
                    simDef += iLookUp[i]->defBoost;
                    simSpe += iLookUp[i]->speedBoost;
                    simAgi += iLookUp[i]->agilBoost;
                    simGut += iLookUp[i]->gutsBoost;
                    simWit += iLookUp[i]->witsBoost;
                }
            }
        }
        if (player.pMiscEquiped == true) {
            for (int i = 0; i < iLookUp.size(); i++) {
                if (iLookUp[i]->itemId == player.pMiscId) {
                    simAtk += iLookUp[i]->atkBoost;
                    simDef += iLookUp[i]->defBoost;
                    simSpe += iLookUp[i]->speedBoost;
                    simAgi += iLookUp[i]->agilBoost;
                    simGut += iLookUp[i]->gutsBoost;
                    simWit += iLookUp[i]->witsBoost;
                }
            }
        }
    }
   //finished!
}
void MainFrame::populateInventory() {
    inventoryList->DeleteAllItems();
    for (size_t i = 0; i < pItems.size(); ++i) {
        long index = inventoryList->InsertItem(i, pItems[i]->name); // Column 0
        if (pItems[i]->type == 0) {
            if (pItems[i]->equiped == true) {
                inventoryList->SetItem(index, 1, wxString("[E]")); // Column 1
            }
            else {
                inventoryList->SetItem(index, 1, wxString("[ ]")); // Column 1
            }
        }
        else {
            inventoryList->SetItem(index, 1, wxString("N/A")); // Column 1
        }
        
        inventoryList->SetItem(index, 2, wxString::Format(wxT("%d"), pItems[i]->itemId));   // Column 2

        // Associate client data (e.g., the item's unique ID or index in vector)
        // This is crucial for retrieving the correct data when an item is selected
        inventoryList->SetItemData(index, i); // Store the vector index as client data
    }
}
void MainFrame::populateStats(Player player) {
    /**
    * Stats will be
    * Name
    * Level
    * Exp
    * Gold
    * Hp/MaxHp
    * Mp/MaxMp
    * Attack
    * Defence
    * Speed
    * Agility
    * Guts
    * Wits
    * We can't just use the player, we need that stats for level up, and these will use base stats plus weapons.
    **/
    getPlayerStatsSimple(player, simpleAttack, simpleDefense, simpleSpeed, simpleAgility, simpleGuts, simpleWits);
    statGrid->Append(new  wxPropertyCategory("Player Info", "player_info"));
    statGrid->Append(new wxStringProperty("Name", "player_name", player.pName));
    statGrid->Append(new wxIntProperty("Level", "player_level", player.pLevel));
    statGrid->Append(new wxIntProperty("EXP", "player_exp", player.pExp));
    statGrid->Append(new wxIntProperty("Gold", "player_gold", player.pGold));

    statGrid->Append(new  wxPropertyCategory("Player Stats", "player_stats"));
    statGrid->Append(new wxStringProperty("HP", "player_HPOOM", wxString::Format("%d / %d", player.pHP, player.maxHP)));
    statGrid->Append(new wxStringProperty("MP", "player_MPOOM", wxString::Format("%d / %d", player.pMP, player.maxMP)));
    statGrid->Append(new wxIntProperty("Attack", "player_atk", simpleAttack));
    statGrid->Append(new wxIntProperty("Defense", "player_def", simpleDefense));
    statGrid->Append(new wxIntProperty("Speed", "player_spe", simpleSpeed));
    statGrid->Append(new wxIntProperty("Agility", "player_agi", simpleAgility));
    statGrid->Append(new wxIntProperty("Guts", "player_gut", simpleGuts));
    statGrid->Append(new wxIntProperty("Wits", "player_wit", simpleWits));
    setUpStats = true;
}
void MainFrame::updateStats(Player player) {
    /**
    * Stats will be
    * Name
    * Level
    * Exp
    * Gold
    * Hp/MaxHp
    * Mp/MaxMp
    * Attack
    * Defence
    * Speed
    * Agility
    * Guts
    * Wits
    * We can't just use the player, we need that stats for level up, and these will use base stats plus weapons.
    **/
    getPlayerStatsSimple(player, simpleAttack, simpleDefense, simpleSpeed, simpleAgility, simpleGuts, simpleWits);
    /**
    statGrid->Append(new wxStringProperty("Name", "player_name", player.pName));
    statGrid->Append(new wxIntProperty("Level", "player_level", player.pLevel));
    statGrid->Append(new wxIntProperty("EXP", "player_exp", player.pExp));
    statGrid->Append(new wxIntProperty("Gold", "player_gold", player.pGold));

    statGrid->Append(new  wxPropertyCategory("Player Stats", "player_stats"));
    statGrid->Append(new wxStringProperty("HP", "player_HPOOM", wxString::Format("%d / %d", player.pHP, player.maxHP)));
    statGrid->Append(new wxStringProperty("MP", "player_MPOOM", wxString::Format("%d / %d", player.pMP, player.maxMP)));
    statGrid->Append(new wxIntProperty("Attack", "player_atk", simpleAttack));
    statGrid->Append(new wxIntProperty("Defense", "player_def", simpleDefense));
    statGrid->Append(new wxIntProperty("Speed", "player_spe", simpleSpeed));
    statGrid->Append(new wxIntProperty("Agility", "player_agi", simpleAgility));
    statGrid->Append(new wxIntProperty("Guts", "player_gut", simpleGuts));
    statGrid->Append(new wxIntProperty("Wits", "player_wit", simpleWits));
    setUpStats = true;
    **/
    wxPGProperty* nameProp = statGrid->GetPropertyByName("player_name");
    if (nameProp) {
        statGrid->SetPropertyValue(nameProp, wxVariant(player.pName));
    }
    wxPGProperty* levelProp = statGrid->GetPropertyByName("player_level");
    if (levelProp) {
        statGrid->SetPropertyValue(levelProp, wxVariant(player.pLevel));
    }
    wxPGProperty* expProp = statGrid->GetPropertyByName("player_exp");
    if (expProp) {
        statGrid->SetPropertyValue(expProp, wxVariant(player.pExp));
    }
    wxPGProperty* goldProp = statGrid->GetPropertyByName("player_gold");
    if (goldProp) {
        statGrid->SetPropertyValue(goldProp, wxVariant(player.pGold));
    }

    wxPGProperty* hpProp = statGrid->GetPropertyByName("player_HPOOM");
    if (hpProp) {
        statGrid->SetPropertyValue(hpProp, wxVariant(wxString::Format("%d / %d", player.pHP, player.maxHP)));
    }
    wxPGProperty* mpProp = statGrid->GetPropertyByName("player_MPOOM");
    if (mpProp) {
        statGrid->SetPropertyValue(mpProp, wxVariant(wxString::Format("%d / %d", player.pMP, player.maxMP)));
    }
    wxPGProperty* atkProp = statGrid->GetPropertyByName("player_atk");
    if (atkProp) {
        statGrid->SetPropertyValue(atkProp, wxVariant(simpleAttack));
    }
    wxPGProperty* defProp = statGrid->GetPropertyByName("player_def");
    if (defProp) {
        statGrid->SetPropertyValue(defProp, wxVariant(simpleDefense));
    }

    wxPGProperty* speProp = statGrid->GetPropertyByName("player_spe");
    if (speProp) {
        statGrid->SetPropertyValue(speProp, wxVariant(simpleSpeed));
    }
    wxPGProperty* agiProp = statGrid->GetPropertyByName("player_agi");
    if (agiProp) {
        statGrid->SetPropertyValue(agiProp, wxVariant(simpleAgility));
    }
    wxPGProperty* gutProp = statGrid->GetPropertyByName("player_gut");
    if (gutProp) {
        statGrid->SetPropertyValue(gutProp, wxVariant(simpleGuts));
    }
    wxPGProperty* witProp = statGrid->GetPropertyByName("player_wit");
    if (witProp) {
        statGrid->SetPropertyValue(witProp, wxVariant(simpleWits));
    }
}
void MainFrame::switchViewButton(wxCommandEvent& evt) {
    //int parentId = 0;
    
	if (startPanel->IsShown())
	{
		startPanel->Hide();
		savePanel->Show();
	}
	else if (savePanel->IsShown())
	{
        savePanel->Hide();
        namePanel->Show();
	}
    else if (namePanel->IsShown()) {
        namePanel->Hide();
        choicePanel->Show();
    }
    else if (choicePanel->IsShown()) {
        choicePanel->Hide();
        menuPanel->Show();
    }
    else if (menuPanel->IsShown()) {
        menuPanel->Hide();
        inventoryPanel->Show();
    }
    else if (inventoryPanel->IsShown()) {
        inventoryPanel->Hide();
        statPanel->Show();
    }
    else if (statPanel->IsShown()) {
        statPanel->Hide();
        startPanel->Show();
    }
	GetSizer()->Layout(); // Update the layout
}
void MainFrame::startButtonClicked(wxCommandEvent& evt) {
    if (iLookUpMade == false) {
        setUpLookUp();
    }
    if (eLookUpMade == false) {
        setUpEnenmyLookup();
    }
    
	startPanel->Hide();
	savePanel->Show();
	GetSizer()->Layout(); // Update the layout
}
void MainFrame::saveFileChosen(wxCommandEvent& evt) {
	int clickedId = evt.GetId();
	if (clickedId == ID_BUTTON_A)
	{
		// Handle Button A specific logic
		wxLogStatus("Button A clicked!");
		selectedPath = 0;
	}
	else if (clickedId == ID_BUTTON_B)
	{
		// Handle Button B specific logic
		wxLogStatus("Button B clicked!");
		selectedPath = 1;
	}
	else if (clickedId == ID_BUTTON_C)
	{
		// Handle Button C specific logic
		wxLogStatus("Button C clicked!");
		selectedPath = 2;
	}
    loadPlayerSave(savePaths[selectedPath]);

}
void MainFrame::choiceBoxSelect(wxKeyEvent& evt) {
    //0 is menu
    //1 is castle in scene 1. 1 is save in scene 2
    //2 is shop in scene 1, and is town square in scene 2
    //3 is only in scene 1, and is the fight section.
    //Now work on the field.
    if (evt.GetKeyCode() == WXK_RETURN) {
        int choiceSelected = infoBox->GetSelection();
        if (choiceSelected != wxNOT_FOUND) {
            wxString holderStr = wxString::Format("Choice Selected: %d", choiceSelected);
            wxLogStatus(holderStr);
            if (choiceSelected == 0) {
                if (sceneCurrent == 1 || sceneCurrent == 2) {
                    choicePanel->Hide();
                    menuPanel->Show();
                    GetSizer()->Layout(); // Update the layout
                }
            }
            if (choiceSelected == 1) {
                if (sceneCurrent == 1) {
                    infoBox->Deselect(choiceSelected);
                    infoBox->Set(choiceCastle);
                    choiceSelected = -1;
                    if (playerChar.pStoryFlag == 1) {
                        
                        sceneText->SetLabelText("Welcome Hero. This is the castle. You can save your quest here. Take this sword and 20 gold.");
                        getItem(1);
                        playerChar.pGold += 20;
                        playerChar.pStoryFlag = 2;
                    }
                    else {
                        sceneText->SetLabelText("Welcome Hero. This is the castle. You can save your quest here.");
                    }
                    sceneCurrent = 2;
                }
                else if (sceneCurrent == 2) {
                    wxLogStatus("Saving game");
                    savePlayerSave(savePaths[selectedPath]);
                }
            }
            if (choiceSelected == 2) {
                if (sceneCurrent == 1) {
                    wxLogStatus("Not done yet!");
                }
                if (sceneCurrent == 2) {
                    infoBox->Set(choiceOptions);
                    infoBox->Deselect(choiceSelected);
                    choiceSelected = -1;
                    sceneText->SetLabelText("You are in the town square. Select where you want to go.");
                    sceneCurrent = 1;
                }
            }
            if (choiceSelected == 3) {
                if (sceneCurrent == 1) {
                    wxLogStatus("Not done yet!");
                    choicePanel->Hide();
                    fightPanel->Show();
                    if (setUpStats == false) {
                        populateStats(playerChar);
                    }
                    else {
                        updateStats(playerChar);
                    }
                    battleStart();
                    GetSizer()->Layout();
                }
                if (sceneCurrent == 2) {
                    wxLogStatus("How did you select this?");
                }
            }
            
        }
        
    }
    else {
        evt.Skip();
    }
    
}
void MainFrame::menuBoxSelect(wxKeyEvent& evt) {
    if (evt.GetKeyCode() == WXK_RETURN) {
        int choiceSelected = menuBox->GetSelection();
        if (choiceSelected != wxNOT_FOUND) {
            wxString holderStr = wxString::Format("Choice Selected: %d", choiceSelected);
            wxLogStatus(holderStr);
            if (choiceSelected == 0) {
                wxLogStatus("Not Done Yet!");
                //Inventory
                populateInventory();
                menuPanel->Hide();
                inventoryPanel->Show();
                GetSizer()->Layout(); // Update the layout
            }
            if (choiceSelected == 1) {
                wxLogStatus("Not Done Yet!");
                //Stats
                if (setUpStats == false) {
                    populateStats(playerChar);
                }
                else {
                    updateStats(playerChar);
                }
                menuPanel->Hide();
                statPanel->Show();
                GetSizer()->Layout(); // Update the layout
            }
            if (choiceSelected == 2) {
                wxLogStatus("Not Done Yet!");
                //Magic
                //GetSizer()->Layout(); // Update the layout
            }
            if (choiceSelected == 3) {
                menuPanel->Hide();
                choicePanel->Show();
                GetSizer()->Layout(); // Update the layout
            }
            if (choiceSelected == 4) {
                Close(true); //close the game
            }
        }

    }
    else {
        evt.Skip();
    }

}
void MainFrame::itemSelect(wxListEvent& evt) {
    long selectedItemIndex = evt.GetIndex();
    wxString selectedText = inventoryList->GetItemText(selectedItemIndex);
    wxString selectedItemID = inventoryList->GetItemText(selectedItemIndex,2);
    wxLogStatus("Selected item: %s (Index: %ld) with Item ID of %s", selectedItemID, selectedItemIndex, selectedItemID);
    choiceID = (int)selectedItemIndex;
    evt.Skip();
}
void MainFrame::useItem(wxCommandEvent& evt) {
    if (choiceID != -1) {
        if (pItems[choiceID]->type == 0) {
            if (inBattle == false) {
                if (pItems[choiceID]->equiped == false) {
                    if (pItems[choiceID]->equipType == 0) {
                        if (playerChar.pWeaponEquiped == false) {
                            playerChar.pWeaponEquiped = true;
                        }
                        playerChar.pWeaponId = pItems[choiceID]->itemId;
                    }
                    if (pItems[choiceID]->equipType == 1) {
                        if (playerChar.pBodyEquiped == false) {
                            playerChar.pBodyEquiped = true;
                        }
                        playerChar.pBodyId = pItems[choiceID]->itemId;
                    }
                    if (pItems[choiceID]->equipType == 2) {
                        if (playerChar.pAccEquiped == false) {
                            playerChar.pAccEquiped = true;
                        }
                        playerChar.pAccId = pItems[choiceID]->itemId;
                    }
                    if (pItems[choiceID]->equipType == 3) {
                        if (playerChar.pMiscEquiped == false) {
                            playerChar.pMiscEquiped = true;
                        }
                        playerChar.pMiscId = pItems[choiceID]->itemId;
                    }
                    pItems[choiceID]->equiped = true;
                    inventroyMessage = "Equipped " + pItems[choiceID]->name;
                }
                else {
                    if (pItems[choiceID]->equipType == 0) {
                        if (playerChar.pWeaponEquiped == true) {
                            playerChar.pWeaponEquiped = false;
                        }
                        playerChar.pWeaponId = 0;
                    }
                    if (pItems[choiceID]->equipType == 1) {
                        if (playerChar.pBodyEquiped == true) {
                            playerChar.pBodyEquiped = false;
                        }
                        playerChar.pBodyId = 0;
                    }
                    if (pItems[choiceID]->equipType == 2) {
                        if (playerChar.pAccEquiped == true) {
                            playerChar.pAccEquiped = false;
                        }
                        playerChar.pAccId = 0;
                    }
                    if (pItems[choiceID]->equipType == 3) {
                        if (playerChar.pMiscEquiped == true) {
                            playerChar.pMiscEquiped = false;
                        }
                        playerChar.pMiscId = 0;
                    }
                    pItems[choiceID]->equiped = false;
                    inventroyMessage = "Unequipped " + pItems[choiceID]->name;
                }
            }
            else if (inBattle == true) {
                inventroyMessage = "Now is not the time for that!";
            }
        }
        else if (pItems[choiceID]->type == 1) {
            if (inBattle == true) {
                usedItem = true;
                usedID = choiceID;
            }
            bool hpMaxed = false;
            bool mpMaxed = false;
            bool noHPHeal = false;
            bool noMPHeal = false;
            string hpHealed = "";
            string mpHealed = "";
            playerChar.pHP += pItems[choiceID]->hpHeal;
            if (playerChar.pHP > playerChar.maxHP) {
                playerChar.pHP = playerChar.maxHP;
                hpMaxed = true;
            }
            else {
                hpMaxed = false;
                if (pItems[choiceID]->hpHeal != 0) {
                    noHPHeal = false;
                    hpHealed = to_string(pItems[choiceID]->hpHeal);
                }
                else {
                    noHPHeal = true;
                }
            }
            playerChar.pMP += pItems[choiceID]->mpHeal;
            if (playerChar.pMP > playerChar.maxMP) {
                playerChar.pMP = playerChar.maxMP;
                mpMaxed = true;
            }
            else {
                mpMaxed = false;
                if (pItems[choiceID]->mpHeal != 0) {
                    noMPHeal = false;
                    mpHealed = to_string(pItems[choiceID]->mpHeal);
                }
                else {
                    noMPHeal = true;
                }
            }
            if (hpMaxed == true && mpMaxed == true) {
                inventroyMessage = "HP and MP maxed out!";
            }
            else if (hpMaxed == true && mpMaxed == false) {
                if (noMPHeal == true) {
                    inventroyMessage = "HP maxed out!";
                }
                else {
                    inventroyMessage = "HP maxed out! Recovered " + mpHealed + " MP!";
                }
                
            }
            else if (hpMaxed == false && mpMaxed == true) {
                if (noHPHeal == true) {
                    inventroyMessage = "MP maxed out!";
                }
                else {
                    inventroyMessage = "Recovered " + hpHealed + " MP maxed out!";
                }

            }
            else if (hpMaxed == false && mpMaxed == false) {
                if (noHPHeal == true && noMPHeal == true) {
                    inventroyMessage = "You don't feel anyhing...";
                }
                else if (noHPHeal == true && noMPHeal == false) {
                    inventroyMessage = "Recovered " + mpHealed + "MP!";
                }
                else if (noHPHeal == false && noMPHeal == true) {
                    inventroyMessage = "Recovered " + hpHealed + "HP!";
                }
                else if (noHPHeal == false && noMPHeal == false) {
                    inventroyMessage = "Recovered " + hpHealed + "HP! Recovered " + mpHealed + "MP!";
                }

            }
            pItems.erase(pItems.begin() + choiceID);
            choiceID = -1;
            
        }
        if (inBattle == true && usedItem == true) {
            inventoryPanel->Hide();
            fightPanel->Show();
            itemUseTestMessage = inventroyMessage;
            playerbattleChoice = 3;
            battleUsedItem = true;
            playerFightReady = true;
            battleTime(playerbattleChoice);
            GetSizer()->Layout(); // Update the layout
            
            
            
        }
        describeText->SetLabelText(inventroyMessage);
        populateInventory();
    }else if (choiceID == -1) {
        evt.Skip();
    }
}
void MainFrame::fightChoiceSelect(wxKeyEvent& evt) {
    //0 = attack
    //1 = magic
    //2 = inventory
    //3 = run
    //Second Scene is for after fight
    if (evt.GetKeyCode() == WXK_RETURN) {
        int choiceSelected = fightBox->GetSelection();

        if (choiceSelected != wxNOT_FOUND) {
            wxString holderStr = wxString::Format("Choice Selected: %d", choiceSelected);
            wxLogStatus(holderStr);
            if (choiceSelected == 0) {
                if (lostBattle == true){
                    fightPanel->Hide();
                    choicePanel->Show();
                    fightBox->Deselect(choiceSelected);
                    fightBox->Set(choiceMenuFight);
                    lostBattle = false;
                    choiceSelected = -1;
                    GetSizer()->Layout(); // Update the layout
                }
                else {
                    if (inBattle == true) {
                        wxLogStatus("Attacked");
                        playerbattleChoice = 1;
                        playerFightReady = true;
                    }
                    else if (inBattle == false) {
                        playerWon = false;
                        fightBox->Set(choiceMenuFight);
                        fightBox->Deselect(choiceSelected);
                        choiceSelected = -1;
                        battleEn->enHP = battleEn->enHPM;
                        battleStart();
                        fightBox->Deselect(choiceSelected);
                        choiceSelected = -1;
                        wxLogStatus("B Start");
                    }
                }
                
            }
            if (choiceSelected == 1) {
                if (lostBattle == true) {
                    Close(true); //close the game
                }
                else {
                    if (inBattle == true) {
                        wxLogStatus("Not Done");
                        playerbattleChoice = 2;
                        playerFightReady = false;
                    }
                    else if (inBattle == false) {
                        playerWon = false;
                        fightPanel->Hide();
                        choicePanel->Show();
                        fightBox->Deselect(choiceSelected);
                        fightBox->Set(choiceMenuFight);
                        playerFightReady = false;
                        choiceSelected = -1;
                        GetSizer()->Layout(); // Update the layout
                    }
                }
                
            }
            if (choiceSelected == 2) {
                if (inBattle == true) {
                    //wxLogStatus("Not Done");
                    populateInventory();
                    fightPanel->Hide();
                    inventoryPanel->Show();
                    GetSizer()->Layout(); // Update the layout

                }
                else { 
                    wxLogStatus("Error"); 
                }
            }
            if (choiceSelected == 3) {
                if (inBattle == true) {
                    playerbattleChoice = 4;
                    playerFightReady = false;
                    fightText->SetLabelText("You \nran \n\n\naway!");
                    fightBox->Deselect(choiceSelected);
                    fightBox->Set(fightOverMenu);
                    GetSizer()->Layout(); // Update the layout
                    choiceSelected = -1;
                    inBattle = false;

                    
                } 
                else {
                    wxLogStatus("Error");
                }
            }
            
        }
        if (playerFightReady == true) {
            battleTime(playerbattleChoice);
        }
    }
    else {
        evt.Skip();
    }
}
void MainFrame::exitInventory(wxCommandEvent& evt) {
    if (inBattle == false) {
        //For menu outside of battel
        inventroyMessage = "";
        describeText->SetLabelText(inventroyMessage);
        inventoryPanel->Hide();
        menuPanel->Show();
        sceneText->SetLabelText("You are in the town square. Select where you want to go.");
        GetSizer()->Layout(); // Update the layout
    }
    else {
        wxLogStatus("In battle");
        //Temp code. REMEBER TO REMOVE
        inventoryPanel->Hide();
        fightPanel->Show();
        usedItem = false;
        GetSizer()->Layout(); // Update the layout
    }
}
void MainFrame::exitStats(wxCommandEvent& evt) {
    statPanel->Hide();
    menuPanel->Show();
    GetSizer()->Layout(); // Update the layout
}
void MainFrame::battleTime(int battleChoice) {
    wxLogStatus("Used %d",battleChoice);
    //case 1 will be attack, 2 is magic, 3 is item
    wxString fightingResult = "";
    wxString playerFightResult = "";
    wxString enResult = "It stood there...";
    bool enFirst = false;
    if (simpleSpeed >= battleEn->enSpe) {
        enFirst = false;
    }
    else {
        //en attack, not implimented yet.
        enFirst = true;
    }
    switch (battleChoice) {
    case 1:
        wxLogStatus("Simple attack is%d", simpleAttack);
        playerFightResult = "You swing at " + battleEn->enName + "\n";
        if (playerChar.pCrit() == true) {
            int damageDelt = (4 * simpleAttack - battleEn->enDef);
            playerFightResult += "SMASH! You hit " + battleEn->enName + " for " + to_string(damageDelt)+ " damage!";
            battleEn->enHP -= damageDelt;
            if (battleEn->enHP < 0) {
                battleEn->enHP = 0;
            }
        }
        else {
            if (playerChar.pHit(battleEn->enSlowStat, playerChar.playerSpeedEffect, battleEn->enAgi, simpleAgility) == false) {
                playerFightResult += "Missed!";
            }
            else if (playerChar.pHit(battleEn->enSlowStat, playerChar.playerSpeedEffect, battleEn->enAgi, simpleAgility) == true) {
                int damageDelt = (simpleAttack - battleEn->enDef);
                playerFightResult += "You hit " + battleEn->enName + " for " + to_string(damageDelt) + " damage!";
                battleEn->enHP -= damageDelt;
                if (battleEn->enHP < 0) {
                    battleEn->enHP = 0;
                }
            }
        }
        break;
    case 2:
        playerFightResult = "ERR Something Went wrong. Magic not done";
        break;
    case 3:
        playerFightResult += itemUseTestMessage;
        break;
    default:
        playerFightResult = "ERR Something Went wrong";
    }
    if (enFirst == true) {
        fightingResult += (enResult + "\n");
        if (playerChar.pHP <= 0) {
            fightingResult += "You blacked out!";
            lostBattle = true;
        } else {
            fightingResult += playerFightResult;
            if (battleEn->enHP <= 0) {
                fightingResult += ("\n" + battleEn->enName + " was defeated!");
                playerWon = true;
            }
        }
    }
    else {
        fightingResult += playerFightResult;
        if (battleEn->enHP <= 0) {
            fightingResult += ("\n" + battleEn->enName + " was defeated!");
            playerWon = true;
        } else {
            fightingResult += ("\n" + enResult);
            if (playerChar.pHP <= 0) {
                fightingResult += "You blacked out!";
                lostBattle = true;
            }
        }
    }
    fightText->SetLabelText(fightingResult);
    if (playerWon == true) {
        fightBox->Set(fightOverMenu);
        inBattle = false;
        GetSizer()->Layout(); // Update the layout
        playerChar.pGold += battleEn->enGold;
        playerChar.pExp += battleEn->enEXP;
    }
}
void MainFrame::battleStart() {
    inBattle = true;
    int ranEn = getRandom(0, (numOEn - 1));
    battleEn = eLookUP[0];
    fightText->SetLabelText("An Enemy Approaches!");
    playerFightReady = false;
    battleEn->enHP = battleEn->enHPM;

}