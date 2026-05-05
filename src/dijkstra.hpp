#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include "graph.hpp"
#include <vector>

struct DijkstraResult {
    long long distance;
    int explored_nodes;
    double time_ms;
    std::vector<int> path;
};

DijkstraResult run_dijkstra(const Graph& g, int source_orig, int target_orig, bool save_path);

#endif