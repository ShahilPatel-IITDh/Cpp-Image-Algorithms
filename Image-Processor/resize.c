#include "resize.h"
#include <string.h>

void resize_to_32x32(unsigned char **input, int w, int h, unsigned char output[32][32]) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int y = i * h / 32;
            int x = j * w / 32;
            if (y < h && x < w)
                output[i][j] = input[y][x];
            else
                output[i][j] = 0;
        }
    }
}