/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: An Heap based implementation of the PriorityQueue. This is the header file.
*/

#ifndef LAB3_PRIORITYQUEUE_H
#define LAB3_PRIORITYQUEUE_H

#include "Heap.h"// ADT heap operations
#include "Log.h"
class PriorityQueue {
public:
    PriorityQueue();
    PriorityQueue( int size);
    ~PriorityQueue();

    // priority-queue operations:
    bool pqIsEmpty() const;
    void pqInsert(const Log& newItem);
    void pqDelete(Log& priorityItem);
    int getTopSendTime();
    Log& getTop();

private:
    Heap* h;
};


#endif //LAB3_PRIORITYQUEUE_H
