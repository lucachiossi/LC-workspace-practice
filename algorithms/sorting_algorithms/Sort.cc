#include "SortAlgorithms.h"
#include <fstream>
#include <ostream>
#include <string>
#include <sys/stat.h>
#include <ctime>

int main(int argc, char* argv[]) {
    // check parameters
    if(argc != 2) {
        std::cout << "bad arguments\ncall: sort <filepath>" << std::endl;
        return 0;
    }
    
    // check if the file exists
    struct stat buffer;   
    if(stat(argv[1], &buffer) != 0) {
        std::cout << "the file '" << argv[1] << "' does no exists" << std::endl;
        return 0;
    }

    // time measuring variables
    std::clock_t c_start;
    std::clock_t c_end;
    double time_elapsed_ms;

    // get input
    std::vector<int> array;
    std::ifstream is;
    is.open ("./inputfile.txt");
    std::string val;
    int temp;

    while(std::getline(is,val,',')) {
        temp = atoi(val.c_str());
        array.push_back(temp);
    }

    PRINTDBG_SINGLE_ARRAY(array,"INPUT");

    std::vector<int> sortedVector;

    // mergesort algorithm
    c_start = std::clock();

    sortedVector = mergeSort(array);
    
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "mergesort took: " << time_elapsed_ms << "ms\n" << std::endl;
    
    PRINTDBG_SINGLE_ARRAY(sortedVector,"OUTPUT");

    // quick sort
    c_start = std::clock();

    sortedVector = quickSort(array);
    
    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "quicksort took: " << time_elapsed_ms << "ms/n" << std::endl;

    PRINTDBG_SINGLE_ARRAY(sortedVector,"OUTPUT");
}
