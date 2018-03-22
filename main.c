#include <stdio.h>
#include "photofilters.h"

int main() {
        Image image;

        // read type of image
        char p3[4];
        scanf("%s", p3);
        // read width height and color of image
        int max_color;
        scanf("%u %u %d", &image.width, &image.height, &max_color);

        // read all pixels of image
        read_pixels_of_image(image.pixel,image.width, image.height);

        int option_numbers;
        scanf("%d", &option_numbers);

        for(int i = 0; i < option_numbers; ++i) {
                int opcao;
                scanf("%d", &opcao);

                switch(opcao) {
                case 1: { // Escala de Cinza
                        image = escala_de_cinza(image);
                        break;
                }
                case 2: { // Filtro Sepia
                        sepia_filter(image.pixel, image.height, image.width);

                        break;
                }
                case 3: { // Blur
                        int size = 0;
                        scanf("%d", &size);
                        blur(image.height, image.pixel, size, image.width);
                        break;
                }
                case 4: { // Rotacao
                        int quantas_vezes = 0;
                        scanf("%d", &quantas_vezes);
                        image_rotation (quantas_vezes, image);
                        break;
                }
                case 5: { // Espelhamento
                        int horizontal = 0;
                        scanf("%d", &horizontal);
                        mirror_effect(horizontal,image.pixel,image.width, image.height);
                        break;
                }
                case 6: { // Inversao de Cores
                        inverter_cores(image.pixel, image.width, image.height);
                        break;
                }
                case 7: { // Cortar Imagem
                        int pixel_width, pixel_height;
                        scanf("%d %d", &pixel_width, &pixel_height);
                        int width, height;
                        scanf("%d %d", &width, &height);

                        image = cortar_imagem(image, pixel_width, pixel_height, width, height);
                        break;
                }
                }

        }

        // print type of image
        printf("P3\n");
        // print width height and color of image
        printf("%u %u\n255\n", image.width, image.height);

        print_pixels_of_image(image.pixel, image.width, image.height);

        return 0;
}
