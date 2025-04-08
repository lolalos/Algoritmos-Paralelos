#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Define el número de nodos en el grafo
#define N 3000

// Función mín para calcular valores mínimos entre dos números
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

// Define una matriz de tamaño N * N para almacenar las distancias entre los nodos
// Inicializa las distancias en cero
int distance_matrix[N][N] = {0};

int main(int argc, char* argv[]) {
    int src, dst, middle;

    // Inicializa el grafo con distancias aleatorias
    for (src = 0; src < N; src++) {
        for (dst = 0; dst < N; dst++) {
            // La distancia de un nodo al mismo nodo es 0
            if (src != dst) {
                // Las distancias son generadas entre 0 y 19
                distance_matrix[src][dst] = rand() % 20;
            }
        }
    }

    // ======= ALGORITMO SECUENCIAL =========
    // Obtiene el tiempo inicial
    double start_time = omp_get_wtime();
    for (middle = 0; middle < N; middle++) {
        int* dm = distance_matrix[middle];
        for (src = 0; src < N; src++) {
            int* ds = distance_matrix[src];
            for (dst = 0; dst < N; dst++) {
                ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
            }
        }
    }
    // Obtiene el tiempo final
    double sequential_time = omp_get_wtime() - start_time;
    printf("Tiempo Total secuencial (en seg): %.2f\n", sequential_time);

    // ========= ALGORITMO PARALELO ==============
    printf("+------------+-----------------------+----------------+----------------+\n");
    printf("| Nro. Hilos | Tiempo Paralelo (seg) | Speedup (Sp)   | Eficiencia (E) |\n");
    printf("+------------+-----------------------+----------------+----------------+\n");

    for (int nthreads = 1; nthreads <= 10; nthreads++) {
        // Define diferente número de hilos
        omp_set_num_threads(nthreads);

        // Obtiene el tiempo inicial
        start_time = omp_get_wtime();

        #pragma omp parallel shared(distance_matrix)
        for (middle = 0; middle < N; middle++) {
            int* dm = distance_matrix[middle];
            #pragma omp for private(src, dst) schedule(dynamic)
            for (src = 0; src < N; src++) {
                int* ds = distance_matrix[src];
                for (dst = 0; dst < N; dst++) {
                    ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
                }
            }
        }

        // Obtiene el tiempo final
        double parallel_time = omp_get_wtime() - start_time;

        // Calcula Speedup y Eficiencia
        double speedup = sequential_time / parallel_time;
        double efficiency = speedup / nthreads;

        // Imprime los resultados en la tabla
        printf("| %10d | %21.2f | %14.2f | %14.2f |\n", nthreads, parallel_time, speedup, efficiency);
    }

    printf("+------------+-----------------------+----------------+----------------+\n");

    return 0;
}