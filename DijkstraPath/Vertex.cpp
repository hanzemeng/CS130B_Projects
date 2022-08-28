#include "Vertex.h"
using namespace std;

int Vertex::COUNT = 0;

Vertex::Vertex() : ID(COUNT++), x(0), y(0), dist(INFINITY), prev(nullptr)
{}
Vertex::Vertex(double x, double y) : ID(COUNT++), x(x), y(y), dist(INFINITY), prev(nullptr)
{}
Vertex::Vertex(string input) : ID(COUNT++), dist(INFINITY), prev(nullptr)
{
    string temp = "";
    for(char c : input)
    {
        if(' ' != c)
        {
            temp += c;
        }
        else
        {
            x = stod(temp);
            temp = "";
        }
    }
    y = stod(temp);
}
void Vertex::addNeighbor(Vertex* a)
{
    neighbors.push_back(a);
}
double Vertex::distanceFrom(Vertex* a) const
{
    return sqrt((a->x-x)*(a->x-x) + (a->y-y)*(a->y-y));
}

void Vertex::print() const
{
    /*
    cout << ID << ": " << x << ", " << y << ". Nei: ";
    for(Vertex* n : neighbors)
    {
        cout << n->ID << ", ";
    }
    */
}

string Vertex::printPath() const
{
    string res = printPath(prev);
    res += to_string(ID);
    res += "\n";
    return res;
}
string Vertex::printPath(Vertex* current) const
{
    if(!current)
    {
        return "";
    }
    string res = printPath(current->prev);
    res += to_string(current->ID);
    res += ", ";
    return res;
}
