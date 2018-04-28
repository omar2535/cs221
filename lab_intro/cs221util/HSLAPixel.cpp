#include "HSLAPixel.h"

namespace cs221util {
    HSLAPixel::HSLAPixel(){
        h = 0.0;
        s = 0.0;
        l = 1.0;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hu,double sa,double lu){
        h = hu;
        s = sa;
        l = lu;
    }
    HSLAPixel::HSLAPixel(double hu,double sa,double lu,double al){
        h = hu;
        s = sa;
        l = lu;
        a = al;
    }

}