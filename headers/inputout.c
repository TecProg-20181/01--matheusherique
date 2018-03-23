/**
 * This file is part of Photopobre project.
 * @file inputout.c
 * @brief This file include all functions used for the inputs and output of
 * project.
 *
 */

#include <stdio.h>
#include "inputout.h"
#include "photofilters.h"

// Print each pixel of image.
void print_pixels_of_image(Image image) {

        // Print type of image.
        printf("P3\n");
        // Print width, height and color of image.
        printf("%u %u\n255\n", image.width, image.height);
        // Print each pixel of image.

        for (unsigned int line = 0; line < image.height; ++line) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        printf("%hu %hu %hu ", image.pixel[line][column][RED_COLOR],
                               image.pixel[line][column][GREEN_COLOR],
                               image.pixel[line][column][BLUE_COLOR]);

                }
                printf("\n");
        }
}

// Read each pixel of image.
Image read_pixels_of_image(Image image) {

        // Read type of image.
        char image_type[4];
        scanf("%s", image_type);

        // Read width, height and color of image.
        int max_color;
        scanf("%u %u %d", &image.width, &image.height, &max_color);

        // read all pixels of image
        for (unsigned int row = 0; row < image.height; ++row) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        scanf("%hu %hu %hu", &image.pixel[row][column][RED_COLOR],
                              &image.pixel[row][column][GREEN_COLOR],
                              &image.pixel[row][column][BLUE_COLOR]);
                }
        }
        return image;
}
