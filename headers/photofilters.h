/**
* This file is part of Photopobre project.
* @file photofilters.h
* @brief This file include all headers used for the filters of project.
*
*/

#ifndef PHOTOFILTERS_H_
#define PHOTOFILTERS_H_
#include "inputout.h"
#include "calculations.h"
#include <stdio.h>

void image_rotation (int how_many_times, Image image);
Image mirror_effect(Image image);
Image sepia_filter(Image image);
Image grayscale(Image image);
Image blur(Image image);
Image rotate_nineth_degrees_to_the_right(Image image);
Image color_invert(Image image);
Image cut_image(Image image);

#endif
