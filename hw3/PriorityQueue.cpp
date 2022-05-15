/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: An Heap based implementation of the PriorityQueue. This is the source file.
*/

#include "PriorityQueue.h"

PriorityQueue::PriorityQueue() {
}

//Creating the priority queue with a size
PriorityQueue::PriorityQueue( int size) {
    h = new Heap(size);
}

//Deleting the priority queue
PriorityQueue::~PriorityQueue() {
    delete h;
}

//Checking whether the priority queue is empty
bool PriorityQueue::pqIsEmpty() const {
    return h->heapIsEmpty();
}

//Inserting an item to the priority queue
void PriorityQueue::pqInsert(const Log& newItem){
    h->heapInsert(newItem);
}

//Deleting the "top" item in the priority queue
void PriorityQueue::pqDelete(Log& priorityItem){
    h->heapDelete(priorityItem);
}

//returning when the HTTP request at the top of the queue is sent
int PriorityQueue::getTopSendTime() {
    return h->getTopSendTime();
}

//returning the top request
Log& PriorityQueue::getTop() {
    return h->getTop();
}