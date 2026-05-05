// =====================================================================
//  main.cpp
//  CLI principal del proyecto. Selecciona modulo por argumento.
//
//  Uso:
//    ./eda_pf A data/roadNet-PA.txt        # Modulo A: analisis estructural
//    ./eda_pf B data/roadNet-PA.txt        # Modulo B: Dijkstra + BFS (10 P2P)
//    ./eda_pf C data/roadNet-PA.txt        # Modulo C: subgrafo, MST, DAG
//
//  Por defecto los archivos de salida se escriben en ./results/
//  Asegurate de que ese directorio exista (mkdir -p results) antes de correr.
// =====================================================================

#include "graph.hpp"
#include "loader.hpp"
#include "structural.hpp"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

static void print_usage(const char* prog) {
    std::cerr << "Uso: " << prog << " <modulo> <archivo_dataset>\n"
              << "  modulo: A | B | C\n"
              << "Ejemplo: " << prog << " A data/roadNet-PA.txt\n";
}

int main(int argc, char** argv) {
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    const std::string modulo = argv[1];
    const std::string path   = argv[2];

    // ------------------ Carga (comun a los 3 modulos) ------------------
    std::cerr << "Cargando grafo desde: " << path << "\n";
    auto t0 = std::chrono::high_resolution_clock::now();

    Graph g;
    if (!load_snap_undirected(path, g)) return 2;

    auto t1 = std::chrono::high_resolution_clock::now();
    double load_ms = std::chrono::duration<double, std::milli>(t1 - t0).count();
    std::cerr << "Tiempo de carga: " << std::fixed << std::setprecision(2)
              << load_ms << " ms\n\n";

    // ------------------ Despacho por modulo ----------------------------
    if (modulo == "A") {
        std::cerr << "Ejecutando analisis estructural...\n";
        StructuralAnalysis a = run_structural_analysis(g);

        print_structural_summary(g, a);

        const std::string out = "results/analisis_estructural.txt";
        if (write_structural_report(g, a, out)) {
            std::cout << "\nReporte escrito en: " << out << "\n";
        } else {
            std::cerr << "ATENCION: no se pudo escribir el reporte "
                      << "(verifica que exista la carpeta results/)\n";
            return 3;
        }
    }
    else if (modulo == "B") {
        std::cout << "[TODO] Modulo B (Dijkstra + BFS, 10 consultas P2P): pendiente\n";
    }
    else if (modulo == "C") {
        std::cout << "[TODO] Modulo C (subgrafo inducido, MST, DAG): pendiente\n";
    }
    else {
        std::cerr << "Modulo desconocido: '" << modulo << "'\n";
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
