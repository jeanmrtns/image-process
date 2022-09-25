#include <stdio.h>
#include "brilho.h"

void brilho(int width, int height, unsigned char matriz[width][height]){
    int i,j,fator,aux;
    printf("Digite o fator de brilho: ");
    scanf("%d", &fator);
    for (i=0; i<height; ++i){
        for (j=0; j<width; ++j){
            aux = matriz[i][j] + fator;
            if (aux > MAX_COLOR)
                matriz[i][j] = MAX_COLOR;
            else
                matriz[i][j] = aux;
        }
    }
}