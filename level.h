// -*-c++-*-
#ifndef LEVEL_H
#define LEVEL_H
using namespace std;

#include "player.h"
#include "scout.h"

class Level {

private:
    
    vector< vector<char> > map;
    Player* player;
    /* Map characters:
       (space) - open ground
       # - wall
       P - player
       E - enemy
    */
    vector<Scout> scouts;
    

    void movePlayerTo(int, int); //Move the player to any location
    
public:
    
    Level(Player*, int, int); //Constructor
    vector< vector<char> > getMap(); //Return the map
    vector< vector<char> > getMapWithEntities(); //Returns the map with all entities
    void generateMap(); //Creates the map
    vector< vector<int> > getDistanceMap(int, int, int); //Gets the map but shows the distances from a single space
    bool hasLOS(int, int, int, int); //Checks if two positions have line of sight between each other
    bool playerMove(char); //Moves the player in a specified direction
    bool playerAttack(char); //Melee attack in the specified direcrion
    void enemiesTurn(); //Performs the turn for the enemies
    bool isEntity(int, int); //Checks if there is an entity at the specified location
    Entity* getEntityAtPosition(int, int); //Gets a pointer to the entity at a given location
    void cleanUp(); //Removes all dead enemies
    /*
      Distance Map characters:
      -2 - impassable object (wall)
      -1 - open space (not within range)
      0+ - the amount of movements required to move there (0 is current location)*/
    
};

#endif
