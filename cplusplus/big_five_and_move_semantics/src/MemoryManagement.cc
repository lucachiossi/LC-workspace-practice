/* file containing BIG FIVE and MANUAL memory management utilization */

#include <iostream>
#include <ostream>
#include "Data.h"

int main(int argc, char* argv[]) {
    std::cout << "START main" << std::endl << std::endl;

    // RESOURCE INITIALIZATION
    Resource rscOne{};      // rscOne
    Resource rscTwo{10};    // rscTwo

    std::cout << "prova1: " << rscOne.getThirdInt() << std::endl;
    std::cout << "prova2: " << rscTwo.getThirdInt() << std::endl << std::endl;

    Object objOne{};        // objOne
    Object objTwo{1,2,3};   // objTwo
    Object objThree{6,6,6}; // objThree

    std::cout << "prova3:";
    objOne.printInt();
    std::cout << "prova4:";
    objTwo.printInt();

    std::cout << std::endl;

    // COPY POLICY -> default copies variables' address
    /* the Copy Constructor/Assignment must be implemented in order to avoid memory leak
     * if not implemented objThree and objFour will point to the same src */
    Object objFour(objThree);   // objFour
    std::cout << "prova 5:";
    objFour.printInt(); 

    std::cout << std::endl;

    objFour = objTwo;       // objFour
    std::cout << "prova 6:";
    objFour.printInt(); 

    std::cout << std::endl;

    // MOVE POLICY -> not implemented by default
    /* the Move Constructor/Assignment must be implemented in order to reduce allocation and
     * deallocation of the memory when using temporary objects */
    objFour = Object(3,3,3);   // objFour
    std::cout << "prova 7:";
    objFour.printInt();

    std::cout << "\nEND main" << std::endl;
    return 0;
}
