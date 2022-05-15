/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: A class to represent requests. It has id, priority, the time it was sent and its process time as properties.
 * This is the header file.
*/

#ifndef LAB3_LOG_H
#define LAB3_LOG_H

class Log {
public:
    Log();
    Log(int id, int priority, int sentAfter, int processTime);
    int getId();
    int getPriority();
    int getSentAfter();
    int getProcessTime();

private:

    int id;
    int priority;
    int sentAfter;
    int processTime;

};
#endif //LAB3_LOG_H
