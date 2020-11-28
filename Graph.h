#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stack>

using namespace std;

#define MAX_VERTICES 256
#define EDGE_RELATION_LEN 2
#define MAX_EDGES (MAX_VERTICES * MAX_VERTICES)

class NeighboursOf
{
public:
    int vertex;
    int *neighboursArr;
    int noOfNeighbours;
};

class VertexMetaData
{
public:
    int low;
    int desc;
    bool onStack;
    bool visited;

    void printMetaData();
};

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
    int vertexPtrs[MAX_VERTICES + 1];
    int edgeListLength;
    Edge *edges[MAX_EDGES];

    // Method Prototypes
    Graph(int nVertices, int relationShips[][EDGE_RELATION_LEN], int nEdges, bool isDirected);
    void displayEdgeList();
    void displayVertextPtrs();
    void display();
    NeighboursOf *getNeighboursOf(int vertex);
    void dfs();
    void dfs(int vertex);
    void tarjansAlgo();

private:
    void dfsUtil(int vertex, bool isVisited[]);
    int tarjansAlgoUtil(int vertex, int parent, VertexMetaData metaData[], stack<Edge> edgeStack, int *descTime, int *child);
};

#endif /*__GRAPH_H__*/