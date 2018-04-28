#include <cmath>
#include <vector>
#include "point.h"
#include "stack.h"
#include "convexhull.h"
#include <iostream>
#include <math.h> 

using namespace std;

//Sorts this vector by their angle
void sortByAngle(vector<Point>& v){
    findSmallestYAndSwap(v);
    for(unsigned int i=1; i<v.size(); i++){
        Point curr = v.at(i);
        double minAngle = getAngle(v.at(0), v.at(i));
        //cout<<minAngle<<endl;
        int index = i;
        for(unsigned int x=i; x<v.size(); x++){
            //cout<<getAngle(v.at(0), v.at(x))<<endl;
            if(getAngle(v.at(0), v.at(x)) >= minAngle){
                minAngle = getAngle(v.at(0), v.at(x));
                index = x;
            }
        }
        v.at(i) = v.at(index);
        v.at(index) = curr;    
    }
}

//Check if 3 points form a counter clockwise turn
bool ccw(Point p1, Point p2, Point p3){
    double firstDet = p1.x * (p2.y - p3.y);
    double secondDet = p1.y * (-1) * (p2.x - p3.x);
    double thirdDet = p2.x*p3.y - p2.y*p3.x;
    return firstDet + secondDet + thirdDet > 0;

}

//Gets next next of top
Point nextToTop(Stack& s)
{
    Point p = s.peek();
    s.pop();
    Point res = s.peek();
    s.push(p);
    return res;
}

//check if straight line
//returns true if it is a straight line
bool ifIsStraightLine(vector<Point> &v){
    bool isStraight = true;
    for(int i=0; i<v.size()-2; i++){
        double x1 = v.at(i).x;
        double y1 = v.at(i).y;
        double x2 = v.at(i+1).x;
        double y2 = v.at(i+1).y;
        double x3 = v.at(i+2).x;
        double y3 = v.at(i+2).y;
        double firstSlope = (y2-y1)/(x2-x1);
        double secondSlope = (y3-y1)/(x3-x1);
        if(firstSlope != secondSlope){
            isStraight = false;
            break;
        }
    }
    return isStraight;
}


//make our convex hull
vector<Point> getConvexHull(vector<Point>& v){
    vector<Point> ret;
    sortByAngle(v);
    //Check if at least 3 points
    if(v.size() < 3){
        return ret;
    }
    //Check if straight line
    if(ifIsStraightLine(v)){
        return ret;
    }

    Stack stack;
    stack.push(v.at(0));
    stack.push(v.at(1));
    stack.push(v.at(2));

    for(unsigned int i=3; i<v.size(); i++){
        while(!ccw(nextToTop(stack), stack.peek(), v.at(i))){
            stack.pop();
        }
        stack.push(v.at(i));
    }


    while(!stack.isEmpty()){
        ret.push_back(stack.pop());
    }
    return ret;
}


//Returns angle between x and vector making up smallest and compare
double getAngle(Point smallest, Point compare){
    //cout<<smallest.x<<smallest.y<<endl;
    //cout<<compare.x<<compare.y<<endl;
    Point lineVector = Point(compare.x-smallest.x, compare.y-smallest.y);
    //cout<<lineVector.x<<lineVector<<endl;
    Point xAxis = Point(1,0);
    double dotProd = (lineVector.x*xAxis.x + lineVector.y * xAxis.y);
    //cout<<dotProd<<endl;
    double lineVectorMag = sqrt(lineVector.x * lineVector.x + lineVector.y * lineVector.y);
    double xAxisMag = sqrt(xAxis.x * xAxis.x + xAxis.y *xAxis.y);
    return dotProd/(lineVectorMag * xAxisMag);
}

//Finds smallest angle and swaps
void findSmallestYAndSwap(vector<Point>& v){
    Point min = v.at(0);
    int index = 0;
    for(unsigned int i=0; i<v.size(); i++){
        if(v.at(i).y <= min.y){
            min = v.at(i);
            index = i;
        } 
    }
    //Swap the smallest one to the front
    v.at(index) = v.at(0);
    v.at(0) = min;
}

