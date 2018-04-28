#include "block.h"

int Block::width() const{
   return data.size(); //Width
}
int Block::height() const{
   return data[0].size(); //Height
}

void Block::render(PNG & im, int upLeftX, int upLeftY) const {

    for(unsigned x=upLeftX; x<upLeftX + width(); x++){
       for(unsigned y=upLeftY; y<upLeftY + height(); y++){
           HSLAPixel *currentPixel = im.getPixel(x,y);
           *currentPixel = data.at(x-upLeftX).at(y-upLeftY);
       }
   }
}

void Block::build(PNG & im, int upLeftX, int upLeftY, int cols, int rows) {
    for(int x=0; x<cols; x++){
        vector<HSLAPixel> colPixels;
        for(int y=0; y<rows; y++){
            HSLAPixel *currentPixel = im.getPixel(x+upLeftX, y+upLeftY);
            colPixels.push_back(*currentPixel);
        }
        data.push_back(colPixels);
    }
}
