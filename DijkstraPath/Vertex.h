#ifndef VERTEX
#define VERTEX

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

struct Vertex
{
    Vertex();
    Vertex(double, double);
    Vertex(std::string);
    void addNeighbor(Vertex*);
    double distanceFrom(Vertex*) const;
    void print() const;
    std::string printPath() const;
    std::string printPath(Vertex*) const;


    int ID;
    double x;
    double y;
    std::vector<Vertex*> neighbors;
    
    double dist; // record the shortest distance to self
    Vertex* prev; // record the previous vertex in the shortest path to self
    static int COUNT; // use to set up ID
};

#endif
