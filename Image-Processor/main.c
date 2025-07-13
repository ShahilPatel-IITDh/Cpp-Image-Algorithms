#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "bmp_io.h"
#include "resize.h"
#include "enhance.h"
#include "otsu.h"
#include "save_h_file.h"

void make_dir_if_not_exists(const char *dirname) {
#ifdef _WIN32
    _mkdir(dirname);
#else
    mkdir(dirname, 0777);
#endif
}

int main() {
    const char *input_path = "inputImages/six.bmp";
    const char *output_bmp_path = "outputImage/output.bmp";
    const char *output_header_path = "imageHeaderFile/output_image.h";

    make_dir_if_not_exists("outputImage");
    make_dir_if_not_exists("imageHeaderFile");

    int width, height;
    unsigned char **image = load_bmp(input_path, &width, &height);
    if (!image) {
        printf("Failed to load image from %s\n", input_path);
        return 1;
    }

    unsigned char resized[32][32];
    resize_to_32x32(image, width, height, resized);

    enhance_image(resized);

    unsigned char binary[32][32];
    otsu_binarize(resized, binary);

    save_bmp(output_bmp_path, binary, 32, 32);
    save_as_c_array(output_header_path, binary);

    free_image(image, height);
    printf("Processing complete.\n");
    printf("Output BMP: %s\n", output_bmp_path);
    printf("Output .h: %s\n", output_header_path);
    return 0;
}