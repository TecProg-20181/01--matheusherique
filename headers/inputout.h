#ifndef INPUTOUT_H_  /* Include guard */
#define INPUTOUT_H_
#include "photofilters.h"

void print_pixels_of_image(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                           unsigned int width,
                           unsigned int height);

void read_pixels_of_image(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                          unsigned int width,
                          unsigned int height);

#endif
