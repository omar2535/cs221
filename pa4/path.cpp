#include "path.h"
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

path::path(const PNG & im, pair<int,int> s, pair<int,int> e)
   :start(s),end(e),image(im){
    BFS();
}

void path::BFS(){
    cout <<"Image width: "<< image.width() << endl;
    cout <<"Image height: "<< image.height() << endl;
    // initialize working vectors
	vector<vector<bool>> V(image.height(), vector<bool> (image.width(),false));
	vector<vector<pair<int,int>>> P(image.height(), vector<pair<int,int>> (image.width(),end));
    
    queue<pair<int, int>> q;
    q.push(start);
    V[start.second][start.first] = true;

    while(!q.empty()){
        pair<int, int> currVertex = q.front();
        q.pop();
        vector<pair<int, int>> adj = neighbors(currVertex);
        for(size_t i = 0; i<adj.size(); i++){
            pair<int, int> nextVertex = adj[i];
            if(good(V, currVertex, nextVertex)){
                V[nextVertex.second][nextVertex.first] = true;
                P[nextVertex.second][nextVertex.first] = currVertex;
                q.push(adj[i]);
            }
        }
    }

	pathPts = assemble(P,start,end);
}

PNG path::render(){
    PNG copy = image;
    cout<<"Length of path: "<<length()<<endl;
    if(length() == 1){
        return copy;
    }else{
        for (int i = 0; i < length(); i++){
            pair<int, int> currPoint = pathPts[i];
            int x = currPoint.first;
            int y = currPoint.second;
            RGBAPixel *currPixel = copy.getPixel(x, y);
            currPixel->r = 255;
            currPixel->g = 0;
            currPixel->b = 0;
        }
    }

    return copy;
}

vector<pair<int,int>> path::getPath() { return pathPts;}

int path::length() { return pathPts.size();}

bool path::good(vector<vector<bool>> & v, pair<int,int> curr, pair<int,int> next){
    if(next.first >= (int)image.width() || next.second >= (int)image.height() || next.first < 0 || next.second < 0){
        return false;
    }
    //cout<<"X: "<< next.first <<" Y: "<< next.second<<endl;
    
    if(v[next.second][next.first] == false){
        RGBAPixel* firstPixel = image.getPixel(curr.first, curr.second);
        RGBAPixel* secondPixel = image.getPixel(next.first, next.second);
        if(closeEnough(*firstPixel, *secondPixel)){
            return true;
        }
    }
    return false;
}

vector<pair<int,int>> path::neighbors(pair<int,int> curr) {
	vector<pair<int,int>> n;
    int x = curr.first;
    int y = curr.second;
    pair<int, int> up = make_pair(x, y-1);
    pair<int, int> down = make_pair(x, y+1);
    pair<int, int> left = make_pair(x-1, y);
    pair<int, int> right = make_pair(x+1, y);
    n.push_back(up);
    n.push_back(down);
    n.push_back(left);
    n.push_back(right);
    return n;
}

vector<pair<int,int>> path::assemble(vector<vector<pair<int,int>>> & p,pair<int,int> s, pair<int,int> e) {
    stack<pair<int, int>> stackOfPoints;
    vector<pair<int, int>> P;
    pair<int, int> current = e;

    if(p[e.second][e.first] != e){
        while (current != s){
            stackOfPoints.push(current);
            pair<int, int> pred = p[current.second][current.first];
            current = pred;
        }
        stackOfPoints.push(current);
        cout << "stack size: " << stackOfPoints.size() << endl;
        while (!stackOfPoints.empty()){
            P.push_back(stackOfPoints.top());
            stackOfPoints.pop();
        }
    }else{
        P.push_back(s);
    }
    
    return P;
}

bool path::closeEnough(RGBAPixel p1, RGBAPixel p2){
   int dist = (p1.r-p2.r)*(p1.r-p2.r) + (p1.g-p2.g)*(p1.g-p2.g) +
               (p1.b-p2.b)*(p1.b-p2.b);

   return (dist <= 80);
}
