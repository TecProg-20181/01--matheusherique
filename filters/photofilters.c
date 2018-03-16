#include "photofilters.h"  /* Include the header (not strictly necessary here) */

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int pixel_igual(Pixel p1, Pixel p2) {
    if (p1.red == p2.red &&
        p1.green == p2.green &&
        p1.blue == p2.blue)
        return 1;
    return 0;
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

void read_pixels_of_image(unsigned short int pixel[512][512][3],
                          unsigned int width,
                          unsigned int height) {

    for (unsigned int i = 0; i < height; ++i) {
      for (unsigned int j = 0; j < width; ++j) {
        scanf("%hu %hu %hu", &pixel[i][j][RED_COLOR],
                             &pixel[i][j][GREEN_COLOR],
                             &pixel[i][j][BLUE_COLOR]);
      }
    }

}

// print pixels of image
void print_pixels_of_image(unsigned short int pixel[512][512][3],
                           unsigned int w,
                           unsigned int h) {

  for (unsigned int i = 0; i < h; ++i) {
      for (unsigned int j = 0; j < w; ++j) {
          printf("%hu %hu %hu ", pixel[i][j][RED_COLOR],
                                 pixel[i][j][GREEN_COLOR],
                                 pixel[i][j][BLUE_COLOR]);

      }
      printf("\n");
  }
}
