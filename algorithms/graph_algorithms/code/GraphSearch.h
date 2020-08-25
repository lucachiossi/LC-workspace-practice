#ifndef GRAPH_SEARCH
#define GRAPH_SEARCH

#include "GraphUtils.h"
#include <deque>
#include <iostream>
#include <string>

class GraphExploration { // abstract class
    protected:
        std::deque<AdjVertex*> explorationStatus;
    public:
        explicit GraphExploration(AdjVertex* startVertex);
        virtual ~GraphExploration() = default;
        AdjVertex* getFront();
        virtual void explore() = 0; // pure virtual method (abstract)
        virtual std::string printExplorationStatus() = 0; // pure virtual method (abstract)
        virtual void printExploration() = 0; // pure virtual method (abstract)
};

/* Breadth First Search [BFS] implementation */
class BreadthFirstSearch : public GraphExploration {
    public:
        explicit BreadthFirstSearch(AdjVertex* startVertex);
        ~BreadthFirstSearch() {};
        void explore() override;
        std::string printExplorationStatus() override;
        void printExploration() override;
};

/* Depth First Search [DFS] implementation */
class DepthFirstSearch : public GraphExploration {
    public:
        DepthFirstSearch(AdjVertex* startVertex);
        ~DepthFirstSearch() {};
        void explore() override;
        std::string printExplorationStatus() override;
        void printExploration() override;
};

#endif
