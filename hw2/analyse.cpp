/*
* Title: Trees
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 2
* Description: For analysis of BST
*/

#include <iostream>
#include <cstdlib>
#include <bits/stdc++.h>
#include "BinarySearchTree.h"
using namespace std;

void analyseBST() {

    BinarySearchTree testTree;
    int arr[10000];
    //To create completely different arrays each time
    srand(time(NULL));
    for(int i = 0; i  < 10000; i++) { //Creating a random array
        int random = rand() % 100000; //Creating a random values
        arr[i] = random;    //Storing random values in the array
    }

    cout << "Random BST size vs. height (Insertion)" << endl;
    cout << "-----------------------------------------" << endl;
    for(int i = 0; i  < 10000; i++) {
        testTree.add(arr[i]);
        if((i + 1) % 100 == 0) {
            cout << testTree.getNumberOfNodes() << " " << testTree.getHeight() << endl;
        }
    }

    //To shuffle the array
    random_shuffle(arr, arr + 10000);

    cout << "Random BST size vs. height (Deletion)" << endl;
    cout << "-----------------------------------------" << endl;
    for(int i = 0; i  < 10000; i++) {
        testTree.remove(arr[i]);
        if((i + 1) % 100 == 0) {
            cout << testTree.getNumberOfNodes() << " " << testTree.getHeight() << endl;
        }    }
}

int main() {
    analyseBST();
    return 0;
}