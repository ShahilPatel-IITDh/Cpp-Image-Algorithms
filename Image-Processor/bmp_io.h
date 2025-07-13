#ifndef BMP_IO_H
#define BMP_IO_H

unsigned char **load_bmp(const char *filename, int *width, int *height);
void save_bmp(const char *filename, unsigned char image[32][32], int width, int height);
void free_image(unsigned char **image, int height);

#endif