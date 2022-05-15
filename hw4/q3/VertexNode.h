/*
 * Title: CS202 Spring 2022
 * Author: Erkin Aydın
 * ID: 22002956
 * Section: 2
 * Assignment: 4
 * Description: Header file of the VertexNode class.
*/

#ifndef HW4_VERTEXNODE_H
#define HW4_VERTEXNODE_H


class VertexNode {
public:
    VertexNode(int verticeIndex, int weight);
    ~VertexNode();
    int getWeight();
    int getVerticeIndex();
    VertexNode*& getAdjacentPtr();
private:
    int weight;
    int verticeIndex;
    VertexNode* adjacentPtr;
};


#endif //HW4_VERTEXNODE_H