/*
Copyright (C) 2006 Pedro Felzenszwalb

Este programa es software libre; puedes redistribuirlo y/o modificarlo
bajo los términos de la Licencia Pública General de GNU publicada por
la Free Software Foundation; ya sea la versión 2 de la Licencia, o
(cualquier versión posterior).

Este programa se distribuye con la esperanza de que sea útil,
pero SIN NINGUNA GARANTÍA; incluso sin la garantía implícita de
COMERCIALIZACIÓN o IDONEIDAD PARA UN PROPÓSITO PARTICULAR.  Consulta la
Licencia Pública General de GNU para más detalles.

Deberías haber recibido una copia de la Licencia Pública General de GNU
junto con este programa; si no, escribe a la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <cstdio>
#include <cstdlib>
#include "image.h"
#include "misc.h"
#include "pnmfile.h"
#include "segment-image.h"
#include <chrono>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 6) {
    fprintf(stderr, "uso: %s sigma k min entrada(ppm) salida(ppm)\n", argv[0]);
    return 1;
  }

  float sigma = atof(argv[1]);
  float k = atof(argv[2]);
  int min_size = atoi(argv[3]);

  printf("Cargando imagen de entrada.\n");
  image<rgb> *input = loadPPM(argv[4]);

  printf("Procesando\n");
  int num_ccs;

  // Iniciar temporizador
  auto start = std::chrono::high_resolution_clock::now();

  image<rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs);

  // Detener temporizador
  auto end = std::chrono::high_resolution_clock::now();

  // Calcular duración
  std::chrono::duration<double, std::milli> duration_ms = end - start;

  savePPM(seg, argv[5]);

  printf("Se encontraron %d componentes\n", num_ccs);
  std::cout << "La segmentación tomó " << duration_ms.count() << " ms.\n";
  printf("¡Listo! Uf... eso fue mucho trabajo.\n");

  delete input;
  delete seg;

  return 0;
}