/*
* Title: Sorting and Algorithm Efficiency
* Author: Erkin Aydın
* ID: 22002956
* Section: 2
* Assignment: 1
* Description: header file for sorting.cpp
 * contains functions necessary for Question 2.a, 2.b, 2.d
*/

#ifndef LAB1_SORTING_H
#define LAB1_SORTING_H

//Functions for Question 2.a
    void insertionSort(int *arr, const int size, int &compCount, int &moveCount);
    void bubbleSort(int *arr, const int size, int &compCount, int &moveCount);
    void mergeSort(int *arr, const int size, int &compCount, int &moveCount);
    void quickSort(int *arr, const int size, int &compCount, int &moveCount);
    void swap(int &first, int& second);
    void mergeSortSub(int *arr, int first, int last, int &compCount, int &moveCount);
    void quickSortSub(int *arr, int first, int last, int &compCount, int &moveCount);
    void partition(int *arr, int first, int last, int &pivotIndex, int &compCount, int &moveCount);
    void merge(int *arr, int first, int mid, int last, int &compCount, int &moveCount);

//Functions for Question 2.b
    void displayArray(const int *arr, const int size);
    void createRandomArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void createAlmostSortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void createAlmostUnsortedArrays(int *&arr1, int *&arr2, int *&arr3, int *&arr4, const int size);
    void createHomeworkArray(int *&arr1, int *&arr2, int *&arr3, int *&arr4);
//Functions for Question 2.d
    void performanceAnalysis();
    void displayTable(double *times, int* comp, int* move, const int baseNumber, const int size);
#endif
