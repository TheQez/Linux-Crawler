#include <iostream>
#include <vector>
#include "level.h"
#include "display.h"

void Display::open(string s) {
    if(s == "death_screen") {
	isDeathScreenOpen = true;
    }
}

void Display::close(string s) {
    if(s == "death_screen") {
	isDeathScreenOpen = false;
    }
}

void Display::changeFocus(string s) {
    if(s == "death_screen") {
	currentFocus = "death_screen";
    }
}

string Display::getFocus() {
    return currentFocus;
}

void Display::moveSelection(char direction) {
    switch(direction) {
	case 'L':
	    //Do something
	    break;
	case 'R':
	    //Do something
	    break;
    }
}

void Display::displayLevel(Level level, int currentHitpoints, int maxHitpoints) {
    vector< vector<char> > map = level.getMapWithEntities();
    vector< vector<char> > nextScreen(map.size()+2, vector<char>(map[0].size()+2, ' ')); //Contains what we will show
    //Set level up into nextScreen
    nextScreen[0][0] = '/';
    for(int i=1; i<=map[0].size(); i++) {
	nextScreen[0][i] = '=';
    }
    nextScreen[0][nextScreen[0].size()-1] = '\\';
    for(int i=1; i<=map.size(); i++) {
	nextScreen[i][0] = '|';
	for(int j=1; j<=map[0].size(); j++) {
	    nextScreen[i][j] = map[i-1][j-1];
	}
	nextScreen[i][nextScreen[i].size()-1] = '|';
    }
    nextScreen[nextScreen.size()-1][0] = '\\';
    for(int i=1; i<=map[0].size(); i++) {
	nextScreen[nextScreen.size()-1][i] = '=';
    }
    nextScreen[nextScreen.size()-1][nextScreen[0].size()-1] = '/';

    //Add windows over this
    if(getFocus() == "death_screen") { //"Game Over" screen
	//10 wide, 4 high window
	int windowHeight = 10;
	int windowWidth = 4;
	for(int i=(nextScreen.size()-windowHeight)/2; i<=(nextScreen.size()+windowHeight)/2; i++) {
	    for(int j=(nextScreen[0].size()-windowWidth)/2; i<=(nextScreen[0].size()+windowWidth)/2; j++) {
		if(i == (nextScreen.size()-windowHeight)/2 || i == (nextScreen.size()+windowHeight)/2 || j == (nextScreen[0].size()-windowWidth)/2 || j == (nextScreen[0].size()+windowWidth)/2) { //Borders
		    //nextScreen[i][j] = '*';
		}
		else {
		    nextScreen[i][j] = ' ';
		}
	    }
	}
    }
    
    for(int i=0; i<nextScreen.size(); i++) {
	for(int j=0; j<nextScreen[0].size(); j++) {
	    cout << nextScreen[i][j] << ' ';
	}
	cout << endl;
    }
    cout << "HP: " << currentHitpoints << " / " << maxHitpoints;
}
