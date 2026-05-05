#ifndef STRUCTURAL_HPP
#define STRUCTURAL_HPP

#include "graph.hpp"
#include <string>

struct StructuralAnalysis {
    int num_components;
    int max_component_size;
    int max_degree_node_idx;
    int max_degree;
    int approx_diameter;
};

// Funciones para calcular e imprimir las estadísticas
StructuralAnalysis run_structural_analysis(const Graph& g);
void print_structural_summary(const Graph& g, const StructuralAnalysis& a);
bool write_structural_report(const Graph& g, const StructuralAnalysis& a, const std::string& path);

#endif