#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <math.h>
#include <memory>

using std::vector;
using std::cout;
using std::endl;
using std::shared_ptr;

const double infi = std::numeric_limits<int>::max();

enum class Status{
    path,obstacle,road,start,end
};

struct Node{
    shared_ptr<Node> parent;
    int x;
    int y;
    int g;
    int rhs;
    Status status;
    Node(int x, int y): x(x), y(y), status(Status::road),g(infi),rhs(infi),parent(nullptr){}
    double cost(shared_ptr<Node> other){
        if(this->status==Status::obstacle||other->status==Status::obstacle){
            return infi;
        }
        return abs(this->x-other->x)+abs(this->y-other->y);
    }
};

/*----------------------------------start of Map------------------------------------------*/

class Map{
public:
    Map(int row, int col):row(row),col(col){
        myMap = Init();
    }
    int getRow() const {return row;}
    int getCol() const { return col;}
    void printMap();
    void setObstacle(vector<vector<int>> &points);
    void setPath(int x, int y);
    shared_ptr<Node> setStart(int x, int y);
    shared_ptr<Node> setEnd(int x, int y);
    shared_ptr<Node> getNode(int x, int y) const { return myMap[x][y];}
    vector<shared_ptr<Node>> getNeighbor(shared_ptr<Node> curr);
    void clearPath();
    void checkMapTransistioncost();
    
private:
    int row;
    int col;
    vector<vector<shared_ptr<Node>>> myMap;
    vector<vector<shared_ptr<Node>>> Init();
    const vector<vector<int>> dirs = {{-1,0},{1,0},{0,-1},{0,1}};
    
};

#endif