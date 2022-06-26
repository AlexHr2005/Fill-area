#include <stdio.h>
#include <stdlib.h>

struct pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

float calculate_avarage_intensity(struct pixel p) {
    return ((float) p.R + (float) p.G + (float) p.B) / 3;
}

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

void fill_area(struct pixel** picture, int rows, int columns, int row_to_fill, int column_to_fill) {
    fill_horizontally(picture, columns, row_to_fill, column_to_fill);
    fill_vertically(picture, rows, row_to_fill, column_to_fill);

    picture[row_to_fill][column_to_fill].R = 0;
    picture[row_to_fill][column_to_fill].G = 0;
    picture[row_to_fill][column_to_fill].B = 0;
}

void fill_horizontally(struct pixel** picture, int columns, int row_to_fill, int column_to_fill) {
    int row[columns];
    for(int i = 0; i < columns; i++){
        row[i] = 0;
    }

    struct pixel current = picture[row_to_fill][column_to_fill];
    float curr_avarage_intensity;
    float start_avarage_intensity = calculate_avarage_intensity(current);

    for(int c = column_to_fill + 1; c < columns; c++) {
        current = picture[row_to_fill][c];
        curr_avarage_intensity = calculate_avarage_intensity(current);

        if(curr_avarage_intensity - start_avarage_intensity >= -1.00 && curr_avarage_intensity - start_avarage_intensity <= 1.00) {
            row[c] = 1;
        }
        else break;
    }

    for(int c = column_to_fill - 1; c >= 0; c--) {
        current = picture[row_to_fill][c];
        curr_avarage_intensity = calculate_avarage_intensity(current);
        if(curr_avarage_intensity - start_avarage_intensity >= -1.00 && curr_avarage_intensity - start_avarage_intensity <= 1.00) {
            row[c] = 1;
        }
        else break;
    }

    for(int i = 0; i < columns; i++) {
        if(row[i] == 1){
            picture[row_to_fill][i].R = 0;
            picture[row_to_fill][i].G = 0;
            picture[row_to_fill][i].B = 0;
        }
    }
}

void fill_vertically(struct pixel** picture, int rows, int row_to_fill, int column_to_fill) {
    int column[rows];
    for(int i = 0; i < rows; i++) {
        column[i] = 0;
    }

    struct pixel current = picture[row_to_fill][column_to_fill];
    float curr_avarage_intensity;
    float start_avarage_intensity = calculate_avarage_intensity(current);

    for(int r = row_to_fill + 1; r < rows; r++) {
        current = picture[r][column_to_fill];
        curr_avarage_intensity = calculate_avarage_intensity(current);

        if(curr_avarage_intensity - start_avarage_intensity >= -1.00 && curr_avarage_intensity - start_avarage_intensity <= 1.00) {
            column[r] = 1;
        }
        else break;
    }

    for(int r = row_to_fill + -1; r >= 0; r--) {
        current = picture[r][column_to_fill];
        curr_avarage_intensity = calculate_avarage_intensity(current);

        if(curr_avarage_intensity - start_avarage_intensity >= -1.00 && curr_avarage_intensity - start_avarage_intensity <= 1.00) {
            column[r] = 1;
        }
        else break;
    }

    for(int i = 0; i < rows; i++) {
        if(column[i] == 1){
            picture[i][column_to_fill].R = 0;
            picture[i][column_to_fill].G = 0;
            picture[i][column_to_fill].B = 0;
        }
    }
}

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
