#ifndef BFS_HPP
#define BFS_HPP

#include "graph.hpp"
#include <vector>

struct BFSResult {
    int jumps;
    int explored_nodes;
    double time_ms;
};

BFSResult run_bfs(const Graph& g, int source_orig, int target_orig);

#endif