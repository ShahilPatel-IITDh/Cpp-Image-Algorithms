#include "resize.h"
#include <string.h>

void resize_to_32x32(unsigned char **input, int w, int h, unsigned char output[32][32]) {
    memset(output, 0, 32 * 32);

    int start_x = (w > 32) ? (w - 32) / 2 : 0;
    int start_y = (h > 32) ? (h - 32) / 2 : 0;

    int copy_w = (w < 32) ? w : 32;
    int copy_h = (h < 32) ? h : 32;

    for (int i = 0; i < copy_h; i++) {
        for (int j = 0; j < copy_w; j++) {
            output[i][j] = input[start_y + i][start_x + j];
        }
    }
}
