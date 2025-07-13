#include "enhance.h"

void enhance_image(unsigned char img[32][32]) {
    int min = 255, max = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++) {
            if (img[i][j] < min) min = img[i][j];
            if (img[i][j] > max) max = img[i][j];
        }

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            int val = img[i][j];
            if (max > min)
                val = (val - min) * 255 / (max - min);
            else
                val = 0;
            img[i][j] = (unsigned char)val;
        }
    }
}