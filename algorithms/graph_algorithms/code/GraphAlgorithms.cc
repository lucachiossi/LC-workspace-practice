#include "GraphAlgorithms.h"

#include <deque>
#include <iostream>
#include <vector>

// BFS Shortest Path
void shortestPath_BFS(AdjVertex* start, AdjVertex* end) {
    std::deque<AdjVertex*> queue;
    start->setExplored(true);
    queue.push_front(start);
    while(queue.size() != 0) {
        AdjVertex* exploring = queue.front();
        queue.pop_front();
        // check if found end
        /* std::cout << "exploring " << exploring->getId() << std::endl; */
        if(exploring->getId() == end->getId()) {
            /* std::cout << "found path [" << start->getId() << "," << end->getId() << "] with length " << exploring->getDistance() << std::endl; */
            return;
        }
        // explore next nodes
        std::vector<AdjEdge*>* edges = exploring->getIncidenceEdges();
        for(auto it = edges->begin(); it != edges->end(); it++) {
            AdjVertex* following = (*it)->getFollowing();
            if(!(following->isExplored())) {
                following->setExplored(true);
                following->setDistance(exploring->getDistance()+(*it)->getWeight());
                queue.push_back(following);
            }
        }
    }
    /* std::cout << "NOT found path [" << start->getId() << "," << end->getId() << "]" << std::endl; */
}

// DFS Search Path
bool shortestPath_DFS(AdjVertex* start, AdjVertex* end) {
    start->setExplored(true);
    if(start->getId() == end->getId()) {
        /* std::cout << "found path with length " << start->getDistance() << std::endl; */
        return true;
    }
    for(auto it = start->getIncidenceEdges()->begin(); it != start->getIncidenceEdges()->end(); it++) {
        AdjVertex* following = (*it)->getFollowing();
        if(!following->isExplored()) {
            /* std::cout << "exploring " << following->getId() << std::endl; */
            following->setDistance(start->getDistance()+(*it)->getWeight());
            if(shortestPath_DFS(following, end)) {
                return true;
            }
        }
    }
    /* std::cout << "no path [" << start->getId() << "," << end->getId() << "]" << std::endl; */
    return false;
}

// Topological Ordering
int current_label;

void sort_DFS(AdjVertex* v, std::vector<AdjVertex*>& topologically_ordered_verteces) {
    v->setExplored(true);
    for(auto it = v->getIncidenceEdges()->begin(); it != v->getIncidenceEdges()->end(); it++) {
        if(!(*it)->getFollowing()->isExplored()) {
            sort_DFS((*it)->getFollowing(), topologically_ordered_verteces);
        }
    }
    v->setLabel(current_label);
    /* std::cout << "vertex " << v->getId() << " with label " << v->getLabel() << std::endl; */
    topologically_ordered_verteces.push_back(v);
    current_label--;
}

void topologicalSort_DFS(std::map<int, AdjVertex*>* vertecesList, std::vector<AdjVertex*>& topologically_ordered_verteces) {
    current_label = vertecesList->size();
    for(auto it = vertecesList->begin(); it != vertecesList->end(); it++) {
        if(!(it->second->isExplored())) {
            sort_DFS(it->second, topologically_ordered_verteces);
        }
    }
}

// Strongly Connected Components
int t = 0;
AdjVertex* s = nullptr;

void Kosaraju_DFS(AdjVertex* v) {
    v->setExplored(true);
    v->setLeader(s);
    for(auto it = v->getIncidenceEdges()->begin(); it != v->getIncidenceEdges()->end(); it++) {
        if(!((*it)->getFollowing()->isExplored())) {
            Kosaraju_DFS((*it)->getFollowing());
        }
    }
}

void Kosaraju_Algorithm(AdjacencyList& list) {
    // 1) reverse edges
    std::map<int,AdjEdge*>* edges = list.getEdges();
    for(auto it = edges->begin(); it != edges->end(); it++) {
        it->second->reverse();
    }
    std::vector<AdjVertex*> topologically_ordered_verteces;
    
    // 2) Topological Ordering on Grev
    topologicalSort_DFS(list.getVerteces(), topologically_ordered_verteces);
    /* std::cout << list.printGraph("labelled graph"); */
    
    // make G ready
    for(auto it = edges->begin(); it != edges->end(); it++) {
        it->second->reverse();
    }
    for(auto t = list.getVerteces()->begin(); t != list.getVerteces()->end(); t++) {
        t->second->setExplored(false);
    }
    
    // 3) Discover SCCs one by one -> processing nodes in decreasing order of label
    for(auto itt = topologically_ordered_verteces.begin(); itt != topologically_ordered_verteces.end(); itt++) {
        s = *itt;
        if(!(*itt)->isExplored()) {
            Kosaraju_DFS(*itt);
        }
    }
}
