#include "pixel.h"

#include <inttypes.h>
#include <stdio.h>

bool read_pixel_line( FILE* f, struct pixel* p, size_t len) {
    return (fread( p, sizeof( struct pixel ), len, f ) == len);
}

bool write_pixel_line( FILE* f, struct pixel* p, size_t len) {
    return (fwrite( p, sizeof( struct pixel ), len, f ) == len);
}