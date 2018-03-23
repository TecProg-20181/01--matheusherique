#include "calculations.h"

int minimum(int first_input, int second_input) {
        int which_input = 0;

        if (first_input < second_input) {
                which_input = first_input;
        } else {
                which_input = second_input;
        }

        return which_input;
}


int minimum_height (unsigned int height, unsigned int iterator, int size) {
        int minimum_height = 0;

        if (height - 1 > iterator + size/2) {
                minimum_height = iterator + size/2;
        } else {
                minimum_height = height - 1;
        }

        return minimum_height;
}

int minimum_width (unsigned int width, unsigned int iterator, int size) {
        int minimum_width = 0;

        if (width - 1 > iterator + size/2) {
                minimum_width = iterator + size/2;
        } else {
                minimum_width = width - 1;
        }

        return minimum_width;
}
