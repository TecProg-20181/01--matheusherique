#ifndef INPUTOUT_H_  /* Include guard */
#define INPUTOUT_H_

void print_pixels_of_image(unsigned short int pixel[512][512][3],
                           unsigned int w,
                           unsigned int h);

void read_pixels_of_image(unsigned short int pixel[512][512][3],
                          unsigned int width,
                          unsigned int height);

#endif
