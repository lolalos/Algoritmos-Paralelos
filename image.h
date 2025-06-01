/*
Copyright (C) 2006 Pedro Felzenszwalb

Este programa es software libre; puedes redistribuirlo y/o modificarlo
bajo los términos de la Licencia Pública General GNU publicada por
la Free Software Foundation; ya sea la versión 2 de la Licencia, o
(a tu elección) cualquier versión posterior.

Este programa se distribuye con la esperanza de que sea útil,
pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
COMERCIABILIDAD o IDONEIDAD PARA UN PROPÓSITO PARTICULAR. Consulta
la Licencia Pública General GNU para obtener más detalles.

Deberías haber recibido una copia de la Licencia Pública General GNU
junto con este programa; si no es así, escribe a la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

/* una clase simple para imágenes */

#ifndef IMAGE_H
#define IMAGE_H

#include <cstring>

template <class T>
class image {
 public:
  /* crea una imagen */
  image(const int width, const int height, const bool init = true);

  /* elimina una imagen */
  ~image();

  /* inicializa una imagen */
  void init(const T &val);

  /* copia una imagen */
  image<T> *copy() const;

  /* obtiene el ancho de una imagen. */
  int width() const { return w; }

  /* obtiene el alto de una imagen. */
  int height() const { return h; }

  /* datos de la imagen. */
  T *data;

  /* punteros a las filas. */
  T **access;

 private:
  int w, h;
};

/* usa imRef para acceder a los datos de la imagen. */
#define imRef(im, x, y) (im->access[y][x])

/* usa imPtr para obtener un puntero a los datos de la imagen. */
#define imPtr(im, x, y) &(im->access[y][x])

template <class T>
image<T>::image(const int width, const int height, const bool init) {
  w = width;
  h = height;
  data = new T[w * h];  // reserva espacio para los datos de la imagen
  access = new T*[h];   // reserva espacio para los punteros a las filas

  // inicializa los punteros a las filas
  for (int i = 0; i < h; i++)
    access[i] = data + (i * w);

  if (init)
    memset(data, 0, w * h * sizeof(T));
}

template <class T>
image<T>::~image() {
  delete [] data;
  delete [] access;
}

template <class T>
void image<T>::init(const T &val) {
  T *ptr = imPtr(this, 0, 0);
  T *end = imPtr(this, w-1, h-1);
  while (ptr <= end)
    *ptr++ = val;
}


template <class T>
image<T> *image<T>::copy() const {
  image<T> *im = new image<T>(w, h, false);
  memcpy(im->data, data, w * h * sizeof(T));
  return im;
}

#endif
