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


int minimum_height (unsigned int height, unsigned int iterator, int T) {
        int minimum_height = (height - 1 > iterator + T/2) ? iterator + T/2 : height - 1;

        return minimum_height;
}

int minimum_width (unsigned int width, unsigned int iterator, int T) {
        int minimum_width = (width - 1 > iterator + T/2) ? iterator + T/2 : width - 1;

        return minimum_width;
}
