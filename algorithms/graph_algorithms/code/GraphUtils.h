#ifndef GRAPH_UTILS
#define GRAPH_UTILS

#define BAD_ARGUMENTS -1

#include <clocale>
#include <map>
#include <vector>
#include <iostream>

class AdjVertex;
class AdjEdge;

class AdjVertex {
    private:
        int id;
        int val;
        std::vector<AdjEdge*>* incidenceEdges;
    public:
        AdjVertex(int id, int val=0) :
            id(id),
            val(val) {
                this->incidenceEdges = new std::vector<AdjEdge*>();
                std::cout << "created vertex " << id << std::endl;
            }
        ~AdjVertex() {
            std::vector<AdjEdge*>::iterator it;
            for(it = this->incidenceEdges->begin(); it != this->incidenceEdges->end(); it++) {
                AdjEdge* edge = *it;
                delete edge;
            }
            delete this->incidenceEdges;
            std::cout << "deleted vertex " << id << std::endl;
        }
        int getId();
        int getVal();
        void addEdge(AdjEdge* edge);
        void eraseEdge(int idEdge);
        /* std::vector<int> incidentEdges(); // */
        /* bool isIncidentTo(AdjVertex* v); // */
};

class AdjEdge {
    private:
        int id;
        int weight;
        AdjVertex* left;
        AdjVertex* right;
    public:
        AdjEdge(int id, AdjVertex* left, AdjVertex* right, int weight=1) :
            id(id),
            left(left),
            right(right),
            weight(weight) {
                std::cout << "created edge " << id << std::endl;
            }
        ~AdjEdge() {
            this->left->eraseEdge(this->id);
            this->right->eraseEdge(this->id);
            std::cout << "deleted edge " << id << std::endl;
        };
        int getId();
};

/*
 * directed/undirected
 * weighted/unweighted */
class AdjacencyList {
    private:
        std::map<int, AdjVertex*>* vertecesList;
        std::map<int, AdjEdge*>* edgesList;
        int idVertex;
        int idEdge;
    public:
        /*
         * construct the Adjacency Linked List from a jsonFile containing
         * directed: d|nd
         * weighted edges: we|nwe
         * matrix: adjacency_matrix */
        AdjacencyList(char* jsonInputFile);
        ~AdjacencyList();

        std::vector<AdjVertex> getVerteces();
        std::vector<AdjEdge> getEdges();

        void insertVertex(AdjVertex vertex);
        void eraseVertex(int id);

        void insertEdge(AdjEdge edge);
        void eraseEdge(int idEdge);
};

/*
 * directed/undirected
 * weighted/unweighted */
/* class AdjacencyMatrix { */

/* }; */

#endif
