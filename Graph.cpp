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
    cout << this->tailVertex << " --> " << this->headVertex << endl;

    return;
}

Graph::Graph(int nVertices, int relationShips[][EDGE_RELATION_LEN], int nEdges)
{
    this->nVertices = nVertices;
    this->nEdges = nEdges;
    this->edgeListLength = 0;

    int tailVertex, i, edgeIndex = 0;
    int head, tail;
    Edge *tmpEdge;

    for (tailVertex = 1; tailVertex <= nVertices; tailVertex++)
    {
        (this->vertexPtrs)[tailVertex - 1] = edgeIndex;
        // cout << "Tail Vertex: " << tailVertex << endl;
        for (i = 0; i < nEdges; i++)
        {
            head = relationShips[i][1];
            tail = relationShips[i][0];

            // printf("Head: %d, Tail: %d\n", head, tail);

            if (tail == tailVertex)
            {
                // printf("\tConnected! %d\n", head);
                tmpEdge = new Edge(head, tail);
                edges[edgeIndex] = tmpEdge;
                edgeIndex += 1;
            }

            if (head == tailVertex)
            {
                // printf("\tConnected! %d\n", tail);
                tmpEdge = new Edge(tail, head);
                edges[edgeIndex] = tmpEdge;
                edgeIndex += 1;
            }
        }
    }

    this->edgeListLength = edgeIndex;
    // A dummy slot for nVertices+1 vertex.
    this->vertexPtrs[nVertices] = edgeIndex;
}

void Graph::displayEdgeList()
{
    cout << "Edge list:\n";
    int i;

    for (i = 0; i < this->edgeListLength; i++)
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

int *Graph::getNeighboursOf(int vertex)
{
    int noOfNeighbours, ptrToEdgelist, i, j;

    // noOfNeighbours(1) = vertexPtrs[2] - vertextPtrs[1]
    noOfNeighbours = this->vertexPtrs[vertex] - this->vertexPtrs[vertex - 1];
    ptrToEdgelist = this->vertexPtrs[vertex - 1];

    printf("Vertex: %d, no.neighbours: %d, ptrToEdgelist: %d\n", vertex, noOfNeighbours, ptrToEdgelist);

    int *neighbors = new int[noOfNeighbours];

    j = 0;
    cout << "Neighbours of " << vertex << " are: \n(";
    for (i = ptrToEdgelist; i < ptrToEdgelist + noOfNeighbours; i++)
    {
        cout << (this->edges)[i]->headVertex << ", ";
        neighbors[j] = (this->edges)[i]->headVertex;
    }
    cout << "\b\b)\n";

    return neighbors;
}
