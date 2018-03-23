/**
* This file is part of Photopobre project.
* @file photofilters.c
* @brief This file include all functions used for the image filters of project
*
*/

#include "photofilters.h"
#include "calculations.h"

Image grayscale(Image image) {

        for (unsigned int row = 0; row < image.height; ++row) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        int media = image.pixel[row][column][RED_COLOR] +
                                    image.pixel[row][column][GREEN_COLOR] +
                                    image.pixel[row][column][BLUE_COLOR];
                        media /= 3;
                        image.pixel[row][column][RED_COLOR] = media;
                        image.pixel[row][column][GREEN_COLOR] = media;
                        image.pixel[row][column][BLUE_COLOR] = media;
                }
        }

        return image;
}

Image blur(Image image) {
        int size = 0;
        scanf("%d", &size);
        for (unsigned int line = 0; line < image.height; ++line) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        Pixel media = {0, 0, 0};


                        for(int pixel_line = maximum(0, line - size/2); pixel_line <= minimum(image.height - 1, line + size/2); ++pixel_line) {
                                for(int pixel_column = maximum(0, column - size/2); pixel_column <= minimum(image.width - 1, column + size/2); ++pixel_column) {
                                        media.red += image.pixel[pixel_line][pixel_column][RED_COLOR];
                                        media.green += image.pixel[pixel_line][pixel_column][GREEN_COLOR];
                                        media.blue += image.pixel[pixel_line][pixel_column][BLUE_COLOR];
                                }
                        }

                        media.red /= size * size;
                        media.green /= size * size;
                        media.blue /= size * size;

                        image.pixel[line][column][RED_COLOR] = media.red;
                        image.pixel[line][column][GREEN_COLOR] = media.green;
                        image.pixel[line][column][BLUE_COLOR] = media.blue;
                }
        }

        return image;
}

Image rotate_nineth_degrees_to_the_right(Image image) {
        Image rotate;

        rotate.width = image.height;
        rotate.height = image.width;

        for (unsigned int row = 0, y = 0; row < rotate.height; ++row, ++y) {
                for (int column = rotate.width - 1, x = 0; column >= 0; --column, ++x) {
                        rotate.pixel[row][column][RED_COLOR] = image.pixel[x][y][RED_COLOR];
                        rotate.pixel[row][column][GREEN_COLOR] = image.pixel[x][y][GREEN_COLOR];
                        rotate.pixel[row][column][BLUE_COLOR] = image.pixel[x][y][BLUE_COLOR];
                }
        }

        return rotate;
}

Image color_invert(Image image) {
        for (unsigned int line = 0; line < image.height; ++line) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        image.pixel[line][column][RED_COLOR] = 255 - image.pixel[line][column][RED_COLOR];
                        image.pixel[line][column][GREEN_COLOR] = 255 - image.pixel[line][column][GREEN_COLOR];
                        image.pixel[line][column][BLUE_COLOR] = 255 - image.pixel[line][column][BLUE_COLOR];
                }
        }
        return image;
}



Image cut_image(Image image) {

        int pixel_width, pixel_height;
        scanf("%d %d", &pixel_width, &pixel_height);
        int width, height;
        scanf("%d %d", &width, &height);

        Image cut;

        cut.width = width;
        cut.height = height;

        for(int line = 0; line < height; ++line) {
                for(int column = 0; column < width; ++column) {
                        cut.pixel[line][column][RED_COLOR] = image.pixel[line + pixel_height][column + pixel_width][RED_COLOR];
                        cut.pixel[line][column][GREEN_COLOR] = image.pixel[line + pixel_height][column + pixel_width][GREEN_COLOR];
                        cut.pixel[line][column][BLUE_COLOR] = image.pixel[line + pixel_height][column + pixel_width][BLUE_COLOR];
                }
        }

        return cut;
}

Image sepia_filter(Image image) {
        for (unsigned int line = 0; line < image.height; ++line) {
                for (unsigned int column = 0; column < image.width; ++column) {
                        Pixel pixel_color;

                        pixel_color.red = image.pixel[line][column][RED_COLOR];
                        pixel_color.green = image.pixel[line][column][GREEN_COLOR];
                        pixel_color.blue = image.pixel[line][column][BLUE_COLOR];

                        int sepia_filter =  pixel_color.red * .393 + pixel_color.green * .769 + pixel_color.blue * .189;

                        image.pixel[line][column][RED_COLOR] = minimum(sepia_filter,255);

                        sepia_filter =  pixel_color.red * .349 + pixel_color.green * .686 + pixel_color.blue * .168;
                        image.pixel[line][column][GREEN_COLOR] = minimum(sepia_filter,255);

                        sepia_filter =  pixel_color.red * .272 + pixel_color.green * .534 + pixel_color.blue * .131;
                        image.pixel[line][column][BLUE_COLOR] = minimum(sepia_filter,255);
                }
        }
        return image;
}

Image mirror_effect(Image image) {
        int horizontal = 0;
        scanf("%d", &horizontal);

        if (horizontal == 1) {
                image.width /= 2;
        } else {
                image.height /= 2;
        }

        for (int line = 0; line < image.height; ++line) {
                for (int column = 0; column < image.width; ++column) {
                        int pixel_line = line, pixel_column = column;

                        if (horizontal == 1) {
                                pixel_column = image.width - 1 - column;
                        } else {
                                pixel_line = image.height - 1 - line;
                        }

                        Pixel auxiliary_pixel;
                        auxiliary_pixel.red = image.pixel[line][column][RED_COLOR];
                        auxiliary_pixel.green = image.pixel[line][column][GREEN_COLOR];
                        auxiliary_pixel.blue = image.pixel[line][column][BLUE_COLOR];

                        image.pixel[line][column][RED_COLOR] = image.pixel[pixel_line][pixel_column][RED_COLOR];
                        image.pixel[line][column][GREEN_COLOR] = image.pixel[pixel_line][pixel_column][GREEN_COLOR];
                        image.pixel[line][column][BLUE_COLOR] = image.pixel[pixel_line][pixel_column][BLUE_COLOR];

                        image.pixel[pixel_line][pixel_column][RED_COLOR] = auxiliary_pixel.red;
                        image.pixel[pixel_line][pixel_column][GREEN_COLOR] = auxiliary_pixel.green;
                        image.pixel[pixel_line][pixel_column][BLUE_COLOR] = auxiliary_pixel.blue;
                }
        }
        return image;
}

void image_rotation (int how_many_times, Image img){
        how_many_times %= 4;
        for (int j = 0; j < how_many_times; ++j) {
                img = rotate_nineth_degrees_to_the_right(img);
        }
}
