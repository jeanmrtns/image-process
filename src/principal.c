#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "bmp.h"
#include "showheader.h"

/* Compilar com:
 	clang -Wall -std=c11 -O2 showheader.c -o showheader

        clang -Wall src/principal.c lib/showheader.c -I./include -o executavel
 */
/*
   Header:
   offset	size	description
   0		2	signature, must be 4D42 hex
   2		4	size of BMP file in bytes (unreliable)
   6		2	reserved, must be zero
   8		2	reserved, must be zero
   10		4	offset to start of image data in bytes
   14		4	size of BITMAPINFOHEADER structure, must be 40
   18		4	image width in pixels
   22		4	image height in pixels
   26		2	number of planes in the image, must be 1
   28		2	number of bits per pixel (1, 4, 8, or 24)
   30		4	compression type (0=none, 1=RLE-8, 2=RLE-4)
   34		4	size of image data in bytes (including padding)
   38		4	horizontal resolution in pixels per meter (unreliable)
   42		4	vertical resolution in pixels per meter (unreliable)
   46		4	number of colors in image, or zero
   50		4	number of important colors, or zero
*/

int main(void) {
	bmpheader hd;
	bmpinfoheader infohd;

	unsigned char header[HDRBMP] = {0};	/* To store the image header */
	unsigned char colorTable[HBMPCT] = {0};	/* To store the colorTable, if it exists */

	char fname[] = "./lena512.bmp";
	char out[] = "./saida.bmp";
	unsigned char *buf;

	FILE *streamIn, *fo;

	unsigned int i;
	double sz;

	streamIn = fopen(fname, "rb");		/* Open the file */
	if (streamIn == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

        /* Reading the bitmap file header struct */
        // fread(&hd, sizeof(bmpheader), 1, streamIn);
	// if (hd.type != 0x4D42) {fclose(streamIn); exit(EXIT_FAILURE);}
        /* Reading the bitmap info header struct */
        // fread(&infohd, sizeof(bmpinfoheader), 1, streamIn);
        // Moving the file pointer to the beginning of bitmap data
        // fseek(streamIn, hd.offset, SEEK_SET);

	for (i = 0; i < HDRBMP; i++) {
		header[i] = getc(streamIn);				/* Strip out BMP header, byte-wise */
	}

	if (gethd(&header[0], &hd)) {
	    fclose(streamIn);
	    perror("BMP header error");
	    exit(EXIT_FAILURE);
	}
	getinfohd(header, &infohd);

	/* BMP (Windows) header */
	printf("\nBMP (Windows) header\n");
	// printhd(&hd);
	// printinfohd(&infohd);

	if (infohd.bits <= HDRBD) {
		fread(colorTable, sizeof(unsigned char), HBMPCT, streamIn);
	}

	/* Avoid invalid requests */
	if (infohd.height < 0 || infohd.width < 0)
	    perror("Overflow");

	/* Check for signed int overflow */
	if (infohd.height && infohd.width > INT_MAX / infohd.height)
	    perror("Overflow");

	sz = infohd.height * infohd.width;
	buf = (unsigned char *) malloc(sz);	/* To store the image data */

	if (buf == NULL) {
		perror("malloc()");
                exit(EXIT_FAILURE);
	}
	int borda = 10;
	fread(buf, sizeof(unsigned char), sz, streamIn);
	for (i = 0; i < 512*512; i++) {
		if(i <= 512*borda){
			buf[i] = 255;
		}else if(i >= 512*502){
			buf[i] = 255;
		}else if(i > 512*borda && i < 512*502){
			// int linha = ceil(i/512);
			// if(i <= (512*linha)-(512-borda)){
			// 	buf[i] = 255;
			// }
		}
	}
	// int i;
	// int j;
	// unsigned char matriz[512][512];
	// for (i=0; i<512; ++i)
	// 	for (j=0; j<512; ++j)
	// 		matriz[i][j] = buf[i+j];

	// for (i=0; i<10; ++i){
	// 	for (j=0; j<512; ++j)
	// 		matriz[i][j] = 1;
  // }

	fo = fopen(out, "wb");			/* Open the file */
	if (fo == NULL) {
		perror("fopen()");
		exit(EXIT_FAILURE);
	}

	/* Write the image header to output file */
	fwrite(header, sizeof(unsigned char), HDRBMP, fo);

	if (infohd.bits <= 8) {
		fwrite(colorTable, sizeof(unsigned char), HBMPCT, fo);
	}

	fwrite(buf, sizeof(unsigned char), sz, fo);

	fclose(fo);
	fclose(streamIn);

	free(buf);
	return(EXIT_SUCCESS);
}

/* Bitmap BGR to bitmap RGB (swaping R and B values) */
/*
uint idx = 0;
unsigned char buf[];

for (idx = 0; idx < infohd->imagesize; idx += 3) { // infohd->imagesize or sz
     buf[idx]     = buf[idx] ^ buf[idx + 2];
     buf[idx + 2] = buf[idx + 2] ^ buf[idx];
     buf[idx]     = buf[idx] ^ buf[idx + 2];
}

or

typedef struct {
    unsigned char r, g, b, junk;
} COLOUR_IDX;
*/

/**************************/
/* Vers�o compacta:       */
/* *x ^= *y ^= *x^ = *y;  */
/**************************/

