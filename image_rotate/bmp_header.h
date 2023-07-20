#ifndef LAB_BMP_ROTATE_BMP_HEADER_H
#define LAB_BMP_ROTATE_BMP_HEADER_H

#include "image.h"

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#pragma pack(push, 1)

#define BMP_COLOR_DEPTH 24
#define BMP_TYPE 0x4d42
#define BMP_OFFBITS 0x36
#define BMP_SIZE 40
#define BMP_PLANES 1

struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

bool read_bmp_header( FILE* f, struct bmp_header* header );
size_t get_bmp_padding_from_image(struct image const* img);
struct bmp_header get_bmp_header_from_image(struct image const* img);
enum read_status bmp_header_verify(struct bmp_header const* header);
#pragma pack(pop)
#endif
