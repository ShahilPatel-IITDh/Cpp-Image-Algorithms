#include "otsu.h"

void otsu_binarize(unsigned char input[32][32], unsigned char output[32][32]) {
    int hist[256] = {0};
    for (int i = 0; i < 32; i++)
        for (int j = 0; j < 32; j++)
            hist[input[i][j]]++;

    int total = 32 * 32;
    float sum = 0;
    for (int t = 0; t < 256; t++)
        sum += t * hist[t];

    float sumB = 0, wB = 0, wF = 0, maxVar = 0;
    int threshold = 0;

    for (int t = 0; t < 256; t++) {
        wB += hist[t];
        if (wB == 0) continue;
        wF = total - wB;
        if (wF == 0) break;

        sumB += t * hist[t];
        float mB = sumB / wB;
        float mF = (sum - sumB) / wF;

        float varBetween = wB * wF * (mB - mF) * (mB - mF);
        if (varBetween > maxVar) {
            maxVar = varBetween;
            threshold = t;
        }
    }

    // ✅ Invert the binary image: foreground = black, background = white
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (input[i][j] > threshold)
                output[i][j] = 0;     // Was 255 → Inverted to black
            else
                output[i][j] = 255;   // Was 0 → Inverted to white
        }
    }
}