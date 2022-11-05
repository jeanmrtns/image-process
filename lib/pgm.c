#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "pgm.h"

#define HI(num)	(((num) & 0x0000FF00) << 8)
#define LO(num)	((num) & 0x000000FF)

int **allocate_dynamic_matrix(int row, int col)
{
    int **ret_val;
    int i;
 
    ret_val = (int **)malloc(sizeof(int *) * row);
    if (ret_val == NULL) {
        perror("memory allocation failure");
        exit(EXIT_FAILURE);
    }
 
    for (i = 0; i < row; ++i) {
        ret_val[i] = (int *)malloc(sizeof(int) * col);
        if (ret_val[i] == NULL) {
            perror("memory allocation failure");
            exit(EXIT_FAILURE);
        }
    }
 
    return ret_val;
}
 
void deallocate_dynamic_matrix(int **matrix, int row)
{
    int i;
 
    for (i = 0; i < row; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void SkipComments(FILE *fp)
{
    int ch;
    char line[100];
    while ((ch = fgetc(fp)) != EOF && isspace(ch)) {
        ;
    }
 
    if (ch == '#') {
        fgets(line, sizeof(line), fp);
        SkipComments(fp);
    } else {
        fseek(fp, -1, SEEK_CUR);
    }
}

PGMData* readPGM(const char *file_name, PGMData *data)
{
    FILE *pgmFile;
    char ext[5] = ".pgm";
    char version[3];
    int i, j;
    int lo, hi;
    pgmFile = fopen(strcat(file_name, ext), "rb");
    if (pgmFile == NULL) {
        perror("cannot open file to read");
        exit(EXIT_FAILURE);
    }
    fgets(version, sizeof(version), pgmFile);
    if (strcmp(version, "P5")) {
        fprintf(stderr, "Wrong file type!\n");
        exit(EXIT_FAILURE);
    }
    SkipComments(pgmFile);
    fscanf(pgmFile, "%d", &data->col);
    SkipComments(pgmFile);
    fscanf(pgmFile, "%d", &data->row);
    SkipComments(pgmFile);
    fscanf(pgmFile, "%d", &data->max_gray);
    fgetc(pgmFile);
 
    data->matrix = allocate_dynamic_matrix(data->row, data->col);
    if (data->max_gray > 255) {
        for (i = 0; i < data->row; ++i) {
            for (j = 0; j < data->col; ++j) {
                hi = fgetc(pgmFile);
                lo = fgetc(pgmFile);
                data->matrix[i][j] = (hi << 8) + lo;
            }
        }
    }
    else {
        for (i = 0; i < data->row; ++i) {
            for (j = 0; j < data->col; ++j) {
                lo = fgetc(pgmFile);
                data->matrix[i][j] = lo;
            }
        }
    }
 
    fclose(pgmFile);
    return data;
 
}
 
void writePGM(const char *filename, const PGMData *data)
{
    char ext[5] = ".pgm";
    FILE *pgmFile;
    int i, j, choice;
    int hi, lo;
    int sair = 1;
 
    pgmFile = fopen(strcat(filename, ext), "wb");
    if (pgmFile == NULL) {
        perror("cannot open file to write");
        exit(EXIT_FAILURE);
    }
 
    fprintf(pgmFile, "P5 ");
    fprintf(pgmFile, "%d %d ", data->col, data->row);
    fprintf(pgmFile, "%d ", data->max_gray);
 
    if (data->max_gray > 255) {
        for (i = 0; i < data->row; ++i) {
            for (j = 0; j < data->col; ++j) {
                hi = HI(data->matrix[i][j]);
                lo = LO(data->matrix[i][j]);
                fputc(hi, pgmFile);
                fputc(lo, pgmFile);
            }
        }
    }
    else {
        while(sair == 1){
            exibirMenuPGM();
            scanf("%d", &choice);
            getchar();

            switch(choice) {
            case 0:
                sair = 0;
				printf("Saindo do programa\n");
				break;
            case 1:
                for (i = 0; i < data->row; ++i) {
                for (j = 0; j < data->col; ++j) {
                    lo = LO(data->matrix[data->col - 1 - j][i]);
                    fputc(lo, pgmFile);
                }
                }
                break;
            case 2:
                for (i = 0; i < data->row; ++i) {
                for (j = 0; j < data->col; ++j) {
                    lo = LO(data->matrix[j][data->col - 1 - i]);
                    fputc(lo, pgmFile);
                }
                }
                break;
            case 3:
                for (i = 0; i < data->row; ++i) {
                for (j = 0; j < data->col; ++j) {
                    lo = LO(data->matrix[data->row - 1 - i][j]);
                    fputc(lo, pgmFile);
                }
                }
                break;
            default:
                printf("\nOpcao invalida!\n\n");
                break;
            }
        }
    }

    fclose(pgmFile);
    deallocate_dynamic_matrix(data->matrix, data->row);
}