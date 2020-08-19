#include <vector>
#include <iostream>

#define DEBUG 1
#if DEBUG
#define PRINTDBG_SINGLE_ARRAY(array,prefix) do{ \
    std::cout << prefix << ""; \
    printArray(array); \
    std::cout << std::endl;} while(0)
#define PRINTDBG_PAIR_ARRAY(leftArray,rightArray) do{ \
    printArray(leftArray); \
    std::cout << " | ";  \
    printArray(rightArray); \
    std::cout << std::endl;} while(0)
#define PRINTDBG_PAIR_ARRAY_PIVOT(leftArray,pivotVal,rightArray) do{ \
    printArray(leftArray); \
    std::cout << " | " << pivotVal << " | "; \
    printArray(rightArray); \
    std::cout << std::endl;} while(0)
#else
#define PRINTDBG_SINGLE_ARRAY(array,prefix) {}
#define PRINTDBG_PAIR_ARRAY(leftArray,rightArray) {}
#define PRINTDBG_PAIR_ARRAY_PIVOT(leftArray,pivotVal,rightArray) {}
#endif

// utility functions
void printArray(std::vector<int> array);

// merge sort
std::vector<int> merge(std::vector<int> leftArray, std::vector<int> rightArray);
std::vector<int> mergeSort(std::vector<int> array);

// quick sort
std::vector<int> quickSort(std::vector<int> array);
