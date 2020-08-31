#include "GraphUtils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <jsoncpp/json/json.h> 
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <map>
#include <sstream>
#include <string>
#include <utility>

// Adjacency Vertex
std::string AdjVertex::printVertex() {
    std::stringstream str;
    str << "vertex(id:" << this->id << ", explored: " << this->explored << ", label: " << this->label;
    str << ", numIncidenceEdges:" << this->incidenceEdges->size();
    std::vector<AdjEdge*>::iterator it;
    for(it = this->incidenceEdges->begin(); it != this->incidenceEdges->end();  it++) {
        str << ", " << (*it)->getId();
    }
    str << ")";
    return str.str();
}

AdjVertex::AdjVertex(int id, int val) {
    this->id = id;
    this->val = val;
    this->distance = 0;
    this->label = 0;
    this->explored = false;
    this->incidenceEdges = new std::vector<AdjEdge*>();
    this->leader = nullptr;
    // check vertex created
    /* std::cout << "created " << this->printVertex() << std::endl; */
}

AdjVertex::~AdjVertex() {
    std::vector<AdjEdge*>::iterator it;
    while((it = this->incidenceEdges->begin()) != this->incidenceEdges->end()) {
        delete (*it);
    }
    delete this->incidenceEdges;
    // check vertex deleted
    /* std::cout << "deleted vertex " << this->id << std::endl; */
}

int AdjVertex::getId() {
    return this->id;
}

int AdjVertex::getVal() {
    return this->val;
}

int AdjVertex::getDistance() {
    return this->distance;
}

int AdjVertex::getLabel() {
    return this->label;
}

AdjVertex* AdjVertex::getLeader() {
    return this->leader;
}

/* void AdjVertex::setVal(int val) { */
/*     this->val = val; */
/* } */

void AdjVertex::setDistance(int dist) {
    this->distance = dist;
}

void AdjVertex::setLabel(int label) {
    this->label = label;
}

void AdjVertex::setLeader(AdjVertex* leader) {
    this->leader = leader;
}

bool AdjVertex::isExplored() {
    return this->explored;
}

void AdjVertex::setExplored(bool explored) {
    this->explored = explored;
}

std::vector<AdjEdge*>* AdjVertex::getIncidenceEdges() {
    return this->incidenceEdges;
}

void AdjVertex::addEdge(AdjEdge* edge) {
    this->incidenceEdges->push_back(edge);
    /* std::cout << "added edge " << edge->getId() << " to vertex " << this->id << std::endl; */
}

void AdjVertex::removeEdge(int idEdge) {
    std::vector<AdjEdge*>::iterator it;
    for(it = this->incidenceEdges->begin(); it != this->incidenceEdges->end(); it++) {
        if((*it)->getId() == idEdge) {
            this->incidenceEdges->erase(it);
            break;
        }
    }
    /* std::cout << "removed edge " << idEdge << " from vertex " << this->id << std::endl; */
}

/* 
 * check if (this) vertex and (v) vertex have at least a common edge */
bool AdjVertex::isIncidentTo(AdjVertex* v) {
    for(auto it = this->incidenceEdges->begin(); it != this->incidenceEdges->end(); it++) {
        if((*it)->incidentOn(v)) {
            /* std::cout << "found " << (*it)->getId() << std::endl; */
            return true;
        }
    }
    for(auto it = v->getIncidenceEdges()->begin(); it != v->getIncidenceEdges()->end(); it++) {
        if((*it)->incidentOn(this)) {
            /* std::cout << "found " << (*it)->getId() << std::endl; */
            return true;
        }
    }
    return false;
}

// Adjacency Edge
std::string AdjEdge::printEdge() {
    std::stringstream str;
    str << "edge(id:" << this->id << ", left:" << this->left->getId() << ", right:" << this->right->getId() << ", weight:" << this->weight << ")";
    return str.str();
}

AdjEdge::AdjEdge(int id, AdjVertex* left, AdjVertex* right, int weight) {
    this->id = id;
    this->left = left;
    this->right = right;
    this->weight = weight; 
    // check edge created
    /* std::cout << "created " << this->printEdge() << std::endl; */
}

AdjEdge::~AdjEdge() {
    this->left->removeEdge(this->id);
    // chwck edge deleted
    /* std::cout << "deleted edge " << this->id << std::endl; */
}


int AdjEdge::getId() {
    return this->id;
}

int AdjEdge::getWeight() {
    return this->weight;
}

std::pair<AdjVertex*,AdjVertex*> AdjEdge::endVerteces() {
    return std::pair<AdjVertex*,AdjVertex*>(this->left,this->right);
}

AdjVertex* AdjEdge::opposite(AdjVertex* v) {
    if(this->left->getId() == v->getId()) {
        return this->right;
    }
    else {
        return this->left;
    }
}

bool AdjEdge::incidentOn(AdjVertex* v) {
    int v_id = v->getId();
    if(v_id == this->left->getId() || v_id == this->right->getId()) {
        /* std::cout << "edge " << this->id << " incident with vertex " << v->getId() << std::endl; */
        return true;
    }
    return false;
}

AdjVertex* AdjEdge::getFollowing() {
    return this->right;
}

void AdjEdge::reverse() {
    this->left->removeEdge(this->id);

    AdjVertex* temp = this->left;
    this->left = this->right;
    this->right = temp;
    
    this->left->addEdge(this);

    this->weight = -(this->weight);
}

// Adjacency Linked LIst
std::string AdjacencyList::printVerteces() {
    std::stringstream str;
    str << "---verteces---" << std::endl;
    std::map<int,AdjVertex*>::iterator it;
    for(it = this->vertecesList->begin(); it != this->vertecesList->end(); it++) {
        str << (*it).second->printVertex() << std::endl;
    }
    return str.str();
}

std::string AdjacencyList::printEdges() {
    std::stringstream str;
    str << "---edges---:" << std::endl;
    std::map<int,AdjEdge*>::iterator it;
    for(it = this->edgesList->begin(); it != this->edgesList->end(); it++) {
        str << (*it).second->printEdge() << std::endl;
    }
    return str.str();
}

std::string AdjacencyList::printGraph(std::string message) {
    std::stringstream str;
    str << "\n---Graph -> " << message << std::endl << this->printVerteces() << this->printEdges() << std::endl;
    return str.str();
}

AdjacencyList::AdjacencyList(char* jsonInputFile) {
    std::ifstream ifs(jsonInputFile); 
    Json::Reader reader;
    Json::Value obj;

    reader.parse(ifs, obj);
    bool isDirtected = (obj["directed"].asString() == "d");
    bool isWeighted = (obj["weighted edges"].asString() == "we");

    Json::Value matrix = obj["matrix"];
    int vertex_number = matrix.size();

    // check parameters
    /* std::cout << "json details:\n\tisDirtected: " << isDirtected << "\n\tisWeighted: " << isWeighted << "\n\tvertex number: " << vertex_number << std::endl; */

    // create verteces and edges containers
    this->vertecesList = new std::map<int,AdjVertex*>();
    this->edgesList = new std::map<int,AdjEdge*>();

    // insert verteces
    for(int i = 0; i < vertex_number; i++) {
        AdjVertex* vertex = new AdjVertex(i);
        this->vertecesList->emplace(i,vertex);
        this->idVertex = i+1;
    }

    this->idEdge = 0;

    // insert edges
    for(int y = 0; y < vertex_number; y++) {
        for(int x = 0; x < vertex_number; x++) {
            // get matrix value (x,y)
            std::stringstream val;
            val << obj["matrix"][y][x].asString();

            if(val.str() != "x") {
                // check endpoints
                /* std::cout << "edge connecting " << y << " and " << x << std::endl; */

                AdjVertex* left = this->vertecesList->at(y);
                AdjVertex* right = this->vertecesList->at(x);

                int weight = atoi(val.str().c_str());

                AdjEdge* edge = new AdjEdge(this->idEdge, left, right, weight);
                this->idEdge++;

                left->addEdge(edge); // only left as it is considered also the direction

                this->edgesList->emplace(edge->getId(),edge);
            }
        }
    }
}

AdjacencyList::~AdjacencyList() {
    // delete verteces
    std::map<int,AdjVertex*>::iterator v_it;
    for(v_it = this->vertecesList->begin(); v_it != this->vertecesList->end(); v_it++) {
        delete (*v_it).second;
    }
    delete this->vertecesList;
    // verteces delete incidence edges when they are deleted
    delete this->edgesList;
}

std::map<int,AdjVertex*>* AdjacencyList::getVerteces() {
    return this->vertecesList;
}

std::map<int,AdjEdge*>* AdjacencyList::getEdges() {
    return this->edgesList;
}

void AdjacencyList::insertVertex(int val) {
    AdjVertex* vertex = new AdjVertex(this->idVertex, val);
    this->idVertex++;
    // insert new vertex into verteces list
    this->vertecesList->emplace(vertex->getId(),vertex);
    /* std::cout << "added vertex " << vertex->getId() << " to the graph" << std::endl; */
}

void AdjacencyList::insertEdge(int id_left, int id_right, int weight) {
    auto l = this->vertecesList->find(id_left);
    auto r = this->vertecesList->find(id_right);
    if(l==this->vertecesList->end() || r==this->vertecesList->end()) {
        std::cout << "(!!!) tried to insert edge with not existing verteces linked (!!!)" << std::endl;
        return;
    }
    AdjVertex* left = l->second;
    AdjVertex* right = r->second;
    AdjEdge* edge = new AdjEdge(this->idEdge, left, right, weight);
    this->idEdge++;
    // insert new edge into incidence lists of right as it takes into account direction
    left->addEdge(edge);
    // insert new edge into edges list
    this->edgesList->emplace(edge->getId(),edge);
    /* std::cout << "added edge " << edge->getId() << " to the graph" << std::endl; */
}

void AdjacencyList::eraseVertex(int id) {
    auto v = this->vertecesList->find(id);
    if(v==this->vertecesList->end()) {
        std::cout << "(!!!) tried to erase not existing vertex (!!!)" << std::endl;
        return;
    }
    AdjVertex* vertex = v->second;
    // remove vertex from verteces list
    this->vertecesList->erase(id);
    for(auto it = vertex->getIncidenceEdges()->begin(); it != vertex->getIncidenceEdges()->end(); it++) {
        // remove related edge from edges list
        this->edgesList->erase((*it)->getId());
    }
    delete vertex;
    /* std::cout << "removed vertex " << vertex->getId() << " to the graph" << std::endl; */
}

void AdjacencyList::eraseEdge(int id) {
    auto e = this->edgesList->find(id);
    if(e==this->edgesList->end()) {
        std::cout << "(!!!) tried to erase not existing edge (!!!)" << std::endl;
        return;
    }
    AdjEdge* edge = e->second;
    // remove edge from edges list
    this->edgesList->erase(id);
    delete edge; // remove edge from related vertex incident lists
    /* std::cout << "removed edge " << edge->getId() << " to the graph" << std::endl; */
}

void AdjacencyList::resetExploration() {
    for(auto it = this->vertecesList->begin(); it != this->vertecesList->end(); it++) {
        it->second->setExplored(false);
        it->second->setDistance(0);
        it->second->setLabel(0);
        it->second->setLeader(nullptr);
    }
}

std::string AdjacencyList::printSCC() {
    std::stringstream str;
    str << "SCC:";

    for(auto it = this->vertecesList->begin(); it != this->vertecesList->end(); it++) {
        if(it->second->getLeader() != nullptr) {
            str << std::endl << "id: " << it->second->getId() << ", leader: " << it->second->getLeader()->getId();
        }
    }

    return str.str();
}
