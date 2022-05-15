/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: An implementation of heap, modified to fit the needs of the assignment, such as inserting items with respect
 * to their priorities and their send times. This is the header file.
*/

#ifndef LAB3_HEAP_H
#define LAB3_HEAP_H
#include "Log.h"

class Heap {
public:
    Heap();
    Heap( int size);
    ~Heap();
    bool heapIsEmpty() const;
    void heapInsert(const Log& newItem);
    void heapDelete(Log& rootItem);
    int getTopSendTime();
    Log& getTop();

protected:
    void heapRebuild(int root);		// Converts the semiheap rooted at
    // index root into a heap
private:
    Log* items;	// array of heap items
    int maxSize;
    int curSize;
};


#endif //LAB3_HEAP_H
