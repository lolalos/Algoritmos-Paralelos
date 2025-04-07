#include <math.h>
#include <iostream>
#include <omp.h>
using namespace std;
double empezar, terminar;
int main(int argc, char *argv[])
{
int n;
cout << "Introduce el número de rectángulos (n > 0): ";
cin >> n;
double PI25DT = 3.141592653589793238462643;
double h = 1.0 / (double)n;
double sum = 0.0;
empezar = omp_get_wtime();
#pragma omp parallel for shared( sum )
for (int i = 1; i <= n; i++) {
double x = h * ((double)i - 0.5);
sum += (4.0 / (1.0 + x*x));
}
double pi = sum * h;
terminar = omp_get_wtime();
cout << "El valor aproximado de PI es: " << pi
<< ", con un error de " << fabs(pi - PI25DT) << endl;
cout << "el tiempo de procesamiento fue: "
<< fixed << terminar - empezar << endl;
cin.get();
return 0;
}