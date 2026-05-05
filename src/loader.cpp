// =====================================================================
//  loader.cpp
//  Parser del archivo roadNet-PA.txt (formato SNAP).
// =====================================================================

#include "loader.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib> // srand, rand

// El archivo SNAP de roadNet-PA contiene cada arista no dirigida DOS veces
// (una en cada direccion: "u v" y "v u"). Por eso necesitamos deduplicar:
// la primera vez que vemos la arista, la insertamos; la segunda, la
// saltamos. La deduplicacion la hacemos revisando si v ya esta en adj[u].
// Como el grado promedio es ~2.83, este chequeo es practicamente O(1).
static bool edge_exists(const Graph& g, int u_idx, int v_idx) {
    for (const Edge& e : g.adj[u_idx]) {
        if (e.to == v_idx) return true;
    }
    return false;
}

bool load_snap_undirected(const std::string& path, Graph& g) {
    std::ifstream fin(path);
    if (!fin.is_open()) {
        std::cerr << "ERROR: no se pudo abrir el archivo: " << path << "\n";
        return false;
    }

    // Semilla fija ANTES del parseo: garantiza que todos los equipos
    // obtengan los mismos pesos para las mismas aristas.
    std::srand(42);

    std::string line;
    long long lines_read     = 0;
    long long edges_inserted = 0;
    long long duplicates     = 0;
    long long self_loops     = 0;
    long long comments       = 0;

    while (std::getline(fin, line)) {
        ++lines_read;

        if (line.empty()) continue;
        if (line[0] == '#') { ++comments; continue; }

        // Cada linea de datos: "u<TAB>v" o "u v"
        std::istringstream iss(line);
        int u_orig, v_orig;
        if (!(iss >> u_orig >> v_orig)) continue; // linea malformada: la ignoramos

        if (u_orig == v_orig) { ++self_loops; continue; } // descartamos self-loops

        // Reindexar: asegurar que ambos nodos tengan indice interno.
        int u_idx = g.get_or_create_index(u_orig);
        int v_idx = g.get_or_create_index(v_orig);

        // Si la arista ya existe (porque vimos la otra direccion), saltamos
        // SIN gastar una llamada a rand(): asi cada arista logica recibe
        // exactamente UNA llamada a rand() y todos los equipos coinciden.
        if (edge_exists(g, u_idx, v_idx)) { ++duplicates; continue; }

        int w = (std::rand() % 10) + 1; // peso entero en [1, 10]
        g.add_undirected_edge(u_idx, v_idx, w);
        ++edges_inserted;

        // Reporte de progreso cada 200k aristas (util en datasets grandes).
        if ((edges_inserted % 200000) == 0) {
            std::cerr << "  ...insertadas " << edges_inserted
                      << " aristas no dirigidas\n";
        }
    }

    std::cerr << "----------------------------------------\n";
    std::cerr << "Carga finalizada\n";
    std::cerr << "  Lineas leidas:           " << lines_read     << "\n";
    std::cerr << "  Lineas de comentario:    " << comments       << "\n";
    std::cerr << "  Self-loops descartados:  " << self_loops     << "\n";
    std::cerr << "  Duplicados saltados:     " << duplicates     << "\n";
    std::cerr << "  Aristas no dirigidas:    " << edges_inserted << "\n";
    std::cerr << "  Nodos (reindexados):     " << g.num_nodes()  << "\n";
    std::cerr << "----------------------------------------\n";
    return true;
}
