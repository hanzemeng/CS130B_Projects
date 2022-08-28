#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <cmath>
#include <algorithm>
#include <fstream>

#include "Point.h"
using namespace std;
// home-made 3 by 3 matrix solver using Cramer's rule
struct DetIsZero{};
double findDet(vector<vector<double>>& M);
vector<double> solveY(vector<vector<double>>& M, vector<double>& y);

void setUp(char* path);
void randomFit();
void leastSqrFit();

vector<Point> points;
double bestMedian = 666666;
QuadEqu bestEqu;
QuadEqu resEqu;

int main(int argc, char** argv)
{
    setUp(argv[1]);
    /* remove the comment if you want to see the points
    for(Point& p : points)
    {
        p.print();
    }
    */
    randomFit();
    //bestEqu.print(); // remove the comment for the equation produced by the random algorithm
    leastSqrFit();
    resEqu.print();

    return 0;
}

void setUp(char* path)
{
    fstream inFile;
    inFile.open(path);
    string temp;
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
}

void randomFit()
{
    double goalPercent = 0.99;
    double badPercent = 0.3;
    double base = 1 - pow(1-badPercent, 3);
    int sampleSize = ceil(log(1-goalPercent)/log(base));

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, points.size()-1);
    
    while(sampleSize-->0)
    {
        set<int> selectIndex;
        while(3 != selectIndex.size())
        {
            selectIndex.insert(distrib(gen));
        }

        vector<vector<double>> A(3, vector<double>(3));
        vector<double> y(3);
        int count = 0;
        for(int i : selectIndex)
        {
            A[count][0] = points[i].x*points[i].x;
            A[count][1] = points[i].x;
            A[count][2] = 1;
            y[count] = points[i].y;
            count++;
        }
        vector<double> coef;
        try
        {
            coef = solveY(A, y);
        }
        catch(DetIsZero e)
        {
            sampleSize++;
            continue;
        }
        QuadEqu newEqu{coef[0], coef[1], coef[2]};
        vector<double> errors(points.size());
        for(int i=0; i<points.size(); i++)
        {
            errors[i] = newEqu.distanceAbs(points[i]);
        }
        sort(errors.begin(), errors.end());
        double newMedian = errors[(3+errors.size())/2]; // +3 because 3 points are used to find the equation
        if(newMedian < bestMedian)
        {
            bestMedian = newMedian;
            bestEqu = newEqu;
        }
    }
}

void leastSqrFit()
{
    vector<Point> goodPoints;
    for(Point& p : points)
    {
        if(bestEqu.distanceAbs(p) < bestMedian)
        {
            goodPoints.push_back(p);
        }
    }
    vector<vector<double>> A(3, vector<double>(3));
    vector<double> y(3);

    double temp = goodPoints.size();
    A[2][2] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += p.x;
    }
    A[2][1] = A[1][2] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += p.x*p.x;
    }
    A[2][0] = A[0][2] = A[1][1] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += pow(p.x,3);
    }
    A[1][0] = A[0][1] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += pow(p.x,4);
    }
    A[0][0] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += p.y;
    }
    y[2] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += p.x*p.y;
    }
    y[1] = temp;
    temp = 0;
    for(Point& p : goodPoints)
    {
        temp += p.x*p.x*p.y;
    }
    y[0] = temp;
    
    vector<double> res;
    try
    {
        res = solveY(A, y);
        resEqu.a = res[0];
        resEqu.b = res[1];
        resEqu.c = res[2];
    }
    catch(DetIsZero e)
    {
        resEqu = bestEqu;
    }
}

double findDet(vector<vector<double>>& M)
{
    double a = M[0][0]*M[1][1]*M[2][2]+M[0][1]*M[1][2]*M[2][0]+M[0][2]*M[1][0]*M[2][1];
    double b = M[0][2]*M[1][1]*M[2][0]+M[0][0]*M[1][2]*M[2][1]+M[0][1]*M[1][0]*M[2][2];
    return a-b;
}
vector<double> solveY(vector<vector<double>>& M, vector<double>& y)
{
    vector<double> res;
    double oriDet = findDet(M);
    if(0 == oriDet)
    {
        throw DetIsZero{};
    }
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            swap(M[j][i], y[j]);
        }
        res.push_back(findDet(M)/oriDet);
        for(int j=0; j<3; j++)
        {
            swap(M[j][i], y[j]);
        }
    }
    return res;
}
