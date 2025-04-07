#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <fstream>

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

    //========= ALGORITMO PARALELO ==============
    double par_times[10];
    double speedups[10];
    double efficiencies[10];

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
        speedups[nthreads - 1] = seq_time / par_time;
        efficiencies[nthreads - 1] = speedups[nthreads - 1] / nthreads;
    }

    // Crear el archivo README.md
    std::ofstream readme("README.md");
    readme << "# Resultados del Algoritmo de Floyd-Warshall Paralelo\n\n";
    readme << "Este programa implementa el algoritmo de Floyd-Warshall para calcular las distancias más cortas entre todos los pares de nodos en un grafo.\n\n";
    readme << "### Enlace al código fuente\n";
    readme << "[Código fuente](D:/Algoritmos-Paralelos/laboratorio4/ejercicio2.cpp)\n\n";
    readme << "### Tabla 2. Resultados experimentales\n";
    readme << "| Nro. Hilos | Tiempo Paralelo (seg) | Speedup (Sp) | Eficiencia (E) |\n";
    readme << "|------------|-----------------------|--------------|----------------|\n";
    for (nthreads = 1; nthreads <= 10; nthreads++) {
        readme << "| " << nthreads << " | " << par_times[nthreads - 1] << " | " 
               << speedups[nthreads - 1] << " | " << efficiencies[nthreads - 1] << " |\n";
    }
    readme.close();

    return 0;
}
