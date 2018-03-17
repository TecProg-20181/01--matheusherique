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
                        sepia_filter(img.pixel, img.height, img.width);

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
                        image_rotation (quantas_ve #00FDFFzes, img);
                        break;
                }
                case 5: { // Espelhamento
                        int horizontal = 0;
                        scanf("%d", &horizontal);
                        mirror_effect(horizontal,img.pixel,img.width, img.height);
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
