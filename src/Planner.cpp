#include "Planner.h"


void LPAStar::computeRHS(shared_ptr<Node> curr){
    vector<shared_ptr<Node>> neighbors = roadMap.getNeighbor(curr);
    curr->rhs = infi;
    for(auto &neighbor: neighbors){
        //cout<<neighbor->x<<" "<<neighbor->y<<endl;
        if(neighbor->g!=infi){
            if(curr->rhs>(curr->cost(neighbor)+neighbor->g)){
                curr->rhs = curr->cost(neighbor)+neighbor->g;
                curr->parent = neighbor;
            }
        }
    }
}

int LPAStar::computeH(shared_ptr<Node> curr){
    return curr->cost(end);
}

void LPAStar::remove(shared_ptr<Node> node){
    
    for(int i = 0; i<openList.size(); i++){
        if(openList[i]->x==node->x&&openList[i]->y==node->y){
            openList.erase(openList.begin()+i);
            break;
        }
    }
}

pair<int,int> LPAStar::calculateKey(shared_ptr<Node> node){
    int g = node->g;
    int rhs = node->rhs;
    int h = computeH(node);
    if(std::min(g,rhs)==infi){
        return std::make_pair(infi,infi);
    }
    else{
        return std::make_pair(std::min(g,rhs)+h,std::min(g,rhs));
    }
}

void LPAStar::insert(shared_ptr<Node> node){
    openList.push_back(node);
    sort(openList.begin(),openList.end(),[this](shared_ptr<Node> n1, shared_ptr<Node> n2){
        auto res1 = calculateKey(n1);
        auto res2 = calculateKey(n2);
        return ((res1.first<res2.first)||(res1.first==res2.first && res1.second < res2.second));
    });
}

void LPAStar::updateVertex(shared_ptr<Node> curr){
    int x = curr->x;
    int y = curr->y;
    if(x!=startx||y!=starty){
        computeRHS(curr);
        //cout<<curr->rhs<<" "<<curr->g<<endl;
    }
    remove(curr);
    if(curr->rhs!=curr->g){
        insert(curr);
    }
}

bool LPAStar::compare(shared_ptr<Node> n1, shared_ptr<Node> n2){
    auto res1 = calculateKey(n1);
    auto res2 = calculateKey(n2);
    if((res1.first<res2.first)||(res1.first==res2.first&&res1.second<res2.second)){
        return true;
    }
    return false;
}


void LPAStar::inti(){
    start->rhs = 0;
    openList.push_back(start);
}


void LPAStar::planner(){

    while(openList.size()>0&&(compare(openList[0],end)||end->rhs!=end->g)){
        shared_ptr<Node> curr = openList[0];
        //cout<<curr->x<<" "<<curr->y<<" "<<curr->rhs<<" "<<curr->g<<endl;
        remove(curr);
        vector<shared_ptr<Node>> neighbors = roadMap.getNeighbor(curr);
        if(curr->g>curr->rhs){
            curr->g = curr->rhs;
            for(auto &neighbor: neighbors){
                //cout<<neighbor->x<<" "<<neighbor->y<<endl;
                updateVertex(neighbor);
            }
        }
        else{
            curr->g = infi;
            for(auto &neighbor: neighbors){
                updateVertex(neighbor);
            }
            updateVertex(curr);   
        }
    }
    //cout<<openList.size()<<endl;
}

vector<pair<int,int>> LPAStar::constructPath(){
    //cout<<end->rhs<<" "<<end->g<<endl;
    vector<pair<int,int>> trajectory;
    if(end->rhs==end->g&&end->g!=infi){
        shared_ptr<Node> ref = end;
        while(ref!=nullptr){
            if(ref->status==Status::road){
                roadMap.setPath(ref->x,ref->y);
                trajectory.push_back(std::make_pair(ref->x,ref->y)); //exclude the start and end point
            }
            ref = ref->parent;
        }
        roadMap.printMap();
    }
    else{
        ableFindPath = false;
        cout<<"unable to find a path from starting point to ending point"<<endl;
    }
    return trajectory;
    //roadMap.checkMapTransistioncost();

}

void LPAStar::costChange( vector<vector<int>> &obstacles){
    roadMap.setObstacle(obstacles);
    for(auto &obstacle:obstacles){
        shared_ptr<Node> costChange = roadMap.getNode(obstacle[0],obstacle[1]);
        vector<shared_ptr<Node>> neighbors = roadMap.getNeighbor(costChange);
        for(auto& neighbor : neighbors){
            updateVertex(neighbor);
        }
    }
}