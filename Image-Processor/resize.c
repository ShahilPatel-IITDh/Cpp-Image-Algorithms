#include "resize.h"
#include <string.h>

void resize_to_32x32(unsigned char **input, int w, int h, unsigned char output[32][32]) {
    memset(output, 0, 32 * 32);

    int x_offset = 0, y_offset = 0;
    int crop_w = w, crop_h = h;

    if (w > 32) {
        x_offset = (w - 32) / 2;
        crop_w = 32;
    }
    if (h > 32) {
        y_offset = (h - 32) / 2;
        crop_h = 32;
    }

    for (int i = 0; i < 32; i++) {
        int src_y = y_offset + i * crop_h / 32;
        if (src_y >= h) continue;
        for (int j = 0; j < 32; j++) {
            int src_x = x_offset + j * crop_w / 32;
            if (src_x >= w) continue;
            output[i][j] = input[src_y][src_x];
        }
    }
}