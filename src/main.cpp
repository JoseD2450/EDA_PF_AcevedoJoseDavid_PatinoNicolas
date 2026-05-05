#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "graph.hpp"
#include "loader.hpp"
#include "structural.hpp"
#include "dijkstra.hpp"
#include "bfs.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Uso correcto: ./eda_pf <modulo> <archivo_dataset>\n";
        return 1;
    }

    std::string modulo = argv[1];
    std::string path = argv[2];

    Graph g;
    if (!load_snap_undirected(path, g)) return 1;

    if (modulo == "A") {
        std::cout << "Iniciando analisis estructural...\n";
        StructuralAnalysis analysis = run_structural_analysis(g);
        print_structural_summary(g, analysis);
        write_structural_report(g, analysis, "results/analisis_estructural.txt");
    } 
    else if (modulo == "B") {
        std::cout << "Ejecutando las 10 consultas P2P (Modulo B)...\n";
        
        // Las 10 consultas requeridas por el proyecto
        std::vector<std::pair<int, int>> queries = {
            {1, 500000}, {100, 1000000}, {50000, 750000}, {200000, 800000}, 
            {300000, 100000}, {1, 1087562}, {500000, 1}, {250000, 600000}, 
            {10000, 900000}, {400000, 150000}
        };

        std::ofstream csv("results/consultas_p2p.csv");
        csv << "consulta,origen,destino,dist_dijkstra,saltos_bfs,nodos_dijkstra,nodos_bfs,t_dijkstra_ms,t_bfs_ms\n";

        for (size_t i = 0; i < queries.size(); ++i) {
            int src = queries[i].first;
            int tgt = queries[i].second;
            std::string q_name = "Q" + (i < 9 ? std::string("0") : "") + std::to_string(i + 1);
            
            // Requerimiento: Guardar camino SOLO para Q01 y Q06
            bool save_path = (q_name == "Q01" || q_name == "Q06");

            DijkstraResult d_res = run_dijkstra(g, src, tgt, save_path);
            BFSResult b_res = run_bfs(g, src, tgt);

            csv << q_name << "," << src << "," << tgt << "," 
                << (d_res.distance == -1 ? "INF" : std::to_string(d_res.distance)) << ","
                << (b_res.jumps == -1 ? "INF" : std::to_string(b_res.jumps)) << ","
                << d_res.explored_nodes << "," << b_res.explored_nodes << ","
                << d_res.time_ms << "," << b_res.time_ms << "\n";

            std::cout << q_name << " completada. Dijkstra: " << d_res.time_ms << "ms | BFS: " << b_res.time_ms << "ms\n";
        }
        
        std::cout << "Archivo results/consultas_p2p.csv generado exitosamente.\n";
    }

    return 0;
}