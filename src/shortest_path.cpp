#include "shortest_path.hpp"
#include <queue>
#include <limits>
#include <algorithm>
#include <iostream>

PathResult find_shortest_path(const Graph& g, int source_orig, int target_orig) {
    PathResult res;
    res.total_distance = -1; // -1 indica que no hay camino o hubo un error

    // 1. Verificar que los nodos existan en nuestro grafo
    auto it_src = g.orig_to_idx.find(source_orig);
    auto it_tgt = g.orig_to_idx.find(target_orig);

    if (it_src == g.orig_to_idx.end() || it_tgt == g.orig_to_idx.end()) {
        std::cerr << "Error: Uno o ambos nodos no existen en el grafo.\n";
        return res;
    }

    int src_idx = it_src->second;
    int tgt_idx = it_tgt->second;

    // 2. Inicializar distancias y predecesores (para reconstruir el camino luego)
    const long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dist(g.num_nodes(), INF);
    std::vector<int> parent(g.num_nodes(), -1);

    // Cola de prioridad: almacena pares (distancia_acumulada, nodo_actual). 
    using PII = std::pair<long long, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;

    dist[src_idx] = 0;
    pq.push({0, src_idx});

    // 3. Ejecutar algoritmo de Dijkstra
    while (!pq.empty()) {
        long long current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // Si llegamos al destino, podemos detener la busqueda para ahorrar tiempo
        if (u == tgt_idx) break;

        // Si encontramos en la cola un camino más largo al que ya teníamos registrado, lo ignoramos
        if (current_dist > dist[u]) continue;

        // Explorar las calles vecinas
        for (const Edge& e : g.adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    // 4. Reconstruir el camino desde el destino hacia el origen
    if (dist[tgt_idx] != INF) {
        res.total_distance = dist[tgt_idx];
        int current = tgt_idx;
        while (current != -1) {
            res.path_nodes.push_back(g.idx_to_orig.at(current)); 
            current = parent[current];
        }
        // Como lo reconstruimos de atras para adelante, le damos la vuelta al final
        std::reverse(res.path_nodes.begin(), res.path_nodes.end());
    }

    return res;
}