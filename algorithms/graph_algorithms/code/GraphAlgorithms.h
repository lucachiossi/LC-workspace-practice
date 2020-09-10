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
// All Pairs Shortest Path //TODO
/* void Floyd_Warshall_Algorithm(AdjacencyList& adj_list); */ 
/* void Johsnon_Algorithm(AdjacencyList& adj_list); */

// NP-Complete Problems
/* Knapskack Problem */

// Exact Algorithm (KP) (DP) - (wi integers) - correct
void Knapsack(std::vector<int>& weights, std::vector<int>& vals, int W);
// Approximation Algorithm (KP) (Greedy) - (go faster) - less precise
void Knapsack_greedy_heuristic(std::vector<int>& weights, std::vector<int>& vals, int W);
// Approximation Algorithm (KP) (DP) - (vi integers) - less precise
void Knapsack_dynamic_heuristic(std::vector<int>& weights, std::vector<int>& vals, int W);

#endif
