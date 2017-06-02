#ifndef POINT_H
#define POINT_H

#include <math.h>
#include "opencv/highgui.h"

using namespace cv;
using namespace std;

class EmoPoint
{
public:
    EmoPoint();
    EmoPoint(int x, int y);
    int getX();
    int getY();
    double getDistance(EmoPoint p);
    EmoPoint afterChange(float a, float b, float c, float d);
    EmoPoint afterChange(float a, float c, float d);
    EmoPoint afterChange(float a, float b);
    float getSlope(EmoPoint p);
    Point toPoint();
private:
    float x;
    float y;
};

#endif // POINT_H
