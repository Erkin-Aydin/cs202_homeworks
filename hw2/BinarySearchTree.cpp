/*
* Title: Trees
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 2
* Description: Source file for BinarySearchTree. Contains implementations of all the necessary functions for this assignment.
*/

#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

BinarySearchTree::BinarySearchTree() {
    root = NULL;
}
BinarySearchTree::~BinarySearchTree() {
    deleteTree(root);
}

void BinarySearchTree::deleteTree(BinaryNode *&nodePtr) {
    if(nodePtr == NULL) {
        return;
    }
    else if(nodePtr->leftChildPtr == NULL && nodePtr->rightChildPtr == NULL) {
        delete nodePtr;
        return;
    }
    else if(nodePtr->leftChildPtr == NULL && nodePtr->rightChildPtr != NULL) {
        deleteTree(nodePtr->rightChildPtr);
        delete nodePtr;
        return;
    }
    else if(nodePtr->leftChildPtr != NULL && nodePtr->rightChildPtr == NULL) {
        deleteTree(nodePtr->leftChildPtr);
        delete nodePtr;
        return;
    }
    else {
        deleteTree(nodePtr->leftChildPtr);
        deleteTree(nodePtr->rightChildPtr);
        delete nodePtr;
        return;
    }
}

bool BinarySearchTree::isEmpty() {
    return root == NULL;
}

//İf the BST is empty, then its height is 0 for sure. If not, then the height is nonzero
int BinarySearchTree::getHeight() {
    if (isEmpty() == 1) {
        return 0;
    }
    else {
        return getHeightSub(root); // BST is not empty, thus sub-function is called
    }
}

/*
 * This is the recursive function for determining height. If we reach to a NULL pointer, then the BST ended, thus we return
 * 0. If this is not the case, then the BST height should be 1 bigger than its maxHeight(leftSubTree, rightSubTree), as
 * we have a node pointing to these left and right subtrees.
 */
int BinarySearchTree::getHeightSub(BinaryNode *&treePtr) {
    if(treePtr == NULL) {
        return 0;
    }
    //Since the height is not 0, we shall call this function recursively both for left and right subtrees.
    else {
        int heightOfLeft = getHeightSub(treePtr->leftChildPtr);
        int heightOfRight = getHeightSub(treePtr->rightChildPtr);
        if(heightOfLeft > heightOfRight) { //we get the max of them
            return heightOfLeft + 1;
        }
        else {
            return  heightOfRight + 1;
        }
    }
}
/*
 * This is the function to get the number of nodes of a BST. If the size of each node is kept neatly and correctly, then
 * the size parameter of the first node of the BST gives us the number of nodes of the BST. For this function to work properly,
 * sizes should be kept properly. Thus, this function is dependent on "add" and "delete" functions.
 */
int BinarySearchTree::getNumberOfNodes() {
    if(isEmpty()) {
        return 0;
    }
    else {
        return root->size;
    }
}

//Add part starts

/*
 * This is the function to add a node to a BST. If the BST is empty, then we can just set the first node to out new node.
 * If this is not the case, then we should call the sub-function to find the proper place to add this new node and add it.
 */
bool BinarySearchTree::add(int newEntry) {
    if(isEmpty()) {
        root = new BinaryNode(newEntry);
        return true;
    }
    else {
        return addSub(root, newEntry);
    }
}

/*
 * This is the sub-function to find the proper place to add the node, and add it. Since this is a recursive function, the
 * base case should check treePtr == NULL. If so, this is the place we should insert it. İf not, we should look whether the
 * data of treePtr is bigger then the data of new node. If so, we shall go to the left subtree and continue our search there as
 * all de nodes there will certainly be smaller than current treePtr data. Otherwise, we do the same for the right subtree.
 */
bool BinarySearchTree::addSub(BinaryNode *&treePtr, int newEntry) {
    if(treePtr->nodeData > newEntry) {
        if(treePtr->leftChildPtr == NULL) {
            treePtr->leftChildPtr = new BinaryNode(newEntry, treePtr);
            BinaryNode* prevPtr = treePtr;
            while(prevPtr != NULL) {
                prevPtr->size++;
                prevPtr = prevPtr->parentPointer;
            }
            return true;
        }
        else {
            return addSub(treePtr->leftChildPtr, newEntry);
        }
    }
    //If left is not greater than the new nodes' data, we go to right subtree.
    else {
        if(treePtr->rightChildPtr == NULL) {
            treePtr->rightChildPtr = new BinaryNode(newEntry, treePtr);
            BinaryNode* prevPtr = treePtr;
            BinaryNode* left = treePtr->rightChildPtr;
            while(prevPtr != NULL) {
                prevPtr->size++;
                prevPtr = prevPtr->parentPointer;
            }
            return true;
        }
        else {
            return addSub(treePtr->rightChildPtr, newEntry);
        }
    }
}
//Add part ends

/*
 * To remove a node, we should first detect its place in the BST. If it is there, we will delete it and return. If it is not there,
 * we won't delete it because, obviously, we can't delete something nonexistent. However, if we detect a node with the
 * given value but it is at the end of the BST, then we delete it.
 */
bool BinarySearchTree::remove(int anEntry) {
    bool checker = false;
    deleteItem(root, anEntry, checker);
    return checker;
}

void BinarySearchTree::deleteItem(BinaryNode*& treePtr, int item, bool& checker)
{
    if (treePtr == NULL) {// Empty tree
        return;
    }
        // Position of deletion found
    else if (item == treePtr->nodeData) {
        BinaryNode* delPtr;
        int replacementItem;
        // (1)  Test for a leaf
        if ((treePtr->leftChildPtr == NULL) && (treePtr->rightChildPtr == NULL)) {
            BinaryNode* prevPtr = treePtr->parentPointer;
            while(prevPtr != NULL) {
                prevPtr->size--;
                prevPtr = prevPtr->parentPointer;
            }
            delete treePtr;
            treePtr = NULL;
        }
            // (2)  Test for no left child
        else if (treePtr->leftChildPtr == NULL) {
            delPtr = treePtr;
            treePtr = treePtr->rightChildPtr;
            delPtr->rightChildPtr = NULL;
            treePtr->parentPointer = delPtr->parentPointer;
            BinaryNode* prevPtr = treePtr->parentPointer;
            while(prevPtr != NULL) {
                prevPtr->size--;
                prevPtr = prevPtr->parentPointer;
            }
            delete delPtr;
        }
            // (3)  Test for no right child
        else if (treePtr->rightChildPtr == NULL) {
            delPtr = treePtr;
            treePtr = treePtr->leftChildPtr;
            delPtr->leftChildPtr = NULL;
            treePtr->parentPointer = delPtr->parentPointer;
            BinaryNode* prevPtr = treePtr->parentPointer;
            while(prevPtr != NULL) {
                prevPtr->size--;
                prevPtr = prevPtr->parentPointer;
            }
            delete delPtr;
        }
            // (4)  There are two children:
            //      Retrieve and delete the inorder successor
        else {
            processLeftmost(treePtr->rightChildPtr, replacementItem);
            treePtr->nodeData = replacementItem;
        }
    }
        // Else search for the deletion position
    else if (item < treePtr->nodeData){
        deleteItem(treePtr->leftChildPtr, item, checker);
    }
    else{
        deleteItem(treePtr->rightChildPtr, item, checker);
    }
}

void BinarySearchTree::processLeftmost(BinaryNode *&nodePtr, int& treeItem){

    if (nodePtr->leftChildPtr == NULL) {
        treeItem = nodePtr->nodeData;
        BinaryNode *delPtr = nodePtr;
        BinaryNode* prevPtr = nodePtr;
        nodePtr = nodePtr->rightChildPtr;
        if(nodePtr != NULL) {
            nodePtr->parentPointer = delPtr->parentPointer;
        }
        delPtr->rightChildPtr = NULL; // defense
        while(prevPtr != NULL) {
            prevPtr->size--;
            prevPtr = prevPtr->parentPointer;
        }
        delete delPtr;
    }
    else {
        processLeftmost(nodePtr->leftChildPtr, treeItem);
    }
}
//Contains part starts

//We check whether the BST contains a node with the given entry. For this, a helper subfunction is implemented.
bool BinarySearchTree::contains(int anEntry) {
    return containsSub(root, anEntry);
}

/*
 * This is the helper sub-function to check whether there exists a node with the given value or not. If it exists, we return true.
 * If it does not exist, we return false.
 */
bool BinarySearchTree::containsSub(BinaryNode *&nodePtr, int anEntry) {
    if(nodePtr == NULL) {
        return false;
    }
    else if(nodePtr->nodeData == anEntry) {
        return true;
    }
    else if(anEntry < nodePtr->nodeData) {
        return containsSub(nodePtr->leftChildPtr, anEntry);
    }
    else {
        return containsSub(nodePtr->rightChildPtr, anEntry);
    }
}
//Contains part ends

//Inorder part starts
void BinarySearchTree::inorderTraverse() {
    inOrder(root);
}

//Classical inorder traversal. We print each time. Do nothing if the treePtr == NULL, as there is nothing to do.
void BinarySearchTree::inOrder(BinaryNode *&treePtr) {
    if(treePtr == NULL) {
        return;
    }
    inOrder(treePtr->leftChildPtr);
    cout << treePtr->nodeData << " ";
    inOrder(treePtr->rightChildPtr);
}
//Inorder part ends

//Width part starts
int BinarySearchTree::getWidth() {
    int maxWidth = 0;
    int height = getHeight();
    int temp;
    for(int i = 1; i <= height; i++) {
        //"getWidthSub" sub-function will return us the width in each level.
        temp = getWidthSub(root, i);
        //If temp > max, then we have a new max!
        if(temp > maxWidth) {
            maxWidth = temp;
        }
    }
    return maxWidth;
}

/*
 * If treePtr == NULL, then the tree is empty, so the width of it is 0. If we want the width of the first level, it is 1
 * for sure. Since this condition is put in an "else if" after checking treePtr == NULL, it is certain that there is indeed
 * a node, and only one node, there. If the level is higher, then we go to these levels by recursively calling for left subtree
 * and right subtree
 */
int BinarySearchTree::getWidthSub(BinaryNode *&treePtr, int height) {
    if(treePtr == NULL) {
        return 0;
    }
    else if(height == 1) {
        return 1;
    }
    else {
        return getWidthSub(treePtr->leftChildPtr, height - 1) + getWidthSub(treePtr->rightChildPtr, height - 1);
    }
}
//Width part ends

//Count part starts
int BinarySearchTree::count(int a, int b) {
    return countSub(root, a, b);
}

/*
 * Each visited node, satisfying that its data is between a and b, is a +1 for the count, then we should find how many
 * nodes in the left and right subtrees. Simple as that.
 */
int BinarySearchTree::countSub(BinaryNode *&nodePtr, int a, int b) {
    if(nodePtr == NULL) {
        return 0;
    }
    else if(nodePtr->nodeData >= a && nodePtr->nodeData <= b) {
        return 1 + countSub(nodePtr->leftChildPtr, a, b) + countSub(nodePtr->rightChildPtr, a, b);
    }
    else {
        return countSub(nodePtr->leftChildPtr, a, b) + countSub(nodePtr->rightChildPtr, a, b);
    }
}
//Count part ends

//Select part starts
int BinarySearchTree::select(int anEntry) {
    return selectSub(root, anEntry);
}

//Returns the inorder index of the node with the given entry, starting from index 1.
int BinarySearchTree::selectSub(BinaryNode *&nodePtr, int anEntry) {
    if(nodePtr == NULL) {   //Node does not exist.
        return -1;
    }
    else if(anEntry < nodePtr->nodeData) {  //Node may exist in the left subtree
        return successorSub(nodePtr->leftChildPtr, anEntry);
    }
    else if(anEntry > nodePtr->nodeData) {  //Node may exist in the right subtree
        return successorSub(nodePtr->rightChildPtr, anEntry);
    }
    else {  //Node exists.
        int index = 0;
        if(nodePtr->leftChildPtr != NULL) {
            index += nodePtr->leftChildPtr->size;
        }
        BinaryNode* parentPtr = nodePtr->parentPointer;
        while(parentPtr != NULL && nodePtr == parentPtr->leftChildPtr) {
            nodePtr = parentPtr;
            parentPtr = parentPtr->parentPointer;
        }
        while(parentPtr != NULL && nodePtr == parentPtr->rightChildPtr) {
            index += parentPtr->leftChildPtr->size + 1;
            nodePtr = parentPtr;
            parentPtr = parentPtr->parentPointer;
        }
        return index;
    }
}
//Select part ends

//Successor part starts
int BinarySearchTree::successor(int anEntry) {
    return successorSub(root, anEntry);
}

/*
 * If no successor exists, returns -1. If it exists, but it is the maximum of the BST, then returns -2. If previous
 * conditions are false, then it returns the successor.
 */
int BinarySearchTree::successorSub(BinaryNode *&nodePtr, int anEntry) {
    if(nodePtr == NULL) {   //No entry exists.
        return -1;
    }
    else if(anEntry < nodePtr->nodeData) {  //entry may exist in the left subtree.
        return successorSub(nodePtr->leftChildPtr, anEntry);
    }
    else if(anEntry > nodePtr->nodeData) {  //entry may exist in the right subtree.
        return successorSub(nodePtr->rightChildPtr, anEntry);
    }
    else {  //entry exists.
        if(nodePtr->rightChildPtr != NULL) { //If right subtree exists, then the successor is certainly there.
            return minimumOfRight(nodePtr->rightChildPtr);
        }
        else {
            if(nodePtr->parentPointer != NULL) {
                BinaryNode *parentPtr = nodePtr->parentPointer;
                BinaryNode *curPtr = nodePtr;
                //The moment we go to left with parentPtr, here is our successor.
                while (parentPtr != NULL && curPtr == parentPtr->rightChildPtr) {
                    curPtr = parentPtr;
                    parentPtr = parentPtr->parentPointer;
                }
                /*
                 * parentPtr == NULL means we never ever happened to be in a position where we are in a left subtree, which means
                 * we were the rightest of all nodes!
                 */
                if (parentPtr == NULL) {
                    return -2;
                } else {  //Else, just return the successor.
                    return parentPtr->nodeData;
                }
            }
            else {
                return -1;
            }
        }
    }
}

/*
 * To fnd the minimum of a right subtree. We go left, left, and left as much as we can. if ce can't anymore, we found our
 * minimum.
 */
int BinarySearchTree::minimumOfRight(BinaryNode *nodePtr) {
    BinaryNode* leftPtr = nodePtr;
    while(leftPtr->leftChildPtr != NULL) {
        leftPtr = leftPtr->leftChildPtr;
    }
    return leftPtr->nodeData;
}
//Successor part ends


