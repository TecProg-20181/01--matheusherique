#include <stdio.h>
#include "photofilters.h"

int main() {
    Image img;

    // read type of image
    char p3[4];
    scanf("%s", p3);

    // read width height and color of image
    int max_color;
    scanf("%u %u %d", &img.width, &img.height, &max_color);

    // read all pixels of image
    read_pixels_of_image(img.pixel,img.width, img.height);

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

    print_pixels_of_image(img.pixel, img.width, img.height);

    return 0;
}
