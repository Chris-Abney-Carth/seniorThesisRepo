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
#include <wx/wx.h>

using namespace std;

enum {
	ID_BUTTON_A = 101,
	ID_BUTTON_B,
	ID_BUTTON_C
};

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {

	savePaths.push_back("playerSave1.txt");
	savePaths.push_back("playerSave2.txt");
	savePaths.push_back("playerSave3.txt");

    

	startPanel = new wxPanel(this, wxID_ANY);
	startPanel->SetBackgroundColour(*wxBLACK);

	savePanel = new wxPanel(this, wxID_ANY);
	savePanel->SetBackgroundColour(*wxBLUE);
	savePanel->Hide();

	wxStaticText* gameTitle = new wxStaticText(startPanel, wxID_ANY, "BITQUEST", wxPoint(300, 175), wxSize(200, 50), wxALIGN_CENTER_HORIZONTAL);
	gameTitle->SetForegroundColour(*wxGREEN);
	wxFont titleFont = gameTitle->GetFont();
	titleFont.SetPointSize(20);
	gameTitle->SetFont(titleFont);
	gameTitle->GetParent()->Layout();

	

	

	switchButton = new wxButton(this, wxID_ANY, "Switch View");
	wxButton* startButton = new wxButton(startPanel, wxID_ANY, "START", wxPoint(300, 275), wxSize(200, 50));

	switchButton->Bind(wxEVT_BUTTON, &MainFrame::switchViewButton, this);
	startButton->Bind(wxEVT_BUTTON, &MainFrame::startButtonClicked, this);

	wxButton* saveOneButton = new wxButton(savePanel, ID_BUTTON_A, "Save 1", wxPoint(300, 175), wxSize(200, 50));
	wxButton* saveTwoButton = new wxButton(savePanel, ID_BUTTON_B, "Save 2", wxPoint(300, 275), wxSize(200, 50));
	wxButton* saveThreeButton = new wxButton(savePanel, ID_BUTTON_C, "Save 3", wxPoint(300, 375), wxSize(200, 50));
	
	Bind(wxEVT_BUTTON, &MainFrame::saveFileChosen, this, ID_BUTTON_A, ID_BUTTON_C);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(startPanel, 1, wxEXPAND);
	mainSizer->Add(savePanel, 1, wxEXPAND); // Add both panels to the sizer
	mainSizer->Add(switchButton, 0, wxALIGN_CENTER | wxALL, 5);
	SetSizerAndFit(mainSizer);
	CreateStatusBar();
}

void MainFrame::setUpLookUp() {
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

int MainFrame::getRandom(int rMin, int rMax) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(rMin, rMax);
	int randomValue = distrib(gen);
	return randomValue;
}

void MainFrame::switchViewButton(wxCommandEvent& evt) {
	if (startPanel->IsShown())
	{
		startPanel->Hide();
		savePanel->Show();
	}
	else
	{
		savePanel->Hide();
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


}