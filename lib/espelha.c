#include "espelha.h"

void espelha(int width, int height, unsigned char matriz[width][height]){
    unsigned char out_buffer[width][height];

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            out_buffer[i][j] = matriz[i][width - j - 1];
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            matriz[i][j] = out_buffer[i][j];
        }
    }    
}
