#include "preto_branco.h"

void preto_branco(int width, int height, unsigned char matriz[width][height]){
    int i,j;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
            if(matriz[i][j] < 128){
                matriz[i][j] = 0;
            }else{
                matriz[i][j] = 255;
            }
        }
    }
}