struct pixel {
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

float calculate_avarage_intensity(struct pixel p) {
    return ((float) p.R + (float) p.G + (float) p.B) / 3;
}