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
    int nVertices, nEdges, i, j;
    Graph *graph;
    NeighboursOf *neighboursObject;

    // Get the graph representation of graph from file.
    strcpy(graphFile, argv[1]);

    parseGraphFile(graphFile, edgeRelationShips, &nEdges, &nVertices);

    graph = new Graph(nVertices, edgeRelationShips, nEdges, false);
    graph->display();

    for (i = 0; i < nVertices; i++)
    {
        neighboursObject = graph->getNeighboursOf(i + 1);
        if (neighboursObject->noOfNeighbours == 0)
        {
            cout << "Neighbours of vertex " << i + 1 << ": {}" << endl;
            continue;
        }
        cout << "Neighbours of vertex " << i + 1 << ": {" << flush;
        for (j = 0; j < neighboursObject->noOfNeighbours; j++)
        {
            cout << neighboursObject->neighboursArr[j] << ", " << flush;
        }
        cout << "\b\b}\n";
    }

    graph->dfs();
    for (i = 0; i < nVertices; i++)
    {
        graph->dfs(i + 1);
    }

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
        return;
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
