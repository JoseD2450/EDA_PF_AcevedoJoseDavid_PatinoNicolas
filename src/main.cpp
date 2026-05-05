#include <iostream>
#include <string>
#include "graph.hpp"
#include "loader.hpp"
#include "structural.hpp"
#include "shortest_path.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Uso correcto Modulo A: ./eda_pf A <archivo_dataset>\n";
        std::cerr << "Uso correcto Modulo B: ./eda_pf B <archivo_dataset> <nodo_origen> <nodo_destino>\n";
        return 1;
    }

    std::string modulo = argv[1];
    std::string path = argv[2];

    Graph g;
    if (!load_snap_undirected(path, g)) {
        return 1;
    }

    if (modulo == "A") {
        std::cout << "Iniciando analisis estructural...\n";
        StructuralAnalysis analysis = run_structural_analysis(g);
        print_structural_summary(g, analysis);

        std::string report_path = "results/analisis_estructural.txt";
        if (write_structural_report(g, analysis, report_path)) {
            std::cout << "Reporte generado en: " << report_path << "\n";
        } else {
            std::cerr << "Error: No se pudo generar el reporte en la carpeta results.\n";
        }
    } 
    else if (modulo == "B") {
        if (argc < 5) {
            std::cerr << "Error: Faltan argumentos para el Modulo B.\n";
            std::cerr << "Uso: ./eda_pf B <archivo_dataset> <nodo_origen> <nodo_destino>\n";
            return 1;
        }

        int origen = std::stoi(argv[3]);
        int destino = std::stoi(argv[4]);

        std::cout << "Calculando la ruta mas corta usando Dijkstra...\n";
        PathResult ruta = find_shortest_path(g, origen, destino);

        if (ruta.total_distance != -1) {
            std::cout << "-------------------------------------------\n";
            std::cout << "Ruta encontrada exitosamente.\n";
            std::cout << "Distancia total (costo): " << ruta.total_distance << "\n";
            std::cout << "Nodos recorridos:        " << ruta.path_nodes.size() << "\n";
            std::cout << "Camino: ";
            
            // Si el camino es corto, imprimimos todos los nodos
            if (ruta.path_nodes.size() <= 15) {
                for (size_t i = 0; i < ruta.path_nodes.size(); ++i) {
                    std::cout << ruta.path_nodes[i] << (i == ruta.path_nodes.size() - 1 ? "" : " -> ");
                }
                std::cout << "\n";
            } else {
                // Si es muy largo, mostramos solo los extremos para no saturar la terminal
                std::cout << ruta.path_nodes[0] << " -> " << ruta.path_nodes[1] << " -> ... (" 
                          << ruta.path_nodes.size() - 4 << " nodos intermedios) ... -> " 
                          << ruta.path_nodes[ruta.path_nodes.size() - 2] << " -> " 
                          << ruta.path_nodes.back() << "\n";
            }
            std::cout << "-------------------------------------------\n";
        } else {
            std::cout << "Resultado: No existe una ruta conectada entre los nodos " << origen << " y " << destino << ".\n";
        }
    }
    else {
        std::cerr << "Error: Modulo no reconocido. Use A o B.\n";
    }

    return 0;
}