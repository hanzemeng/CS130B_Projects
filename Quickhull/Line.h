#ifndef LINE
#define LINE

#include <string>
#include <cmath>
#include <iostream>

const double threshold = 0.0000001; // Floating point comparison tends to be inaccurate
struct Point
{
    Point(double a=0, double b=0);
    Point(std::string data);
    void print();
    double x;
    double y;
    int ID;

    private:
    static int COUNT;
};

struct Line
{
    //y=mx+b
    Line(Point& p1, Point& p2);
    bool isAbove(Point& a);
    bool isBelow(Point& a);
    double distanceFrom(Point& a);
    void print();
    double m;
    double b;
};

#endif
