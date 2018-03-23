#include "photofilters.h"  /* Include the header (not strictly necessary here) */

Image grey_scale(Image image) {

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

void blur(unsigned int height, unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS], int size, unsigned int width) {
        for (unsigned int line = 0; line < height; ++line) {
                for (unsigned int column = 0; column < width; ++column) {
                        Pixel media = {0, 0, 0};


                        for(int pixel_line = line - size/2; pixel_line <= minimum_height(height,line,size); ++pixel_line) {
                                for(int pixel_column = column - size/2; pixel_column <= minimum_width(width,column,size); ++pixel_column) {
                                        media.red += pixel[pixel_line][pixel_column][RED_COLOR];
                                        media.green += pixel[pixel_line][pixel_column][GREEN_COLOR];
                                        media.blue += pixel[pixel_line][pixel_column][BLUE_COLOR];
                                }
                        }

                        media.red /= size * size;
                        media.green /= size * size;
                        media.blue /= size * size;

                        pixel[line][column][RED_COLOR] = media.red;
                        pixel[line][column][GREEN_COLOR] = media.green;
                        pixel[line][column][BLUE_COLOR] = media.blue;
                }
        }
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

void color_invert(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                    unsigned int width, unsigned int height) {
        for (unsigned int line = 0; line < height; ++line) {
                for (unsigned int column = 0; column < width; ++column) {
                        pixel[line][column][RED_COLOR] = 255 - pixel[line][column][RED_COLOR];
                        pixel[line][column][GREEN_COLOR] = 255 - pixel[line][column][GREEN_COLOR];
                        pixel[line][column][BLUE_COLOR] = 255 - pixel[line][column][BLUE_COLOR];
                }
        }
}



Image cut_image(Image img, int pixel_width, int pixel_height, int width, int height) {
        Image cut;

        cut.width = width;
        cut.height = height;

        for(int line = 0; line < height; ++line) {
                for(int column = 0; column < width; ++column) {
                        cut.pixel[line][column][RED_COLOR] = img.pixel[line + pixel_height][column + pixel_width][RED_COLOR];
                        cut.pixel[line][column][GREEN_COLOR] = img.pixel[line + pixel_height][column + pixel_width][GREEN_COLOR];
                        cut.pixel[line][column][BLUE_COLOR] = img.pixel[line + pixel_height][column + pixel_width][BLUE_COLOR];
                }
        }

        return cut;
}

void sepia_filter(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS], unsigned int image_width, unsigned int image_height) {
        for (unsigned int line = 0; line < image_height; ++line) {
                for (unsigned int column = 0; column < image_width; ++column) {
                        Pixel pixel_color;

                        pixel_color.red = pixel[line][column][RED_COLOR];
                        pixel_color.green = pixel[line][column][GREEN_COLOR];
                        pixel_color.blue = pixel[line][column][BLUE_COLOR];

                        int sepia_filter =  pixel_color.red * .393 + pixel_color.green * .769 + pixel_color.blue * .189;

                        pixel[line][column][RED_COLOR] = minimum(sepia_filter,255);

                        sepia_filter =  pixel_color.red * .349 + pixel_color.green * .686 + pixel_color.blue * .168;
                        pixel[line][column][GREEN_COLOR] = minimum(sepia_filter,255);

                        sepia_filter =  pixel_color.red * .272 + pixel_color.green * .534 + pixel_color.blue * .131;
                        pixel[line][column][BLUE_COLOR] = minimum(sepia_filter,255);
                }
        }

}

void mirror_effect(int horizontal, unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS], unsigned int image_width, unsigned int image_height) {
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

                        Pixel auxiliary_pixel;
                        auxiliary_pixel.red = pixel[line][column][RED_COLOR];
                        auxiliary_pixel.green = pixel[line][column][GREEN_COLOR];
                        auxiliary_pixel.blue = pixel[line][column][BLUE_COLOR];

                        pixel[line][column][RED_COLOR] = pixel[pixel_line][pixel_column][RED_COLOR];
                        pixel[line][column][GREEN_COLOR] = pixel[pixel_line][pixel_column][GREEN_COLOR];
                        pixel[line][column][BLUE_COLOR] = pixel[pixel_line][pixel_column][BLUE_COLOR];

                        pixel[pixel_line][pixel_column][RED_COLOR] = auxiliary_pixel.red;
                        pixel[pixel_line][pixel_column][GREEN_COLOR] = auxiliary_pixel.green;
                        pixel[pixel_line][pixel_column][BLUE_COLOR] = auxiliary_pixel.blue;
                }
        }
}

void image_rotation (int how_many_times, Image img){
        how_many_times %= 4;
        for (int j = 0; j < how_many_times; ++j) {
                img = rotate_nineth_degrees_to_the_right(img);
        }
}
