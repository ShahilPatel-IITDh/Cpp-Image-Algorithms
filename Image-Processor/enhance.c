#include "enhance.h"
#include <math.h>

void enhance_image(unsigned char img[32][32]) {
    int min = 255, max = 0;
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++) {
            if (img[i][j] < min) min = img[i][j];
            if (img[i][j] > max) max = img[i][j];
        }

    // Stretch contrast fully 0-255
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++) {
            int val = img[i][j];
            val = (max > min) ? (val - min) * 255 / (max - min) : 0;
            // Apply slight gamma correction for better clarity
            float norm = val / 255.0f;
            norm = pow(norm, 0.8);  // Slight gamma boost
            img[i][j] = (unsigned char)(norm * 255);
        }
}
