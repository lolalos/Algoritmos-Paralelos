#include <iostream>
#include <iomanip>
#include <omp.h>
#include <cmath>

long double f(long double x) {
    return (pow(x, 3.0L) / 3.0L + 4 * x);
}

int main() {
    long double a = 0.0L;      // Límite inferior
    long double b = 10.0L;     // Límite superior
    long long n = 1000000000;  // Número de rectángulos (más grande)
    long double h = (b - a) / n; // Ancho de cada rectángulo

    long double suma_secuencial = 0.0L;
    double start_time, end_time;

    // Tiempo de inicio para ejecución secuencial
    start_time = omp_get_wtime();

    for (long long i = 0; i < n; i++) {
        long double x = a + i * h;
        suma_secuencial += f(x) * h;
    }

    // Tiempo de fin para ejecución secuencial
    end_time = omp_get_wtime();
    double tiempo_secuencial = end_time - start_time;

    std::cout << "Resultado de la integral (secuencial): " << suma_secuencial << std::endl;
    std::cout << "Tiempo secuencial: " << tiempo_secuencial << " segundos" << std::endl;

    // Encabezado de la tabla
    std::cout << std::setw(10) << "Nro. Hilos" 
              << " | " << std::setw(20) << "Tiempo Paralelo (seg)" 
              << " | " << std::setw(10) << "Speedup (Sp)" 
              << " | " << std::setw(10) << "Eficiencia (E)" 
              << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    // Prueba con diferentes números de hilos
    for (int num_hilos = 1; num_hilos <= 8; num_hilos++) {
        omp_set_num_threads(num_hilos);

        long double suma_paralela = 0.0L;

        // Tiempo de inicio para ejecución paralela
        start_time = omp_get_wtime();

        #pragma omp parallel for reduction(+:suma_paralela)
        for (long long i = 0; i < n; i++) {
            long double x = a + i * h;
            suma_paralela += f(x) * h;
        }

        // Tiempo de fin para ejecución paralela
        end_time = omp_get_wtime();
        double tiempo_paralelo = end_time - start_time;

        // Cálculo de Speedup y Eficiencia
        double speedup = tiempo_secuencial / tiempo_paralelo;
        double eficiencia = speedup / num_hilos;

        // Mostrar resultados en formato de tabla
        std::cout << std::setw(10) << num_hilos 
                  << " | " << std::setw(20) << tiempo_paralelo 
                  << " | " << std::setw(10) << speedup 
                  << " | " << std::setw(10) << eficiencia 
                  << std::endl;
    }

    return 0;
}
