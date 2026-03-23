#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
#include "Player.h"
#include <map>
using namespace std;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	bool iLookUpMade = false;
	bool eLookUpMade = false;
	bool inBattle = false;
	bool lostBattle = false;
	int selectedPath = 0;
	int numOEn = 0;
	//This will use pannel ID to identify which panel to go to.
	int curPanelID = 0;
	int totalPanels = 3;
	string tempName = "";
	vector<Item*> iLookUp;
	vector<Enemy*> eLookUP;
	vector<Item*> pItems;
	Player playerChar;
	int simpleAttack = 0;
	int simpleDefense = 0;
	int simpleSpeed = 0;
	int simpleAgility = 0;
	int simpleGuts = 0;
	int simpleWits = 0;
	bool setUpStats = false;
	bool playerWon = false;
	int choiceID = -1;
	bool battleUsedItem = false;
	string inventroyMessage = "";
	string itemUseTestMessage = "Test";
	int sceneCurrent = 0;
	int playerbattleChoice = 0;
	bool playerFightReady = false;
	bool enemyFightReady = false;
	bool usedItem = false;
	int usedID = 0;
	//0 = attack
	//Simple player stats are states that are used for fights or stat screen. They are not the base value for some stats.
	wxArrayString choiceOptions;
	wxArrayString choiceMenuOverworld;
	wxArrayString choiceCastle;
	wxArrayString choiceMenuFight;
	wxArrayString fightOverMenu;
	wxArrayString battleLostMenu;
	wxArrayString battelWonMenu;
	Enemy* battleEn;
private:
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
	wxListBox* fightBox;
	wxListBox* menuBox;
	wxListCtrl* inventoryList;
	wxPropertyGrid* statGrid;
	wxButton* switchButton;
	wxTextCtrl* describeText;
	wxTextCtrl* sceneText;
	wxTextCtrl* fightText;
	vector<string> savePaths;
	//for simple player stats, we need to have more complex items, so sting is best, as how do we show hp/maxHp with numbers? Will set this up with default values
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
	void itemSelect(wxListEvent& evt);
	void populateInventory();
	void populateStats(Player player);
	void getPlayerStatsSimple(Player player, int& simAtk, int& simDef, int& simSpe, int& simAgi, int& simGut, int& simWit);
	void updateStats(Player player);
	void exitInventory(wxCommandEvent& evt);
	void exitStats(wxCommandEvent& evt);
	void useItem(wxCommandEvent& evt);
	void fightChoiceSelect(wxKeyEvent& evt);
	void battleTime(int battleChoice);
	void battleStart();

};

