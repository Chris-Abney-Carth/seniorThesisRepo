#pragma once
#include <wx/wx.h>
#include <string>
#include <vector>
#include "Item.h"
#include "Enemy.h"
using namespace std;

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	bool iLookUpMade = false;
	bool eLookUpMade = false;
	int selectedPath = 0;
	int numOEn = 0;
	vector<Item*> iLookUp;
	vector<Enemy*> eLookUP;
private:
	wxPanel* startPanel;
	wxPanel* savePanel;
	wxButton* switchButton;
	vector<string> savePaths;
	int getRandom(int rMin, int rMax);
	void setUpLookUp();
	void setUpEnenmyLookup();
	void switchViewButton(wxCommandEvent& evt);
	void startButtonClicked(wxCommandEvent& evt);
	void saveFileChosen(wxCommandEvent& evt);
};

