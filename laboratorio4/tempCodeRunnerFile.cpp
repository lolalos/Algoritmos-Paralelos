#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Define el número de nodos en el grafo
#define N 3000

// Función mín para calcular valores mínimos entre dos números
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Matriz para almacenar las distancias entre los nodos
int distance_matrix[N][N];