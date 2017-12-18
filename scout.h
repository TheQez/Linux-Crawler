// -*-c++-*-
#ifndef SCOUT_H
#define SCOUT_H

#include <vector>
#include "enemy.h"

class Scout : public Enemy {
public:
    Scout(int, int, int, int);
    vector<int> getTurn(bool, int, int, vector< vector<int> >, vector< vector<int> >);
};

#endif
