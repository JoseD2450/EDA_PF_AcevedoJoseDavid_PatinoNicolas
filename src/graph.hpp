#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <unordered_map>

// Representa una conexión (arista) hacia otro nodo y su peso
struct Edge {
    int to;
    int weight;
};

class Graph {
public:
    int n;       // Cantidad de nodos
    long long m; // Cantidad de aristas no dirigidas

    // Lista de adyacencia: Un vector que guarda otro vector de aristas para cada nodo
    std::vector<std::vector<Edge>> adj;

    // Para traducir los IDs raros de las calles a índices normales (0, 1, 2...)
    std::unordered_map<int, int> orig_to_idx;
    std::vector<int> idx_to_orig;

    Graph();

    int get_or_create_index(int orig_id);
    void add_undirected_edge(int u_idx, int v_idx, int w);
    
    int num_nodes() const { return n; }
    long long num_undirected_edges() const { return m; }
};

#endif