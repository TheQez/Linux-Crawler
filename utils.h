#ifndef UTILS_H
#define UTILS_H

#include <vector>

using namespace std;

namespace Utility {
    static bool isRandomInitialised = false;
    
    void printMap(vector< vector<int> >);
    int randomNumber(int, int);
    bool isFieldOverlapping(vector<int>, vector<int>);
    float randomProbability();
    vector< vector<int> > getLine(int, int, int, int);
}

#endif
