#include "GraphSearch.h"
#include <iostream>
#include <sstream>
#include <string>

// GraphExploration
GraphExploration::GraphExploration(AdjVertex* startVertex) {
    this->explorationStatus.push_back(startVertex);
    startVertex->setExplored(true);
    /* std::cout << "initialising GraphExploration with " << startVertex << std::endl; */
}


AdjVertex* GraphExploration::getFront() {
    return this->explorationStatus.front();
}

// BreadthFirstSearch
BreadthFirstSearch::BreadthFirstSearch(AdjVertex* startVertex) : GraphExploration(startVertex) {
    std::cout << "initialising BreadthFirstSearch with " << startVertex->getId() << std::endl;
}

void BreadthFirstSearch::explore() {
    AdjVertex* vertex = this->explorationStatus.front();
    this->explorationStatus.pop_front();
    for(auto it = vertex->getIncidenceEdges()->begin(); it != vertex->getIncidenceEdges()->end(); it++) {
        AdjVertex* nextCandidate = (*it)->opposite(vertex);
        if(!(nextCandidate->isExplored())) {
            nextCandidate->setExplored(true);
            this->explorationStatus.push_back(nextCandidate);
        }
    }
}

std::string BreadthFirstSearch::printExplorationStatus() {
    std::stringstream buffer;
    buffer << "BFS queue:";
    for(auto it = this->explorationStatus.begin(); it != this->explorationStatus.end(); it++) {
        buffer << " " << (*it)->getId();
    }
    buffer << std::endl; 
    return buffer.str();
}

void BreadthFirstSearch::printExploration() {
    std::cout << "BFS exploriation" << std::endl;
    while(this->explorationStatus.size() != 0) {
        std::cout << this->printExplorationStatus();
        this->explore();
    }
}

// DepthFirstSearch
DepthFirstSearch::DepthFirstSearch(AdjVertex* startVertex) : GraphExploration(startVertex) {
    std::cout << "initialising DepthFirstSearch with " << startVertex->getId() << std::endl;
}

void DepthFirstSearch::explore() {
    AdjVertex* vertex = this->explorationStatus.front();
    this->explorationStatus.pop_front();
    for(auto it = vertex->getIncidenceEdges()->begin(); it != vertex->getIncidenceEdges()->end(); it++) {
        AdjVertex* nextCandidate = (*it)->opposite(vertex);
        if(!(nextCandidate->isExplored())) {
            nextCandidate->setExplored(true);
            this->explorationStatus.push_front(nextCandidate);
        }
    }
}

std::string DepthFirstSearch::printExplorationStatus() {
    std::stringstream buffer;
    buffer << "DFS queue:";
    for(auto it = this->explorationStatus.begin(); it != this->explorationStatus.end(); it++) {
        buffer << " " << (*it)->getId();
    }
    buffer << std::endl; 
    return buffer.str();
}

void DepthFirstSearch::printExploration() {
    std::cout << "DFS exploriation" << std::endl;
    while(this->explorationStatus.size() != 0) {
        std::cout << this->printExplorationStatus();
        this->explore();
    }
}
