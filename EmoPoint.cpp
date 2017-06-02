#include "EmoPoint.h"

EmoPoint::EmoPoint()
{
    this->x = 0;
    this->y = 0;
}

EmoPoint::EmoPoint(int x, int y): x(x), y(y)
{
}

Point EmoPoint::toPoint()
{
    return Point(this->y, this->x);
}

int EmoPoint::getX()
{
    return this->x;
}

int EmoPoint::getY()
{
    return this->y;
}

double EmoPoint::getDistance(EmoPoint p)
{
    double temp1 =  double(this->x - p.x);
    double temp2 =  double(this->y - p.y);
    return sqrt(temp1*temp1 + temp2*temp2);
}

EmoPoint EmoPoint::afterChange(float a, float b, float c, float d)
{
    return EmoPoint(int(a*x + b*y), int(c*x + d*y));
}

EmoPoint EmoPoint::afterChange(float a, float c, float d)
{
    return EmoPoint(int(a*x + c), int(a*y + d));
}

EmoPoint EmoPoint::afterChange(float a, float b)
{
    return EmoPoint(int(a*x + b), int(a*y + b));
}

float EmoPoint::getSlope(EmoPoint p)
{
    return (p.getY()-y)/(p.getX()-x);
}
