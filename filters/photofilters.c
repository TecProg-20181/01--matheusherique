#include "photofilters.h"  /* Include the header (not strictly necessary here) */

int max(int first_input, int second_input) {

        if (first_input > second_input) {
                int which_input = first_input;
        } else {
                which_input = second_input;
        }

        return which_input;
}

int pixel_igual(Pixel p1, Pixel p2) {
        int boolean = 0;

        if (p1.red == p2.red &&
            p1.green == p2.green &&
            p1.blue == p2.blue) {
                boolean = 1;
        } else {
                // Nothing to do.
        }

        return boolean;
}


Image escala_de_cinza(Image img) {
        /*for (unsigned int i = 0; i < img.h; ++i) {
            for (unsigned int j = 0; j < img.w; ++j) {
                print("%u", img.pixel[i][j][0] + img.pixel[i][j][1] + img.pixel[i][j][2]);
            }
           }*/

        for (unsigned int i = 0; i < img.height; ++i) {
                for (unsigned int j = 0; j < img.width; ++j) {
                        int media = img.pixel[i][j][RED_COLOR] +
                                    img.pixel[i][j][GREEN_COLOR] +
                                    img.pixel[i][j][BLUE_COLOR];
                        media /= 3;
                        img.pixel[i][j][RED_COLOR] = media;
                        img.pixel[i][j][GREEN_COLOR] = media;
                        img.pixel[i][j][BLUE_COLOR] = media;
                }
        }

        return img;
}

int minimum_height (unsigned int height, unsigned int iterator, int T) {
        int minimum_height = (height - 1 > iterator + T/2) ? iterator + T/2 : height - 1;

        return minimum_height;
}

int minimum_width (unsigned int width, unsigned int iterator, int T) {
        int minimum = (width - 1 > iterator + T/2) ? iterator + T/2 : width - 1;

        return minimum_width;
}

void blur(unsigned int height, unsigned short int pixel[512][512][3], int T, unsigned int width) {
        for (unsigned int line = 0; line < height; ++line) {
                for (unsigned int column = 0; column < width; ++column) {
                        Pixel media = {0, 0, 0};


                        for(int pixel_line = (0 > line - T/2 ? 0 : line - T/2); pixel_line <= minimum_height(height,line,T); ++pixel_line) {
                                for(int pixel_column = (0 > column - T/2 ? 0 : column - T/2); pixel_column <= minimum_width(width,column,T); ++pixel_column) {
                                        media.red += pixel[pixel_line][pixel_column][RED_COLOR];
                                        media.green += pixel[pixel_line][pixel_column][GREEN_COLOR];
                                        media.blue += pixel[pixel_line][pixel_column][BLUE_COLOR];
                                }
                        }

                        // printf("%u", media.r)
                        media.red /= T * T;
                        media.green /= T * T;
                        media.blue /= T * T;

                        pixel[line][column][RED_COLOR] = media.red;
                        pixel[line][column][GREEN_COLOR] = media.green;
                        pixel[line][column][BLUE_COLOR] = media.blue;
                }
        }
}

Image rotacionar90direita(Image img) {
        Image rotacionada;

        rotacionada.width = img.height;
        rotacionada.height = img.width;

        for (unsigned int i = 0, y = 0; i < rotacionada.height; ++i, ++y) {
                for (int j = rotacionada.width - 1, x = 0; j >= 0; --j, ++x) {
                        rotacionada.pixel[i][j][RED_COLOR] = img.pixel[x][y][RED_COLOR];
                        rotacionada.pixel[i][j][GREEN_COLOR] = img.pixel[x][y][GREEN_COLOR];
                        rotacionada.pixel[i][j][BLUE_COLOR] = img.pixel[x][y][BLUE_COLOR];
                }
        }

        return rotacionada;
}

void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int w, unsigned int h) {
        for (unsigned int i = 0; i < h; ++i) {
                for (unsigned int j = 0; j < w; ++j) {
                        pixel[i][j][RED_COLOR] = 255 - pixel[i][j][RED_COLOR];
                        pixel[i][j][GREEN_COLOR] = 255 - pixel[i][j][GREEN_COLOR];
                        pixel[i][j][BLUE_COLOR] = 255 - pixel[i][j][BLUE_COLOR];
                }
        }
}



Image cortar_imagem(Image img, int x, int y, int width, int height) {
        Image cortada;

        cortada.width = width;
        cortada.height = height;

        for(int i = 0; i < height; ++i) {
                for(int j = 0; j < width; ++j) {
                        cortada.pixel[i][j][RED_COLOR] = img.pixel[i + y][j + x][RED_COLOR];
                        cortada.pixel[i][j][GREEN_COLOR] = img.pixel[i + y][j + x][GREEN_COLOR];
                        cortada.pixel[i][j][BLUE_COLOR] = img.pixel[i + y][j + x][BLUE_COLOR];
                }
        }

        return cortada;
}

void sepia_filter(unsigned short int pixel[512][512][3], unsigned int image_width, unsigned int image_height) {
        for (unsigned int line = 0; line < image_height; ++line) {
                for (unsigned int column = 0; column < image_width; ++column) {
                        Pixel pixel_color;

                        pixel_color.red = pixel[line][column][RED_COLOR];
                        pixel_color.green = pixel[line][column][GREEN_COLOR];
                        pixel_color.blue = pixel[line][column][BLUE_COLOR];

                        int p =  pixel_color.red * .393 + pixel_color.green * .769 + pixel_color.blue * .189;
                        int menor_r = (255 >  p) ? p : 255;
                        pixel[line][column][RED_COLOR] = menor_r;

                        p =  pixel_color.red * .349 + pixel_color.green * .686 + pixel_color.blue * .168;
                        menor_r = (255 >  p) ? p : 255;
                        pixel[line][column][GREEN_COLOR] = menor_r;

                        p =  pixel_color.red * .272 + pixel_color.green * .534 + pixel_color.blue * .131;
                        menor_r = (255 >  p) ? p : 255;
                        pixel[line][column][BLUE_COLOR] = menor_r;
                }
        }

}

void mirror_effect(int horizontal, unsigned short int pixel[512][512][3], unsigned int image_width, unsigned int image_height) {
        int width = image_width, height = image_height;

        if (horizontal == 1) {
                width /= 2;
        } else {
                height /= 2;
        }

        for (int line = 0; line < height; ++line) {
                for (int column = 0; column < width; ++column) {
                        int pixel_line = line, pixel_column = column;

                        if (horizontal == 1) {
                                pixel_column = image_width - 1 - column;
                        } else {
                                pixel_line = image_height - 1 - line;
                        }

                        Pixel aux1;
                        aux1.red = pixel[line][column][RED_COLOR];
                        aux1.green = pixel[line][column][GREEN_COLOR];
                        aux1.blue = pixel[line][column][BLUE_COLOR];

                        pixel[line][column][RED_COLOR] = pixel[pixel_line][pixel_column][RED_COLOR];
                        pixel[line][column][GREEN_COLOR] = pixel[pixel_line][pixel_column][GREEN_COLOR];
                        pixel[line][column][BLUE_COLOR] = pixel[pixel_line][pixel_column][BLUE_COLOR];

                        pixel[pixel_line][pixel_column][RED_COLOR] = aux1.red;
                        pixel[pixel_line][pixel_column][GREEN_COLOR] = aux1.green;
                        pixel[pixel_line][pixel_column][BLUE_COLOR] = aux1.blue;
                }
        }
}

void image_rotation (int quantas_vezes, Image img){
        quantas_vezes %= 4;
        for (int j = 0; j < quantas_vezes; ++j) {
                img = rotacionar90direita(img);
        }
}
