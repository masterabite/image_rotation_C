#include <stdio.h>
#include "image.h"

int main( int argc, char** argv ) {
    if (argc != 2) {
        printf(stderr, (argc<2?"Not enough arguments \n":"Too many arguments \n" ) );
    }

    struct image img = {0};
    FILE* bmp_file = fopen(argv[1],"r+w");

    enum read_status r_stat = from_bmp(bmp_file, &img);
    img = image_rotate(img);
    enum write_status w_stat = to_bmp(bmp_file, &img);
    fclose(bmp_file);
    free(img.data);
    return 0;
}

