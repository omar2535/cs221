#ifndef CS221UTIL_HSLAPIXEL_H
#define CS221UTIL_HSLAPIXEL_H

namespace cs221util{

    class HSLAPixel {
        public:
        double h;
        double s;
        double l;
        double a;
            HSLAPixel();
            HSLAPixel(double h, double s, double l);
            HSLAPixel(double h, double s, double l, double a);
    };
}

#endif