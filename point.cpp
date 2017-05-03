#include "point.h"

EmoPoint::EmoPoint()
{
    this->x = 0;
    this->y = 0;
}

EmoPoint::EmoPoint(float x, float y): x(x), y(y)
{
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

EmoPoint EmoPoint::getCenter(EmoPoint p)
{
    return EmoPoint((this->getX()+p.getX())/2, (this->getY()+p.getY())/2);
}

EmoPoint EmoPoint::afterChange(float a, float b, float c, float d)
{
    return EmoPoint(a*x + b*y, c*x + d*y);
}

float EmoPoint::getSlope(EmoPoint p)
{
    return (p.getY()-y)/(p.getX()-x);
}
