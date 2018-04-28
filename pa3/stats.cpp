#include "stats.h"
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include <utility>
#include <vector>



/* returns the sums of all pixel values across all color channels.
* useful in computing the score of a rectangle
* PA3 function
* @param channel is one of r, g, or b
* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr){
    int firstX = ul.first;
    int firstY = ul.second;
    int secondX = lr.first;
    int secondY = lr.second;

    // cout<<"secondX: "<<secondX<<endl;
    // cout<<"secondY: "<<secondY<<endl;
    // cout<<"SUMRED[x][y]: "<< sumRed[50][50]<<endl;
    if(channel == 'r'){
        if(firstX == 0 && firstY == 0){
            return sumRed[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumRed[secondX][secondY] - sumRed[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumRed[secondX][secondY] - sumRed[firstX-1][secondY];
        }
        else{
            return sumRed[secondX][secondY] - sumRed[firstX-1][secondY] - sumRed[secondX][firstY-1] + sumRed[firstX-1][firstY-1];
        }
    }
    if(channel == 'g'){
        if(firstX == 0 && firstY == 0){
            return sumGreen[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumGreen[secondX][secondY] - sumGreen[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumGreen[secondX][secondY] - sumGreen[firstX-1][secondY];
        }
        else{
            return sumGreen[secondX][secondY] - sumGreen[firstX-1][secondY] - sumGreen[secondX][firstY-1] + sumGreen[firstX-1][firstY-1];
        }
    }
    if(channel == 'b'){
        if(firstX == 0 && firstY == 0){
            return sumBlue[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumBlue[secondX][secondY] - sumBlue[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumBlue[secondX][secondY] - sumBlue[firstX-1][secondY];
        }
        else{
            return sumBlue[secondX][secondY] - sumBlue[firstX-1][secondY] - sumBlue[secondX][firstY-1] + sumBlue[firstX-1][firstY-1];
        }
    }
    return 0;
}

/* returns the sums of squares of all pixel values across all color channels.
* useful in computing the score of a rectangle
* PA3 function
* @param channel is one of r, g, or b
* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr){
    int firstX = ul.first;
    int firstY = ul.second;
    int secondX = lr.first;
    int secondY = lr.second;
    
    if(channel == 'r'){
        if(firstX == 0 && firstY == 0){
            return sumsqRed[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumsqRed[secondX][secondY] - sumsqRed[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumsqRed[secondX][secondY] - sumsqRed[firstX-1][secondY];
        }
        else{
            return sumsqRed[secondX][secondY] - sumsqRed[firstX-1][secondY] - sumsqRed[secondX][firstY-1] + sumsqRed[firstX-1][firstY-1];
        }
    }
    if(channel == 'g'){
        if(firstX == 0 && firstY == 0){
            return sumsqGreen[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumsqGreen[secondX][secondY] - sumsqGreen[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumsqGreen[secondX][secondY] - sumsqGreen[firstX-1][secondY];
        }
        else{
            return sumsqGreen[secondX][secondY] - sumsqGreen[firstX-1][secondY] - sumsqGreen[secondX][firstY-1] + sumsqGreen[firstX-1][firstY-1];
        }
    }
    if(channel == 'b'){
        if(firstX == 0 && firstY == 0){
            return sumsqBlue[secondX][secondY];
        }
        if(firstX == 0 && firstY > 0){
            return sumsqBlue[secondX][secondY] - sumsqBlue[secondX][firstY-1];
        }
        if(firstX > 0 && firstY == 0){
            return sumsqBlue[secondX][secondY] - sumsqBlue[firstX-1][secondY];
        }
        else{
            return sumsqBlue[secondX][secondY] - sumsqBlue[firstX-1][secondY] - sumsqBlue[secondX][firstY-1] + sumsqBlue[firstX-1][firstY-1];
        }
    }
    return 0;
}

// initialize the private vectors so that, for each color,  entry 
// (x,y) is the cumulative sum of the the color values from (0,0)
// to (x,y). Similarly, the sumSq vectors are the cumulative
// sum of squares from (0,0) to (x,y).
stats::stats(PNG & im){
    sumRed.resize(im.width());
    sumGreen.resize(im.width());
    sumBlue.resize(im.width());
    sumsqRed.resize(im.width());
    sumsqGreen.resize(im.width());
    sumsqBlue.resize(im.width());
    for(unsigned int i=0; i<im.width(); i++){
        sumRed[i].resize(im.height());
        sumGreen[i].resize(im.height());
        sumBlue[i].resize(im.height());
        sumsqRed[i].resize(im.height());
        sumsqGreen[i].resize(im.height());
        sumsqBlue[i].resize(im.height());
    }

    unsigned int accuXR = 0;
    unsigned int accuXG = 0;
    unsigned int accuXB = 0;
    unsigned int accuSqXR = 0;
    unsigned int accuSqXG = 0;
    unsigned int accuSqXB = 0; 

    for(unsigned int x=0; x<im.width(); x++){
        RGBAPixel* currPixel = im.getPixel(x,0);
        accuXR += currPixel->r;
        accuXG += currPixel->g;
        accuXB += currPixel->b;
        accuSqXR += (currPixel->r)*(currPixel->r);
        accuSqXG += (currPixel->g)*(currPixel->g);
        accuSqXB += (currPixel->b)*(currPixel->b);
        sumRed[x][0] = accuXR;
        sumGreen[x][0] = accuXG;
        sumBlue[x][0] = accuXB;
        sumsqRed[x][0] = accuSqXR;
        sumsqGreen[x][0] = accuSqXG;
        sumsqBlue[x][0] = accuSqXB;
    }
    unsigned int accuYR = 0;
    unsigned int accuYG = 0;
    unsigned int accuYB = 0;
    unsigned int accuSqYR = 0;
    unsigned int accuSqYG = 0;
    unsigned int accuSqYB = 0; 

    for(unsigned int y=0; y<im.height(); y++){
        RGBAPixel* currPixel = im.getPixel(0,y);
        accuYR += currPixel->r;
        accuYG += currPixel->g;
        accuYB += currPixel->b;
        accuSqYR += (currPixel->r)*(currPixel->r);
        accuSqYG += (currPixel->g)*(currPixel->g);
        accuSqYB += (currPixel->b)*(currPixel->b);
        sumRed[0][y] = accuYR;
        sumGreen[0][y] = accuYG;
        sumBlue[0][y] = accuYB;
        sumsqRed[0][y] = accuSqYR;
        sumsqGreen[0][y] = accuSqYG;
        sumsqBlue[0][y] = accuSqYB;
    }
    for(unsigned int x=1; x<im.width(); x++){
        for(unsigned int y=1; y<im.height(); y++){
            RGBAPixel* currPixel = im.getPixel(x,y);
            sumRed[x][y] = currPixel->r + sumRed[x-1][y] + sumRed[x][y-1] - sumRed[x-1][y-1];
            sumGreen[x][y] = currPixel->g + sumGreen[x-1][y] + sumGreen[x][y-1] - sumGreen[x-1][y-1];
            sumBlue[x][y] = currPixel->b+ sumBlue[x-1][y] + sumBlue[x][y-1] - sumBlue[x-1][y-1];
            sumsqRed[x][y] = (currPixel->r * currPixel->r) + sumsqRed[x-1][y] + sumsqRed[x][y-1] - sumsqRed[x-1][y-1];
            sumsqGreen[x][y] = (currPixel->g * currPixel->g) + sumsqGreen[x-1][y] + sumsqGreen[x][y-1] - sumsqGreen[x-1][y-1];
            sumsqBlue[x][y] = (currPixel->b * currPixel->b)+sumsqBlue[x-1][y] + sumsqBlue[x][y-1] - sumsqBlue[x-1][y-1];
            // cout<<"X: "<<x<<endl;
            // cout<<"Y: "<<y<<endl;
        }
    }
    // cout<<"WIDTH: "<<im.width()<<endl;
    // cout<<"HEIGHT: "<<im.height()<<endl;

    // for(unsigned int x=0; x< im.width(); x++){
    //     for(unsigned int y=0; y<im.height(); y++){
    //             unsigned int accuR = 0;
    //             unsigned int accuG = 0;
    //             unsigned int accuB = 0;
    //             unsigned int accuSqR = 0;
    //             unsigned int accuSqG = 0;
    //             unsigned int accuSqB = 0;
    //         for(unsigned int xx=0; xx<=x; xx++){
    //             for(unsigned int yy=0; yy<=y; yy++){
    //                 RGBAPixel* currPixel = im.getPixel(xx,yy);
    //                 accuR += currPixel->r;
    //                 accuG += currPixel->g;
    //                 accuB += currPixel->b;
    //                 accuSqR += currPixel->r * currPixel->r;
    //                 accuSqG += currPixel->g * currPixel->g;
    //                 accuSqB += currPixel->b * currPixel->b;
    //             }
    //         }
    //         sumRed[x][y] = accuR;
    //         sumGreen[x][y] = accuG;
    //         sumBlue[x][y] = accuB;
    //         sumsqRed[x][y] = accuSqR;
    //         sumsqGreen[x][y] = accuSqG;
    //         sumsqBlue[x][y] = accuSqB;
    //         cout<<"accuR: "<<accuR<<endl;
    //         cout<<"accuG: "<<accuG<<endl;
    //         cout<<"accuB: "<<accuB<<endl;
    //         cout<<"accuSqR: "<<accuSqR<<endl;
    //         cout<<"accuSqG: "<<accuSqG<<endl;
    //         cout<<"accuSqB: "<<accuSqB<<endl;

    //     }
    // }
}

// given a rectangle, compute its sum of squared deviations from 
    // mean, over all color channels. Will be used to make split when
// building tree.
/* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::getScore(pair<int,int> ul, pair<int,int> lr){
    // cout<<"FIRST:"<<ul.first<<","<<ul.second<<endl;
    // cout<<"SECOND:"<<lr.first<<","<<lr.second<<endl;
    long area = rectArea(ul, lr);
    //cout<<"AREA: "<<area<<endl;
    long redChannel = getSumSq('r', ul, lr) - (getSum('r', ul, lr)*getSum('r', ul, lr))/area;
    long greenChannel = getSumSq('g', ul, lr) - (getSum('g', ul, lr)*getSum('g', ul, lr))/area;
    long blueChannel = getSumSq('b', ul, lr) - (getSum('b', ul, lr)*getSum('b', ul, lr))/area;
    return (redChannel + greenChannel + blueChannel);
}

// given a rectangle, return the average color value over the 
// rectangle as a pixel.
/* Each color component of the pixel is the average value of that 
* component over the rectangle.
* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle */
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr){

    long area = rectArea(ul, lr);
    int r = getSum('r', ul, lr)/area;
    int g = getSum('g', ul, lr)/area;
    int b = getSum('b', ul, lr)/area;
    return RGBAPixel(r, g, b);
}   

// given a rectangle, return the number of pixels in the rectangle
/* @param ul is (x,y) of the upper left corner of the rectangle 
* @param lr is (x,y) of the lower right corner of the rectangle */
long stats::rectArea(pair<int,int> ul, pair<int,int> lr){
    return (1+lr.first-ul.first) * (1+lr.second-ul.second);
}