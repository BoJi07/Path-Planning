#include "Map.h"
#include <iomanip>
vector<vector<shared_ptr<Node>>> Map::Init(){
    vector<vector<shared_ptr<Node>>> res (row, vector<shared_ptr<Node>>(col));
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            res[i][j] = std::make_shared<Node>(i,j);
        }
    }
    return res;
}

void Map::printMap(){
    
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(myMap[i][j]->status==Status::road){
                
                cout<<"  .  ";
            }
            else if(myMap[i][j]->status==Status::path){
                cout<<"  #  ";
            }
            else if(myMap[i][j]->status==Status::start){
            
                cout<<"  S  ";
            }
            else if(myMap[i][j]->status== Status::end){
            
                cout<<"  E  ";
            }
            else{
          
                cout<<"  @  ";
            }
        }
        cout<<"\n\n";
    }
}

void Map::setObstacle(vector<vector<int>> &points){
    for(auto &point : points){
        myMap[point[0]][point[1]]->status = Status::obstacle;
    }
}

void Map::setPath(int x, int y){
    myMap[x][y]->status = Status::path;
}


shared_ptr<Node> Map::setStart(int x, int y){
    myMap[x][y]->status = Status::start;
    return myMap[x][y];
}

shared_ptr<Node> Map::setEnd(int x, int y){
    myMap[x][y]->status = Status::end;
    return myMap[x][y];
}

vector<shared_ptr<Node>> Map::getNeighbor(shared_ptr<Node> curr){
    int x = curr->x;
    int y = curr->y;
    vector<shared_ptr<Node>> neighbor;
    for(auto &dir:dirs){
        if(x+dir[0]>=0&&x+dir[0]<row&&y+dir[1]>=0&&y+dir[1]<col&&myMap[x+dir[0]][y+dir[1]]->status!=Status::obstacle){
            neighbor.push_back(myMap[x+dir[0]][y+dir[1]]);
        }   
    }
    return neighbor;
}

void Map::clearPath(){
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            if(myMap[i][j]->status==Status::path){
                myMap[i][j]->status= Status::road;
            }
        }
    }
}

void Map::checkMapTransistioncost(){
    for(int i = 0; i<row; i++){
        for(int j = 0; j<col; j++){
            cout<<"("<<myMap[i][j]->g<<" , "<<myMap[i][j]->rhs<<")  ";
        }
        cout<<endl;
    }
}
