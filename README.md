# Practica-Final-Estructuras de Datos

## Integrantes
* Jose David Acevedo T.
* Nicolas Patino Palacio

Este repositorio README explica la implementacion en C++ de procesamiento de grafos grandes y como compilar el proyecto.

## Compilacion del Proyecto 

Para compilar este proyecto, primero hay que asegurarse de tener instalado el compilador `g++`. Se usa el siguiente comando desde la terminal apuntando a la carpeta principal:

```bash
g++ -std=c++17 -O2 -o eda_pf src/main.cpp src/graph.cpp src/loader.cpp src/structural.cpp src/dijkstra.cpp src/bfs.cpp src/subgraph.cpp

#Ejecucion por Modulos

El programa cuenta con tres modulos principales A, B y C. Todos los resultados generados seran guardados automaticamente en la carpeta de results/.

# Modulo A

Este carga el grafo en memoria y calcula todos los parametros como la cantidad de nodos, aristas y estadisticas como grado promedio, grado de mayor grado, el diametro esperado de este y mas. Para ejecutarlo se usa el comando:

.\eda_pf.exe A data/roadNet-PA.txt

#Modulo B 

Ejecuta 10 consultas de encontrar una ruta comparando dos algoritmos:

Dijkstra: Este encuentra la ruta optima considerando los pesos de las aristas, optimo para encontrar la ruta mas "barata".

BFS: Este algoritmo se enfoca en la ruta con menor cantidad de nodos, ignorando los pesos por completo.

Se exportan los tiempos de ejecucion y sus resultados al archivo consultas_p2p.csv
Su comando es:
.\eda_pf.exe B data/roadNet-PA.txt