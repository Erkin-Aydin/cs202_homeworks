/*
* Title: Heaps, Priority Queues
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 3
* Description: This is the source file that simulation happens. A clock signal is mocked by an integer value. we start
 * simulating with 1 computer, then we increase the number of computers each time the average waiting time is higher than
 * the wished one. We stop when average waiting time is lower than or equal to the entered one through the command line.
 * A Little Note: There may be, and probably are, better ways to convert strings to integers, however I chose to convert
 * it by using c-type strings as I found it interesting.
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Log.h"
#include "PriorityQueue.h"
#include <bits/stdc++.h>
using namespace std;

int readyCompCalc(bool arr[], int size);
void nextLogReturn( ifstream& infile, Log& newLog);

int main(int argc, char* argv[]) {
    cout << endl;
    int i = 0; //1 less from the computer number
    int maxProcessTime = atoi(argv[2]); //converting max average waiting time.
    for( ; maxProcessTime > 0; i++) {
        int compNumber = i + 1;//number of computers in a simulation
        bool compArray[compNumber]; // Computers are represented by bool expressions

        // processTimes and requestSendTimes will be used to ready the busy computer when the processing of the request is finished.
        double processTimes[compNumber]; // process times are represented here
        double requestSendTimes[compNumber]; // arrival times of requests are here
        for(int j = 0; j < compNumber; j++) {
            compArray[j] = true;
            processTimes[j] = -1;
            requestSendTimes[j] = -1;
        }
        string readData;// to read the first line.
        ifstream infile(argv[1]);//reading the ".txt" file
        infile >> readData; //reading the number of logs in the file, which is the first line in the file
        char read_array[readData.length() + 1];
        strcpy(read_array, readData.c_str());
        int readDataInt = atoi(read_array); // integer version of the first line
        int numOfLogs = readDataInt;
        PriorityQueue logs(numOfLogs);
        /*
         * In these arrays, values that will be printed will be stored, such as computer nums, wait results...
         * compNumResults: store computer id's that take HTTP requests
         * requestNumResults: store request id's
         * msNumResults: start of process times of the requests
         * waitResults: stores wait times
         */
        int compNumResults[numOfLogs];
        int requestNumResults[numOfLogs];
        int msNumResults[numOfLogs];
        int waitResults[numOfLogs];
        int resultIndex = 0;

        //Here, the processing starts.
        int readyCompIndex = 0; // This will be used to keep track of the ready computer with the lowest id.
        int timeChecker = 0; // This is our clock signal
        int logCounter = 0; // keeps track of how many HTTP requests arrived.
        Log newLog; //this is to store newly arriving HTTP requests into our priority queue
        nextLogReturn( infile, newLog); //we take the first HTTP request
        while( logCounter < numOfLogs || !logs.pqIsEmpty()) {
            /*
             * This while loop(the one below) functions as a checker between requests and time. If their time arrived, we read requests from
             * the file one by one and store to the priority queue that we created. Important thing here is that we also
             * retrieve the first HTTP request that will come after this clock signal, but we do not insert it into the
             * priority queue.
             */
            while( logCounter < numOfLogs && newLog.getSentAfter() <= timeChecker) {
                logs.pqInsert( newLog); // inserting last arriving HTTP request
                nextLogReturn( infile, newLog); //we retrieve the next HTTP request
                logCounter++;
            }

            /*
             * Here, we release all the busy computers with requests, if and only if they finished processing.
             */
            for( int j = 0; j < compNumber; j++) {
                if( ( !compArray[j]) && ( processTimes[j] + requestSendTimes[j]) <= timeChecker) {
                    compArray[j] = true;
                    processTimes[j] = -1;
                    requestSendTimes[j] = -1;
                    readyCompIndex = readyCompCalc(compArray, compNumber);
                }
            }

            /*
             * Where the processing starts with a computer. Here, the log should be deleted and its start and wait times with their id's should be stored.
             */
            while( ( readyCompIndex != -1) && (logs.getTop().getId() != -1) && ( logs.getTopSendTime() <= timeChecker)) {
                Log toDel;
                logs.pqDelete(toDel);//deleting the request with the highest priority
                compArray[readyCompIndex] = false;//computer is busy now
                processTimes[readyCompIndex] = toDel.getProcessTime();  //will be used to make the computer ready when the process is finished
                requestSendTimes[readyCompIndex] = timeChecker;         //will be used to make the computer ready when the process is finished
                //compNumResults[resultIndex] := this should be initialized to ready computer's id value, its index value in the bool array.
                compNumResults[resultIndex] = readyCompIndex;
                //requestNumResults[resultIndex] := this is the id of the request
                requestNumResults[resultIndex] = toDel.getId();
                //msNumResults[resultIndex] := the time when the request started to be processed
                msNumResults[resultIndex] = timeChecker;
                //waitResults[resultIndex] := the difference between current time and when the request was sent
                waitResults[resultIndex] = timeChecker - toDel.getSentAfter();

                //readyCompIndex := -1 if none of the computers are available, != -1 if otherwise.
                readyCompIndex = readyCompCalc(compArray, compNumber);
                resultIndex++;  //one other request is being processed, so we increment this to continue storing for next requests.
            }

            timeChecker++;
        }
        double averageWait = 0;
        for(int j = 0; j < numOfLogs; j++) {
            averageWait += waitResults[j];
        }
        averageWait = averageWait / numOfLogs;
        if(averageWait <= maxProcessTime) {
            //All the printing happens here.
            cout << "Minimum number of computers required: " << compNumber << endl;
            cout << endl;
            cout << "Simulation with " << compNumber << " computers:" << endl;
            cout << endl;
            for(int j = 0; j < numOfLogs; j++) {
                cout << "Computer " << compNumResults[j] << " takes request " << requestNumResults[j] << " at ms " << msNumResults[j]
                    << " (wait: " << waitResults[j] << " ms)" << endl;
            }
            cout << endl;
            cout << "Average waiting time: " << averageWait << " ms";
            maxProcessTime = -1;//to exit the top while loop-to stop simulating.
        }
    }
    return 0;
}
/*
 * This function calculates the ready computer with the lowest id. It basically returns the index value of the computer
 * where it is "true"(remember, computers are represented by booleans), starting from the first index, where index values are id's.
 * If none of them are ready for a new request, then -1 is returned.
 */
int readyCompCalc(bool arr[], int size) {
    for(int i = 0; i < size; i++) {
        if(arr[i]) {
            return i;
        }
    }
    return -1;
}

// This function is to retrieve the next HTTP request from the file.
void nextLogReturn( ifstream& infile, Log& newLog) {
    string id;
    string priority;
    string sentAfter;
    string processTime;
    infile >> id;           //reading id as a string
    infile >> priority;     //reading priority as a string
    infile >> sentAfter;    //reading the clock signal it was sent as a string
    infile >> processTime;  //reading the amount of time needed to process as a string

    //Converting strings to integer values
    char new_array1[id.length() + 1];
    strcpy(new_array1, id.c_str());
    int readId = atoi(new_array1);

    char read_array2[priority.length() + 1];
    strcpy(read_array2, priority.c_str());
    int readPriority = atoi(read_array2);

    char read_array3[sentAfter.length() + 1];
    strcpy(read_array3, sentAfter.c_str());
    int readSentAfter = atoi(read_array3);

    char read_array4[processTime.length() + 1];
    strcpy(read_array4, processTime.c_str());
    int readProcessTime = atoi(read_array4);

    //creating a log with retrieved&converted integers and returning it
    newLog = Log(readId, readPriority, readSentAfter, readProcessTime);
}