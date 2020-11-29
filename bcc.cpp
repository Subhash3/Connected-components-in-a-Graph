#include <iostream>
#include <cstring>
#include <fstream>
#include "Graph.h"

using namespace std;

// All constant definitions
#define MAX_STR_LEN 256

// Function Prototypes
void parseGraphFile(char *graphFile, int edgeRelationShips[][EDGE_RELATION_LEN], int *nEdges, int *nVertices);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cout << "Usage " << argv[0] << " <Graph Representation File>\n";
        exit(1);
    }

    // Declare variables
    char graphFile[MAX_STR_LEN];
    int edgeRelationShips[MAX_EDGES][EDGE_RELATION_LEN];
    int nVertices, nEdges;
    Graph *graph;
    // NeighboursOf *neighboursObject;
    // int i, j;

    // Get the graph representation of graph from file.
    strcpy(graphFile, argv[1]);

    parseGraphFile(graphFile, edgeRelationShips, &nEdges, &nVertices);

    graph = new Graph(nVertices, edgeRelationShips, nEdges, false);
    // graph->display();

    graph->tarjansAlgo();

    exit(0);
}

void parseGraphFile(char *graphFile, int edgeRelationShips[][EDGE_RELATION_LEN], int *nEdges, int *nVertices)
{
    // cout << "Parsing graph file...\n";

    int head, tail, i;
    char line[MAX_STR_LEN];
    fstream fp;

    fp.open(graphFile);
    if (!fp)
    {
        fprintf(stderr, "\x1b[31mError opening file\x1b[0m %s\n", graphFile);
        exit(1);
    }

    fp.getline(line, MAX_STR_LEN, '\n');
    sscanf(line, "%d %d", nVertices, nEdges);

    for (i = 0; i < *nEdges; i++)
    {
        fp.getline(line, MAX_STR_LEN, '\n');
        if (!fp)
        {
            break;
        }
        // cout << line << endl;
        sscanf(line, "%d %d", &tail, &head);
        // cout << "Head: " << head << ", Tail: " << tail << endl;
        edgeRelationShips[i][0] = tail;
        edgeRelationShips[i][1] = head;
    }

    fp.close();

    // cout << "Parsing Done!...\n";

    return;
}
