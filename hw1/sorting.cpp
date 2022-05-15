/*
* Title: Sorting and Algorithm Efficiency
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 1
* Description: Here are all the necessary functions for the assignment
 *
*/
#include "sorting.h"
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

//This is the classical implementation of the insertion sort algorithm
void insertionSort(int *arr, const int size, int &compCount, int &moveCount)
{
    for(int unsorted = 1; unsorted < size; unsorted++) {
        int item = arr[unsorted];
        moveCount++; //a movement happened in the previous line
        int location = unsorted;
        for( ; location > 0 && arr[location -1] > item; location--) {
            arr[location] = arr[location - 1];
            compCount++; //if we are in the for loop, a key comparison happened for sure
            moveCount++; //if we are in the for loop, a movement happened for sure
        }
        //if for loop is finished with a key comparison, we should increase comparison value by 1.
        if(location > 0) {
            compCount++;
        }
        arr[location] = item;
        moveCount++; //a movement happened in the previous line
    }
}

//This is the classical implementation of the bubble sort algorithm
void bubbleSort(int *arr, const int size, int &compCount, int &moveCount)
{
    bool sorted = false;
    for(int pass = 1; pass < size && !sorted; pass++) {
        sorted = true; //assuming it is sorted
        for(int index = 0; index < size - pass; index++) {
            if(arr[index] > arr[index + 1]) {
                swap(arr[index], arr[index + 1]);
                moveCount = moveCount + 3; //1 swap == 3 move
                sorted = false; //signaling that it isn't to continue the loop
            }
            compCount++;//a comparison made for each if, whether it is executed or not
        }
    }
}

//This is the modified implementation of the merge sort algorithm to fit the prototype given in the assignment
void mergeSort(int *arr, const int size, int &compCount, int &moveCount)
{
    mergeSortSub(arr, 0, size - 1, compCount, moveCount);
}

//This is the modified implementation of the quick sort algorithm to fit the prototype given in the assignment
void quickSort(int *arr, const int size, int &compCount, int &moveCount)
{
    quickSortSub(arr, 0, size - 1, compCount, moveCount);
}

void quickSortSub(int *arr, int first, int last, int &compCount, int &moveCount)
{
    int pivotIndex;

    if (first < last) {
        partition(arr, first, last, pivotIndex, compCount, moveCount);

        quickSortSub(arr, first, pivotIndex - 1, compCount, moveCount);
        quickSortSub(arr, pivotIndex + 1, last, compCount, moveCount);
    }
}
//Partition algorithm for quickSortSub
void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount)
{
    int pivot = arr[first]; //Selecting the first elemet as pivot
    moveCount++;
    int lastS1 = first;
    int firstUnknown = first + 1;

    for( ; firstUnknown <= last; firstUnknown++) {
        if(arr[firstUnknown] < pivot) {
            lastS1++;
            swap(arr[firstUnknown], arr[lastS1]);
            moveCount = moveCount + 3; //1 swap == 3 move
        }
        compCount++; //a comparison made for each if, whether it is executed or not
    }
    swap(arr[first], arr[lastS1]);
    moveCount = moveCount + 3; //1 swap == 3 move
    pivotIndex = lastS1;
}

//Swapping two values
void swap(int &first, int &second)
{
    int temp = first;
    first = second;
    second = temp;
}

//This is the implementation of a classical merge sort algorithm
void mergeSortSub(int *arr, int first, int last, int &compCount, int &moveCount)
{
    //if first >= last, then there is no array to divide: size < 2
    if(first < last) {
        int mid = (first + last) / 2;
        mergeSortSub(arr, first, mid, compCount, moveCount);
        mergeSortSub(arr, mid + 1, last, compCount, moveCount);
        merge(arr,first, mid, last, compCount, moveCount);
    }
}

//This is the implementation of a classical merge algorithm
void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount)
{
    int tempArr[last + 1]; //last is index
    int first1 = first;
    int last1 = mid;
    int first2 = mid + 1;
    int last2 = last;
    int index = first;

    //Making comparisons and copying to tempArr accordingly
    for( ;first1 <= last1 && first2 <= last2; index++) {
        //if arr[first1] < arr[first2], we copy arr[first]
        if(arr[first1] < arr[first2]) {
            tempArr[index] = arr[first1];
            first1++;
        }
        //if arr[first1] >= arr[first2], we copy arr[first2]
        else {
            tempArr[index] = arr[first2];
            first2++;
        }
        moveCount++;
        compCount++;
    }

    //Copying the rest of the first part of the array if anything is left
    for( ; first1 <= last1; index++) {
        tempArr[index] = arr[first1];
        first1++;
        moveCount++;
    }

    //Copying the rest of the second part of the array if anything is left
    for( ; first2 <= last2; index++) {
        tempArr[index] = arr[first2];
        first2++;
        moveCount++;
    }

    //Carrying back values to their original place in a sorted fashion
    for(index = first; index <= last; index++) {
        arr[index] = tempArr[index];
        moveCount++;
    }
}

//This is the function to display the contents of an array starting from index 0.
void displayArray(const int *arr, const int size)
{
    for(int i = 0; i < size; i++) {
        if(i != 0) {
            cout << ", ";
        }
        cout << arr[i];
    }
    cout << endl;
}

/*This function creates 4 random arrays each containing same elements in the same order,
 that is, these arrays are copies of each other.*/
void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size)
{
    //Allocating memory
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    //To create completely different arrays each time
    srand(time(NULL));
    for(int i = 0; i  < size; i++) { //Creating 4 identical ramdom arrays
        int random = rand() % size; //Creating a random value
        arr1[i] = random;
        arr2[i] = random;
        arr3[i] = random;
        arr4[i] = random;
    }
}
/*This function creates 4 arrays each containing same elements in the same order,
 that is, these arrays are copies of each other. Elements of the arrays first created as equal to their index, then
 they are slightly perturbed for our purposes. The way they are perturbed is important: First random indexes are
 created and stored in an array, then using this array of indexes we swap elements of each 4 of the arrays*/
void createAlmostSortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size)
{
    //Allocating memory
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    srand(time(NULL)); //To create completely different arrays each time
    for(int i = 0; i  < size; i++) { //Creating a sorted array
        arr1[i] = i;
        arr2[i] = i;
        arr3[i] = i;
        arr4[i] = i;
    }
    //To perturb ~10% of the arrays
    int toPerturb = size / 10;
    int perturbIndexes[toPerturb];
    for(int i = 0; i < toPerturb; i++) {
        perturbIndexes[i] = rand() % size; //creating random indexes
    }
    int i = 0;
    int j = toPerturb - 1;

    while(i<j) { //Here, we perturb
        swap(arr1[perturbIndexes[i]], arr1[perturbIndexes[j]]);
        swap(arr2[perturbIndexes[i]], arr2[perturbIndexes[j]]);
        swap(arr3[perturbIndexes[i]], arr3[perturbIndexes[j]]);
        swap(arr4[perturbIndexes[i]], arr4[perturbIndexes[j]]);
        i++;
        j--;
    }
}
/*This function creates 4 arrays each containing same elements in the same order,
 that is, these arrays are copies of each other. Elements of the arrays first created as equal to (size - index - 1),
 then they are slightly perturbed for our purposes. The way they are perturbed is important: First random indexes are
 created and stored in an array, then using this array of indexes we swap elements of each 4 of the arrays*/
void createAlmostUnsortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size)
{
    //Allocating memory
    arr1 = new int[size];
    arr2 = new int[size];
    arr3 = new int[size];
    arr4 = new int[size];
    srand(time(NULL)); //To create completely different arrays each time
    for(int i = 0; i  < size; i++) { //Creating a sorted array
        arr1[i] = size - i - 1;
        arr2[i] = size - i - 1;
        arr3[i] = size - i - 1;
        arr4[i] = size - i - 1;
    }
    //To perturb ~10% of the arrays
    int toPerturb = size / 10;
    int perturbIndexes[toPerturb];
    for(int i = 0; i < toPerturb; i++) {
        perturbIndexes[i] = rand() % size; //creating random indexes
    }
    int i = 0;
    int j = toPerturb - 1;
    while(i<j) { //Here, we perturb
        swap(arr1[perturbIndexes[i]], arr1[perturbIndexes[j]]);
        swap(arr2[perturbIndexes[i]], arr2[perturbIndexes[j]]);
        swap(arr3[perturbIndexes[i]], arr3[perturbIndexes[j]]);
        swap(arr4[perturbIndexes[i]], arr4[perturbIndexes[j]]);
        i++;
        j--;
    }
}

/*This is the function we analyse the performance of functions and display elapse times, comparison and move counts for
 *  Question 2.d. For each scenario (random, almost sorted, almost unsorted), we use the
 *  following sizes for the arrays: 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000. We run
 *  each of the sorting algorithms with each scenario and output the elapsed time in
 *  milliseconds, the number of key comparisons and the number of data moves
 */
void performanceAnalysis()
{
    int *arr1, *arr2, *arr3, *arr4;
    int fiveThousand = 5000;
    for(int arraySelect = 0; arraySelect < 3; arraySelect++) { //Selecting between random, almost sorted and almost unsorted
        double insertionTimes[8], bubbleTimes[8], mergeTimes[8], quickTimes[8]; //Arrays to store elapse times
        int insertionComp[8], bubbleComp[8], mergeComp[8], quickComp[8]; //Arrays to store comparison counts
        int insertionMove[8], bubbleMove[8], mergeMove[8], quickMove[8]; //Arrays to store move counts
        //Displayıng a message to distinguish between arrays
        if(arraySelect == 0) {
            cout << "createRandomArrays" << endl;
        }
        else if(arraySelect == 1) {
            cout << "createAlmostSortedArrays" << endl;
        }
        else {
            cout << "createAlmostUnsortedArrays" << endl;
        }
        cout << "=====================================================" << endl;
        //Now we will one by one create 5000, 10000, 15000... sized arrays and call functions, and then display results.
        for(int i = 0; i < 8; i++) {
            //Creating appropriate 4 identical arrays with appropriate size
            if(arraySelect == 0) {
                createRandomArrays(arr1, arr2, arr3, arr4, fiveThousand * (i + 1));
            }
            else if(arraySelect == 1) {
                createAlmostSortedArrays(arr1, arr2, arr3, arr4, fiveThousand * (i + 1));
            }
            else {
                createAlmostUnsortedArrays(arr1, arr2, arr3, arr4, fiveThousand * (i + 1));
            }

            /*Here, we call sorting algorithms one by one and store elapse times, comp counts and move counts
             * in appropriate arrays
             */
            int comp = 0;
            int move = 0;
            clock_t insertionStart = clock();
            insertionSort( arr1, fiveThousand * (i + 1), comp, move);
            double insertionTime = 1000 * double(clock() - insertionStart) / CLOCKS_PER_SEC;
            insertionTimes[i] = insertionTime; //Storing elapse time
            insertionComp[i] = comp; //Storing comparison count
            insertionMove[i] = move; //Storing move count

            comp = 0;
            move = 0;
            clock_t bubbleStart = clock();
            bubbleSort( arr2, fiveThousand * (i + 1), comp, move);
            double bubbleTime = 1000 * double(clock() - bubbleStart) / CLOCKS_PER_SEC;
            bubbleTimes[i] = bubbleTime; //Storing elapse time
            bubbleComp[i] = comp; //Storing comparison count
            bubbleMove[i] = move; //Storing move count

            comp = 0;
            move = 0;
            clock_t mergeStart = clock();
            mergeSort( arr3, fiveThousand * (i + 1), comp, move);
            double mergeTime = 1000 * double(clock() - mergeStart) / CLOCKS_PER_SEC;
            mergeTimes[i] = mergeTime; //Storing elapse time
            mergeComp[i] = comp; //Storing comparison count
            mergeMove[i] = move; //Storing move count

            comp = 0;
            move = 0;
            clock_t quickStart = clock();
            quickSort( arr4, fiveThousand * (i + 1), comp, move);
            double quickTime = 1000 * double(clock() - quickStart) / CLOCKS_PER_SEC;
            quickTimes[i] = quickTime; //Storing elapse time
            quickComp[i] = comp; //Storing comparison count
            quickMove[i] = move; //Storing move count

            //Deallocating arrays to avoid memory leak
            delete[] arr1;
            delete[] arr2;
            delete[] arr3;
            delete[] arr4;
        }
        //Here we print the results.
        cout << "-----------------------------------------------------" << endl;
        cout << "Analysis of Insertion Sort" << endl;
        cout << "|    Array Size    |    Elapsed time    |    compCount    |    moveCount    |" << endl;
        displayTable(insertionTimes, insertionComp, insertionMove, fiveThousand, 8);
        cout << "-----------------------------------------------------" << endl;
        cout << "Analysis of Bubble Sort" << endl;
        cout << "|    Array Size    |    Elapsed time    |    compCount    |    moveCount    |" << endl;
        displayTable(bubbleTimes, bubbleComp, bubbleMove, fiveThousand, 8);
        cout << "-----------------------------------------------------" << endl;
        cout << "Analysis of Merge Sort" << endl;
        cout << "|    Array Size    |    Elapsed time    |    compCount    |    moveCount    |" << endl;
        displayTable(mergeTimes, mergeComp, mergeMove, fiveThousand, 8);
        cout << "-----------------------------------------------------" << endl;
        cout << "Analysis of Quick Sort" << endl;
        cout << "|    Array Size    |    Elapsed time    |    compCount    |    moveCount    |" << endl;
        displayTable(quickTimes, quickComp, quickMove, fiveThousand, 8);
    }
}

//Creating 4 identical arrays for Question 2.c
void createHomeworkArray(int *&arr1, int *&arr2, int *&arr3, int *&arr4)
{
    arr1 = new int[16];
    arr2 = new int[16];
    arr3 = new int[16];
    arr4 = new int[16];
    arr1[0] = 9;
    arr1[1] = 6;
    arr1[2] = 7;
    arr1[3] = 16;
    arr1[4] = 18;
    arr1[5] = 5;
    arr1[6] = 2;
    arr1[7] = 12;
    arr1[8] = 20;
    arr1[9] = 1;
    arr1[10] = 16;
    arr1[11] = 17;
    arr1[12] = 4;
    arr1[13] = 11;
    arr1[14] = 13;
    arr1[15] = 8;
    for(int i = 0; i < 16; i++) {
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
        arr4[i] = arr1[i];
    }
}

//Displaying array contents one by one
void displayTable(double *times, int* comp, int* move, const int baseNumber, const int size)
{
    for (int i = 0; i < size; i++) {
        cout << "    " << baseNumber * (i + 1) << "                " << times[i] << " ms        "
             << comp[i] << "                 " << move[i] << endl;
    }
}