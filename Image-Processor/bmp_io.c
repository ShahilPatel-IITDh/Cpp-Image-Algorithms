#include "bmp_io.h"
#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
    unsigned short type;
    unsigned int size;
    unsigned short reserved1, reserved2;
    unsigned int offset;
} BMPHeader;

typedef struct {
    unsigned int size;
    int width, height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerM, yPixelsPerM;
    unsigned int clrUsed, clrImportant;
} DIBHeader;
#pragma pack(pop)

unsigned char **alloc_image(int width, int height) {
    unsigned char **img = malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++) {
        img[i] = malloc(width);
    }
    return img;
}

void free_image(unsigned char **image, int height) {
    for (int i = 0; i < height; i++) {
        free(image[i]);
    }
    free(image);
}

unsigned char **load_bmp(const char *filename, int *width, int *height) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        printf("Failed to open file.\n");
        return NULL;
    }

    BMPHeader bmp;
    DIBHeader dib;
    fread(&bmp, sizeof(BMPHeader), 1, fp);
    fread(&dib, sizeof(DIBHeader), 1, fp);

    if (bmp.type != 0x4D42) {
        printf("Not a valid BMP file.\n");
        fclose(fp);
        return NULL;
    }

    *width = dib.width;
    *height = dib.height;

    unsigned char **image = alloc_image(*width, *height);

    fseek(fp, bmp.offset, SEEK_SET);
    int pad = ((*width * (dib.bitCount / 8)) % 4) ? (4 - ((*width * (dib.bitCount / 8)) % 4)) : 0;

    if (dib.bitCount == 8) {
        fseek(fp, 1024, SEEK_SET);
        for (int i = *height - 1; i >= 0; i--) {
            fread(image[i], 1, *width, fp);
            fseek(fp, pad, SEEK_CUR);
        }
    } else if (dib.bitCount == 24) {
        for (int i = *height - 1; i >= 0; i--) {
            for (int j = 0; j < *width; j++) {
                unsigned char b = fgetc(fp);
                unsigned char g = fgetc(fp);
                unsigned char r = fgetc(fp);
                unsigned char gray = (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
                image[i][j] = gray;
            }
            fseek(fp, pad, SEEK_CUR);
        }
    } else {
        printf("Unsupported BMP bit depth: %d-bit\n", dib.bitCount);
        fclose(fp);
        free_image(image, *height);
        return NULL;
    }

    fclose(fp);
    return image;
}

void save_bmp(const char *filename, unsigned char image[32][32], int width, int height) {
    FILE *fp = fopen(filename, "wb");
    int rowSize = (width + 3) & (~3);
    int imgSize = rowSize * height;

    BMPHeader bmp = {0x4D42, 54 + imgSize, 0, 0, 54};
    DIBHeader dib = {40, width, height, 1, 8, 0, imgSize, 2835, 2835, 256, 0};

    fwrite(&bmp, sizeof(BMPHeader), 1, fp);
    fwrite(&dib, sizeof(DIBHeader), 1, fp);

    for (int i = 0; i < 256; i++) {
        fputc(i, fp); fputc(i, fp); fputc(i, fp); fputc(0, fp);
    }

    unsigned char padding[3] = {0};
    for (int i = height - 1; i >= 0; i--) {
        fwrite(image[i], 1, width, fp);
        fwrite(padding, 1, rowSize - width, fp);
    }
    fclose(fp);
}