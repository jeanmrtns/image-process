#include "gira180.h"

void gira180(int width, int height, unsigned char matriz[width][height]){
    unsigned char out_buffer[width][height];

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            out_buffer[width - 1 - i][j] = matriz[i][j];
        }
    }

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            matriz[i][j] = out_buffer[i][j];
        }
    }    
}
