#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "bmp.h"
#include "showheader.h"
#include "border.h"
#include "menu.h"
#include "maxmin.h"
#include "preto_branco.h"
#include "brilho.h"
#include "gira180.h"
#include "espelha.h"
#include "gira90.h"
#include "pgm.h"
#include "rgb_to_gray.h"
#include "sepia.h"
#include "negative.h"


// Alunos: Jean, Lucas e Ulysses 

/* Compilar com:
 	clang -Wall -std=c11 -O2 showheader.c -o showheader

	clang -Wall src/principal.c lib/showheader.c -I./include -o executavel
*/

int main(void) {
	bmpheader hd;
	bmpinfoheader infohd;

	unsigned char header[HDRBMP] = {0};	/* To store the image header */
	unsigned char colorTable[HBMPCT] = {0};	/* To store the colorTable, if it exists */

	char fname[50];
	char out[50];

	exibirMenuFormatos();
	int choice;
	scanf("%d", &choice);
	getchar();
	
	if (choice == 1) {
		PGMData* data = malloc(sizeof(PGMData));
		printf("Insira o nome do arquivo (sem a extensao): ");
		scanf("%s", fname);
		getchar();
		printf("Digite o nome de saida do arquivo (sem a extensao): ");
		scanf("%s", out);
		getchar();
    	readPGM(fname, &(*data));
    	writePGM(out, &(*data));
	}else if (choice == 2) {
		char ext[5] = ".bmp";
		printf("Digite o nome do arquivo (sem a extensao): ");
		scanf("%s", fname);
		getchar();
		printf("Digite o nome de saida do arquivo (sem a extensao): ");
		scanf("%s", out);
		getchar();

		unsigned char *buf;

		FILE *streamIn, *fo;

		unsigned int i;
		double sz;

		streamIn = fopen(strcat(fname, ext), "rb");		/* Open the file */
		if (streamIn == NULL) {
			perror("fopen()");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < HDRBMP; i++) {
			header[i] = getc(streamIn);				/* Strip out BMP header, byte-wise */
		}

		if (gethd(&header[0], &hd)) {
			fclose(streamIn);
			perror("BMP header error");
			exit(EXIT_FAILURE);
		}
		getinfohd(header, &infohd);

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
		fread(buf, sizeof(unsigned char), sz, streamIn);

		int j;
		unsigned char matriz[infohd.height][infohd.width];
		for (i=0; i<infohd.height; ++i)
			for (j=0; j<infohd.width; ++j)
				matriz[i][j] = buf[i*infohd.width+j];

		int filtro = 0;
		int sair = 1;
		verifyDataLength(&infohd, streamIn);
		maxmin(buf, sz);
		
		while(sair == 1) {
			exibirMenu();
			scanf("%d", &filtro);
			
			switch(filtro) {
				case 0:
					sair = 0;
					printf("Saindo do programa\n");
					break;
				case 1:
					set_border(infohd.width, infohd.height, matriz);
					printf("\nBorda aplicada!\n");
					break;
				case 2:
					negative(infohd.width, infohd.height, matriz);
					printf("\nFiltro negativo aplicado!\n");
					break;
				case 3:
					preto_branco(infohd.width, infohd.height, matriz);
					printf("\nFiltro preto e branco aplicado!\n");
					break;
				case 4:
					brilho(infohd.width, infohd.height, matriz);
					printf("\nFiltro de brilho aplicado!\n");
					break;
				case 5:
					gira180(infohd.width, infohd.height, matriz);
					printf("\nImagem rotacionada!\n");
					break;
				case 6:
					espelha(infohd.width, infohd.height, matriz);
					printf("\nImagem espelhada!\n");
					break;
				case 7:
					gira90(infohd.width, infohd.height, matriz);
					printf("\nImagem rotacionada em 90 graus!\n");
					break;
				default:
					printf("\nOpção invalida\n");
					break;
			}

			printf("\nEscrevendo no arquivo %s\n", out);
			if (strstr(out, ext) != NULL) {
				fo = fopen(out, "wb");
			}
			
			else {
				fo = fopen(strcat(out, ext), "wb");			/* Open the file */
			}

			if (fo == NULL) {
				perror("fopen()");
				exit(EXIT_FAILURE);
			}

			/* Write the image header to output file */
			fwrite(header, sizeof(unsigned char), HDRBMP, fo);

			if (infohd.bits <= 8) {
				fwrite(colorTable, sizeof(unsigned char), HBMPCT, fo);
			}

			fwrite(matriz, sizeof(unsigned char), sz, fo);

		}
		fclose(fo);
		fclose(streamIn);

		free(buf);
		return(EXIT_SUCCESS);
	}else if(choice == 3){
		char ext[5] = ".bmp";
		printf("Digite o nome do arquivo (sem a extensao): ");
		scanf("%s", fname);
		getchar();
		printf("Digite o nome de saida do arquivo (sem a extensao): ");
		scanf("%s", out);
		getchar();

		FILE *streamIn, *fo;

		unsigned int i;
		int sz;

		streamIn = fopen(strcat(fname, ext), "rb");		/* Open the file */
		if (streamIn == NULL) {
			perror("fopen()");
			exit(EXIT_FAILURE);
		}

		for (i = 0; i < HDRBMP; i++) {
			header[i] = getc(streamIn);				/* Strip out BMP header, byte-wise */
		}

		if (gethd(&header[0], &hd)) {
			fclose(streamIn);
			perror("BMP header error");
			exit(EXIT_FAILURE);
		}
		getinfohd(header, &infohd);

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
		unsigned char buf[sz][3];
		
		/*Lendo imagem e armazenando em buf*/
		for (i = 0; i < sz; i++) {
			buf[i][0] = getc(streamIn);      // Blue
			buf[i][1] = getc(streamIn);      // Green
			buf[i][2] = getc(streamIn);      // Red
		}
		int filtro = 0;
		int sair = 1;
		while(sair == 1) {
			exibirMenuRGB();
			scanf("%d", &filtro);

			switch(filtro) {
				case 0:
					sair = 0;
					printf("Saindo do programa\n");
					break;
				case 1:
					rgb_to_gray(infohd.width, infohd.height, buf);
					printf("\nFiltro aplicado!\n");
					break;
				case 2:
					sepia(infohd.width, infohd.height, buf);
					printf("\nFiltro aplicado!\n");
					break;
				default:
					printf("\nOpção invalida\n");
					break;
			}
			printf("\nEscrevendo no arquivo %s\n", out);
			if (strstr(out, ext) != NULL) {
				fo = fopen(out, "wb");
			}
			
			else {
				fo = fopen(strcat(out, ext), "wb");			/* Open the file */
			}

			if (fo == NULL) {
				perror("fopen()");
				exit(EXIT_FAILURE);
			}
			fwrite(header, sizeof(unsigned char), HDRBMP, fo);
			if (infohd.bits <= 8) {
				fwrite(colorTable, sizeof(unsigned char), HBMPCT, fo);
			}
			fwrite(buf, sizeof(unsigned char), sz*3, fo);
		}
		fclose(fo);
		fclose(streamIn);
	}

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

