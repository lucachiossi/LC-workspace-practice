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

// Minimum Cut Problem
// TODO

// Dijkstra's Shortest Path
void Dijkstras_Shortest_Path(AdjacencyList& list, AdjVertex* start, AdjVertex* end);

#endif
