#ifndef PHOTOFILTERS_H_  /* Include guard */
#define PHOTOFILTERS_H_
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

int max(int a, int b);
int pixel_igual(Pixel p1, Pixel p2);
Image escala_de_cinza(Image img);
void blur(unsigned int h, unsigned short int pixel[512][512][3], int T, unsigned int w);
Image rotacionar90direita(Image img);
void inverter_cores(unsigned short int pixel[512][512][3],
                    unsigned int w, unsigned int h);
Image cortar_imagem(Image img, int x, int y, int width, int height);
void read_pixels_of_image(unsigned short int pixel[512][512][3],
                          unsigned int width,
                          unsigned int height);

void print_pixels_of_image(unsigned short int pixel[512][512][3],
                           unsigned int w,
                           unsigned int h);

#endif
