#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

using namespace std;

void Utility::printMap(vector< vector<int> > map) {
    for(int i=0; i<map.size(); i++) {
	for(int j=0; j<map[i].size(); j++) {
	    cout << map[i][j] << " ";
	}
	cout << endl;
    }
}

int Utility::randomNumber(int min, int max) {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return (rand() % (max-min+1)) + min;
}

float Utility::randomProbability() {
    if(!isRandomInitialised) {
	srand(time(NULL));
	isRandomInitialised = true;
    }
    return rand() / (RAND_MAX + 1.0);
}

bool Utility::isFieldOverlapping(vector<int> field1, vector<int> field2) {
    sort(field1.begin(), field1.end()); sort(field2.begin(), field2.end());
    if(field1[0] == field2[0]) {
	return true;
    }
    else if(field1[0] < field2[0]) {
	if(field1[1] >= field2[0]) { //Max of field 1 is greater than min of field 2
	    return true;
	}
	else {
	    return false; //Max and min of field 1 are lower than min field 2
	}
    }
    else {
	if(field2[1] >= field1[0]) {
	    return true;
	}
	else {
	    return false;
	}
    }
}

vector< vector<int> > Utility::getLine(int x1, int y1, int x2, int y2) {
    //Based on bresenham's line algorithm
    int dx = x2 - x1;
    int dy = y2 - y1;
    int aSize; //aSize is the larger difference, it will map to a
    int bSize;
    float gradient;
    bool xBiggest;
    vector< vector<int> > points;
    
    if(abs(dx) >= abs(dy)) { //More x values than y values, a = x, b = y, shallow
	aSize = dx;
	bSize = dy;
	xBiggest = true;
    }
    else { //More y values than x, a = y, b = x, steep
	aSize = dy;
	bSize = dx;
	xBiggest = false;
    }
    if(x2 == x1 || y2 == y1) { //Vertical or horizontal
	gradient = (float) 0;
    }
    else if(x2 > x1 && y2 > y1) { //Both up
	gradient = (float) abs(bSize) / (float) abs(aSize);
    }
    else if(x2 > x1 && y2 < y1) { //X up, y down
	gradient = -((float) abs(bSize) / (float) abs(aSize));
    }
    else if(x2 < x1 && y2 > y1) { //X down, y up
	gradient = -((float) abs(bSize) / (float) abs(aSize));
    }
    else if(x2 < x1 && y2 < y1) { //Both down
	gradient = (float) abs(bSize) / (float) abs(aSize);
    }
    int c = (xBiggest ? y1 : x1) - round((xBiggest ? x1 : y1) * gradient);
    for(int a= (xBiggest ? x1 : y1); (aSize < 0 ? a>=aSize + (xBiggest ? x1 : y1) : a<=aSize + (xBiggest ? x1 : y1)); (aSize >= 0 ? a++ : a--)) {
	int b = round((a * gradient) + c);
	if(xBiggest) {
	    points.push_back({a, b});
	}
	else {
	    points.push_back({b, a});
	}
    }
    return points;
}
