#ifndef SHORTEST_PATH_HPP
#define SHORTEST_PATH_HPP

#include "graph.hpp"
#include <vector>

// Esta estructura guardará el resultado de nuestra búsqueda
struct PathResult {
    long long total_distance;
    std::vector<int> path_nodes;
};

// Función principal de Dijkstra
PathResult find_shortest_path(const Graph& g, int source_orig, int target_orig);

#endif