typedef struct _PGMData {
    int row;
    int col;
    int max_gray;
    int **matrix;
} PGMData;

PGMData* readPGM(const char *file_name, PGMData *data);
void writePGM(const char *filename, const PGMData *data);
