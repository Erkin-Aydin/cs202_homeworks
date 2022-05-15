/*
 * Title: CS202 Spring 2022
 * Author: Erkin Aydın
 * ID: 22002956
 * Section: 2
 * Assignment: 4
 * Description: Header file of the Graph class.
*/
#ifndef HW4_GRAPH_H
#define HW4_GRAPH_H

#include "VertexNode.h"
using namespace std;

class Graph {
public:
    Graph(int size);
    ~Graph();
    //Algorithm1
    void insertEdge(int u, int v, int w);
    //Algorithm2
    void listFlights(int u);
    //Algorithm3
    void shortestPath(int s, int t);
    //Algorithm4
    void minimizeCosts();
private:
    int size;
    VertexNode** vertexArray;

};

#endif //HW4_GRAPH_H