#include "Point.h"
using namespace std;

Point::Point(double x, double y) : x(x), y(y)
{}
Point::Point(string data)
{
    string temp = "";
    for(int i=0; i<data.size(); i++)
    {
        if(' ' == data[i])
        {
            x = stod(temp);
            //i++;
            temp = "";
        }
        else
        {
            temp += data[i];
        }
    }
    y = stod(temp);
}

void Point::print()
{
    cout << x << ", " << y << endl;
}

QuadEqu::QuadEqu(double a, double b, double c) : a(a), b(b), c(c)
{}

double QuadEqu::distanceAbs(Point& p)
{
    double equY = a*p.x*p.x + b*p.x + c;
    return abs(equY-p.y);
}

void QuadEqu::print()
{
    cout << showpos;
    cout << a << "x^2" << b << "x" << c << endl;
}
