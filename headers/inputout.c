#include <stdio.h>
#include "inputout.h"
#include "photofilters.h"

// print pixels of image
void print_pixels_of_image(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                           unsigned int width,
                           unsigned int height) {

        for (unsigned int line = 0; line < height; ++line) {
                for (unsigned int column = 0; column < width; ++column) {
                        printf("%hu %hu %hu ", pixel[line][column][RED_COLOR],
                               pixel[line][column][GREEN_COLOR],
                               pixel[line][column][BLUE_COLOR]);

                }
                printf("\n");
        }
}

void read_pixels_of_image(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                          unsigned int width,
                          unsigned int height) {

        for (unsigned int line = 0; line < height; ++line) {
                for (unsigned int column = 0; column < width; ++column) {
                        scanf("%hu %hu %hu", &pixel[line][column][RED_COLOR],
                              &pixel[line][column][GREEN_COLOR],
                              &pixel[line][column][BLUE_COLOR]);
                }
        }

}
