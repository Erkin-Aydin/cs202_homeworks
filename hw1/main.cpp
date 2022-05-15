/*
* Title: Sorting and Algorithm Efficiency
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 1
* Description: main function to test functions in sorting.cpp
 * Here, we first create 4 identical dynamically allocated arrays, then one by one apply
 * insertion bubble merge and quick sorting algorithms. In each step, we will display the final
 * version of the array, number of comparison and move counts in algorithms.
*/

#include <iostream>
#include "sorting.h"
using namespace std;

int main(){

    int *arr1, *arr2, *arr3, *arr4;
    createHomeworkArray(arr1,arr2,arr3,arr4);
    cout << "Insertion Sort" << endl;
    int comp = 0;
    int  move = 0;
    insertionSort(arr1, 16, comp, move);
    displayArray(arr1, 16);
    cout << "Comparison Count: " << comp << endl;
    cout << "Move Count: " << move << endl;
    cout << endl;

    cout << "Bubble Sort" << endl;
    comp = 0;
    move = 0;
    bubbleSort(arr2, 16, comp, move);
    displayArray(arr2, 16);
    cout << "Comparison Count: " << comp << endl;
    cout << "Move Count: " << move << endl;
    cout << endl;

    cout << "Merge Sort" << endl;
    comp = 0;
    move = 0;
    mergeSort(arr3, 16, comp, move);
    displayArray(arr3, 16);
    cout << "Comparison Count: " << comp << endl;
    cout << "Move Count: " << move << endl;
    cout << endl;

    cout << "Quick Sort" << endl;
    comp = 0;
    move = 0;
    quickSort(arr4, 16, comp, move);
    displayArray(arr4, 16);
    cout << "Comparison Count: " << comp << endl;
    cout << "Move Count: " << move << endl;

    cout << endl;
    cout << "Performance Analysis time!" << endl;
    cout << endl;

    delete[] arr1;
    delete[] arr2;
    delete[] arr3;
    delete[] arr4;

    performanceAnalysis();

     return 0;
}
