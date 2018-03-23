/**
* This file is part of Photopobre project.
* @file main.c
* @brief This file the main of project. Include all functions used in others
* header.
*/

#include <stdio.h>
#include "photofilters.h"

int main() {
        Image image;
        image = read_pixels_of_image(image);

        // Read one number to choose a image filter.
        int option_numbers;
        scanf("%d", &option_numbers);


        for(int iterator = 0; iterator < option_numbers; ++iterator) {
                // Read one number to choose a image filter.
                int option;
                scanf("%d", &option);

                switch(option) {
                        // Grayscale filter.
                        case 1: {
                                image = grayscale(image);
                                break;
                        }
                        // Sepia filter.
                        case 2: {
                                image = sepia_filter(image);

                                break;
                        }
                        // Blur filter.
                        case 3: {
                                image = blur(image);
                                break;
                        }
                        // Rotate image.
                        case 4: {
                                int how_many_times = 0;
                                scanf("%d", &how_many_times);
                                image_rotation (how_many_times, image);
                                break;
                        }
                        // Mirror effect filter.
                        case 5: {
                                image = mirror_effect(image);
                                break;
                        }
                        // Color invert filter.
                        case 6: {
                                image = color_invert(image);
                                break;
                        }
                        // Cut image.
                        case 7: {
                                image = cut_image(image);
                                break;
                        }
                }

        }

        print_pixels_of_image(image);

        return 0;
}
