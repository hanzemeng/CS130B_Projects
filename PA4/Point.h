#ifndef POINT
#define POINT
#include <cmath>
#include <iostream>
#include <string>

struct Point
{
    Point(double x, double y);
    Point(std::string data);
    void print();
    double x;
    double y;
};

struct QuadEqu
{
    // y = ax^2 + bx + c
    QuadEqu(double a=0, double b=0, double c=0);
    double distanceAbs(Point& p);
    void print();

    double a;
    double b;
    double c;
};

#endif
