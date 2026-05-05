#ifndef LOADER_HPP
#define LOADER_HPP

#include "graph.hpp"
#include <string>

// Función que lee el archivo txt y llena el grafo
bool load_snap_undirected(const std::string& path, Graph& g);

#endif