#include "bmp_header.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>

bool read_bmp_header( FILE* f, struct bmp_header* header ) {
    return fread( header, sizeof( struct bmp_header ), 1, f );
}

size_t get_bmp_padding_from_image(struct image const* img) {
    uint64_t round_width = img->width*3;
    size_t padding = 0;

    while (round_width % 4 != 0) {
        ++padding;
        ++round_width;
    }

    return padding;
}

struct bmp_header get_bmp_header_from_image(struct image const* img) {
    struct bmp_header header = {0};
    header.bfType = BMP_TYPE;
    header.bOffBits = BMP_OFFBITS;
    header.biSize = BMP_SIZE;
    header.biSizeImage = (sizeof(struct pixel)*img->width+get_bmp_padding_from_image(img))*img->height;
    header.bfileSize = sizeof(struct bmp_header)+header.biSizeImage;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biBitCount = BMP_COLOR_DEPTH;
    header.biPlanes = BMP_PLANES;
    return header;
}

enum read_status bmp_header_verify(struct bmp_header const* header) {
    if (header->bfType != BMP_TYPE) {
        return READ_INVALID_SIGNATURE;
    } else
    if (header->bOffBits != BMP_OFFBITS || header->biPlanes != BMP_PLANES) {
        return READ_INVALID_HEADER;
    } else
    if (header->biBitCount != BMP_COLOR_DEPTH) {
        return READ_INVALID_BITS;
    } else
    if (header->biWidth == 0 || header->biHeight == 0) {
        return READ_INVALID_SIZE;
    } else {
        return READ_OK;
    }
}