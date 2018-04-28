#include <cstdlib>
#include <cmath>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"

using namespace cs221util;
using namespace std;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
    HSLAPixel* pixel = new HSLAPixel(170, saturation, 0.5);
    return pixel;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    PNG* original = new PNG();
    cout<<"reached line"<<__LINE__<<endl;
    original->readFromFile(inputFile);
    cout<<"reached line"<<__LINE__<<endl;
    unsigned width = original->width();
    cout<<"reached line"<<__LINE__<<endl;
    unsigned height = original->height();
    cout<<"reached line"<<__LINE__<<endl;
    // Create out.png
    PNG* output = setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);
    cout<<height<<endl;
    cout<<width<<endl;
    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output
    for (unsigned y = 1; y < height; y++) {
        for (unsigned x = 1; x < width; x++) {
            //cout<<"reached line"<<__LINE__<<endl;
            // Calculate the pixel difference
            HSLAPixel* prev = original->getPixel(x - 1, y - 1);
            HSLAPixel* curr = original->getPixel(x, y);
            double diff = std::fabs(curr->h - prev->h);
            //cout<<"reached line"<<__LINE__<<endl;        
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel* currOutPixel = (*output).getPixel(x, y);
            //cout<<"reached line"<<__LINE__<<endl;
            if (diff > 20) {
                
                *currOutPixel = *myPixel;
            }
            //cout<<"reached line"<<__LINE__<<endl;
        }
    }
    cout<<"reached line"<<__LINE__<<endl;
    // Save the output file
    output->writeToFile(outputFile);
    cout<<"reached line"<<__LINE__<<endl;
    // Clean up memory
    delete myPixel;
    cout<<"reached line"<<__LINE__<<endl;
    delete output;
    cout<<"reached line"<<__LINE__<<endl;
    delete original;
    cout<<"reached line"<<__LINE__<<endl;
}
