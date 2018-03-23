#ifndef PHOTOFILTERS_H_
#define PHOTOFILTERS_H_
#include "inputout.h"
#include "calculations.h"

void image_rotation (int how_many_times, Image image);
void mirror_effect(int horizontal,unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                   unsigned int image_width,
                   unsigned int image_height);
void sepia_filter(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                  unsigned int image_width,
                  unsigned int image_height);
Image grey_scale(Image image);
void blur(unsigned int height, unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS], int size, unsigned int width);
Image rotate_nineth_degrees_to_the_right(Image image);
void color_invert(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                    unsigned int width, unsigned int height);
Image cut_image(Image image, int x, int y, int width, int height);

#endif
