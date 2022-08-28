#include <iostream>
#include <fstream>
#include <iomanip> 
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
using namespace std;

#include "Line.h"

vector<Point> res;
vector<Point> aboveLine;
vector<Point> belowLine;
Point center;

void setUp(string path); // read in data and draw the initial line
void solveAbove(vector<Point>& points, Point left, Point right); // solve for all points above the initial line
void solveBelow(vector<Point>& points, Point left, Point right); // solve for all points below the initial line
void sortAndRemoveCollinearAndPrint(); // modify the result and print it

int main(int argc, char** argv)
{
    setUp(argv[1]);
    solveAbove(aboveLine, res[0], res[1]);
    solveBelow(belowLine, res[0], res[1]);
    sortAndRemoveCollinearAndPrint();
    return 0;
}

void setUp(string path)
{
    fstream inFile;
    inFile.open(path);
    string temp;
    getline(inFile, temp);
    vector<Point> points;
    points.reserve(stoi(temp));
    aboveLine.reserve(stoi(temp)*3/4);
    belowLine.reserve(stoi(temp)*3/4);

    while(!inFile.eof())
    {
        getline(inFile, temp);
        if("" == temp)
        {
            break;
        }
        points.push_back(Point(temp));
    }
    inFile.close();

    int leftestPoint = 0;
    int rightestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(points[i].x<points[leftestPoint].x)
        {
            leftestPoint = i;
        }
        if(points[i].x>points[rightestPoint].x)
        {
            rightestPoint = i;
        }
    }
    res.push_back(move(points[leftestPoint]));
    res.push_back(move(points[rightestPoint]));

    Line middleLine{points[leftestPoint], points[rightestPoint]};
    for(int i=0; i<points.size(); i++)
    {
        if(i == leftestPoint || i == rightestPoint)
        {
            continue;
        }
        if(middleLine.isAbove(points[i]))
        {
            aboveLine.push_back(move(points[i]));
        }
        else if (middleLine.isBelow(points[i]))
        {
            belowLine.push_back(move(points[i]));
        }
    }
}

void solveAbove(vector<Point>& points, Point left, Point right)
{
    if(points.empty())
    {
        return;
    }
    Line l{left, right};
    int furthestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(l.distanceFrom(points[furthestPoint]) < l.distanceFrom(points[i]))
        {
            furthestPoint = i;
        }
    }
    res.push_back(points[furthestPoint]);
    Line l1{left, points[furthestPoint]};
    Line l2{points[furthestPoint], right};
    vector<Point> points1;
    vector<Point> points2;

    for(int i=0; i<points.size(); i++)
    {
        if(furthestPoint == i)
        {
            continue;
        }
        if(l1.isAbove(points[i]))
        {
            points1.push_back(move(points[i]));
        }
        else if(l2.isAbove(points[i]))
        {
            points2.push_back(move(points[i]));
        }
    }

    solveAbove(points1, left, points[furthestPoint]);
    solveAbove(points2, points[furthestPoint], right);
}
void solveBelow(vector<Point>& points, Point left, Point right)
{
    if(points.empty())
    {
        return;
    }
    Line l{left, right};
    int furthestPoint = 0;
    for(int i=1; i<points.size(); i++)
    {
        if(l.distanceFrom(points[furthestPoint]) < l.distanceFrom(points[i]))
        {
            furthestPoint = i;
        }
    }
    res.push_back(points[furthestPoint]);
    Line l1{left, points[furthestPoint]};
    Line l2{points[furthestPoint], right};
    vector<Point> points1;
    vector<Point> points2;

    for(int i=0; i<points.size(); i++)
    {
        if(furthestPoint == i)
        {
            continue;
        }
        if(l1.isBelow(points[i]))
        {
            points1.push_back(move(points[i]));
        }
        else if(l2.isBelow(points[i]))
        {
            points2.push_back(move(points[i]));
        }
    }

    solveBelow(points1, left, points[furthestPoint]);
    solveBelow(points2, points[furthestPoint], right);
}

struct comp 
{
public:
    bool operator()(Point& a, Point& b)
    {
        double aAngle = atan((a.y-center.y)/(a.x-center.x));
        if(a.x-center.x<0)
        {
            aAngle += M_PI;
        }
        double bAngle = atan((b.y-center.y)/(b.x-center.x));
        if(b.x-center.x<0)
        {
            bAngle += M_PI;
        }
        return aAngle<bAngle;
    }
};
void sortAndRemoveCollinearAndPrint()
{
    double tempX = 0;
    double tempY = 0;
    for(Point& p : res)
    {
        tempX += p.x;
        tempY += p.y;
    }
    center.x = tempX/((double)res.size());
    center.y = tempY/((double)res.size());
    sort(res.begin(), res.end(), comp());

    int startIndex = 0;
    int endIndex = 2;
    while(endIndex<res.size())
    {
        Line l{res[startIndex], res[endIndex]};
        if(l.distanceFrom(res[endIndex-1]) < threshold)
        {
            res.erase(res.begin()+endIndex-1);
        }
        else
        {
            startIndex++;
            endIndex++;
        }
    }
    if(res.size()>3)
    {
        Line l{res[1], res.back()};
        if(l.distanceFrom(res[0]) < threshold)
        {
            res.erase(res.begin());
        }
    }

    cout << fixed << setprecision(5);
    cout << res.size() << endl;
    startIndex = 0;
    for(int i=1; i<res.size(); i++)
    {
        if(res[startIndex].y > res[i].y)
        {
            startIndex = i;
        }
        else if(res[startIndex].y == res[i].y)
        {
            if(res[startIndex].x > res[i].x)
            {
                startIndex = i;
            }
        }
    }
    endIndex = startIndex-1;
    if(endIndex<0)
    {
        endIndex += res.size();
    }
    while(startIndex != endIndex)
    {
        res[startIndex].print();
        startIndex++;
        startIndex %= res.size();
    }
    res[endIndex].print();
}
