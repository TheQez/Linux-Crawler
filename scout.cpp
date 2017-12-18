#include <iostream>
#include <vector>
#include "utils.h"
#include "scout.h"

using namespace std;

Scout::Scout(int x, int y, int current, int max) {
    xPos = x;
    yPos = y;
    currentHitpoints = current;
    maxHitpoints = max;
}
vector<int> Scout::getTurn(bool hasLOS, int playerX, int playerY, vector< vector<int> > playerDistMap, vector< vector<int> > selfDistMap) { //0 first is move, 1 first is attack
    if(!hasLOS) {
	vector<int> v = {0, xPos, yPos};
	return v;
    }
    if((playerX == xPos && (playerY == yPos-1 || playerY == yPos+1)) || (playerY == yPos && (playerX == xPos-1 || playerX == xPos+1))) { //Next to player
	vector<int> v = {1, meleeDamage};
	return v;
    }
    int closestMove;
    vector< vector<int> > closestPositions;
    for(int y=0; y<playerDistMap.size(); y++) {
	for(int x=0; x<playerDistMap[0].size(); x++) {
	    if(selfDistMap[y][x] >= 0 && playerDistMap[y][x] >= 0) {
		if(playerDistMap[y][x] < closestMove) { //New best move, clear all ways of geting last value and set this as best
		    closestPositions.clear();
		    closestMove = playerDistMap[y][x];
		    vector<int> v = {x, y};
		    closestPositions.push_back(v);
		}
		else if(playerDistMap[y][x] == closestMove) { //Same, set as a new way of getting this value
		    vector<int> v = {x, y};
		    closestPositions.push_back(v);
		}
	    }
	}
    }
    if(closestPositions.size() > 0) { //We have a valid move
	int n = Utility::randomNumber(0, closestPositions.size()-1);
	vector<int> v = {0, closestPositions[n][0], closestPositions[n][1]};
	return v;
    }
    else { //Failsafe in case we have no valid moves
	vector<int> v = {0, xPos, yPos};
	return v;
    }
}
