#include "GraphAlgorithms.h"

#include <deque>
#include <iostream>
#include <vector>

// MINIMUM PATH PROBLEM

void shortestPath_BFS(AdjVertex* start, AdjVertex* end) {
    std::deque<AdjVertex*> queue;
    start->setExplored(true);
    queue.push_front(start);
    while(queue.size() != 0) {
        AdjVertex* exploring = queue.front();
        queue.pop_front();
        // check if found end
        std::cout << "exploring " << exploring->getId() << std::endl;
        if(exploring->getId() == end->getId()) {
            std::cout << "found path [" << start->getId() << "," << end->getId() << "] with length " << exploring->getDistance() << std::endl;
            return;
        }
        // explore next nodes
        std::vector<AdjEdge*>* edges = exploring->getIncidenceEdges();
        for(auto it = edges->begin(); it != edges->end(); it++) {
            AdjVertex* following = (*it)->getFollowing();
            if(!(following->isExplored())) {
                following->setExplored(true);
                following->setDistance(exploring->getDistance()+1);
                queue.push_back(following);
            }
        }
    }
    std::cout << "NOT found path [" << start->getId() << "," << end->getId() << "]" << std::endl;
}

void shortestPath_DFS(AdjVertex* start, AdjVertex* end) {
    //TODO
}

