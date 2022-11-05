#include "rgb_to_gray.h"

void rgb_to_gray(int width, int height, unsigned char buf[width*height][3]){
    int sz = height * width;
    int i;

    for (i = 0; i < sz; i++) {
        int y = 0;
        y = (buf[i][0] * 0.3) + (buf[i][1] * 0.59) + (buf[i][2] * 0.11); // Conversion formula of RGB to gray
        buf[i][0] = y;
        buf[i][1] = y;
        buf[i][2] = y;
    }
}