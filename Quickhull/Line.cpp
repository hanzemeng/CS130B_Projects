#include "Line.h"
using namespace std;

int Point::COUNT = -1; //for indexing each point

Point::Point(double a, double b)
{
    x = a;
    y = b;
    ID = COUNT++;
}
Point::Point(string data)
{
    string temp = "";
    for(int i=0; i<data.size(); i++)
    {
        if(',' == data[i])
        {
            x = stod(temp);
            i++;
            temp = "";
        }
        else
        {
            temp += data[i];
        }
    }
    y = stod(temp);
    ID = COUNT++;
}
void Point::print()
{
    //cout << "(" << x << ", " << y << ")" << endl;
    cout << ID << ", " << x << ", " << y <<  endl;
}


Line::Line(Point& p1, Point& p2)
{
    if(abs(p1.x-p2.x)<threshold)
    {
        m = INFINITY;
        b = p1.x;
    }
    else
    {
        m = (p1.y-p2.y)/(p1.x-p2.x);
        b = p1.y-m*p1.x;
    }
}
bool Line::isAbove(Point& a)
{
    if(INFINITY == m)
    {
        return false;
    }
    double lineY = m*a.x+b;
    if(abs(lineY-a.y)<threshold)
    {
        return false;
    }
    return a.y>lineY;
}
bool Line::isBelow(Point& a)
{
    if(INFINITY == m)
    {
        return false;
    }
    double lineY = m*a.x+b;
    if(abs(lineY-a.y)<threshold)
    {
        return false;
    }
    return a.y<lineY;
}
double Line::distanceFrom(Point& a)
{
    if(INFINITY == m)
    {
        return abs(a.x-b);
    }
    double top = abs(m*a.x-a.y+b);
    double bottom = sqrt(m*m+1);
    return top/bottom;
}
void Line::print()
{
    cout << m << "x+" << b << endl;
}
