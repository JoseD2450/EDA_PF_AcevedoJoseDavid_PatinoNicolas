#include "loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

static bool edge_exists(const Graph& g, int u_idx, int v_idx) {
    if (u_idx >= g.adj.size()) return false;
    for (const Edge& e : g.adj[u_idx]) {
        if (e.to == v_idx) return true;
    }
    return false;
}

bool load_snap_undirected(const std::string& path, Graph& g) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << path << "\n";
        return false;
    }

    std::srand(42); 

    std::string line;
    long long edges_inserted = 0;

    std::cout << "Cargando dataset...\n";

    while (std::getline(fin, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream iss(line);
        int u_orig, v_orig;
        if (!(iss >> u_orig >> v_orig)) continue;

        if (u_orig == v_orig) continue;

        int u_idx = g.get_or_create_index(u_orig);
        int v_idx = g.get_or_create_index(v_orig);

        if (edge_exists(g, u_idx, v_idx)) continue;

        int w = (std::rand() % 10) + 1; 
        g.add_undirected_edge(u_idx, v_idx, w);
        edges_inserted++;

        if (edges_inserted % 200000 == 0) {
            std::cout << "Progreso: " << edges_inserted << " aristas cargadas.\n";
        }
    }

    std::cout << "Carga finalizada.\n";
    return true;
}