#include "maxmin.h"

void maxmin(unsigned char *array, int tam) {
    int i;
    int max, min;

    max = min = array[0];
    for (i = 1; i < tam; i++) {
        if (array[i] > max)
            max = array[i];
        else if (array[i] < min)
            min = array[i];
    }

    printf("O array tem min de %d e max de %d\n\n", min, max);
}