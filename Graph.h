#ifndef __GRAPH_H__
#define __GRAPH_H__

#define MAX_VERTICES 256
#define EDGE_RELATION_LEN 2
#define MAX_EDGES (MAX_VERTICES * MAX_VERTICES)

class Edge
{
public:
    // Class variables
    int tailVertex, headVertex;

    // Method Prototypes
    Edge(int head, int tail);
    void display();
};

class Graph
{
public:
    // Class variables
    int nVertices, nEdges;
    int vertexPtrs[MAX_VERTICES];
    Edge *edges[MAX_EDGES];

    // Method Prototypes
    Graph(int nVertices, int relationShips[][EDGE_RELATION_LEN], int nEdges);
    void displayEdgeList();
    void displayVertextPtrs();
    void display();
};

#endif /*__GRAPH_H__*/