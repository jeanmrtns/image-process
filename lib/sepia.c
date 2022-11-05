#include "sepia.h"

void sepia(int width, int height, unsigned char buf[width*height][3]){
    int sz = height * width;
    int i;

    for (i = 0; i < sz; i++) {
        int r = 0, g = 0, b = 0;
        r = (buf[i][0] * 0.393) + (buf[i][1] * 0.769) + (buf[i][2] * 0.189);
        g = (buf[i][0] * 0.349) + (buf[i][1] * 0.686) + (buf[i][2] * 0.168);
        b = (buf[i][0] * 0.272) + (buf[i][1] * 0.534) + (buf[i][2] * 0.131);

        if (r > MAX_VALUE) {           // If value exceeds
            r = MAX_VALUE;
        }
        if (g > MAX_VALUE) {
            g = MAX_VALUE;
        }
        if (b > MAX_VALUE) {
            b = MAX_VALUE;
        }
        
        buf[i][0] = b;
        buf[i][1] = g;
        buf[i][2] = r;
    }
}