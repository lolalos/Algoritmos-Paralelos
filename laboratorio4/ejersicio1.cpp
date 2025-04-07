#include <stdio.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    int i, j;
    srand(time(NULL));
    int n;
    cout << "ingrese el valor de n: ";
    cin >> n;
    //--crea las matrices n x n
    int **matriz_a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matriz_a[i] = new int[n];
    }
    int **matriz_b = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matriz_b[i] = new int[n];
    }
    int **matriz_c = new int *[n];
    for (int i = 0; i < n; i++)
    {
        matriz_c[i] = new int[n];
    }
    //--llena las matrices a y b con valores aleatorios
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matriz_a[i][j] = (rand() % 4) + 1;
            matriz_b[i][j] = (rand() % 4) + 1;
        }
    }
    /* muestra la matriz_a */
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", matriz_a[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    /* muestra la matriz_b*/
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", matriz_b[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    /* realizar la multiplicación en paralelo */
#pragma omp parallel
    {
        int i, j, k, suma;

#pragma omp for private(i, suma)
        for (i = 0; i < n; i++)

        {
            for (j = 0; j < n; j++)
            {
                suma = 0;
                for (k = 0; k < n; k++)
                {
                    suma += (matriz_a[i][k] * matriz_b[k][j]);
                }
                matriz_c[i][j] = suma;
            }
        }
    }
    //-- muestra la matriz_c de resultados
    ofstream file_md;
    file_md.open("README.md", ios::app);
    file_md << "\n## Ejercicio 1 - Multiplicación de Matrices\n";
    file_md << "[Enlace al código fuente](D:/Algoritmos-Paralelos/laboratorio4/ejersicio1.cpp)\n";
    file_md << "Valor de n: " << n << "\n";
    file_md << "\n## Result Matrix C:\n";
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", matriz_c[i][j]);
            file_md << matriz_c[i][j] << " ";
        }
        printf("\n");
        file_md << "\n";
    }
    file_md.close();
    system("PAUSE");
    return 0;
}