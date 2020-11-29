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

void VertexMetaData::printMetaData()
{
    printf("Desc: %d, Low: %d, Visited: %d, onStack: %d\n", this->desc, this->low, this->visited, this->onStack);

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

void Graph::tarjansAlgo()
{
    int firstVertex, i;
    int descTime = 0, child = -1;
    list<list<Edge *>> *componentsList = new list<list<Edge *>>;
    list<list<Edge *>>::iterator componentsIterator;
    list<Edge *> component = list<Edge *>();
    VertexMetaData metaData[this->nVertices];
    stack<Edge *> *edgeStack = new stack<Edge *>;

    // Ofcourse, it will always be 1. But just to avoid hard-coding;
    firstVertex = this->edges[0]->tailVertex;

    for (i = 0; i < this->nVertices; i++)
    {
        metaData[i].onStack = false;
        metaData[i].low = 0;
        metaData[i].desc = 0;
        metaData[i].visited = false;
    }
    // printf("\n");
    tarjansAlgoUtil(firstVertex, 0, metaData, edgeStack, &descTime, &child, (const int)firstVertex, componentsList);

    // printf("Remaining edges on stack: \n");

    if (!edgeStack->empty())
    {
        while (!edgeStack->empty())
        {
            Edge *topEdge = edgeStack->top();
            // topEdge->display();
            component.push_back(topEdge);
            edgeStack->pop();
        }

        componentsList->push_back(component);
    }

    i = 1;
    for (componentsIterator = componentsList->begin(); componentsIterator != componentsList->end(); ++componentsIterator)
    {
        list<Edge *> component = *componentsIterator;
        list<Edge *>::iterator edgeIterator;

        printf("Biconnected Component %d:\n{", i);
        for (edgeIterator = component.begin(); edgeIterator != component.end(); ++edgeIterator)
        {
            Edge *edge = *edgeIterator;

            printf("(%d, %d), ", edge->tailVertex, edge->headVertex);
        }
        printf("\b\b}\n\n");
        i++;
    }

    return;
}

int Graph::tarjansAlgoUtil(int vertex, int parent, VertexMetaData metaData[], stack<Edge *> *edgeStack, int *descTime, int *child, const int root, list<list<Edge *>> *componentsList)
{
    int i, val;

    if (DEBUG)
    {
        printf("\x1b[33mTAUtil(%d, %d, metdata, edgeStack, %d, child: %d, %d, componentsList)\x1b[0m\n", vertex, parent, *descTime, *child, root);
    }

    if (metaData[vertex - 1].visited)
    {
        (*descTime) -= 1;
        if (DEBUG)
        {
            printf("%d is already visted.\n", vertex);
        }
        if (metaData[vertex - 1].onStack)
        {
            if (DEBUG)
            {

                printf("%d is already visted and is on stack.\n", vertex);
                printf("Backedge! Returning my(%d) desc value: %d\n", vertex, metaData[vertex - 1].desc);
            }
            *child = -1;
            return metaData[vertex - 1].desc;
        }
        else
        {
            if (DEBUG)
            {

                edgeStack->top()->display();
                printf("\x1b[32mPopping this edge because this is already on stack\x1b[0m\n");
            }
            edgeStack->pop();
        }

        *child = -1;
        if (DEBUG)
        {
            printf("returning -1\n");
        }
        return -1;
    }

    metaData[vertex - 1].onStack = true;
    metaData[vertex - 1].desc = *descTime;
    metaData[vertex - 1].low = *descTime;
    metaData[vertex - 1].visited = true;

    // cout << vertex << " -> " << flush;
    NeighboursOf *neighboursObject = this->getNeighboursOf(vertex);

    for (i = 0; i < neighboursObject->noOfNeighbours; i++)
    {
        if (neighboursObject->neighboursArr[i] == parent)
        {
            continue;
        }
        (*descTime)++;

        Edge *edge = new Edge(neighboursObject->neighboursArr[i], vertex);
        edgeStack->push(edge);
        if (DEBUG)
        {

            printf("\x1b[32mPushing edge(%d, %d)\x1b[0m\n", vertex, neighboursObject->neighboursArr[i]);
            edgeStack->top()->display();
        }

        val = tarjansAlgoUtil(neighboursObject->neighboursArr[i], vertex, metaData, edgeStack, descTime, child, root, componentsList);
        if (DEBUG)
        {

            printf("\tBack in \x1b[34mTAUtil(%d, %d, metdata, edgeStack, %d, child: %d, %d, componentsList)\x1b[0m\n", vertex, parent, *descTime, *child, root);
        }

        if (val != -1)
        {
            metaData[vertex - 1].low = min(val, metaData[vertex - 1].low);
        }
        if (*child != -1)
        {
            bool rootCondition = vertex != root && (metaData[vertex - 1].desc <= metaData[*child - 1].low);
            bool nonRootCondition = vertex == root && (metaData[*child - 1].desc == metaData[*child - 1].low);
            if (rootCondition || nonRootCondition)
            {
                list<Edge *> component = list<Edge *>();

                if (DEBUG)
                {

                    printf("\x1b[31m%d is an Articulation Point!\x1b[0m\n", vertex);
                    printf("Pop all the edges from the stack until (%d, %d)\n", *child, vertex);
                }

                while (true)
                {
                    if (edgeStack->empty())
                    {
                        if (DEBUG)
                        {
                            printf("Stack is empty\n");
                        }
                        break;
                    }
                    Edge *topEdge = edgeStack->top();
                    component.push_back(topEdge);
                    if (DEBUG)
                    {
                        topEdge->display();
                    }
                    edgeStack->pop();

                    if (topEdge->headVertex == *child && topEdge->tailVertex == vertex)
                    {
                        if (DEBUG)
                        {
                            printf("This id the head of cc\n");
                        }
                        break;
                    }
                }
                // printf("\n");
                componentsList->push_back(component);
            }
        }
        if (DEBUG)
        {

            printf("\tVertex: %d\n\t  ", vertex);
            metaData[vertex - 1].printMetaData();
        }
    }

    if (DEBUG)
    {

        printf("Returning my(%d) low value: %d\n", vertex, metaData[vertex - 1].low);
    }
    metaData[vertex - 1].onStack = false;
    *child = vertex;
    return metaData[vertex - 1].low;
}