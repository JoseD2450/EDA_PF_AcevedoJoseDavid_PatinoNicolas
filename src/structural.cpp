#include "structural.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <iomanip>

StructuralAnalysis run_structural_analysis(const Graph& g) {
    StructuralAnalysis res = {0, 0, 0, 0, 0};
    if (g.num_nodes() == 0) return res;

    // 1. Nodo de mayor grado
    for (int i = 0; i < g.num_nodes(); ++i) {
        int d = g.adj[i].size();
        if (d > res.max_degree) {
            res.max_degree = d;
            res.max_degree_node_idx = i;
        }
    }

    // 2. Componentes conexas usando BFS
    std::vector<bool> visited(g.num_nodes(), false);
    for (int i = 0; i < g.num_nodes(); ++i) {
        if (!visited[i]) {
            res.num_components++;
            int current_comp_size = 0;
            std::queue<int> q;
            
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                current_comp_size++;

                for (const Edge& e : g.adj[u]) {
                    if (!visited[e.to]) {
                        visited[e.to] = true;
                        q.push(e.to);
                    }
                }
            }

            if (current_comp_size > res.max_component_size) {
                res.max_component_size = current_comp_size;
            }
        }
    }

    // 3. Diámetro aproximado desde el nodo de mayor grado
    std::vector<int> dist(g.num_nodes(), -1);
    std::queue<int> q_diam;

    q_diam.push(res.max_degree_node_idx);
    dist[res.max_degree_node_idx] = 0;
    int max_dist = 0;

    while (!q_diam.empty()) {
        int u = q_diam.front();
        q_diam.pop();

        for (const Edge& e : g.adj[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                if (dist[e.to] > max_dist) {
                    max_dist = dist[e.to];
                }
                q_diam.push(e.to);
            }
        }
    }
    res.approx_diameter = max_dist;

    return res;
}

void print_structural_summary(const Graph& g, const StructuralAnalysis& a) {
    std::cout << "\n--- Resultados Modulo A ---\n";
    std::cout << "Nodos:                     " << g.num_nodes() << "\n";
    std::cout << "Aristas (no dirigidas):    " << g.num_undirected_edges() << "\n";
    std::cout << "Grado promedio:            " << std::fixed << std::setprecision(4) 
              << (2.0 * g.num_undirected_edges() / g.num_nodes()) << "\n";
    std::cout << "Nodo de mayor grado:       " << g.idx_to_orig[a.max_degree_node_idx] 
              << " (Grado: " << a.max_degree << ")\n";
    std::cout << "Componentes conexas:       " << a.num_components << "\n";
    std::cout << "Nodos en comp. principal:  " << a.max_component_size << "\n";
    std::cout << "Diametro aproximado:       " << a.approx_diameter << "\n";
    std::cout << "---------------------------\n";
}

bool write_structural_report(const Graph& g, const StructuralAnalysis& a, const std::string& path) {
    std::ofstream out(path);
    if (!out.is_open()) return false;

    out << "Estadistica | Valor SNAP publicado | Valor obtenido\n";
    out << "---------------------------------------------------\n";
    out << "Numero de nodos | 1,088,092 | " << g.num_nodes() << "\n";
    out << "Numero de aristas | 1,541,898 | " << g.num_undirected_edges() << "\n";
    out << "Nodos en componente principal | 1,087,562 | " << a.max_component_size << "\n";
    out << "Grado promedio | ~2.83 | " << std::fixed << std::setprecision(4) 
        << (2.0 * g.num_undirected_edges() / g.num_nodes()) << "\n";
    out << "Nodo de mayor grado | (identificar) | " << g.idx_to_orig[a.max_degree_node_idx] << "\n";
    out << "Diametro aproximado | 782 | " << a.approx_diameter << "\n";

    return true;
}