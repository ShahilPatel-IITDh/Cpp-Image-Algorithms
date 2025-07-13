#include "enhance.h"

void enhance_image(unsigned char img[32][32]) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int val = img[i][j];
            val = val * 1.2 + 15; // brightness + contrast
            if (val > 255) val = 255;
            if (val < 0) val = 0;
            img[i][j] = val;
        }
    }
}