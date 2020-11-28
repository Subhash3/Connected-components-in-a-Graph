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

Graph::Graph(int nVertices, int relationShips[][EDGE_RELATION_LEN], int nEdges, bool isDirected)
{
    this->nVertices = nVertices;
    this->nEdges = nEdges;
    this->edgeListLength = 0;

    int tailVertex, i;
    int head, tail;
    Edge *tmpEdge;

    for (tailVertex = 1; tailVertex <= nVertices; tailVertex++)
    {
        (this->vertexPtrs)[tailVertex - 1] = this->edgeListLength;
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
                edges[this->edgeListLength] = tmpEdge;
                this->edgeListLength += 1;
            }

            if (!isDirected && (head == tailVertex))
            {
                // printf("\tConnected! %d\n", tail);
                tmpEdge = new Edge(tail, head);
                edges[this->edgeListLength] = tmpEdge;
                this->edgeListLength += 1;
            }
        }
    }

    // A dummy slot for nVertices+1 vertex.
    this->vertexPtrs[nVertices] = this->edgeListLength;
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

NeighboursOf *Graph::getNeighboursOf(int vertex)
{
    NeighboursOf *neighboursObject = new NeighboursOf();

    if (vertex < 0 || vertex > this->nVertices)
    {
        cout << "Invalid vertex(" << vertex << ")\n";
        return NULL;
    }

    neighboursObject->vertex = vertex;

    int noOfNeighbours, ptrToEdgelist, i, j;

    // noOfNeighbours(1) = vertexPtrs[2] - vertextPtrs[1]
    noOfNeighbours = this->vertexPtrs[vertex] - this->vertexPtrs[vertex - 1];
    ptrToEdgelist = this->vertexPtrs[vertex - 1];
    neighboursObject->noOfNeighbours = noOfNeighbours;

    // printf("Vertex: %d, no.neighbours: %d, ptrToEdgelist: %d\n", vertex, noOfNeighbours, ptrToEdgelist);

    int *neighbours = new int[noOfNeighbours];

    j = 0;
    // cout << "Neighbours of " << vertex << " are: \n(";
    for (i = ptrToEdgelist; i < ptrToEdgelist + noOfNeighbours; i++)
    {
        // cout << (this->edges)[i]->headVertex << ", ";
        neighbours[j++] = (this->edges)[i]->headVertex;
    }
    // cout << "\b\b)\n";

    neighboursObject->neighboursArr = neighbours;

    return neighboursObject;
}

void Graph::dfs()
{
    int firstVertex;

    // Ofcourse, it will always be 1. But just to avoid hard-coding;
    firstVertex = this->edges[0]->tailVertex;
    dfs(firstVertex);

    return;
}

void Graph::dfs(int vertex)
{
    // cout << "Depth First Search\n";

    bool isVisited[this->nVertices];
    int i;

    for (i = 0; i < this->nVertices; i++)
    {
        isVisited[i] = false;
    }

    dfsUtil(vertex, isVisited);
    cout << "\b\b\n";

    return;
}

void Graph::dfsUtil(int vertex, bool isVisited[])
{
    // printf("dfs(%d)\n", vertex);
    if (isVisited[vertex - 1])
    {
        // printf("%d is already visited. Returning...\n", vertex);
        return;
    }

    int i;

    isVisited[vertex - 1] = true;
    cout << vertex << " -> " << flush;
    NeighboursOf *neighboursObject = this->getNeighboursOf(vertex);

    for (i = 0; i < neighboursObject->noOfNeighbours; i++)
    {
        dfsUtil(neighboursObject->neighboursArr[i], isVisited);
    }

    return;
}
