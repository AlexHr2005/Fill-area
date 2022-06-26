#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"
#include "handle_file.h"
#include "fill.h"

int main()
{
    FILE *fptr;
    char fileName[20];
    int rows, columns;
    int row_to_fill, column_to_fill;

    printf("Welcome to Fill Area! (basically Paint)\n");
    printf("\nName of the file: ");
    scanf("%s", fileName);

    struct pixel** picture = read_file(fptr, fileName, &rows, &columns);
    if(picture == NULL) {
        return -1;
    }

    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            printf("%d:%d:%d ", picture[r][c].R, picture[r][c].G, picture[r][c].B);
        }
        printf("\n");
    }

    printf("Coordinates - '[row] [column]': ");
    scanf("%d %d", &row_to_fill, &column_to_fill);

    while(row_to_fill >= rows || column_to_fill >= columns) {
        printf("\nInvalid coordinates (row/column). Try again\n");
        printf("Coordinates - '[row] [column]': ");
        scanf("%d %d", &row_to_fill, &column_to_fill);
    }

    fill_area(picture, rows, columns, row_to_fill, column_to_fill);

    printf("\n");
    for(int r = 0; r < rows; r++) {
        for(int c = 0; c < columns; c++) {
            printf("%d:%d:%d ", picture[r][c].R, picture[r][c].G, picture[r][c].B);
        }
        printf("\n");
    }

    write_to_file(fptr, fileName, picture, rows, columns);

    free(picture);

    return 0;
}
