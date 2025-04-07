#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    int i, j;
    srand(time(NULL));
    int n;
    cout << "Ingrese el valor de n (recomendado >= 500 para resultados significativos): ";
    cin >> n;
    if (n < 1)
    {
        cerr << "El tamano de la matriz debe ser mayor o igual a 1." << endl;
        return 1;
    }

    // Crear las matrices n x n
    int **matriz_a = new int *[n];
    int **matriz_b = new int *[n];
    int **matriz_c = new int *[n];
    for (i = 0; i < n; i++)
    {
        matriz_a[i] = new int[n];
        matriz_b[i] = new int[n];
        matriz_c[i] = new int[n];
    }

    // Llenar las matrices a y b con valores aleatorios
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matriz_a[i][j] = (rand() % 4) + 1;
            matriz_b[i][j] = (rand() % 4) + 1;
        }
    }

    // Medir tiempo secuencial
    double start_time = omp_get_wtime();
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            int suma = 0;
            for (int k = 0; k < n; k++)
            {
                suma += matriz_a[i][k] * matriz_b[k][j];
            }
            matriz_c[i][j] = suma;
        }
    }
    double end_time = omp_get_wtime();
    double tiempo_secuencial = end_time - start_time;

    // Medir tiempo paralelo con diferentes numeros de hilos
    int hilos[] = {1, 2, 4, 6, 8, 10, 12};
    double tiempos_paralelos[7];
    double speedup[7];
    double eficiencia[7];

    for (int h = 0; h < 7; h++)
    {
        omp_set_num_threads(hilos[h]);
        start_time = omp_get_wtime();
#pragma omp parallel for private(i, j)
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                int suma = 0;
                for (int k = 0; k < n; k++)
                {
                    suma += matriz_a[i][k] * matriz_b[k][j];
                }
                matriz_c[i][j] = suma;
            }
        }
        end_time = omp_get_wtime();
        tiempos_paralelos[h] = end_time - start_time;

        if (tiempos_paralelos[h] > 0)
        {
            speedup[h] = tiempo_secuencial / tiempos_paralelos[h];
            eficiencia[h] = speedup[h] / hilos[h];
        }
        else
        {
            speedup[h] = 0;
            eficiencia[h] = 0;
        }
    }

    // Escribir resultados en el archivo README.md
    ofstream readme("README.md", ios::app);
    if (!readme)
    {
        cerr << "Error al abrir el archivo README.md" << endl;
        return 1;
    }

    readme << "\n## Evaluacion del desempeno del algoritmo paralelo para multiplicar dos matrices\n";
    readme << "### Tabla 1. Parametros iniciales\n";
    readme << "Arquitectura del equipo: Intel Xeon\n";
    readme << "Nro. de procesadores: 12\n";
    readme << "Tamano del problema: N = " << n << "\n";

    readme << "\n### Tabla 2. Resultados experimentales\n";
    readme << "| Nro. Hilos | Tiempo Paralelo (seg) | Speedup (Sp) | Eficiencia (E) |\n";
    readme << "|------------|-----------------------|--------------|----------------|\n";
    for (int h = 0; h < 7; h++)
    {
        readme << "| " << setw(10) << hilos[h] << " | " << setw(21) << fixed << setprecision(3) << tiempos_paralelos[h]
               << " | " << setw(12) << fixed << setprecision(3) << speedup[h]
               << " | " << setw(14) << fixed << setprecision(3) << eficiencia[h] << " |\n";
    }

    readme.close();

    // Liberar memoria
    for (i = 0; i < n; i++)
    {
        delete[] matriz_a[i];
        delete[] matriz_b[i];
        delete[] matriz_c[i];
    }
    delete[] matriz_a;
    delete[] matriz_b;
    delete[] matriz_c;

    return 0;
}
