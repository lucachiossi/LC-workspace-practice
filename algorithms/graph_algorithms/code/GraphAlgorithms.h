#ifndef GRAPH_ALGORITHMS
#define GRAPH_ALGORITHMS

#include "GraphUtils.h"
#include "GraphSearch.h"

// (Shortest) Path
void shortestPath_BFS(AdjVertex* start, AdjVertex* end);
bool shortestPath_DFS(AdjVertex* start, AdjVertex* end);

// Topological Sort
void topologicalSort_DFS(std::map<int, AdjVertex*>* vertecesList, std::vector<AdjVertex*>& topologically_ordered_verteces);

// Strongly Connected Component SCC
void Kosaraju_Algorithm(AdjacencyList& list);

// Minimum Cut Problem //TODO
void Minimum_Cutting_Edge(AdjacencyList& adj_list);

// Dijkstra's Shortest Path (Greedy)
void Dijkstras_Shortest_Path(AdjacencyList& list, AdjVertex* start, AdjVertex* end);

// Minimum Spanning Tree
void Prim_Algorithm(AdjacencyList& list);
void Kruskal_Algorithm(AdjacencyList& list);

// Dinamic Programming
void WIT_PathGraph(AdjacencyList& list, AdjVertex* start, AdjVertex* end);
    /* it is interesting to see the following algorithm as the
     * possible optimal scenarios are 3 */
void SequenceAlignmentProblem(std::string& string1, std::string& string2);

// Bellman-Ford's Shortest Path (DP)
void Bellman_Ford_Algorithm(AdjacencyList& adj_list, AdjVertex* start, AdjVertex* end);

// NP-Complete Problems
/* Knapskack Problem */
// Exact Algorithm

// Approximation Algorithm
#endif
