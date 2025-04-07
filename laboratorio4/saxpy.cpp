# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>
int main(int argc, char* argv[])
{
int i;
int n = 10000000;
float s = 1.5;
float* x;
float* y;
float* z;
printf("\n");
printf("SAXPY\n");
printf("\n");
printf(" Un programa que agrega un multiplo de un vector a otro.\n");
printf("\n");
printf(" Numero de procesadores disponibles = %d\n", omp_get_num_procs());
printf(" Numero de hilos = %d\n", omp_get_max_threads());
/*
reservar memoria para los vectores
*/
x = (float*)malloc(n * sizeof(float));
y = (float*)malloc(n * sizeof(float));
z = (float*)malloc(n * sizeof(float));
/*
comienza la región paralela
*/
# pragma omp parallel private ( i )
{
/*
Poner datos a los vectores
*/
# pragma omp for
for (i = 0; i < n; i++)
{
x[i] = (float)((i + 1) % 7);
y[i] = (float)((i + 1) % 3);
}
/*
Realiza la operacion SAXPY
*/
# pragma omp for
for (i = 0; i < n; i++)
{
z[i] = x[i] + s * y[i];
}
/*
Termina la región paralela
*/
}
/*
imprime algunos datos
*/
printf("\n");
printf(" i x[i] y[i] z[i]=x[i]+s*y[i]\n");
printf("\n");
for (i = 0; i < n && i < 10; i++)
{
printf(" %2d %10.4f %10.4f %10.4f\n", i, x[i], y[i], z[i]);

}
/*
liberar memoria
*/
free(x);
free(y);
system("pause");
return 0;
}