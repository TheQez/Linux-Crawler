// -*-c++-*-
#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

using namespace std;

class Entity {
public:
    int xPos;
    int yPos;
    int currentHitpoints;
    int maxHitpoints;
    bool isDead = false;
    int meleeDamage = 3;
    
    void damage(int); //Take damage
};

#endif
