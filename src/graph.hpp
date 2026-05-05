#ifndef GRAPH_HPP
#define GRAPH_HPP

// =====================================================================
//  graph.hpp
//  Estructura de datos principal del proyecto: grafo NO DIRIGIDO con
//  pesos enteros, representado como LISTA DE ADYACENCIA.
//
//  Justificacion (ver informe): el dataset roadNet-PA tiene
//  V = 1,088,092 nodos. Una matriz de adyacencia booleana
//  requeriria V*V = ~1.18*10^12 bits = ~138 GB en RAM (y ~4.7 TB
//  con enteros de 32 bits). La lista de adyacencia, en cambio,
//  ocupa O(V + E) ~ 50-80 MB porque guarda solo las aristas
//  reales (~1.54M aristas no dirigidas, ~3M arcos dirigidos).
// =====================================================================

#include <vector>
#include <unordered_map>
#include <cstdint>

// Una arista saliente desde un nodo: a quien llega y con que peso.
struct Edge {
    int to;     // indice INTERNO (0..n-1) del vecino
    int weight; // peso entero en [1, 10] (asignado en la carga)
};

class Graph {
public:
    int n;                                      // # de nodos (despues de reindexar)
    long long m;                                // # de aristas no dirigidas (logicas)

    std::vector<std::vector<Edge>> adj;         // adj[u] = vecinos de u con peso

    // Reindexacion: el dataset usa IDs no consecutivos. Los mapeamos a 0..n-1.
    std::unordered_map<int,int> orig_to_idx;    // ID original SNAP -> indice interno
    std::vector<int> idx_to_orig;               // indice interno -> ID original SNAP

    Graph();

    // Devuelve el indice interno del ID original. Si es nuevo, le asigna uno.
    int get_or_create_index(int orig_id);

    // Inserta arista NO DIRIGIDA con peso w (es decir, agrega u->v y v->u).
    // Asume u_idx y v_idx ya estan reindexados.
    void add_undirected_edge(int u_idx, int v_idx, int w);

    // Estadisticas basicas del grafo cargado.
    int  num_nodes()             const { return n; }
    long long num_undirected_edges() const { return m; }
    long long num_directed_arcs()    const { return 2 * m; } // cada arista cuenta dos veces
    double avg_degree()          const;       // 2*m / n
    int  degree_of(int u_idx)    const { return (int)adj[u_idx].size(); }
    int  max_degree_node()       const;       // indice interno del nodo de mayor grado
};

#endif // GRAPH_HPP
