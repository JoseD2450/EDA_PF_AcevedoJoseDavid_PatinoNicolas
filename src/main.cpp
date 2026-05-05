#include <iostream>
#include <string>
#include "graph.hpp"
#include "loader.hpp"
#include "structural.hpp"

int main(int argc, char** argv) {
    // Requerimos que nos pasen por consola el modulo y el archivo
    if (argc < 3) {
        std::cerr << "Uso correcto: ./eda_pf <modulo> <archivo_dataset>\n";
        std::cerr << "Ejemplo: ./eda_pf A data/roadNet-PA.txt\n";
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
    else {
        std::cout << "Modulo no implementado todavia.\n";
    }

    return 0;
}