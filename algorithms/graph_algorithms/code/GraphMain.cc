/*
 * Graph experiments and Algotithms practicing */

#include "GraphUtils.h"
#include "GraphSearch.h"
#include "GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <sys/stat.h>

#include <vector>

int main(int argc, char* argv[]) {
    std::cout << "-*-*-*START*-*-*-\n\n";

    std::string errorCallMessage = "graph_program <input-file> m|ll <experiment-number>";

    // Check Arguments
    if(argc != 4) {
        std::cout << "bad arguments, please call:\n" << errorCallMessage << std::endl;
        exit(BAD_ARGUMENTS);
    }

    std::string inputFile = argv[1];
    std::string graphRepresentation = argv[2];
    std::string experimentNumberCheck = argv[3];
    int experimentNumber = -1;

    struct stat statBuff;
    if((stat(argv[1], &statBuff) != 0)) {
        std::cout << "bad <input-file>, please call:\n" << errorCallMessage << std::endl;
        exit(BAD_ARGUMENTS);
    }
    if((graphRepresentation != "m" && graphRepresentation != "ll")) {
        std::cout << "bad m|ll, please call:\n" << errorCallMessage << std::endl;
        exit(BAD_ARGUMENTS);
    }
    for(int i = 0; i < experimentNumberCheck.length(); i++) {
        if(!isdigit(experimentNumberCheck.at(i))) {
            std::cout << "<experiment-number> bad number, please call:\n" << errorCallMessage << std::endl;
            exit(BAD_ARGUMENTS);
        }
    }
    experimentNumber = atoi(argv[3]);
    /* std::cout << inputFile << std::endl << graphRepresentation << std::endl << experimentNumber << std::endl; */

    // Get Graph
    
    std::cout << "\n-*-*-*END*-*-*-\n";
}
