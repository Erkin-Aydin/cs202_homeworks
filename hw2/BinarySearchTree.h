/*
* Title: Trees
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 2
* Description: Header file for BinarySearchTree
*/

#ifndef LAB2_BINARYSEARCHTREE_H
#define LAB2_BINARYSEARCHTREE_H


#include "BinaryNode.h"

class BinarySearchTree {
public:
    BinarySearchTree();
    ~BinarySearchTree();
    void deleteTree(BinaryNode*& nodePtr);
    void processLeftmost(BinaryNode *&nodePtr, int& treeItem);
    bool isEmpty();
    int getHeight();
    int getNumberOfNodes();
    bool add(int newEntry);
    bool remove(int anEntry);
    bool contains(int anEntry);
    void inorderTraverse();
    int getWidth();
    int count(int a, int b);
    int select(int anEntry);
    int successor(int anEntry);




private:
    int getHeightSub(BinaryNode*& treePtr);
    bool addSub(BinaryNode*& treePtr, int newEntry);
    void deleteItem(BinaryNode*& nodePtr, int anEntry, bool& checker);
    bool containsSub(BinaryNode*& nodePtr, int anEntry);
    void inOrder(BinaryNode*& treePtr);
    int getWidthSub(BinaryNode*& treePtr, int height);
    int countSub(BinaryNode*& nodePtr, int a, int b);
    int selectSub(BinaryNode*& nodePtr, int anEntry);
    int successorSub(BinaryNode*& nodePtr, int anEntry);
    int minimumOfRight(BinaryNode* nodePtr);

    BinaryNode* root;

};


#endif //LAB2_BINARYSEARCHTREE_H
