#include "save_h_file.h"
#include <stdio.h>

void save_as_c_array(const char *filename, unsigned char image[32][32]) {
    FILE *f = fopen(filename, "w");
    fprintf(f, "#ifndef OUTPUT_IMAGE_H\n#define OUTPUT_IMAGE_H\n\n");
    fprintf(f, "const unsigned char image_data[32][32] = {\n");
    for (int i = 0; i < 32; i++) {
        fprintf(f, "    {");
        for (int j = 0; j < 32; j++) {
            int val = (image[i][j] == 255) ? 1 : 0;
            fprintf(f, "%d", val);
            if (j < 31) fprintf(f, ", ");
        }
        fprintf(f, "}");
        if (i < 31) fprintf(f, ",");
        fprintf(f, "\n");
    }
    fprintf(f, "};\n\n#endif\n");
    fclose(f);
}