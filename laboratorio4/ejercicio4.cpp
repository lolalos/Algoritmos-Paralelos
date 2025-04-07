#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <omp.h>
using namespace std;
double prodpunto(double *a, double *b, int n)
{
double res = 0;
int i;
#pragma omp parallel for reduction(+:res)
for (i = 0; i < n; i++)
{
res += a[i] * b[i];
}
return res;
}
int main()
{
int n=100;
double *a = new double[n];
double *b = new double[n];
//--colocacion de datos al arreglo a
for (int i = 0; i < n; i++)
a[i] = i;
//--colocaciòn de datos al arreglo b
for (int j = 0; j < n; j++)
b[j] = j * 10;
//--calcular producto punto en paralelo
double pp = prodpunto(a, b, n);
cout <<"elproducto punto es: "<<fixed<<setprecision(2)<< pp << endl;
getchar();
return(0);
}