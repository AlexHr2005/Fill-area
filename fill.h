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