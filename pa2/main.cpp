// File:        main.cpp
// Author:      gctien
// Date:        2018-02-15
// Description: Partial test of PA2 classes
//              Reads Point data from external files
//              Produces PNG images of the point sets
//              and their convex hulls and intersections

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//#include "cs221util/RGB_HSL.h"
#include "cs221util/HSLAPixel.h"
#include "cs221util/PNG.h"
#include "convexhull.h"
#include "convexintersection.h"
#include "drawingio.h"
#include "point.h"
#include "stack.h"

using namespace cs221util;
using namespace std;

// forward declarations

//Prints elements in vector
void printVector(vector<Point> &v);

// returns a Point representing 20 pixels more than
// the maximum x and y coordinates found in the provided
// Point vector
// Used for determining output PNG dimensions
Point getDimension(vector<Point>& v);

// manages the convex hull generation
// infilename: input file with Point data
// outfilename: name of output PNG
void convexHullFromFile(string infilename, string outfilename);

// manages multiple convex hull and intersection generation
// infile1: input file with Point data, set 1
// infile2: input file with Point data, set 2
// outfilename: name of output PNG
void intersectionFromFile(string infile1, string infile2, string outfilename);

// initializes a PNG to all white pixels
void initializePNG(PNG& im);

int main()
{
  convexHullFromFile("points1.txt", "out-hull_1.png");
  convexHullFromFile("points2.txt", "out-hull_2.png");
  convexHullFromFile("points3.txt", "out-hull_3.png");

  cout << "Convex hulls produced." << endl;
  cout <<"_______________________________" <<endl;
  intersectionFromFile("dept_1a.txt", "dept_1b.txt", "out-intersection_1.png");
  intersectionFromFile("dept_2a.txt", "dept_2b.txt", "out-intersection_2.png");
  intersectionFromFile("dept_3a.txt", "dept_3b.txt", "out-intersection_3.png");

  cout << "Convex intersections produced." << endl;
  cout <<"_______________________________" <<endl;
  //FOR STACK DEBUGGING
  /*Stack s;
    s.push(Point(0,0));
    s.push(Point(1,1));
    cout<<s.size()<<endl;
    cout<< s.peek().x << " " << s.peek().y<<endl;
    cout<<s.size()<<endl;
    Point p = s.pop();
    cout<<p.x<<" "<<p.y<<endl;
    cout<<s.size()<<endl;
    cout<< s.peek().x << " " << s.peek().y<<endl;
    cout<<s.size()<<endl;
    s.pop();
    cout<<s.isEmpty()<<endl;
    cout<<s.size()<<endl;
    cout<< s.peek().x << " " << s.peek().y<<endl;
    Point p1 = s.pop();
    cout<<p1.x<<" "<<p1.y<<endl;
  */

  //For convexhull debugging
  vector<Point> v;
  v.push_back(Point(-1,1));
  v.push_back(Point(-1,2));
  v.push_back(Point(-1,3));
  v.push_back(Point(1,7));
  v.push_back(Point(1,9));
  v.push_back(Point(1,8));
  v.push_back(Point(1,2));
  v.push_back(Point(1,3));
  v.push_back(Point(1,1));
  v.push_back(Point(0,0));
  
  /*
  findSmallestYAndSwap(v);
  cout<<"smallest y point: x: "<<v.at(0).x<<" y: "<<v.at(0).y<<endl;
  cout<<"original y point at 0: x: "<<v.at(5).x<<" y: "<<v.at(5).y<<endl;
  cout <<"_______________________________" <<endl;
  cout <<getAngle(v.at(0), v.at(1))<<endl;
  */
  
  /*
  sortByAngle(v);
  printVector(v);

  cout<<"Counter Clockwise? "<<ccw(Point (0,0), Point(1,0), Point(1,1))<<endl;
  */
  cout<<"inside? "<<inside(Point(3,0), Point(2,2),Point(1,0))<<endl;
  Point P = computeIntersection(Point(0,0), Point(1,1), Point(-5,-6), Point(-6,10));
  cout<<"intersection: "<<P.x<<P.y<<endl;

  //test cases of files
  intersectionFromFile("mytest2.txt", "mytest1.txt", "mytest.png");
  intersectionFromFile("testsamepoly1.txt", "testsamepoly2.txt", "samepoly.png");
  convexHullFromFile("singleline.txt", "singlelineHull.png");
  convexHullFromFile("2points.txt", "2points.png");
  return 0;
}

// returns a Point representing 20 pixels more than
// the maximum x and y coordinates found in the provided
// Point vector
// Used for determining output PNG dimensions
Point getDimension(vector<Point>& v)
{
  double maxx = 0;
  double maxy = 0;
  for (unsigned int i = 0; i < v.size(); i++)
  {
    if (v[i].x > maxx)
      maxx = v[i].x;
    if (v[i].y > maxy)
      maxy = v[i].y;
  }
  return Point(maxx + 20, maxy + 20);
}

// manages the convex hull generation
// infilename: input file with Point data
// outfilename: name of output PNG
void convexHullFromFile(string infilename, string outfilename)
{
  vector<Point> v = readPointsFromFile(infilename);
  Point dims = getDimension(v);
  unsigned int dimx = (unsigned int)dims.x;
  unsigned int dimy = (unsigned int)dims.y;
  // Create a blank white PNG
  PNG base(dimx, dimy);
  initializePNG(base);

  // draw the original points
  drawPoints(base, HSLAPixel(0, 0, 0, 1), v);

  // get the convex hull
  vector<Point> v_hull = getConvexHull(v);
  // draw the convex hull
  drawPolygon(base, HSLAPixel(0, 1, 0.5, 1), v_hull);

  base.writeToFile(outfilename);
}

// manages multiple convex hull and intersection generation
// infile1: input file with Point data, set 1
// infile2: input file with Point data, set 2
// outfilename: name of output PNG
void intersectionFromFile(string infile1, string infile2, string outfilename)
{
  vector<Point> v1 = readPointsFromFile(infile1);
  Point dims1 = getDimension(v1);
  vector<Point> v2 = readPointsFromFile(infile2);
  Point dims2 = getDimension(v2);
  unsigned int dimx = (unsigned int) max(dims1.x, dims2.x);
  unsigned int dimy = (unsigned int) max(dims1.y, dims2.y);
  // Create a blank white PNG
  PNG base(dimx, dimy);
  initializePNG(base);

  // draw the original points
  drawPoints(base, HSLAPixel(0, 1, 0.25, 1), v1);
  drawPoints(base, HSLAPixel(240, 1, 0.25, 1), v2);

  // get the convex hull
  vector<Point> v_hull_1 = getConvexHull(v1);
  vector<Point> v_hull_2 = getConvexHull(v2);
  // draw the convex hull
  drawPolygon(base, HSLAPixel(0, 1, 0.5, 1), v_hull_1);
  drawPolygon(base, HSLAPixel(240, 1, 0.5, 1), v_hull_2);

  // get the intersection
  vector<Point> hull_intersection = getConvexIntersection(v_hull_1, v_hull_2);
  // draw the intersection
  drawPolygon(base, HSLAPixel(120, 1, 0.5, 1), hull_intersection);

  base.writeToFile(outfilename);
}

// initializes a PNG to all white pixels
void initializePNG(PNG& im)
{
  HSLAPixel* px;
  for (unsigned int x = 0; x < im.width(); x++)
  {
    for (unsigned int y = 0; y < im.height(); y++)
    {
      px = im.getPixel(x, y);
      px->h = 0;
      px->s = 0;
      px->l = 1;
      px->a = 1;
    }
  }
}

void printVector(vector<Point> &v){
  for(int i=0; i<v.size(); i++){
    cout<<"X: "<<v.at(i).x<<" Y:"<<v.at(i).y<<endl;
  }
}