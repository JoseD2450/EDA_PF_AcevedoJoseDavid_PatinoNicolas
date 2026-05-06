#ifndef SUBGRAPH_HPP
#define SUBGRAPH_HPP

#include "graph.hpp"
#include <vector>
#include <string>

// Estructura para guardar el resultado del Árbol de Expansión Mínima
struct MSTResult {
    long long total_weight;
    std::vector<std::pair<int, int>> edges;
};

// Funciones principales del Modulo C
Graph build_induced_subgraph(const Graph& original_g, const std::vector<int>& path1, const std::vector<int>& path2);
MSTResult run_kruskal(const Graph& subg);
bool has_cycles(const Graph& subg);
void save_subgraph_reports(const Graph& subg, const MSTResult& mst, bool cycle_found);

#endif