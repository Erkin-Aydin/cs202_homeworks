/*
* Title: Trees
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 2
* Description: Source file for BinaryNode
*/

#include "BinaryNode.h"
#include <iostream>


BinaryNode::BinaryNode() {
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    parentPointer = NULL;
    size = 0;
}

BinaryNode::BinaryNode(int rootData) {
    parentPointer = NULL;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    size = 1;
    nodeData = rootData;

}

BinaryNode::BinaryNode(int rootData, BinaryNode* parent) {
    parentPointer = parent;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    size = 1;
    nodeData = rootData;
}

void  BinaryNode::decreaseSize() {
    size--;
}
