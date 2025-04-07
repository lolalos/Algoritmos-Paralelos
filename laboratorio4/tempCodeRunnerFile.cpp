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

int main() {
    int nthreads;
    int src, dst, middle;

    // Inicializa la semilla de números aleatorios
    srand((unsigned)time(NULL));

    // Inicializa el grafo con distancias aleatorias
    for (src = 0; src < N; src++) {
        for (dst = 0; dst < N; dst++) {
            if (src != dst) {
                distance_matrix[src][dst] = rand() % 20 + 1; // Evita ceros
            } else {
                distance_matrix[src][dst] = 0;
            }
        }
    }

    //======= ALGORITMO SECUENCIAL =========
    double seq_start_time = omp_get_wtime();
    for (middle = 0; middle < N; middle++) {
        int* dm = distance_matrix[middle];
        for (src = 0; src < N; src++) {
            int* ds = distance_matrix[src];
            for (dst = 0; dst < N; dst++) {
                ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
            }
        }
    }
    double seq_time = omp_get_wtime() - seq_start_time;
    printf("Tiempo Total secuencial (en seg): %.2f\n", seq_time);

    //========= ALGORITMO PARALELO ==============
    for (nthreads = 1; nthreads <= 10; nthreads++) {
        omp_set_num_threads(nthreads);

        // Vuelve a inicializar la matriz con distancias aleatorias
        for (src = 0; src < N; src++) {
            for (dst = 0; dst < N; dst++) {
                if (src != dst) {
                    distance_matrix[src][dst] = rand() % 20 + 1;
                } else {
                    distance_matrix[src][dst] = 0;
                }
            }
        }

        double par_start_time = omp_get_wtime();

        for (middle = 0; middle < N; middle++) {
            int* dm = distance_matrix[middle];

            #pragma omp parallel for private(dst) schedule(dynamic)
            for (src = 0; src < N; src++) {
                int* ds = distance_matrix[src];
                for (dst = 0; dst < N; dst++) {
                    ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
                }
            }
        }

        double par_time = omp_get_wtime() - par_start_time;
        printf("Tiempo Total para %d hilos (en seg): %.2f\n", nthreads, par_time);
    }

    return 0;
}
