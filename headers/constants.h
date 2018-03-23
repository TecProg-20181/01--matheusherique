/**
* This file is part of Photopobre project.
* @file constants.h
* @brief This file include all constants used in the project.
*
*/

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define MAX_HEIGHT 512
#define MAX_WIDTH 512
#define MAX_RED_GREEN_BLUE_COLORS 3
#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2

typedef struct _pixel {
        unsigned short int red;
        unsigned short int green;
        unsigned short int blue;
} Pixel;

typedef struct _image {
        // [width][height][rgb]
        // 0 -> r
        // 1 -> g
        // 2 -> b
        unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS];
        unsigned int width;
        unsigned int height;
} Image;

#endif
