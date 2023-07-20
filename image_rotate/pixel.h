#ifndef LAB_BMP_ROTATE_PIXEL_H
#define LAB_BMP_ROTATE_PIXEL_H

    #include <stdbool.h>
    #include <inttypes.h>
    #include <stdio.h>
    struct pixel { uint8_t b, g, r; };
    bool read_pixel_line( FILE* f, struct pixel* p, size_t len);
    bool write_pixel_line( FILE* f, struct pixel* p, size_t len);
#endif //LAB_BMP_ROTATE_PIXEL_H
