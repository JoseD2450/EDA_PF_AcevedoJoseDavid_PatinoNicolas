#include "graph.hpp"

Graph::Graph() : n(0), m(0) {}

int Graph::get_or_create_index(int orig_id) {
    // Si el nodo ya existe, devolvemos su índice
    auto it = orig_to_idx.find(orig_id);
    if (it != orig_to_idx.end()) return it->second;

    // Si es nuevo, lo creamos
    int idx = n++;
    orig_to_idx[orig_id] = idx;
    idx_to_orig.push_back(orig_id);
    adj.emplace_back(); // Creamos su lista de vecinos vacía
    return idx;
}

void Graph::add_undirected_edge(int u_idx, int v_idx, int w) {
    // Es no dirigido, así que la calle va en ambas direcciones
    adj[u_idx].push_back({v_idx, w});
    adj[v_idx].push_back({u_idx, w});
    ++m;
}