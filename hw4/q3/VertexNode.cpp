/*
 * Title: CS202 Spring 2022
 * Author: Erkin Aydın
 * ID: 22002956
 * Section: 2
 * Assignment: 4
 * Description: Contains the necessary functions for a graph to manage vertex nodes properly.
*/

#include "VertexNode.h"
#include <cstdlib>
using namespace std;


//This function is for creating the "VerticeNode"
VertexNode::VertexNode(int verticeIndex, int weight)
{
    this->weight = weight;
    this->verticeIndex = verticeIndex;
    adjacentPtr = NULL;
}
/*
 * This function is for deleting the "VerticeNode". It actually functions as a safeguard to protect the next "VerticeNode",
 * as this class does not contain anything to be deleted, except the next "VerticeNode", but its deletion is already handled
 * in the "Graph" class.
 */
VertexNode::~VertexNode()
{
    adjacentPtr = NULL;// dangerous???? in the deletion, be careful
}
//Returns the weight of the vertex
int VertexNode::getWeight()
{
    return weight;
}

//Returns the position of the vertex in the "verticeArray" of the "Graph" class.
int VertexNode::getVerticeIndex()
{
    int i = 0;
    return verticeIndex;
}
//Returns the pointer to the next "VerticeNode" as a reference value.
VertexNode*& VertexNode::getAdjacentPtr()
{
    return adjacentPtr;
}