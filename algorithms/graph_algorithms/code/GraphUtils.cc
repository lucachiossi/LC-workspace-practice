#include "GraphUtils.h"

#include <algorithm>
#include <fstream>
#include <iterator>
#include <jsoncpp/json/json.h> 
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <sstream>
#include <string>

// Adjacency Vertex
int AdjVertex::getId() {
    return this->id;
}

int AdjVertex::getVal() {
    return this->val;
}

void AdjVertex::addEdge(AdjEdge* edge) {
    this->incidenceEdges->push_back(edge);
}

void AdjVertex::eraseEdge(int idEdge) {
    std::vector<AdjEdge*>::iterator it;
    for(it = this->incidenceEdges->begin(); it != this->incidenceEdges->end(); it++) {
        if((*it)->getId() == idEdge) {
            this->incidenceEdges->erase(it);
        }
    }
}

// Adjacency Edge


int AdjEdge::getId() {
       return this->id;
}


// Adjacency Linked LIst
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
        this->idVertex = i;
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
                std::cout << "edge connecting " << y << " and " << x << std::endl;

                AdjVertex* left = this->vertecesList->at(y);
                AdjVertex* right = this->vertecesList->at(x);

                AdjEdge* edge = new AdjEdge(this->idEdge, left, right);

                left->addEdge(edge);
                right->addEdge(edge);

                this->edgesList->emplace(edge->getId(),edge);
            }
        }
    }
}

AdjacencyList::~AdjacencyList() {

}

