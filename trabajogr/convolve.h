/*
Copyright (C) 2006 Pedro Felzenszwalb

Este programa es software libre; puedes redistribuirlo y/o modificarlo
bajo los términos de la Licencia Pública General GNU publicada por
la Free Software Foundation; ya sea la versión 2 de la Licencia, o
(a tu elección) cualquier versión posterior.

Este programa se distribuye con la esperanza de que sea útil,
pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Consulta la
Licencia Pública General GNU para obtener más detalles.

Deberías haber recibido una copia de la Licencia Pública General GNU
junto con este programa; si no es así, escribe a la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/* convolución */

#ifndef CONVOLVE_H
#define CONVOLVE_H

#include <vector>
#include <algorithm>
#include <cmath>
#include <omp.h>
#include "image.h"

/* convoluciona src con mask. ¡dst está volteado! */
static void convolve_even(image<float> *src, image<float> *dst,
        std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();

  for (int y = 0; y < height; y++) {
  for (int x = 0; x < width; x++) {
    float sum = mask[0] * imRef(src, x, y);
    for (int i = 1; i < len; i++) {
  sum += mask[i] *
    (imRef(src, std::max(x-i,0), y) +
     imRef(src, std::min(x+i, width-1), y));
    }
    imRef(dst, y, x) = sum;
  }
  }
}

/* convoluciona src con mask. ¡dst está volteado! */
static void convolve_odd(image<float> *src, image<float> *dst,
       std::vector<float> &mask) {
  int width = src->width();
  int height = src->height();
  int len = mask.size();

  for (int y = 0; y < height; y++) {
  for (int x = 0; x < width; x++) {
    float sum = mask[0] * imRef(src, x, y);
    for (int i = 1; i < len; i++) {
  sum += mask[i] *
    (imRef(src, std::max(x-i,0), y) -
     imRef(src, std::min(x+i, width-1), y));
    }
    imRef(dst, y, x) = sum;
  }
  }
}

#endif
