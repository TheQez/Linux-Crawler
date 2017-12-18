#include <iostream>
#include <vector>
#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include "level.h"
#include "entity.h"
#include "display.h"
#include "utils.h"

using namespace std;

char getKey() {
    struct termios old_tio, new_tio;
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &=(~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);
    char key = getchar();
    tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
    return key;
}

bool handleKey(char key, Level &level, Display &display) { //Returns true if handled succsesfully
    string currentFocus = display.getFocus();
    if(currentFocus == "level") {
	switch(key) {
	    case 'w': //Will try move, then try attack if not possible
		if(level.playerMove('U')) { return true; }
		else if(level.playerAttack('U')) { return true; }
		break;
	    case 'a':
		if(level.playerMove('L')) { return true; }
		else if(level.playerAttack('L')) { return true; }
		break;
	    case 's':
		if(level.playerMove('D')) { return true; }
		else if(level.playerAttack('D')) { return true; }
		break;
	    case 'd':
		if(level.playerMove('R')) { return true; }
		else if(level.playerAttack('R')) { return true; }
		break;
	}
	return false;
    }
    else if(currentFocus == "death_screen") {
	switch(key) {
	    case 'a':
		display.moveSelection('L');
		return true;
		break;
	    case 'd':
		display.moveSelection('R');
		return true;
		break;
	}
	return false;
    }
}
int main () {
    Player player(1, 1, 10, 10, 5);
    Player* playerptr;
    playerptr = &player;
    Level level(playerptr, 40, 40); //x length, y length
    level.generateMap();
    Display display;
    char key;
    bool validKey;
    while(true) { //TODO: Break on death or end of level
	display.displayLevel(level, player.currentHitpoints, player.maxHitpoints);
	validKey = false;
	while(!validKey) {
	    key = getKey();
	    if(key == 'z') { //Debugging
		return 0;
	    }
	    validKey = handleKey(key, level, display);
	}
        level.enemiesTurn();
	level.cleanUp();
	if(player.isDead) {
	    display.open("death_screen");
	    display.changeFocus("death_screen");
	    while(true) {
		display.displayLevel(level, player.currentHitpoints, player.maxHitpoints);
		key = getKey();
		handleKey(key, level, display);
	    }
	}
    }
    return 0;
}
