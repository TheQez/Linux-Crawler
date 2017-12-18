#include <iostream>
#include <vector>
#include <cmath>
#include "level.h"
#include "utils.h"

using namespace std;

Level::Level(Player* p, int width, int height) {
    player = p;
    //cout << player.getCurrentHitpoints();
    map.resize(height, vector<char>(width, ' '));
}

vector< vector<char> > Level::getMap() {
    return map;
}

vector< vector<char> > Level::getMapWithEntities() {
    vector< vector<char> > entityMap = map;
    entityMap[player->yPos][player->xPos] = 'P';
    for(int i=0; i<scouts.size(); i++) {
	entityMap[scouts[i].yPos][scouts[i].xPos] = 'S';
    }
    return entityMap;
}

void Level::generateMap() { //TODO: Make this randomly generating
    /*map = {{'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
	   {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
	   {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
	   {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
	   {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
	   {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', ' ', '#'},
	   {'#', ' ', '#', '#', '#', '#', '#', '#', ' ', '#'},
	   {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
	   {'#', ' ', ' ', ' ', ' ', ' ', ' ', '#', '#', '#'},
	   {'#', '#', '#', '#', '#', '#', '#', '#', '#', ' '}};
    Scout scout1(3, 3, 10, 10);
    scouts.push_back(scout1);
    Scout scout2(8, 1, 10, 10);
    scouts.push_back(scout2);*/

    //Random generation
    //Number of rooms will be proportional to the map size (in squares)
    int mapWidth = map[0].size();
    int mapHeight = map.size();
    int mapSize = mapWidth * mapHeight;
    int roomDensity = 100; //How many squares are needed for a room to spawn (low number -> many rooms)
    int numRooms = mapSize / roomDensity;
    int avgRoomWidth = 6; //Average room width
    int avgRoomHeight = 8;
    float roomSizeVariation = 0.5f; //Variation in room size
    int minRoomWidth = round(roomSizeVariation * avgRoomWidth);
    int maxRoomWidth = round((2 - roomSizeVariation) * avgRoomWidth);
    int minRoomHeight = round(roomSizeVariation * avgRoomHeight);
    int maxRoomHeight = round((2 - roomSizeVariation) * avgRoomHeight);
    float enemyProbability = 0.5f;
    
    vector< vector<int> > rooms;
    vector< vector<int> > openings;
    vector<int> room(4);
    /*for(int i=0; i<numRooms; i++) {
	while(true) {
	    room[0] = Utility::randomNumber(0, mapWidth-1);
	    room[1] = Utility::randomNumber(0, mapHeight-1);
	    room[2] = Utility::randomNumber(minRoomWidth, maxRoomWidth);
	    room[3] = Utility::randomNumber(minRoomHeight, maxRoomHeight);
	    if(room[0] + room[2] < mapWidth && room[1] + room[3] < mapHeight) { //Not outside map
		bool isValid = true;
		bool xIntersect;
		bool yIntersect;
	        for(int j=0; j<rooms.size(); j++) {
		    xIntersect = false;
		    yIntersect = false;
		    //If we intersect on the x and y values, we intersect, if only one then we do not
		    if(Utility::isFieldOverlapping({room[0], room[0] + room[2]}, {rooms[j][0], rooms[j][0] + rooms[j][2]})) {
			xIntersect = true;
		    }
		    if(Utility::isFieldOverlapping({room[1], room[1] + room[3]}, {rooms[j][1], rooms[j][1] + rooms[j][3]})) {
			yIntersect = true;
		    }
		    if(xIntersect && yIntersect) {
			isValid = false;
			break;
		    }
		}
		if(isValid) { break; }
	    }
	}
	//cout << room[0] << " , " << room[1] << " , " << room[2] << " , " << room[3] << endl;
	rooms.push_back(room);
	}*/
    
    while(true) { //Initial seed room
	room[0] = Utility::randomNumber(0, mapWidth-1);
	room[1] = Utility::randomNumber(0, mapHeight-1);
	room[2] = Utility::randomNumber(minRoomWidth, maxRoomWidth);
	room[3] = Utility::randomNumber(minRoomHeight, maxRoomHeight);
	if(room[0] + room[2] < mapWidth && room[1] + room[3] < mapHeight) { //Not outside map
	    rooms.push_back(room);
	    break;
	}
    }
    int x, y;
    for(int i=0; i<numRooms; i++) {
	while(true) {
	    x = Utility::randomNumber(0, mapWidth-1);
	    y = Utility::randomNumber(0, mapHeight-1);
	    char side = ' ';
	    for(int j=0; j<rooms.size(); j++) {
		if(x == rooms[j][0] && y > rooms[j][1] && y < rooms[j][1] + rooms[j][3]) {
		    side = 'L'; //Left side
		    break;
		}
		else if(x == rooms[j][0] + rooms[j][2] && y > rooms[j][1] && y < rooms[j][1] + rooms[j][3]) {
		    side = 'R'; //Right
		    break;
		}
		else if(y == rooms[j][1] && x > rooms[j][0] && x < rooms[j][0] + rooms[j][2]) {
		    side = 'T'; //Top
		    break;
		}
		else if(y == rooms[j][1] + rooms[j][3] && x > rooms[j][0] && x < rooms[j][0] + rooms[j][2]) {
		    side = 'B'; //Bottom
		    break;
		}
	    }
	    if(side != ' ') { //Check if on wall
		//Make what we build here random

		//Generate the room location and size
		room[2] = Utility::randomNumber(minRoomWidth, maxRoomWidth);
		room[3] = Utility::randomNumber(minRoomHeight, maxRoomHeight);
		switch(side) {
		    case 'T':
			room[1] = y - room[3];
			room[0] = x - Utility::randomNumber(1, room[2]-1); //Randomise where the opening appears on the new room, 1 and room[2]-1 to remove corner connections
			break;
		    case 'B':
			room[1] = y;
			room[0] = x - Utility::randomNumber(1, room[2]-1);
			break;
		    case 'L':
			room[0] = x - room[2];
			room[1] = y - Utility::randomNumber(1, room[3]-1);
			break;
		    case 'R':
			room[0] = x;
			room[1] = y - Utility::randomNumber(1, room[3]-1);
			break;
		}
		//Check if the room is valid

		bool isValid = true;
		
		if(room[0] < 0 || room[1] < 0 || room[0] + room[2] >= mapWidth || room[1] + room[3] >= mapHeight) {
		    isValid = false;
	       	}
	        for(int j=0; j<rooms.size(); j++) {
		    if((Utility::isFieldOverlapping({room[0], room[0] + room[2] - 1}, {rooms[j][0], rooms[j][0] + rooms[j][2] - 1})) && (Utility::isFieldOverlapping({room[1], room[1] + room[3] - 1}, {rooms[j][1], rooms[j][1] + rooms[j][3] - 1}))) { //Uses -1 so room edges touching does not count
			isValid = false;
			break;
		    }
		}
		if(isValid) {
		    //Add stuff
		    if(Utility::randomProbability() < enemyProbability) {
			Scout scout(room[0] + 2, room[1] + 2, 10, 10);
			scouts.push_back(scout);
		    }
		    rooms.push_back(room);
		    openings.push_back({x, y});
		    break;
		}
	    }
	}
    }
    for(int i=0; i<rooms.size(); i++) { //Draw rooms
	for(int j=0; j<=rooms[i][2]; j++) { //Draw horizontal walls
	    map[rooms[i][1]][rooms[i][0] + j] = '#';
	    map[rooms[i][1] + rooms[i][3]][rooms[i][0] + j] = '#';
	}
	for(int j=0; j<=rooms[i][3]; j++) { //Draw vertical walls
	    map[rooms[i][1] + j][rooms[i][0]] = '#';
	    map[rooms[i][1] + j][rooms[i][0] + rooms[i][2]] = '#';
	}
    }
    for(int i=0; i<openings.size(); i++) {
	map[openings[i][1]][openings[i][0]] = ' ';
    }
    player->xPos = rooms[0][0] + 1;
    player->yPos = rooms[0][1] + 1;
}

vector< vector<int> > Level::getDistanceMap(int x, int y, int distance) { //distance = -1 means no limit on distance
    vector< vector<int> > distanceMap(map.size(), vector<int>(map[0].size(), -1));
    for(int i=0; i<map.size(); i++) {
	for(int j=0; j<map[i].size(); j++) {
	    if(map[i][j] == '#' || isEntity(j, i)) { //Blocked if wall or entity
		distanceMap[i][j] = -2;
	    }
	    else if(map[i][j] = ' ') {
		distanceMap[i][j] = -1;
	    }
	}
    }
    distanceMap[y][x] = 0; //Current position, 0 turns to reach it
    vector< vector<int> > newDistanceMap = distanceMap;
    int up, left, down, right;
    if(distance == -1) { //Infinite distance
	int i=0;
	bool isLastMove; //Used to stop once no more moves can be found
	while(true) {
	    i++;
	    isLastMove = true;
	    for(int j=0; j<distanceMap.size(); j++) { //Height
		for(int k=0; k<distanceMap[0].size(); k++) { //Width
		    if(distanceMap[j][k] == -1) { //Empty space, can be passed through
			up = (j==0) ? -2 : distanceMap[j-1][k]; //Value of -2 if outside, real value if not, used to prevent segfaults
			left = (k==0) ? -2 : distanceMap[j][k-1];
			down = (j==distanceMap.size()-1) ? -2: distanceMap[j+1][k];
			right = (k==distanceMap[0].size()-1) ? -2 : distanceMap[j][k+1];
			if(up >= 0 || left >= 0 || down >= 0 || right >= 0) { //If anything next to this tile is accessible, so is this tile
			    newDistanceMap[j][k] = i;
			    isLastMove = false; //We found a move, keep going
			}
		    }
		}
	    }
	    distanceMap = newDistanceMap;
	    if(isLastMove) {
		break; //No more moves
	    }
	}
    }
    else {
	for(int i=1; i<=distance; i++) {
	    for(int j=0; j<distanceMap.size(); j++) { //Height
		for(int k=0; k<distanceMap[0].size(); k++) { //Width
		    if(distanceMap[j][k] == -1) { 
		        up = (j==0) ? -2 : distanceMap[j-1][k];
			left = (k==0) ? -2 : distanceMap[j][k-1];
			down = (j==distanceMap.size()-1) ? -2: distanceMap[j+1][k];
			right = (k==distanceMap[0].size()-1) ? -2 : distanceMap[j][k+1];
			if(up >= 0 || left >= 0 || down >= 0 || right >= 0) { 
			    newDistanceMap[j][k] = i;
			}
		    }
		}
	    }
	    distanceMap = newDistanceMap; //Prevents issues where tile allows other tiles to be accessible on the same turn
	}
    }
    return distanceMap;
}

bool Level::hasLOS(int x1, int y1, int x2, int y2) { //Line of sight
    vector< vector<int> > l = Utility::getLine(x1, y1, x2, y2);
    for(int i=0; i<l.size(); i++) {
	if(map[l[i][1]][l[i][0]] != ' ') {
	    return false;
	}
    }
    return true;
}

void Level::movePlayerTo(int x, int y) {
    player->xPos = x;
    player->yPos = y;
}

bool Level::playerMove(char direction) { //Returns true if valid move, false if not
    int x = player->xPos;
    int y = player->yPos;
    vector< vector<char> > map = getMapWithEntities();
    if(direction == 'U' && map[y-1][x] == ' ') {
	player->yPos = y-1;
	return true;
    }
    else if(direction == 'L' && map[y][x-1] == ' ') {
        player->xPos = x-1;
        return true;
    }
    else if(direction == 'D' && map[y+1][x] == ' ') {
        player->yPos = y+1;
        return true;
    }
    else if(direction == 'R' && map[y][x+1] == ' ') {
        player->xPos = x+1;
        return true;
    }
    return false;
}

bool Level::playerAttack(char direction) {
    int x = player->xPos;
    int y = player->yPos;
    vector< vector<char> > map = getMapWithEntities();
    if(direction == 'U' && isEntity(x, y-1)) {
        Entity* enemy = getEntityAtPosition(x, y-1);
        enemy->damage(player->meleeDamage);
	return true;
    }
    else if(direction == 'L' && isEntity(x-1, y)) {
	Entity* enemy = getEntityAtPosition(x-1, y);
	enemy->damage(player->meleeDamage);
        return true;
    }
    else if(direction == 'D' && isEntity(x, y+1)) {
	Entity* enemy = getEntityAtPosition(x, y+1);
        enemy->damage(player->meleeDamage);
        return true;
    }
    else if(direction == 'R' && isEntity(x+1, y)) {
	Entity* enemy = getEntityAtPosition(x+1, y);
        enemy->damage(player->meleeDamage);
        return true;
    }
    return false;
    }

void Level::enemiesTurn() {
    vector< vector<int> > playerDistMap;
    vector<int> turn;
    vector< vector<int> > selfDistMap;
    playerDistMap = getDistanceMap(player->xPos, player->yPos, -1);
    for(int i=0; i<scouts.size(); i++) {
	selfDistMap = getDistanceMap(scouts[i].xPos, scouts[i].yPos, 1);
	turn = scouts[i].getTurn(hasLOS(player->xPos, player->yPos, scouts[i].xPos, scouts[i].yPos), player->xPos, player->yPos, playerDistMap, selfDistMap);
	if(turn[0] == 0) { //Move
	    scouts[i].xPos = turn[1];
	    scouts[i].yPos = turn[2];
	}
	else if(turn[0] == 1) { //Attack
	    player->damage(turn[1]);
	}
    }
}

bool Level::isEntity(int x, int y) {
    if(x == player->xPos && y == player->yPos) {
	return true;
    }
    for(int i=0; i<scouts.size(); i++) {
	if(x == scouts[i].xPos && y == scouts[i].yPos) {
	    return true;
	}
    }
    return false;
}

Entity* Level::getEntityAtPosition(int x, int y) {
    if(x == player->xPos && y == player->yPos) {
	return player; //Its already a pointer
    }
    Entity* ptr;
    for(int i=0; i<scouts.size(); i++) {
	if(x == scouts[i].xPos && y == scouts[i].yPos) {
	    ptr = &scouts[i];
	    return ptr;
	}
    }
}

void Level::cleanUp() {
    for(int i=0; i<scouts.size(); i++) {
	if(scouts[i].isDead) {
	    scouts.erase(scouts.begin()+i);
	}
    }
}
