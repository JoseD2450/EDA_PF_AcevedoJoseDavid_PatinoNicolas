#include "dijkstra.hpp"
#include <queue>
#include <limits>
#include <chrono>
#include <algorithm>

DijkstraResult run_dijkstra(const Graph& g, int source_orig, int target_orig, bool save_path) {
    DijkstraResult res = {-1, 0, 0.0, {}};
    auto start_time = std::chrono::high_resolution_clock::now();

    auto it_src = g.orig_to_idx.find(source_orig);
    auto it_tgt = g.orig_to_idx.find(target_orig);
    if (it_src == g.orig_to_idx.end() || it_tgt == g.orig_to_idx.end()) return res;

    int src = it_src->second;
    int tgt = it_tgt->second;

    const long long INF = std::numeric_limits<long long>::max();
    std::vector<long long> dist(g.num_nodes(), INF);
    std::vector<int> parent(g.num_nodes(), -1);
    
    using PII = std::pair<long long, int>;
    std::priority_queue<PII, std::vector<PII>, std::greater<PII>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        res.explored_nodes++;

        if (u == tgt) break;
        if (d > dist[u]) continue;

        for (const Edge& e : g.adj[u]) {
            if (dist[u] + e.weight < dist[e.to]) {
                dist[e.to] = dist[u] + e.weight;
                parent[e.to] = u;
                pq.push({dist[e.to], e.to});
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    res.time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    if (dist[tgt] != INF) {
        res.distance = dist[tgt];
        if (save_path) {
            int current = tgt;
            while (current != -1) {
                res.path.push_back(g.idx_to_orig.at(current));
                current = parent[current];
            }
            std::reverse(res.path.begin(), res.path.end());
        }
    }

    return res;
}