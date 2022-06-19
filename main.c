#include <stdio.h>
#include <stdlib.h>

struct pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

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

    char a;
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

int main()
{
    FILE *fptr;
    char fileName[20];
    int rows, columns;
    int row_to_write, column_to_write;

    printf("Welcome to Fill Area! (basically Paint)\n");
    printf("\nName of the file: ");
    scanf("%s", fileName);

    struct pixel** picture = read_file(fptr, fileName, &rows, &columns);
    printf("%d %d\n", rows, columns);

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            printf("%d:%d:%d ", picture[r][c].R, picture[r][c].G, picture[r][c].B);
        }
        printf("\n");
    }

    /*printf("Coordinates - '[row] [column]': ");
    scanf("%d %d", &row_to_write, &column_to_write);
    printf("%d %d", row_to_write, column_to_write);*/

    return 0;
}
