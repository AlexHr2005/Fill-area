struct pixel** read_file(FILE *fptr, char* fileName, int* rows, int* columns) {
    fptr = fopen(fileName, "r");

    if(fptr == NULL) {
       printf("Error! There is no such file existing!\n");
       return NULL;
    }

    fscanf(fptr, "%d", columns);
    fseek(fptr, 1, SEEK_CUR);
    fscanf(fptr, "%d", rows);

    struct pixel** picture = (struct pixel**)malloc(*rows * sizeof(struct pixel*));
    for(int i = 0; i < *rows; i++) {
        picture[i] = (struct pixel*) malloc (*columns * sizeof(struct pixel));
    }

    for(int r = 0; r < *rows; r++) {
        for(int c = 0; c < *columns; c++) {
            fscanf(fptr, "%d", &picture[r][c].R);
            fseek(fptr, 1, SEEK_CUR);
            fscanf(fptr, "%d", &picture[r][c].G);
            fseek(fptr, 1, SEEK_CUR);
            fscanf(fptr, "%d", &picture[r][c].B);
            fseek(fptr, 1, SEEK_CUR);
        }
    }

    fclose(fptr);
    return picture;
}

void write_to_file(FILE *fptr, char* fileName, struct pixel** picture, int rows, int columns) {
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%d ", columns);
    fprintf(fptr, "%d\n", rows);

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            fprintf(fptr, "%d:%d:%d", picture[r][c].R, picture[r][c].G, picture[r][c].B);
            if(c + 1 != columns) {
                fprintf(fptr, " ");
            }
            else {
                if(r + 1 != rows) {
                    fprintf(fptr, "\n");
                }
            }
        }
    }

    fclose(fptr);
}