#include <stdio.h>
#include <math.h>

#include <stdlib.h>
#include <time.h>
#include <omp.h>
//--Define el número de nodos en el grafo
#define N 500
//--Función mín para calcular valores mínimos entre dos números
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
//--Define una matriz de tamaño N * N para almacenar las distancias entre los nodos
//--Inicializa las distancias en cero
int distance_matrix[N][N] = { 0 };
int main(int argc, char* argv[])
{
int nthreads;
int src, dst, middle;
//--Inicializa el grafo con distancias aleatorias
for (src = 0; src < N; src++)
{
for (dst = 0; dst < N; dst++)
{
//--La distancia de un nodo al mismo nodo es 0
if (src != dst) {
//--Las distancias son generadas entre 0 y 19
distance_matrix[src][dst] = rand() % 20;
}
}
}
//=======ALGORITMO SECUENCIAL=========
//--Obtiene el tiempo inicial
double start_time = omp_get_wtime();
for (middle = 0; middle < N; middle++)
{
int* dm = distance_matrix[middle];
for (src = 0; src < N; src++)
{
int* ds = distance_matrix[src];
for (dst = 0; dst < N; dst++)
{
ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
}
}
}
//--obtiene el tiempo final
double time = omp_get_wtime() - start_time;
printf("Tiempo Total secuencial (en seg):%.2f\n", time);
//=========ALGORITMO PARALELO==============
for (nthreads = 1; nthreads <= 10; nthreads++) {
//--Define diferente número de hilos
omp_set_num_threads(nthreads);
//--Define el iterador para iterar sobre la matriz de distancias
//--Obtiene el tiempo inicial
double start_time = omp_get_wtime();
/*Tomando un nodo como mediador
comprobar si la distancia indirecta entre la fuente y la distancia
a través del mediador es menor que la distancia directa entre ellos */
#pragma omp parallel shared(distance_matrix)
for (middle = 0; middle < N; middle++)
{
int* dm = distance_matrix[middle];
#pragma omp parallel for private(src, dst) schedule(dynamic)

for (src = 0; src < N; src++)
{
int* ds = distance_matrix[src];
for (dst = 0; dst < N; dst++)
{
ds[dst] = min(ds[dst], ds[middle] + dm[dst]);
}
}
}
//--obtiene el tiempo final
double time = omp_get_wtime() - start_time;
printf("Tiempo Total para %d hilos (en seg):%.2f\n", nthreads, time);
}
system("pause");
return 0;
}