#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

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
    readFile();
    cout << "After File" << endl;
    return 0;
}