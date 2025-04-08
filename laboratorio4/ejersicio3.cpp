#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream> // Para manejar archivos
using namespace std;

int main(int argc, char const *argv[])
{
    int i, j;
    srand(time(NULL));
    int n;
    cout << "Ingrese el valor de n: ";
    cin >> n;

    //--crea las matrices n x n
    int **matriz_a = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz_a[i] = new int[n];
    }
    int **matriz_b = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz_b[i] = new int[n];
    }
    int **matriz_c = new int*[n];
    for (int i = 0; i < n; i++) {
        matriz_c[i] = new int[n];
    }

    //--llena las matrices a y b con valores aleatorios
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            matriz_a[i][j] = (rand() % 4) + 1;
            matriz_b[i][j] = (rand() % 4) + 1;
        }
    }

    // Variables para medir el tiempo
    double tiempo_secuencial, tiempo_paralelo;
    double start, end;

    // Multiplicación secuencial para calcular el tiempo base
    start = omp_get_wtime();
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            int suma = 0;
            for (int k = 0; k < n; k++) {
                suma += matriz_a[i][k] * matriz_b[k][j];
            }
            matriz_c[i][j] = suma;
        }
    }
    end = omp_get_wtime();
    tiempo_secuencial = end - start;

    // Mostrar encabezado de la tabla con bordes
    cout << "+------------+-----------------------+----------------+----------------+\n";
    cout << "| Nro. Hilos | Tiempo Paralelo (seg) | Speedup (Sp)   | Eficiencia (E) |\n";
    cout << "+------------+-----------------------+----------------+----------------+\n";

    // Pruebas con diferentes números de hilos
    for (int num_hilos = 1; num_hilos <= 10; num_hilos++) {
        omp_set_num_threads(num_hilos);

        // Multiplicación en paralelo
        start = omp_get_wtime();
        #pragma omp parallel
        {
            int i, j, k, suma;
            #pragma omp for private(i, suma)
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    suma = 0;
                    for (k = 0; k < n; k++) {
                        suma += (matriz_a[i][k] * matriz_b[k][j]);
                    }
                    matriz_c[i][j] = suma;
                }
            }
        }
        end = omp_get_wtime();
        tiempo_paralelo = end - start;

        // Calcular Speedup y Eficiencia
        double speedup = tiempo_secuencial / tiempo_paralelo;
        double eficiencia = speedup / num_hilos;

        // Mostrar resultados en el cuadro
        cout << "| " << setw(10) << num_hilos << " | "
             << setw(21) << fixed << setprecision(5) << tiempo_paralelo << " | "
             << setw(14) << fixed << setprecision(5) << speedup << " | "
             << setw(14) << fixed << setprecision(5) << eficiencia << " |\n";
    }

    // Línea final del cuadro
    cout << "+------------+-----------------------+----------------+----------------+\n";

    // Liberar memoria
    for (int i = 0; i < n; i++) {
        delete[] matriz_a[i];
        delete[] matriz_b[i];
        delete[] matriz_c[i];
    }
    delete[] matriz_a;
    delete[] matriz_b;
    delete[] matriz_c;

    return 0;
}