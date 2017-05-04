#ifndef POINT_H
#define POINT_H

#include <math.h>

using namespace std;

class EmoPoint
{
public:
    EmoPoint();
    EmoPoint(float x, float y);
    int getX();
    int getY();
    double getDistance(EmoPoint p);
    double getDistanceY(EmoPoint p);
    EmoPoint afterChange(float a, float b, float c, float d);
    EmoPoint getCenter(EmoPoint p);
    float getSlope(EmoPoint p);
private:
    float x;
    float y;
};

#endif // POINT_H
