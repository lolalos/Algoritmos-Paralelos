#include <cstdio>
#include <cstdlib>
#include <chrono>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.cuh"
#include <cuda_runtime.h>

int main(int argc, char **argv) {
    // Verifica que se pasen los argumentos necesarios
    if (argc != 6) {
        fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
        return 1;
    }

    // Lee los parámetros de segmentación desde la línea de comandos
    float sigma = atof(argv[1]);
    float k = atof(argv[2]);
    int min_size = atoi(argv[3]);

    // Carga la imagen de entrada
    printf("Cargando imagen de entrada desde: %s\n", argv[4]);
    image<rgb> *input = loadPPM(argv[4]);
    printf("Dimensiones de la imagen: %d x %d\n", input->width(), input->height());

    // Inicia el procesamiento y mide el tiempo de ejecución
    printf("Procesando...\n");
    auto start = std::chrono::high_resolution_clock::now();

    int num_ccs;
    // Realiza la segmentación de la imagen usando CUDA
    image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    printf("Tiempo de ejecución CUDA: %.6f segundos\n", elapsed.count());

    // Guarda la imagen segmentada en disco
    savePPM(seg, argv[5]);
    printf("Imagen segmentada guardada en: %s\n", argv[5]);
    printf("Número de componentes segmentados: %d\n", num_ccs);

    // Libera la memoria utilizada por las imágenes
    delete input;
    delete seg;

    // Imprime resultados detallados del proceso de segmentación
    printf("\n--- Resultados detallados ---\n");
    printf("Parámetros de segmentación:\n");
    printf("  Sigma: %.2f\n", sigma);
    printf("  K: %.2f\n", k);
    printf("  Min Size: %d\n", min_size);
    printf("Dimensiones de la imagen: %d x %d\n", input->width(), input->height());
    printf("Número de componentes segmentados: %d\n", num_ccs);
    printf("Tiempo total de procesamiento: %.6f segundos\n", elapsed.count());
    printf("-----------------------------\n");

    return 0;
}
