/*
 * Title: CS202 Spring 2022
 * Author: Erkin Aydın
 * ID: 22002956
 * Section: 2
 * Assignment: 4
 * Description: Contains the following: 1)Insertion Operation, 2)List Operation, 3)Shortest-Path Operation and
 * 4)Minimize-Cost Operation
*/

#include "Graph.h"
#include <cstdlib>
#include <iostream>
#include <sstream>
//This constructor function is to create the graph.
Graph::Graph(int size)
{
    //initializing the size
    this->size = size;
    //creating the vertex array
    vertexArray = new VertexNode*[size];
    //initializing every vertexNode in the array to NULL
    for(int i = 0; i < size; i++)
    {
        vertexArray[i] = NULL;
    }
}
/*
 * This function is to delete the graph. We first delete every "VertexNode" linked list pointed by pointers in the
 * "vertexArray". Then, we delete the "vertexArray".
 */
Graph::~Graph()
{
    /*
     * Every vertexNode pointed by pointers in the vertexArray should be deleted, but if we simply delete that node,
     * we may and probably will end up with undeleted vertexNode linked lists. Thus, our approach is: Delete linked
     * lists pointed by every pointer in the vertexArray.
     */
    for(int i = 0; i < size; i++)
    {
        /*
         * "toDel" will be used to iterate over linked lists and delete every node. "vertexArray[i]" has a different
         * purpose now: It will be used to provide the address of the next node to be deleted to pointer "toDel".
         */
        VertexNode* toDel = vertexArray[i];
        //If "toDel" is NULL, then there is nothing left to delete.
        while(toDel != NULL)
        {
            //Storing the address of the next vertexNode to be deleted in "vertexArray[i]".
            vertexArray[i] = toDel->getAdjacentPtr();
            //Deleting the current vertexNode
            delete toDel;
            //"toDel" is now holds the address of the node to be deleted next.
            toDel = vertexArray[i];
        }
    }
    //Since no pointer of "vertexArray" points to a "vertexNode" now, we can delete the "vertexNode".
    delete[] vertexArray;
}
/*
 * The purpose of this function is to connect to vertices, that is, to add an edge between vertices, that is, to add
 * a flight between two airports. First, we check whether the airports have any flights to any other airport. If not,
 * then simply creating a node pointed by the pointer in the relevant index of the "vertexArray" is sufficient. If so,
 * then we should iterate over the linked list pointed by the pointer in the relevant index of the "vertexArray" to add
 * the edge.
 */
void Graph::insertEdge(int u, int v, int w) {
    //Airport "u" does not have any flight to any other airport.
    if(vertexArray[u] == NULL)
    {
        vertexArray[u] = new VertexNode(v, w);
    }
        //Airport "u" has at least one flight to other airports.
    else
    {
        /*
         * "curPtr" will be used to iterate over the linked list pointed by vertexArray[u].
         * It will point to the last node of the linked list in the end of the operation.
         */
        VertexNode* curPtr;
        //Iterating over the linked list.
        for(curPtr = vertexArray[u]; curPtr->getAdjacentPtr() != NULL; curPtr = curPtr->getAdjacentPtr());
        //"curPtr" now points to the last node of the linked list pointed by vertexArray[u].
        curPtr->getAdjacentPtr() = new VertexNode(v, w);
    }
    //Airport "v" does not have any flight to any other airport.
    if(vertexArray[v] == NULL)
    {
        vertexArray[v] = new VertexNode(u, w);
    }
    else
    {
        /*
        * "curPtr" will be used to iterate over the linked list pointed by vertexArray[v].
        * It will point to the last node of the linked list in the end of the operation.
        */
        VertexNode* curPtr;
        //Iterating over the linked list pointed by vertexArray[v].
        for(curPtr = vertexArray[v]; curPtr->getAdjacentPtr() != NULL; curPtr = curPtr->getAdjacentPtr());
        //"curPtr" now points to the last node of the linked list pointed by vertexArray[v].
        curPtr->getAdjacentPtr() = new VertexNode(u, w);
    }
    //Printing out the inserted flight
    cout << "Inserted a new flight between " << u << " and " << v << "." << endl;
    //"numOfFlights" will contain the amount of flights from airport "u" at the end of the for loop.
    int numOfFlights = 1;
    //Counting the number of flights from airport "u".
    for(VertexNode* curPtr = vertexArray[u];
        curPtr->getAdjacentPtr() != NULL;
        curPtr = curPtr->getAdjacentPtr(), numOfFlights++);
    //Printing the number of flights from airport "u".
    cout << "   The number of flights from " << u << " is " << numOfFlights << "." << endl;
}

/*
 * The purpose of this function is to list all the flights from "u". All the flights will be printed with
 * their durations. At the end, the number of flights from the "u" will be printed.
 */
void  Graph::listFlights(int u)
{
    cout << "List of flights from " << u << ":" << endl;
    //"numOfFlights" will contain the amount of flights from airport "u" at the end of the for loop.
    int numOfFlights = 1;
    VertexNode* curPtr;
    //Counting the number of flights from airport "u".
    for(curPtr = vertexArray[u];
        curPtr->getAdjacentPtr() != NULL;
        curPtr = curPtr->getAdjacentPtr(), numOfFlights++)
    {
        //Printing the flight with its duration.
        cout << "   " << u << " to " << curPtr->getVerticeIndex() << " with a duration of " << curPtr->getWeight() << "." << endl;
    }
    cout << "   " << u << " to " << curPtr->getVerticeIndex() << " with a duration of " << curPtr->getWeight() << "." << endl;
    //Printing the number of flights from airport "u".
    cout << "   The number of flights is " << numOfFlights << "." << endl;
}

/*
 * The purpose of this function is to find the shortest duration of flight between two airports. Dijkstra's
 * Shortest-Path Algorithm was used in this part.
 */
void Graph::shortestPath(int s, int t)
{
    bool visited[size];                      //This will contain true if the airport with relevant index is visited.
    int shortestDistance[size];              //This will contain the shortest path length to "t" from "s".
    int previousPort[size];                  //This will contain the previous airports for each airport in the shortest path.
    for(int i = 0; i < size; i++) {
        visited[i] = false;                  //Initially, none of the airports are visited.
        shortestDistance[i] = 0x7fffffff;    //Distances are infinity...
        previousPort[i] = -1;                //Initially, none have a previous airport as none are visited. Only "s" will have
        //-1 as previous airport at the end of Dijkstra's algorithm.
    }

    //For vertex "s"
    shortestDistance[s] = 0;                 //The distance between an airport and itself is 0.
    visited[s] = true;                       //We visited airport "s".
    int smallestDistanceSoFar = 0x7fffffff;  //Infinity.
    int nextVertex;                          //This will be used to trace the next adjacent vertex to visit.
    for(VertexNode* curPtr = vertexArray[s]; curPtr != NULL; curPtr = curPtr->getAdjacentPtr()) {
        //Storing the shortest distance to its adjacent vertices.
        shortestDistance[curPtr->getVerticeIndex()] = shortestDistance[s] + curPtr->getWeight();
        //Storing the previous airport to its adjacent vertices.
        previousPort[curPtr->getVerticeIndex()] = s;
        if(smallestDistanceSoFar > shortestDistance[curPtr->getVerticeIndex()]) {//Here is the time to change the next vertex to visit.
            smallestDistanceSoFar = shortestDistance[curPtr->getVerticeIndex()]; //Smallest distance so far changed.
            nextVertex = curPtr->getVerticeIndex();//Vertex changed
        }
    }

    //For rest of the vertices, ve one by one visit them all. When nextVertex == -1, no connected vertex left to visit.
    while (nextVertex != -1){
        visited[nextVertex] = true;          //ve visited this airport now.
        int prevVertex = nextVertex;         //nextVertex is likely to change, but we still need that value.
        smallestDistanceSoFar = 0x7fffffff;  //Infinity.
        /*
         * We, one by one, go through all unvisited adjacent vertices and update with new shortest paths to them. We also
         * determine the next vertex to visit here in this loop.
         */
        for(VertexNode* curPtr = vertexArray[prevVertex]; curPtr != NULL; curPtr = curPtr->getAdjacentPtr()) {
            //If there is a better path...
            if(curPtr->getWeight() + shortestDistance[prevVertex] < shortestDistance[curPtr->getVerticeIndex()]) {
                //Updating the shortest distance.
                shortestDistance[curPtr->getVerticeIndex()] = curPtr->getWeight() + shortestDistance[prevVertex];
                previousPort[curPtr->getVerticeIndex()] = prevVertex;//Updating previous airport.
            }
            //If the smallest distance changed, our next destination airport also changed.
            if(!visited[curPtr->getVerticeIndex()] && curPtr->getWeight() < smallestDistanceSoFar) {
                nextVertex = curPtr->getVerticeIndex();
            }
        }
        //If prevVertex == nextVertex, then all the vertices are visited.
        if(prevVertex == nextVertex) {
            nextVertex = -1;
        }
    }

    //If ve didn't visit "t"... There is no path.
    if(!visited[t]) {
        cout << "No paths from " << s << " to " << t << "." << endl;
    }
    else {//If we did visit "t"...
        cout << "The shortest path from " << s << " to " << t << ":" << endl;
        int goBack = t;              //To go back through vertices.
        int i = -1;                   //This is to store and print terminal messages.
        string printArray[size];     //This will store terminal messages.
        while(goBack != s) {         //If so, we reached to the initial airport.
            i++;                             //Incrementing the message address.
            stringstream converter;  //This will be used to convert integers and strings to string altogether.
            VertexNode* curPtr;     //For finding the weight, that is, the distance between the previous airport and the current one.
            for(curPtr = vertexArray[previousPort[goBack]]; curPtr->getVerticeIndex() != goBack; curPtr = curPtr->getAdjacentPtr());
            converter << "   " << previousPort[goBack] << " to " << goBack << " with a duration of " << curPtr->getWeight() << ".";
            printArray[i] = converter.str(); //Storing the message to be printed.
            converter.clear();               //Clearing the string stream.
            goBack = previousPort[goBack];   //Updating the previous airport.
        }
        //Printing terminal messages.
        for( ; 0 <= i; i--) {
            cout << printArray[i] << endl;
        }
        cout << "    Total flight duration of path: " << shortestDistance[t] << endl;
    }
}

void Graph::minimizeCosts() {
    //Creating a matrix for Prim's algorithm.
    int adjMatrix[size][size];
    //Initializing all values to infinity.
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            adjMatrix[i][j] = 0x7fffffff;
        }
    }

    //Initializing existing edges.
    for(int i = 0; i < size; i++) {
        for(VertexNode* curPtr = vertexArray[i]; curPtr != NULL; curPtr = curPtr->getAdjacentPtr()) {
            adjMatrix[i][curPtr->getVerticeIndex()] = curPtr->getWeight();
        }
    }

    //Calculating current cost.
    int edgeSum = 0;
    for(int i = 0; i < size; i++){
        for(int j = size - 1; i < j; j--) {
            if(adjMatrix[i][j] != 0x7fffffff) {
                edgeSum += adjMatrix[i][j];
            }
        }
    }
    //Printing current cost.
    cout << "Total cost of operations before minimization: " << edgeSum << endl;

    //For storing visited vertices.
    bool visited[size];
    int vertices[size];
    int edges[size];
    for(int i = 0; i < size; i++) {
        visited[i] = false;
        vertices[i] = -1;
        edges[i] = 0x7fffffff;
    }
    visited[0] = true;                  //Airport 0 is selected automatically.
    edges[0] = 0;                       //Airport 0 is selected automatically.
    int visitCounter = 1;
    VertexNode** minimizedGraph = new VertexNode*[size];
    for(int i = 0; i < size; i++) {
        minimizedGraph[i] = NULL;
    }
    //We will stop when all vertices are visited.
    while(visitCounter < size) {
        //For storing coordinates of the minimum edge
        int leastI = -1;
        int leastJ = -1;
        int leastCostEdge = 0x7fffffff;//Infinity.
        for(int i = 0; i <= visitCounter; i++) {
            //Only if the airport is visited, we can go to another airport from there
            if(visited[i]) {
                //Calculating the minimum edge with unvisited airport.
                for (int j = 0; j < size; j++) {
                    if (!visited[j] && (leastCostEdge > adjMatrix[i][j])) {
                        leastJ = j;
                        leastI = i;
                        leastCostEdge = adjMatrix[i][j];
                    }
                }
            }
        }
        //If an leastCostEdge is found...
        if(leastCostEdge != 0x7fffffff) {
            visited[leastJ] = true;                             //Marking it as visited.
            vertices[visitCounter] = leastJ;                    //Adding vertex.
            edges[visitCounter] = adjMatrix[leastI][leastJ];    //Adding edge.
            visitCounter++;
            //This part is for storing the edges to our minimized graph.
            if(minimizedGraph[leastI] == NULL) {
                minimizedGraph[leastI] = new VertexNode(leastJ, leastCostEdge);
            }
            else {
                VertexNode* curPtr = minimizedGraph[leastI];
                for (curPtr = minimizedGraph[leastI]; curPtr->getAdjacentPtr() != NULL; curPtr = curPtr->getAdjacentPtr());
                curPtr->getAdjacentPtr() = new VertexNode(leastJ, leastCostEdge);
            }
            if(minimizedGraph[leastJ] == NULL) {
                minimizedGraph[leastJ] = new VertexNode(leastI, leastCostEdge);
            }
            else {
                VertexNode* curPtr = minimizedGraph[leastJ];
                for (curPtr = minimizedGraph[leastJ]; curPtr->getAdjacentPtr() != NULL; curPtr = curPtr->getAdjacentPtr());
                curPtr->getAdjacentPtr() = new VertexNode(leastI, leastCostEdge);
            }
        }
    }
    //Calculating the sum of edges after minimizing the cost.
    edgeSum = 0;
    for(int i = 0; i < size; i++) {
        edgeSum += edges[i];
    }
    cout << "Total cost of operations after minimization: " << edgeSum << endl;

    //Updating the vertexArray to our minimizedGraph.
    for(int i = 0; i < size; i++) {

        VertexNode* toDel = vertexArray[i];
        while(toDel != NULL) {
            VertexNode* forNext = toDel->getAdjacentPtr();
            delete toDel;
            toDel = forNext;
        }
    }
    delete[] vertexArray;
    vertexArray = minimizedGraph;
    int g = 0;
}