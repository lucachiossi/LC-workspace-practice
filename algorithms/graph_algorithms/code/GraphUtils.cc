#include "GraphUtils.h"

AdjacencyList::AdjacencyList(char* inputFile) {
    this->adjVertexList = new std::vector<AdjVertex>();
    this->adjEdgeList = new std::vector<AdjEdge>();


}

AdjacencyList::~AdjacencyList() {

}

