#include "SortAlgorithms.h"
#include <algorithm>
#include <iostream>
#include <iterator>

// UTILITIES

/* print a vector of integers */ 
void printArray(std::vector<int> array) {
    std::cout << "[";
    std::vector<int>::iterator i;
    int counter = 0;
    for(i = array.begin(); i != array.end(); i++) {
        std::cout << *i;
        counter ++;
        if(counter != array.size()) {
            std::cout << ",";
        }
    }
    std::cout << "]";
}

// MERGE SORT

/* merge operation */
std::vector<int> merge(std::vector<int> leftArray, std::vector<int> rightArray) {
    std::vector<int> sortedVector;

    std::vector<int>::iterator i = leftArray.begin();
    std::vector<int>::iterator j = rightArray.begin();

    while(i != leftArray.end() || j != rightArray.end()) {
        if(i == leftArray.end()) {
            sortedVector.push_back(*j);
            j++;
        }
        else if(j == rightArray.end()) {
            sortedVector.push_back(*i);
            i++;
        }
        else {
            if(*i < *j) {
                sortedVector.push_back(*i);
                i++;
            }
            else {
                sortedVector.push_back(*j);
                j++;
            }
        }
    }

    PRINTDBG_SINGLE_ARRAY(sortedVector,"sortedVector: ");
    return sortedVector;
}

/* merge sort algorithm implementation */
std::vector<int> mergeSort(std::vector<int> array) {
    PRINTDBG_SINGLE_ARRAY(array, "mergeSort: ");

    int arraySize = array.size();
    if(arraySize == 1) {
        return array;
    }
    else {
        std::vector<int> leftArray;
        std::vector<int> rightArray;

        int count = 1;
        for(std::vector<int>::iterator i = array.begin(); i != array.end(); i++) {
            if(count <= arraySize/2) {
                leftArray.push_back(*i);
            }
            else {
                rightArray.push_back(*i);
            }
            count++;
        }
        std::vector<int> orderedLeft = mergeSort(leftArray);
        std::vector<int> orderedRight = mergeSort(rightArray);

        PRINTDBG_PAIR_ARRAY(orderedLeft,orderedRight);

        return merge(orderedLeft, orderedRight);
    }
}

// QUICK SORT

/* merge partitions operation */
std::vector<int> mergePartitions(std::vector<int> leftArray, int pivotVal, std::vector<int> rightArray) {
    std::vector<int> mergeVector;
    std::vector<int>::iterator i;

    for(i = leftArray.begin(); i != leftArray.end(); i++) {
        mergeVector.push_back(*i);
    }
    mergeVector.push_back(pivotVal);
    for(i = rightArray.begin(); i != rightArray.end(); i++) {
        mergeVector.push_back(*i);
    }

    return mergeVector;
}

/* choose vector pivot */
int choosePivot(std::vector<int> array) {
    return 0;
}

/* quick sort algorithm implementation */
std::vector<int> quickSort(std::vector<int> array) {
    PRINTDBG_SINGLE_ARRAY(array,"quickSort: ");

    int arraySize = array.size();
    if(arraySize <= 1) {
        return array;
    }
    else {
        int pivotAt = choosePivot(array);
        int pivotVal = array.at(pivotAt);

        std::vector<int> leftArray;
        std::vector<int> rightArray;

        int pivotPosition = 0;
        std::vector<int>::iterator i;
        for(i = array.begin(); i != array.end(); i++) {
            if(i == array.begin() + pivotAt) {} 
            else if((*i) <= pivotVal) {
                leftArray.push_back(*i);
                pivotPosition++;
            }
            else {
                rightArray.push_back(*i);
            }
        }

        PRINTDBG_PAIR_ARRAY_PIVOT(leftArray,pivotVal,rightArray);

        std::vector<int> orderedLeft = quickSort(leftArray);
        std::vector<int> orderedRight = quickSort(rightArray);
        std::vector<int> mergedPartitions = mergePartitions(orderedLeft, pivotVal, orderedRight);

        PRINTDBG_SINGLE_ARRAY(mergedPartitions,"merged: ");

        return mergedPartitions;
    }
}
