#include "Vertex.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

int VERTEX_COUNT; // number of vertices
vector<Vertex> vertices;  // vertex objects

void setUp(string path);
void DijkstraPath();

int main(int argc, char** argv)
{
    ofstream outputFile(argv[2]);
    setUp(argv[1]);
    DijkstraPath();

    for(int i=1; i<VERTEX_COUNT; i++)
    {
        outputFile << vertices[i].printPath();
    }
    outputFile.close();
    return 0;
}

struct comp
{
    bool operator()(const Vertex* lhs, const Vertex* rhs) const
    {
        if(lhs->dist == rhs->dist) // if distance is the same, then sort by ID
        {
            return lhs->ID < rhs->ID;
        }
        return lhs->dist < rhs->dist; // sort by distance
    }
};

void DijkstraPath()
{
    set<Vertex*, comp> uncheckedVertices;
    vertices[0].dist = 0;
    for(int i=0; i<VERTEX_COUNT; i++)
    {
        uncheckedVertices.insert(&vertices[i]);
    }

    while(!uncheckedVertices.empty())
    {
        Vertex* currentVertex = *uncheckedVertices.begin(); // first element in the set always has the shortest distance
        uncheckedVertices.erase(uncheckedVertices.begin());

        for(Vertex* n : currentVertex->neighbors)
        {
            double newDist = currentVertex->dist + currentVertex->distanceFrom(n);
            if(n->dist > newDist)
            {
                uncheckedVertices.erase(n); // set doesn't have a way to update an element 
                n->dist = newDist;
                n->prev = currentVertex;
                uncheckedVertices.insert(n); // so the alternative is to remove the old element and insert the new element
            }
        }
    }
}

void setUp(string path)
{
    fstream inFile;
    inFile.open(path);
    string temp;
    getline(inFile, temp);
    int count = stoi(temp);
    VERTEX_COUNT = count;
    vertices.reserve(VERTEX_COUNT);
    while(count-- > 0)
    {
        getline(inFile, temp);
        vertices.push_back(Vertex(temp));
    }
    getline(inFile, temp);
    count = stoi(temp);

    if(0 == count)
    {
        for(int i=0; i<VERTEX_COUNT; i++)
        {
            for(int j=0; j<VERTEX_COUNT; j++)
            {
                if(i==j)
                {
                    continue;
                }
                vertices[i].addNeighbor(&vertices[j]);
                vertices[j].addNeighbor(&vertices[i]);
            }
        }
    }

    while(count-- > 0)
    {
        getline(inFile, temp);
        temp += " ";
        string index = "";
        int v1 = -1;
        int v2 = -1;
        for(char c : temp)
        {
            if(' ' != c)
            {
                index += c;
            }
            else
            {
                if(-1 == v1)
                {
                    v1 = stoi(index);
                    index = "";
                }
                else
                {
                    v2 = stoi(index);
                }
            }
        }
        vertices[v1].addNeighbor(&vertices[v2]);
        vertices[v2].addNeighbor(&vertices[v1]);
    }
    inFile.close();
}
