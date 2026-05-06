#include "subgraph.hpp"
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <fstream>

// Función para construir el mini-mapa (Subgrafo inducido)
Graph build_induced_subgraph(const Graph& original_g, const std::vector<int>& path1, const std::vector<int>& path2) {
    Graph subg;
    std::unordered_set<int> nodes_in_subgraph;

    // Recolectar todos los nodos unicos de ambas rutas
    for (int node : path1) nodes_in_subgraph.insert(node);
    for (int node : path2) nodes_in_subgraph.insert(node);

    // Agregar las aristas que conectan solo a estos nodos
    for (int orig_id : nodes_in_subgraph) {
        auto it = original_g.orig_to_idx.find(orig_id);
        if (it == original_g.orig_to_idx.end()) continue;
        
        int u_idx = it->second;
        int sub_u = subg.get_or_create_index(orig_id);

        for (const Edge& e : original_g.adj[u_idx]) {
            int neighbor_orig = original_g.idx_to_orig[e.to];
            
            // Si el vecino tambien pertenece a nuestro mini-mapa
            if (nodes_in_subgraph.count(neighbor_orig)) {
                // Solo lo agregamos si orig_id < neighbor_orig para no duplicar las aristas
                if (orig_id < neighbor_orig) {
                    int sub_v = subg.get_or_create_index(neighbor_orig);
                    subg.add_undirected_edge(sub_u, sub_v, e.weight);
                }
            }
        }
    }
    return subg;
}

// Estructura auxiliar para Kruskal
struct DSU {
    std::vector<int> parent;
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
    }
    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            return true;
        }
        return false;
    }
};

// Estructura para ordenar aristas
struct KruskalEdge {
    int u, v, weight;
    bool operator<(const KruskalEdge& other) const {
        return weight < other.weight;
    }
};

// Algoritmo de Kruskal para el MST
MSTResult run_kruskal(const Graph& subg) {
    MSTResult res;
    res.total_weight = 0;
    
    std::vector<KruskalEdge> all_edges;
    for (int u = 0; u < subg.num_nodes(); ++u) {
        for (const Edge& e : subg.adj[u]) {
            if (u < e.to) {
                all_edges.push_back({u, e.to, e.weight});
            }
        }
    }

    std::sort(all_edges.begin(), all_edges.end());
    DSU dsu(subg.num_nodes());

    for (const auto& edge : all_edges) {
        if (dsu.unite(edge.u, edge.v)) {
            res.total_weight += edge.weight;
            res.edges.push_back({subg.idx_to_orig[edge.u], subg.idx_to_orig[edge.v]});
        }
    }
    return res;
}

// Deteccion de ciclos usando DFS
bool dfs_cycle(const Graph& g, int u, int p, std::vector<bool>& visited) {
    visited[u] = true;
    for (const Edge& e : g.adj[u]) {
        if (!visited[e.to]) {
            if (dfs_cycle(g, e.to, u, visited)) return true;
        } else if (e.to != p) {
            return true; // Hay un ciclo
        }
    }
    return false;
}

bool has_cycles(const Graph& subg) {
    std::vector<bool> visited(subg.num_nodes(), false);
    for (int i = 0; i < subg.num_nodes(); ++i) {
        if (!visited[i]) {
            if (dfs_cycle(subg, i, -1, visited)) return true;
        }
    }
    return false;
}

// Generador de reportes en .txt
void save_subgraph_reports(const Graph& subg, const MSTResult& mst, bool cycle_found) {
    // Reporte 1: analisis General
    std::ofstream out_analisis("results/analisis_subgrafo.txt");
    if (out_analisis.is_open()) {
        out_analisis << "--- Reporte Modulo C: Analisis del Subgrafo ---\n";
        out_analisis << "Nodos en el subgrafo: " << subg.num_nodes() << "\n";
        out_analisis << "Aristas en el subgrafo: " << subg.num_undirected_edges() << "\n";
        out_analisis << "Costo total del MST (Kruskal): " << mst.total_weight << "\n";
        out_analisis << "Contiene ciclos (DFS): " << (cycle_found ? "Si" : "No") << "\n";
    }

    // Reporte 2: Caminos del MST
    std::ofstream out_caminos("results/subgrafo_caminos.txt");
    if (out_caminos.is_open()) {
        out_caminos << "Aristas que conforman el Arbol de Expansion Minima (Origen - Destino):\n";
        for (const auto& edge : mst.edges) {
            out_caminos << edge.first << " - " << edge.second << "\n";
        }
    }
}