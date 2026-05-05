#ifndef LOADER_HPP
#define LOADER_HPP

// =====================================================================
//  loader.hpp
//  Carga el archivo roadNet-PA.txt (formato SNAP) y construye el grafo.
//
//  Formato SNAP:
//    - Lineas que empiezan con '#' son comentarios (se ignoran)
//    - El resto: dos enteros separados por tab/espacio = arco dirigido u->v
//    - Tratamos el grafo como NO DIRIGIDO: insertamos u->v y v->u
//
//  Pesos: el dataset original es no ponderado. Para Dijkstra asignamos
//  peso = (rand() % 10) + 1 con srand(42), de manera reproducible.
//  Cada arista no dirigida recibe UN solo peso (no uno por direccion).
// =====================================================================

#include "graph.hpp"
#include <string>

// Carga el archivo desde 'path' y rellena 'g'.
// Retorna true si la carga fue exitosa; false si hubo error de IO.
bool load_snap_undirected(const std::string& path, Graph& g);

#endif // LOADER_HPP
