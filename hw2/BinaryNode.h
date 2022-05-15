/*
* Title: Trees
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 2
* Description: Header file for BinaryNode
*/

#ifndef LAB2_BINARYNODE_H
#define LAB2_BINARYNODE_H


class BinaryNode {

public:
    BinaryNode();
    BinaryNode(int rootData);
    BinaryNode(int rootData, BinaryNode* parent);
    void decreaseSize();

    int nodeData;
    BinaryNode *leftChildPtr;
    BinaryNode *rightChildPtr;

    int size;
    BinaryNode *parentPointer;
};


#endif //LAB2_BINARYNODE_H
