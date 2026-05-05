// =====================================================================
//  graph.cpp
//  Implementacion de la clase Graph.
// =====================================================================

#include "graph.hpp"

Graph::Graph() : n(0), m(0) {}

int Graph::get_or_create_index(int orig_id) {
    auto it = orig_to_idx.find(orig_id);
    if (it != orig_to_idx.end()) return it->second;

    // Nodo nuevo: le damos el siguiente indice libre.
    int idx = n++;
    orig_to_idx[orig_id] = idx;
    idx_to_orig.push_back(orig_id);
    adj.emplace_back(); // agrega lista vacia para este nodo
    return idx;
}

void Graph::add_undirected_edge(int u_idx, int v_idx, int w) {
    // Arista no dirigida = dos arcos dirigidos con el MISMO peso.
    adj[u_idx].push_back({v_idx, w});
    adj[v_idx].push_back({u_idx, w});
    ++m; // contamos UNA sola arista logica, no dos
}

double Graph::avg_degree() const {
    if (n == 0) return 0.0;
    // Suma de grados = 2*m (handshake lemma) -> grado promedio = 2m/n.
    return (2.0 * static_cast<double>(m)) / static_cast<double>(n);
}

int Graph::max_degree_node() const {
    int best_node = 0;
    int best_deg  = -1;
    for (int i = 0; i < n; ++i) {
        int d = static_cast<int>(adj[i].size());
        if (d > best_deg) {
            best_deg  = d;
            best_node = i;
        }
    }
    return best_node;
}
