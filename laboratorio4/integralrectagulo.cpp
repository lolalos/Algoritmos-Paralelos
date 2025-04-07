#include <iostream>
#include <omp.h>
#include <cmath>

double f(double x) {
    return (pow(x, 3.0) / 3.0 + 4 * x);
}

int main() {
    double a = 0.0;      // Límite inferior
    double b = 10.0;     // Límite superior
    int n = 100000000;   // Número de rectángulos
    double h = (b - a) / n; // Ancho de cada rectángulo

    double suma = 0.0;
    double start_time, end_time;

    // Tiempo de inicio
    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:suma)
    for (int i = 0; i < n; i++) {
        double x = a + i * h;
        suma += f(x) * h;
    }

    // Tiempo de fin
    end_time = omp_get_wtime();

    std::cout << "Resultado de la integral: " << suma << std::endl;
    std::cout << "Tiempo con OpenMP: " << (end_time - start_time) << " segundos" << std::endl;

    return 0;
}
