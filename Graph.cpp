#include "Graph.h"
#include <iostream>

using namespace std;

Edge::Edge(int head, int tail)
{
    this->headVertex = head;
    this->tailVertex = tail;
}

void Edge::display()
{
    cout << this->tailVertex << " -- " << this->headVertex << endl;

    return;
}

Graph::Graph(int nVertices, int relationShips[][EDGE_RELATION_LEN], int nEdges)
{
    this->nVertices = nVertices;
    this->nEdges = nEdges;

    int tailVertex, i, edgeIndex = 0;
    int head, tail;
    Edge *tmpEdge;

    for (tailVertex = 1; tailVertex <= nVertices; tailVertex++)
    {
        (this->vertexPtrs)[tailVertex - 1] = edgeIndex;
        for (i = 0; i < nEdges; i++)
        {
            head = relationShips[i][1];
            tail = relationShips[i][0];

            if (tail == tailVertex)
            {
                tmpEdge = new Edge(head, tail);
                edges[edgeIndex] = tmpEdge;
                edgeIndex += 1;
            }
        }
    }
}

void Graph::displayEdgeList()
{
    cout << "Edge list:\n";
    int i;

    for (i = 0; i < this->nEdges; i++)
    {
        (this->edges)[i]->display();
    }

    return;
}

void Graph::displayVertextPtrs()
{
    cout << "Vertex Pointers:\n";

    int i;
    for (i = 0; i < this->nVertices; i++)
    {
        cout << i + 1 << " --> " << (this->vertexPtrs)[i] << endl;
    }

    return;
}

void Graph::display()
{
    this->displayEdgeList();
    this->displayVertextPtrs();

    return;
}
