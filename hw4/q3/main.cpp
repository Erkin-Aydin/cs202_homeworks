/*
 * Title: CS202 Spring 2022
 * Author: Erkin Aydın
 * ID: 22002956
 * Section: 2
 * Assignment: 4
 * Description: This is the part we test our Graph implementation. "in.txt" is processed line by line and relevant
 * Graph functions are called. C-type strings are used to convert read string values to integers.
*/
#include <iostream>
#include "Graph.h"
#include <bits/stdc++.h>
using namespace std;

int main( int argc, char* argv[]) {

    //To read number of commands and graph size from input file
    string readLine1;
    string readLine2;
    ifstream infile(argv[1]);
    infile >> readLine1;
    infile >> readLine2;

    //Using C type conversion to convert read values to integer values.
    char read_array1[readLine1.length() + 1];
    char read_array2[readLine2.length() + 1];
    strcpy(read_array1, readLine1.c_str());
    strcpy(read_array2, readLine2.c_str());
    int graphSize = atoi(read_array1);      //Integer version of the first line.
    int numOfCommands = atoi(read_array2);  //Integer version of the second line.

    Graph g(graphSize);                     //Creating the Graph with the input size.

    //We will stop when the last line is processed.
    for(int i = 0; i <numOfCommands; i++) {
        string commandString;
        infile >> commandString;                //Processing the operation: Insertion, shortest-path...

        //For Inserting an edge
        if(commandString == "I") {

            //Reading arguments.
            string argument1String;
            string argument2String;
            string argument3String;
            infile >> argument1String;
            infile >> argument2String;
            infile >> argument3String;

            //Converting arguments to integer values.
            char arg1[argument1String.length() + 1];
            char arg2[argument2String.length() + 1];
            char arg3[argument3String.length() + 1];
            strcpy(arg1, argument1String.c_str());
            strcpy(arg2, argument2String.c_str());
            strcpy(arg3, argument3String.c_str());
            int argument1 = atoi(arg1);
            int argument2 = atoi(arg2);
            int argument3 = atoi(arg3);
            g.insertEdge(argument1 ,argument2, argument3);

        }
        //For Listing all the flights from/to an airport.
        else if(commandString == "L") {

            //Reading the argument.
            string argument1String;
            infile >> argument1String;

            //Converting the argument to integer value.
            char arg1[argument1String.length() + 1];
            strcpy(arg1, argument1String.c_str());
            int argument1 = atoi(arg1);
            g.listFlights(argument1);
        }
        //For Shortest-Path: Dijkstra's Algorithm
        else if(commandString == "S") {

            string argument1String;
            string argument2String;
            //Reading arguments.
            infile >> argument1String;
            infile >> argument2String;
            //Converting arguments to integer values.
            char arg1[argument1String.length() + 1];
            char arg2[argument2String.length() + 1];
            strcpy(arg1, argument1String.c_str());
            strcpy(arg2, argument2String.c_str());
            int argument1 = atoi(arg1);
            int argument2 = atoi(arg2);
            g.shortestPath(argument1, argument2);
        }
        //For minimizing the graph: Prim's Algorithm
        else if(commandString == "M") {
            g.minimizeCosts();
        }
    }
    return 0;
}
