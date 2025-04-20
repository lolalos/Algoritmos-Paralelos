#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <omp.h>  // Added OpenMP header
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"
#include "convolve.h"
#include "filter.h"
#include "disjoint-set.h"

// Function to perform 2D convolution with parallelization
void convolve(image<float>* in, image<float>* out, float* kernel, int kernel_size) {
  int width = in->width();
  int height = in->height();
  int k_half = kernel_size / 2;
  
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float sum = 0.0f;
      for (int ky = -k_half; ky <= k_half; ky++) {
        for (int kx = -k_half; kx <= k_half; kx++) {
          int img_x = std::min(std::max(x + kx, 0), width - 1);
          int img_y = std::min(std::max(y + ky, 0), height - 1);
          int k_index = (ky + k_half) * kernel_size + (kx + k_half);
          sum += imRef(in, img_x, img_y) * kernel[k_index];
        }
      }
      imRef(out, x, y) = sum;
    }
  }
}

// Function to convert input image to grayscale with parallelization
template <typename T>
image<float>* rgb2gray(image<T>* input) {
  int width = input->width();
  int height = input->height();
  image<float>* gray = new image<float>(width, height);
  
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      T val = imRef(input, x, y);
      float gray_val = 0.299f * val.r + 0.587f * val.g + 0.114f * val.b;
      imRef(gray, x, y) = gray_val;
    }
  }
  return gray;
}

// Function to save a float image to PPM (visualization)
void saveFloatImageAsPPM(image<float>* img, const char* filename) {
  int width = img->width();
  int height = img->height();
  image<rgb>* out = new image<rgb>(width, height);
  
  // Find min and max for normalization
  float min_val = imRef(img, 0, 0);
  float max_val = min_val;
  
  #pragma omp parallel
  {
    float local_min = min_val;
    float local_max = max_val;
    
    #pragma omp for collapse(2) nowait
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        float val = imRef(img, x, y);
        if (val < local_min) local_min = val;
        if (val > local_max) local_max = val;
      }
    }
    
    #pragma omp critical
    {
      if (local_min < min_val) min_val = local_min;
      if (local_max > max_val) max_val = local_max;
    }
  }
  
  // Normalize and convert to RGB
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float val = imRef(img, x, y);
      int intensity = (int)(255 * (val - min_val) / (max_val - min_val));
      rgb color;
      color.r = color.g = color.b = intensity;
      imRef(out, x, y) = color;
    }
  }
  
  savePPM(out, filename);
  delete out;
}

// Save detailed information to a report file
void saveReport(const std::string& filename, const std::string& details) {
  FILE* fp = fopen(filename.c_str(), "w");
  if (fp) {
    fprintf(fp, "%s", details.c_str());
    fclose(fp);
  }
}

int main(int argc, char **argv) {
  if (argc < 6 || argc > 7) {
    fprintf(stderr, "Uso: %s sigma k min entrada(ppm) salida(prefix) [num_threads]\n", argv[0]);
    return 1;
  }

  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);
  std::string output_prefix = argv[5];
  
  // Set number of threads if specified, otherwise use max available
  int num_threads = (argc == 7) ? atoi(argv[6]) : omp_get_max_threads();
  omp_set_num_threads(num_threads);
  
  std::stringstream report;

  printf("Cargando imagen de entrada %s...\n", argv[4]);
  image<rgb>* input = loadPPM(argv[4]);
  if (!input) {
    fprintf(stderr, "No se pudo cargar la imagen de entrada\n");
    return 1;
  }

  int width = input->width();
  int height = input->height();
  report << "Imagen cargada: " << width << "x" << height << " píxeles\n";
  report << "Parámetros: sigma=" << sigma << ", k=" << k << ", min_size=" << min_size << "\n";
  report << "Número de hilos: " << num_threads << "\n\n";
  printf("Ejecutando con %d hilos\n", num_threads);

  // Step 1: Convert to grayscale
  printf("Convirtiendo a escala de grises...\n");
  image<float>* gray = rgb2gray(input);
  std::string gray_filename = output_prefix + "_gray.ppm";
  saveFloatImageAsPPM(gray, gray_filename.c_str());
  report << "1. Conversión a escala de grises completada\n";
  
  // Step 2: Apply Gaussian smoothing (filter)
  printf("Aplicando filtro Gaussiano...\n");
  image<float>* smooth_img = smooth(gray, sigma);
  std::string smooth_filename = output_prefix + "_smooth.ppm";
  saveFloatImageAsPPM(smooth_img, smooth_filename.c_str());
  report << "2. Filtro Gaussiano aplicado con sigma=" << sigma << "\n";

  // Step 3: Calculate image gradients (convolve)
  printf("Calculando gradientes...\n");
  image<float>* gradx = new image<float>(width, height);
  image<float>* grady = new image<float>(width, height);
  
  // Use the regular convolve function with Sobel kernels
  float sobel_x[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
  float sobel_y[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
  convolve(smooth_img, gradx, sobel_x, 3);
  convolve(smooth_img, grady, sobel_y, 3);
  
  // Visualize gradient magnitude
  image<float>* grad_mag = new image<float>(width, height);
  
  #pragma omp parallel for collapse(2)
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float gx = imRef(gradx, x, y);
      float gy = imRef(grady, x, y);
      imRef(grad_mag, x, y) = sqrt(gx*gx + gy*gy);
    }
  }
  std::string grad_filename = output_prefix + "_gradient.ppm";
  saveFloatImageAsPPM(grad_mag, grad_filename.c_str());
  report << "3. Convolución con Sobel para calcular gradientes completada\n";

  // Step 4: Perform segmentation (disjoint-set)
  printf("Realizando segmentación...\n");
  auto start = std::chrono::high_resolution_clock::now();
  int num_ccs;
  image<rgb>* seg = segment_image(input, sigma, k, min_size, &num_ccs);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration_ms = end - start;
  
  std::string seg_filename = output_prefix + "_segmented.ppm";
  savePPM(seg, seg_filename.c_str());
  report << "4. Segmentación completada usando disjoint-set\n";
  report << "   - Componentes conectados: " << num_ccs << "\n";
  report << "   - Tiempo de segmentación: " << duration_ms.count() << " ms\n";

  // Save the detailed report
  std::string report_filename = output_prefix + "_report.txt";
  saveReport(report_filename, report.str());

  printf("Proceso completado. Se encontraron %d componentes.\n", num_ccs);
  printf("Tiempo de segmentación: %.2f ms\n", duration_ms.count());
  printf("Resultados guardados con prefijo: %s\n", output_prefix.c_str());
  printf("Reporte detallado guardado en: %s\n", report_filename.c_str());
  printf("Número de hilos utilizados: %d\n", num_threads);

  // Clean up
  delete input;
  delete gray;
  delete smooth_img;
  delete gradx;
  delete grady;
  delete grad_mag;
  delete seg;

  return 0;
}
