#include "GraphAlgorithms.h"

#include <algorithm>
#include <deque>
#include <ios>
#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <string.h>

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

// Dijkstra's Shortest Path
/* 
 * correct if there are no negative edges
 * very efficient if using Heap Structures */
struct heap_element {
    AdjVertex* vertex;
    int distance_from_start;
    AdjVertex* previous_vertex;    
};

struct order_heap {
    bool operator()(struct heap_element a, struct heap_element b) const{
        return a.distance_from_start>b.distance_from_start;
    }
};

void Dijkstras_Shortest_Path(AdjacencyList& list, AdjVertex* start, AdjVertex* end) {
    std::vector<heap_element> heap;
    struct heap_element elem;

    elem.vertex = start;
    elem.distance_from_start = 0;
    elem.previous_vertex = nullptr;

    heap.push_back(elem);
    std::make_heap(heap.begin(), heap.end(), order_heap());

    struct heap_element current = heap.front();
    AdjVertex* exploringVertex = current.vertex;
    std::pop_heap(heap.begin(), heap.end(), order_heap());
    heap.pop_back();

    while(exploringVertex->getId() != end->getId()) {
        exploringVertex->setExplored(true);
        std::cout << "exploring node " << exploringVertex->getId() << std::endl;
        for(auto it = exploringVertex->getIncidenceEdges()->begin(); it != exploringVertex->getIncidenceEdges()->end(); it++) {
            AdjVertex* following = (*it)->getFollowing();
            if(!following->isExplored()) {
                std::cout << "edge " << following->getId() << std::endl;
                struct heap_element temp;
                temp.vertex = following;
                temp.distance_from_start = (*it)->getWeight() + current.distance_from_start;
                temp.previous_vertex = exploringVertex; 

                // if using an heap, it has to be updated when encountering new crossing edges
                // (with new inserts or updates)
                bool insert = true;
                for(auto itt = heap.begin(); itt != heap.end(); itt++) {
                    if((*itt).vertex->getId() == temp.vertex->getId()) {
                        if((*itt).distance_from_start > temp.distance_from_start) {
                            std::cout << "updating distance and previous of node " << (*itt).vertex->getId() << std::endl;
                            heap.erase(itt);
                            break;
                        }
                        else
                            insert = false;
                    }
                }

                if(insert) {
                    std::cout << "inserting in heap " << temp.vertex->getId() << ", distance " << temp.distance_from_start << std::endl;
                    heap.push_back(temp);
                    std::push_heap(heap.begin(), heap.end(), order_heap());
                }
            }
        }
        current = heap.front();
        exploringVertex = current.vertex;
        std::pop_heap(heap.begin(), heap.end(), order_heap());
        heap.pop_back();
    }
    std::cout << "found shortest path with length " << current.distance_from_start << ", previous " << current.previous_vertex->getId();
}

// Random Contraction Algorithm //TODO
void Minimum_Cutting_Edge(AdjacencyList& adj_list) {
    std::map<int,AdjVertex*>* verteces = adj_list.getVerteces();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0, verteces->size());
    auto start_it = verteces->begin();
    for(int i = 0; i < distribution(generator); i++) {
        start_it++;
    }
    AdjVertex* current = start_it->second;
    std::cout << "start with node: " << current->getId() << std::endl;

    /* while(current != nullptr) { */
    /*     std::vector<AdjEdge*>* edges = current->getIncidenceEdges(); */
    /*     std::uniform_int_distribution<int> edge_distribution(0,edges->size()); */
    /*     int edge_to_collapse = edge_distribution(generator); */
    /*     AdjEdge* edge = *(edges->begin()+edge_to_collapse); */
    /*     AdjVertex* next = edge->getFollowing(); */
    /*     std::cout << "collapse " << current->getId() << " with " << next->getId() << std::endl; */
    /* } */
}

// Minimum Spanning Tree
struct prim_compare_edges {
    bool operator()(AdjEdge* a, AdjEdge* b) const{
        return ((a->getWeight()>b->getWeight() && !(b->getFollowing()->isExplored())) || 
                (a->getFollowing()->isExplored() && !(b->getFollowing()->isExplored())) ||
                (a->getWeight()>b->getWeight() && (a->getFollowing()->isExplored())));
    }
};

void Prim_Algorithm(AdjacencyList& list) {
    std::vector<AdjEdge*> spanning_tree;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,list.getVerteces()->size()-1);
    int start_vertex = distribution(generator);

    std::map<int,AdjVertex*>::iterator start_it = list.getVerteces()->begin();
    for(int i = 0; i < start_vertex; i++) {
        start_it++;
    }

    AdjVertex* current = start_it->second;
    int spanned_verteces = 1;
    /* std::cout << "start with vertex: " << current->getId() << std::endl; */

    std::vector<AdjEdge*> crossing_edges;
    while(spanned_verteces != list.getVerteces()->size()) {
        current->setExplored(true);
        for(auto it = current->getIncidenceEdges()->begin(); it != current->getIncidenceEdges()->end(); it++) {
            crossing_edges.push_back(*it);
        }
        std::make_heap(crossing_edges.begin(), crossing_edges.end(), prim_compare_edges());

        AdjEdge* spanning_edge = crossing_edges.front();
        spanning_tree.push_back(spanning_edge);
        current = spanning_edge->getFollowing();
        /* std::cout << "going to " << current->getId() << "edge " << spanning_edge->getId() << std::endl; */
        spanned_verteces++;
    }

    std::cout << "SPANNING TREE:\n";
    for(auto it = spanning_tree.begin(); it != spanning_tree.end(); it++) {
        std::cout << "edge " << (*it)->getId() << std::endl;
    }
}

struct Kruskal_order_edges {
    bool operator() (AdjEdge* a, AdjEdge* b) const {
        return (a->getWeight()<b->getWeight());
    }
};

struct Kruskal_order_verteces {
    bool operator() (AdjVertex* a, AdjVertex* b) const {
        return (a->getId()<b->getId());
    }
};

void Kruskal_Algorithm(AdjacencyList& list) {
    std::vector<AdjEdge*> spanning_tree;

    std::vector<AdjEdge*> edges;
    for(auto it = list.getEdges()->begin(); it != list.getEdges()->end(); it++) {
        edges.push_back(it->second);
    }
    std::sort(edges.begin(), edges.end(), Kruskal_order_edges());

    std::vector<std::set<AdjVertex*>> union_find;

    for(auto it = edges.begin(); it != edges.end(); it++) {
        AdjEdge* current = (*it);
        int previous_set = -1;
        int following_set = -1;
        for(int i = 0; i < union_find.size(); i++) {
            auto set = union_find.at(i);
            if(set.find(current->getPrevious()) != set.end()) {
                previous_set = i;
            }
            if(set.find(current->getFollowing()) != set.end()) {
                following_set = i;
            }
        }
        /* std::cout << "found previous_set: " << previous_set << ", following_set: " << following_set; */
        /* std::cout << "for verteces [" << current->getPrevious()->getId() << "," << current->getFollowing()->getId() <<"]" << std::endl; */
        if(previous_set == -1 || following_set == -1) {   
            if(previous_set == -1 && following_set == -1) {
                /* std::cout << "inserted new disjunction set" << std::endl; */
                std::set<AdjVertex*> set;
                set.emplace(current->getPrevious());
                set.emplace(current->getFollowing());
                union_find.emplace_back(set.begin(),set.end());
                spanning_tree.push_back(current);
            }
            else if(previous_set == -1 && following_set != -1) {
                /* std::cout << "inserted into following disjunction set" << std::endl; */
                std::set<AdjVertex*>& set = union_find.at(following_set);
                set.emplace(current->getPrevious());
                spanning_tree.push_back(current);
            }
            else if(previous_set != -1 && following_set == -1) {
                /* std::cout << "inserted into previous disjunction set" << std::endl; */
                std::set<AdjVertex*>& set = union_find.at(previous_set);
                set.emplace(current->getFollowing());
                spanning_tree.push_back(current);
            }
        }
        else {
            if(previous_set == following_set) {
                /* std::cout << "do nothing" << std::endl; */
            } 
            else {
                /* std::cout << "merge sets" << std::endl; */
                std::set<AdjVertex*>& previousSet = union_find.at(previous_set);
                std::set<AdjVertex*>& followingSet = union_find.at(following_set);
                std::set<AdjVertex*> set;
                std::merge(previousSet.begin(),previousSet.end(),followingSet.begin(),followingSet.end(),std::inserter(set,set.begin()));
                union_find.erase(union_find.begin()+previous_set);
                union_find.erase(union_find.begin()+following_set);
                union_find.emplace_back(set.begin(),set.end());
                spanning_tree.push_back(current);
            }
        }
    }

    std::cout << "SPANNING TREE" << std::endl;
    for(auto it = spanning_tree.begin(); it != spanning_tree.end(); it++) {
        std::cout << "edge: " << (*it)->getId() << std::endl;
    }
}

// Path Graph -> graph with 2 verteces with degree 1 and all the others with degree 2
void WIT_PathGraph(AdjacencyList& list, AdjVertex* start, AdjVertex* end) {
    std::cout << "find Optimal Value" << std::endl;
    int dim = list.getVerteces()->size();
    int weights[dim+1];
    std::vector<AdjVertex*> exploring_status;
    weights[0] = 0;
    weights[1] = start->getVal();
    exploring_status.push_back(start);
    AdjVertex* current = (*start->getIncidenceEdges()->begin())->getFollowing();
    for(int i = 2; i <= dim; i++) {
        exploring_status.push_back(current);
        std::cout << "exploring " << current->getId() << std::endl;
        if(weights[i-2]+current->getVal() > weights[i-1]) {
            weights[i] = weights[i-2]+current->getVal();
        }
        else {
            weights[i] = weights[i-1];
        }
        current = (*current->getIncidenceEdges()->begin())->getFollowing();
    }

    std::cout << "exploring status:";
    for(auto it = exploring_status.begin(); it != exploring_status.end(); it++) {
        std::cout << " " << (*it)->getId();
    }
    std::cout << std::endl;

    std::cout << "weight sums:";
    for(int i = 0; i <= dim; i++) {
        std::cout << " " << weights[i];    
    }
    std::cout << std::endl;

    std::cout << "find Optimal Solution" << std::endl;
    std::vector<AdjVertex*> optimalSolution;
    int i = dim;
    while(i>=1) {
        int weight_i = exploring_status.at(i-1)->getVal();
        /* std::cout << "weight_i" << weight_i; */
        std::cout << "weights[i-2]: " << weights[i-2] << std::endl;
        if(weights[i-1] >= weights[i-2]+weight_i) {
            i-=1;
        }
        else {
            optimalSolution.push_back(exploring_status.at(i-1));
            i-=2;
        }
    }

    std::cout << "optimal solution:";
    for(auto it = optimalSolution.begin(); it != optimalSolution.end(); it++) {
        std::cout << " " << (*it)->getId();
    }
    std::cout << std::endl;
}

int get_alfa(std::string& string1, std::string& string2) {
    int alfa_gap = 1;
    int alfa_mismatch = 1;

    char* str1 = const_cast<char*>(string1.c_str());
    char* str2 = const_cast<char*>(string2.c_str());


    int size1 = strlen(str1);
    int size2 = strlen(str2);
    std::cout << "size1: " << size1 << ", size2: " << size2 << std::endl;

    int cycle;
    if(size1 > size2) {
        cycle = size1;
    }
    else {
        cycle = size2;
    }

    int alfa = 0;
    for(int i = 0; i < cycle; i++) {
        if(i >= size1 || i > size2) {
            alfa += alfa_gap;
        }
        else {
            if(str1[i] == str2[i]) {
                alfa += 0;
            }
            else if(str1[i] == '0' || str2[i] == '0') {
                alfa += alfa_gap;
            }
            else {
                alfa += alfa_mismatch;
            }
        }
    }

    std::cout << "mismatch of " << str1 << " and " << str2 << ": " << alfa << std::endl;
    return alfa;
}


void SequenceAlignmentProblem(std::string& string1, std::string& string2) {
    int A[string1.length()][string2.length()];
    // get values
    std::cout << "get alfa evaluations" << std::endl;
    std::string temp1;
    std::string temp2;
    for(int i = 0; i < string1.length(); i++) {
        temp1.assign(string1,0,i+1);
        temp2.assign(string2,0,1);
        A[i][0] = get_alfa(temp1,temp2);
    }
    for(int j = 0; j < string2.length(); j++) {
        temp1.assign(string1,0,1);
        temp2.assign(string2,0,j+1);
        A[0][j] = get_alfa(temp1,temp2);
    }
    for(int i = 1; i < string1.length(); i++) {
        for(int j = 1; j < string2.length(); j++) {
            std::cout << "iter" << std::endl;
            temp1.assign(string1,0,i+1);
            temp2.assign(string2,0,j+1);
            std::vector<int> min;
            std::make_heap(min.begin(), min.end());
            min.push_back(get_alfa(temp1, temp2)+A[i-1][j-1]); std::push_heap(min.begin(), min.end());
            temp1.assign(string1,0,i);
            temp2.assign(string1,0,j+1);
            min.push_back(get_alfa(temp1, temp2)); std::push_heap(min.begin(), min.end());
            temp1.assign(string1,0,i+1);
            temp2.assign(string1,0,j);
            min.push_back(get_alfa(temp1, temp2)); std::push_heap(min.begin(), min.end());
            A[i][j] = min.front();
        }
    }
    // print values
    std::cout << "penalties:\n";
    for(int i = 0; i < string1.length(); i++) {
        for(int j = 0; j < string2.length(); j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
