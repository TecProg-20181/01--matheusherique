#ifndef PHOTOFILTERS_H_
#define PHOTOFILTERS_H_
#include "inputout.h"
#include "calculations.h"

void image_rotation (int quantas_vezes, Image img);
void mirror_effect(int horizontal,unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                   unsigned int image_width,
                   unsigned int image_height);
void sepia_filter(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                  unsigned int image_width,
                  unsigned int image_height);
Image escala_de_cinza(Image img);
void blur(unsigned int height, unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS], int size, unsigned int width);
Image rotacionar90direita(Image img);
void inverter_cores(unsigned short int pixel[MAX_WIDTH][MAX_HEIGHT][MAX_RED_GREEN_BLUE_COLORS],
                    unsigned int width, unsigned int height);
Image cortar_imagem(Image img, int x, int y, int width, int height);

#endif
