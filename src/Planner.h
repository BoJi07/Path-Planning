#ifndef PLANNER_H
#define PLANNER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <memory>
#include "Map.h"

using std::pair;

class LPAStar{
public:
    LPAStar(int startx, int starty, int endx, int endy, Map m):roadMap(m),startx(startx),starty(starty),endx(endx),endy(endy){
        start = roadMap.setStart(startx,starty);
        end = roadMap.setEnd(endx, endy);
    }
    void inti();
    void planner();
    vector<pair<int,int>> constructPath();
    void costChange(vector<vector<int>> &obstacles);
    void getMapInfo(){roadMap.printMap();}
    void clearPath() {roadMap.clearPath();};
    bool checkPath() const {return ableFindPath;}
private:
    Map roadMap{0,0};
    int startx;
    int starty;
    int endx;
    int endy;
    bool ableFindPath = true;
    shared_ptr<Node> start;
    shared_ptr<Node> end;
    vector<shared_ptr<Node>> openList;
    void computeRHS(shared_ptr<Node> curr);
    int computeH(shared_ptr<Node> curr);
    void remove(shared_ptr<Node> node);
    pair<int,int> calculateKey(shared_ptr<Node> node);
    void updateVertex(shared_ptr<Node> curr);
    void insert(shared_ptr<Node> node);
    bool compare(shared_ptr<Node> n1, shared_ptr<Node> n2);
    
};


#endif