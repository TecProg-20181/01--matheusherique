#include <stdio.h>
#define MAX_HEIGHT 512
#define MAX_WIDTH 512
#define MAX_RED_GREEN_BLUE_COLORS 3
#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

typedef struct _pixel {
    unsigned short int red;
    unsigned short int green;
    unsigned short int blue;
} Pixel;

typedef struct _image {
    // [width][height][rgb]
    // 0 -> r
    // 1 -> g
    // 2 -> b
    unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS];
    unsigned int width;
    unsigned int height;
} Image;


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

void blur(unsigned int h, unsigned short int pixel[512][512][3], int T, unsigned int w) {
    for (unsigned int i = 0; i < h; ++i) {
        for (unsigned int j = 0; j < w; ++j) {
            Pixel media = {0, 0, 0};

            int menor_h = (h - 1 > i + T/2) ? i + T/2 : h - 1;
            int min_w = (w - 1 > j + T/2) ? j + T/2 : w - 1;
            for(int x = (0 > i - T/2 ? 0 : i - T/2); x <= menor_h; ++x) {
                for(int y = (0 > j - T/2 ? 0 : j - T/2); y <= min_w; ++y) {
                    media.red += pixel[x][y][RED_COLOR];
                    media.green += pixel[x][y][GREEN_COLOR];
                    media.blue += pixel[x][y][BLUE_COLOR];
                }
            }

            // printf("%u", media.r)
            media.red /= T * T;
            media.green /= T * T;
            media.blue /= T * T;

            pixel[i][j][0] = media.red;
            pixel[i][j][1] = media.green;
            pixel[i][j][2] = media.blue;
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


int main() {
    Image img;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.width, &img.height, &max_color);

    // read all pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            scanf("%hu %hu %hu", &img.pixel[i][j][RED_COLOR],
                                 &img.pixel[i][j][GREEN_COLOR],
                                 &img.pixel[i][j][BLUE_COLOR]);

        }
    }

    int n_opcoes;
    scanf("%d", &n_opcoes);

    for(int i = 0; i < n_opcoes; ++i) {
        int opcao;
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: { // Escala de Cinza
                img = escala_de_cinza(img);
                break;
            }
            case 2: { // Filtro Sepia
                for (unsigned int x = 0; x < img.height; ++x) {
                    for (unsigned int j = 0; j < img.width; ++j) {
                        Pixel pixel;
                        pixel.red = img.pixel[x][j][RED_COLOR];
                        pixel.green = img.pixel[x][j][GREEN_COLOR];
                        pixel.blue = img.pixel[x][j][BLUE_COLOR];

                        int p =  pixel.red * .393 + pixel.green * .769 + pixel.blue * .189;
                        int menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][RED_COLOR] = menor_r;

                        p =  pixel.red * .349 + pixel.green * .686 + pixel.blue * .168;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][GREEN_COLOR] = menor_r;

                        p =  pixel.red * .272 + pixel.green * .534 + pixel.blue * .131;
                        menor_r = (255 >  p) ? p : 255;
                        img.pixel[x][j][BLUE_COLOR] = menor_r;
                    }
                }

                break;
            }
            case 3: { // Blur
                int tamanho = 0;
                scanf("%d", &tamanho);
                blur(img.height, img.pixel, tamanho, img.width);
                break;
            }
            case 4: { // Rotacao
                int quantas_vezes = 0;
                scanf("%d", &quantas_vezes);
                quantas_vezes %= 4;
                for (int j = 0; j < quantas_vezes; ++j) {
                    img = rotacionar90direita(img);
                }
                break;
            }
            case 5: { // Espelhamento
                int horizontal = 0;
                scanf("%d", &horizontal);

                int w = img.width, h = img.height;

                if (horizontal == 1) w /= 2;
                else h /= 2;

                for (int i2 = 0; i2 < h; ++i2) {
                    for (int j = 0; j < w; ++j) {
                        int x = i2, y = j;

                        if (horizontal == 1) y = img.width - 1 - j;
                        else x = img.height - 1 - i2;

                        Pixel aux1;
                        aux1.red = img.pixel[i2][j][RED_COLOR];
                        aux1.green = img.pixel[i2][j][GREEN_COLOR];
                        aux1.blue = img.pixel[i2][j][BLUE_COLOR];

                        img.pixel[i2][j][RED_COLOR] = img.pixel[x][y][RED_COLOR];
                        img.pixel[i2][j][GREEN_COLOR] = img.pixel[x][y][GREEN_COLOR];
                        img.pixel[i2][j][BLUE_COLOR] = img.pixel[x][y][BLUE_COLOR];

                        img.pixel[x][y][RED_COLOR] = aux1.red;
                        img.pixel[x][y][GREEN_COLOR] = aux1.green;
                        img.pixel[x][y][BLUE_COLOR] = aux1.blue;
                    }
                }
                break;
            }
            case 6: { // Inversao de Cores
                inverter_cores(img.pixel, img.width, img.height);
                break;
            }
            case 7: { // Cortar Imagem
                int x, y;
                scanf("%d %d", &x, &y);
                int w, h;
                scanf("%d %d", &w, &h);

                img = cortar_imagem(img, x, y, w, h);
                break;
            }
        }

    }

    // print type of image
    printf("P3\n");
    // print width height and color of image
    printf("%u %u\n255\n", img.width, img.height);

    // print pixels of image
    for (unsigned int i = 0; i < img.height; ++i) {
        for (unsigned int j = 0; j < img.width; ++j) {
            printf("%hu %hu %hu ", img.pixel[i][j][RED_COLOR],
                                   img.pixel[i][j][GREEN_COLOR],
                                   img.pixel[i][j][BLUE_COLOR]);

        }
        printf("\n");
    }
    return 0;
}
