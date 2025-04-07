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
    printf("Tiempo Secuencial (seg): %.3f\n", seq_time);

    //========= ALGORITMO PARALELO ==============
    printf("\nTabla 2. Resultados experimentales\n");
    printf("Nro. Hilos\t");
    for (nthreads = 1; nthreads <= 10; nthreads++) {
        printf("%d\t", nthreads);
    }
    printf("\n");

    printf("Tiempo Paralelo (seg)\t");
    double par_times[10];
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

        #pragma omp parallel for private(src, dst)
        for (middle = 0; middle < N; middle++) {
            int* dm = distance_matrix[middle];
            for (src = 0; src < N; src++) {
                int* ds = distance_matrix[src];
                for (dst = 0; dst < N; dst++) {
                    ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
                }
            }
        }

        double par_time = omp_get_wtime() - par_start_time;
        par_times[nthreads - 1] = par_time;
        printf("%.3f\t", par_time);
    }
    printf("\n");

    // Calcular Speedup y Eficiencia
    printf("Speedup (Sp)\t\t");
    for (nthreads = 1; nthreads <= 10; nthreads++) {
        double speedup = seq_time / par_times[nthreads - 1];
        printf("%.3f\t", speedup);
    }
    printf("\n");

    printf("Eficiencia (E)\t\t");
    for (nthreads = 1; nthreads <= 10; nthreads++) {
        double speedup = seq_time / par_times[nthreads - 1];
        double efficiency = speedup / nthreads;
        printf("%.3f\t", efficiency);
    }
    printf("\n");

    return 0;
}
