// -*-c++-*-
#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

class Enemy : public Entity {
public:
    virtual vector<int> getTurn() { }; //AI of enemy controls this
};

#endif
