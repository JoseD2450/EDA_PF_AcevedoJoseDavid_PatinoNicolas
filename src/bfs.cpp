#include "bfs.hpp"
#include <queue>
#include <chrono>

BFSResult run_bfs(const Graph& g, int source_orig, int target_orig) {
    BFSResult res = {-1, 0, 0.0};
    auto start_time = std::chrono::high_resolution_clock::now();

    auto it_src = g.orig_to_idx.find(source_orig);
    auto it_tgt = g.orig_to_idx.find(target_orig);
    if (it_src == g.orig_to_idx.end() || it_tgt == g.orig_to_idx.end()) return res;

    int src = it_src->second;
    int tgt = it_tgt->second;

    std::vector<int> dist(g.num_nodes(), -1);
    std::queue<int> q;

    dist[src] = 0;
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        res.explored_nodes++;

        if (u == tgt) break;

        for (const Edge& e : g.adj[u]) {
            if (dist[e.to] == -1) {
                dist[e.to] = dist[u] + 1;
                q.push(e.to);
            }
        }
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    res.time_ms = std::chrono::duration<double, std::milli>(end_time - start_time).count();

    res.jumps = dist[tgt];
    return res;
}