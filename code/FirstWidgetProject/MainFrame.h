#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "Player.h"
using namespace std;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	bool iLookUpMade = false;
	bool eLookUpMade = false;
	int selectedPath = 0;
	int numOEn = 0;
	//This will use pannel ID to identify which panel to go to.
	int curPanelID = 0;
	int totalPanels = 3;
	string tempName;
	vector<Item*> iLookUp;
	vector<Enemy*> eLookUP;
	vector<Item*> pItems;
	Player playerChar;
private:
	//Help for control
	wxBoxSizer* mainSizer;
	//Start screen
	wxPanel* startPanel;
	//Save screen
	wxPanel* savePanel;
	//Name Screen
	wxPanel* namePanel;
	//For main choices, aka town square and town edge
	wxPanel* choicePanel;
	//For menu
	wxPanel* menuPanel;
	//For inventory
	wxPanel* inventoryPanel;
	//For stats
	wxPanel* statPanel;
	//For during battle
	wxPanel* fightPanel;
	wxListBox* infoBox;
	wxListBox* menuBox;
	wxListCtrl* inventoryList;
	wxButton* switchButton;
	vector<string> savePaths;
	string currSavePath;
	bool isValidName(string& playName);
	void namePlayer(wxCommandEvent& evt);
	int getRandom(int rMin, int rMax);
	void setUpLookUp();
	void setUpEnenmyLookup();
	void getItem(int wantedID);
	void loadPlayerSave(string saveFile);
	void savePlayerSave(string saveFile);
	void switchViewButton(wxCommandEvent& evt);
	void startButtonClicked(wxCommandEvent& evt);
	void saveFileChosen(wxCommandEvent& evt);
	void choiceBoxSelect(wxKeyEvent& evt);
	void menuBoxSelect(wxKeyEvent& evt);
	void populateInventory();
};

