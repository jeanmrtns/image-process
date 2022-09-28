#include "gira90.h"

void gira90(int width, int height, unsigned char matriz[width][height]){
    unsigned char out_buffer[width][height];

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            out_buffer[j][width - 1 - i] = matriz[i][j];
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            matriz[i][j] = out_buffer[i][j];
        }
    }    
}
