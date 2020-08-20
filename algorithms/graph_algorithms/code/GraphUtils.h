#ifndef GRAPH_UTILS
#define GRAPH_UTILS

#define BAD_ARGUMENTS -1

#include <clocale>
#include <vector>
#include <iostream>

class AdjVertex;
class AdjEdge;

class AdjVertex {
    private:
        int id;
        int val;
        AdjEdge* next;
    public:
        AdjVertex(int id) :
            id(id),
            val(-1),
            next(nullptr) {
            }
        AdjVertex(int id, int val) :
            id(id),
            val(val),
            next(nullptr) {
            }
        /* ~AdjVertex() { */
        /*     while(next != nullptr) { */
        /*         this->adjEdge->erase(); */
        /*     } */
        /* } */
        /* void addEdge(adjEdge edge); */
        /* void erase(); */
};

class AdjEdge {
    private:
        AdjVertex* left;
        AdjVertex* right;
        int id_left;
        int id_right;
        int weight;
    public:
        /* AdjEdge(id_left, id_right); */
        /* AdjEdge(); */
        /* void erase(); */
};

/*
 * directed/undirected
 * weighted/unweighted */
class AdjacencyList {
    private:
        std::vector<AdjVertex>* adjVertexList;
        std::vector<AdjEdge>* adjEdgeList;
    public:
        /*
         * construct the Adjacency Linked List from a jsonFile containing
         * directed: d|nd
         * weighted edges: we|nwe
         * matrix: adjacency_matrix */
        AdjacencyList(char* jsonInputFile);
        ~AdjacencyList();

        AdjVertex** getVerteces();
        AdjEdge** getEdges();

        void insertVertex(AdjVertex vertex);
        void eraseVertex(AdjVertex vertex);

        void insertEdge(AdjEdge edge);
        void eraseEdge(AdjEdge edge);
};

/*
 * directed/undirected
 * weighted/unweighted */
/* class AdjacencyMatrix { */

/* }; */

#endif
