/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: An implementation of heap, modified to fit the needs of the assignment, such as inserting items with respect
 * to their priorities and their send times. This is the header file.
*/

#include "Heap.h"
#include <iostream>
using namespace std;

//If not specified, the heap properties are -1, the heap is meaningless
Heap::Heap() {
    curSize = -1;
    maxSize = -1;
}

//Creating a heap with the given size. maxSize is the maximum size it can get, while curSize is its contemporary size.
Heap::Heap( int size) {
    maxSize = size;
    items = new Log[maxSize];
    curSize = 0;
}

//deleting the heap
Heap::~Heap() {
    delete[] items;
}

//returning whether the heap is empty or not.(-1 case is not considered, as such a heap won't be used)
bool Heap::heapIsEmpty() const {
    return curSize == 0;
}

//Inserting an item to the heap
void Heap::heapInsert(const Log&newItem){

    if (curSize >= maxSize) {   //If heap is full, we display an error message and exit the function
        cout << "Heap is full." << endl;
        return;
    }
    // Place the new item at the end of the heap
    items[curSize] = newItem;   //If it comes to this, it means heap is not empty.

    // Trickle new item up to its proper position
    int place = curSize;
    int parent = (place - 1)/2;
    //Condition of this while loop is updated, as it is necessary to insert requests with respect to their priorities and their send times
    while ((place > 0) && ( ( items[place].getPriority() > items[parent].getPriority()) ||
        ( items[place].getPriority() == items[parent].getPriority()) && items[place].getSentAfter() < items[parent].getSentAfter())) {
        Log temp = items[parent];
        items[parent] = items[place];
        items[place] = temp;

        place = parent;
        parent = (place - 1)/2;
    }
    curSize++;
}

//Deleting a heap
void Heap::heapDelete(Log&rootItem){
    if (heapIsEmpty()) {    //You can't delete something non-existent.
        cout << "Heap is empty" << endl;
    }
    else {                  //But you can delete something that exists.
        rootItem = items[0];
        curSize--;
        if(curSize > 0) {
            items[0] = items[curSize];
            heapRebuild(0); //Rebuilding the heap
        }
        else {              //Heap is fully emptied
            items[0] = Log();
        }
    }
}

//Rebuilding the heap.
void Heap::heapRebuild(int root) {
    int child = 2 * root + 1;    // index of root's left child, if any
    if (child < curSize) {
        // root is not a leaf so that it has a left child
        int rightChild = child + 1;    // index of a right child, if any
        // If the root has a right child, find larger child
        // Condition of this if is updated, as it is necessary to rebuild requests with respect to their priorities and their send times
        if ((rightChild < curSize) &&
            (items[rightChild].getPriority() > items[child].getPriority()) ||
            (items[rightChild].getPriority() == items[child].getPriority() && items[rightChild].getSentAfter() < items[child].getSentAfter()))
            child = rightChild;    // index of larger child

        // If root’s item is smaller than larger child, swap values
        // Condition of this if is updated, as it is necessary to rebuild requests with respect to their priorities and their send times
        if ((items[root].getPriority() < items[child].getPriority()) ||
            (items[root].getPriority() == items[child].getPriority() && items[root].getSentAfter() > items[child].getSentAfter())) {
            Log temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            // transform the new subtree into a heap
            heapRebuild(child);
        }
    }
}

//returning the time the top request was sent
int Heap::getTopSendTime() {
    return items[0].getSentAfter();
}

//returning the top request.
Log& Heap::getTop() {
    return items[0];
}