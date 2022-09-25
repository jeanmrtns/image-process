#include <stdio.h>
#include "border.h"

void set_border(int width, int height, unsigned char matriz[width][height]){
    int i,j, border_width;

		printf("Insira o tamanho da borda: ");
		scanf("%d", &border_width);

    for (i=0; i<height; ++i){
		for (j=0; j<width; ++j){
			if (i <= border_width || (i >= (height-border_width)) ) {
				matriz[i][j] = 255;
			} else if (j <= border_width || (j >= (width-border_width))) {
				matriz[i][j] = 255;
			}
		}
	}
}