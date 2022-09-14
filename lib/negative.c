#include "negative.h";

void negative(int width, int height, unsigned char matriz[width][height]) {
  int i, j;
  for (i=0; i<width; ++i)
    for (j=0; j<height; ++j)
      matriz[i][j] = 255 - matriz[i][j];
}