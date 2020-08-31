/*
 * Graph experiments and Algotithms practicing */

#include "GraphUtils.h"
#include "GraphSearch.h"
#include "GraphAlgorithms.h"

#include <iostream>
#include <string>
#include <sys/stat.h>
#include <vector>
#include <memory>
#include <ctime>

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

    std::cout << "user input: (" << inputFile << "," << graphRepresentation << "," << experimentNumber << ")\n";

    // time variables
    std::clock_t c_start;
    std::clock_t c_end;
    double time_elapsed_ms;

    // Get Graph
    AdjacencyList adj_list(const_cast<char*>(inputFile.c_str()));
    std::cout << adj_list.printGraph();
    std::map<int,AdjVertex*>* vertecesList = adj_list.getVerteces();
    std::map<int,AdjEdge*>* edgesList = adj_list.getEdges();

    // Experiment1
    std::cout << "TIME RESULTS WILL DIFFERS WITH FUNCTIONS PRINT" << std::endl;
    AdjVertex* startVertex = vertecesList->find(1)->second;
    AdjVertex* endVertex = vertecesList->find(9)->second;

    std::cout << std::endl << "Experiment 1: BFS" << std::endl;
    c_start = std::clock();

    shortestPath_BFS(startVertex, endVertex);

    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "time: " << time_elapsed_ms << " ms" << std::endl;

    adj_list.resetExploration();

    // Experiment2
    std::cout << std::endl << "Experiment 2: DFS" << std::endl;
    c_start = std::clock();

    shortestPath_DFS(startVertex, endVertex);

    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "time: " << time_elapsed_ms << " ms" << std::endl;

    adj_list.resetExploration();

    // Experiment3
    std::cout << std::endl << "Experiment 3: Topological Order" << std::endl;
    c_start = std::clock();

    std::vector<AdjVertex*> topologically_ordered_verteces;
    topologicalSort_DFS(adj_list.getVerteces(), topologically_ordered_verteces);

    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "time: " << time_elapsed_ms << " ms" << std::endl;

    for(auto itt = topologically_ordered_verteces.begin(); itt != topologically_ordered_verteces.end(); itt++) {
        std::cout << "vertex " << (*itt)->getId() << " with label " << (*itt)->getLabel() << std::endl;
    }

    adj_list.resetExploration();

    // Experiment4
    AdjacencyList adj_list_kosaraju(const_cast<char*>(inputFile.c_str()));
    std::cout << std::endl << "Experiment 4: SCC - Kosarajus Algorithm" << std::endl;
    c_start = std::clock();

    /* Kosaraju_Algorithm(adj_list_kosaraju, ); */

    c_end = std::clock();
    time_elapsed_ms = 1000.0 * (c_end-c_start) / CLOCKS_PER_SEC;
    std::cout << "time: " << time_elapsed_ms << " ms" << std::endl;

    adj_list.resetExploration();

    std::cout << "\n-*-*-*END*-*-*-\n";
}
