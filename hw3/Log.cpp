/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: A class to represent requests. It has id, priority, the time it was sent and its process time as properties.
 * This is the header file.
*/

#include "Log.h"
//If it is not specified, all the properties are -1, which means the request is meaningless.
Log::Log() {
    priority = -1;
    id  =-1;
    processTime = -1;
    sentAfter = -1;
}

Log::Log(int newId, int newPriority, int newSentAfter, int newProcessTime) {
    id = newId;
    priority = newPriority;
    sentAfter = newSentAfter;
    processTime = newProcessTime;
}
//returning id
int Log::getId() {
    return id;
}

//returning priority
int Log::getPriority() {
    return priority;
}

//returning processTime
int Log::getProcessTime() {
    return processTime;
}

//returning sentAfter, the time it was sent
int Log::getSentAfter() {
    return sentAfter;
}