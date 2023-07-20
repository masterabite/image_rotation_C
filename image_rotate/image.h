#ifndef LAB_BMP_ROTATE_IMAGE_H
#define LAB_BMP_ROTATE_IMAGE_H
#include <stdio.h>
#include <allocate.h>
#include "pixel.h"
#include "bmp_header.h"
#include "util.h"

struct image {
    uint64_t width, height;
    struct pixel* data;
};

bool read_image(struct image* im, FILE* f);

/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image image_rotate( struct image const source );

bool write_image(struct image const* img, FILE* f);

/*  deserializer   */
enum read_status  {
    READ_OK = 0,
    READ_INVALID_SIGNATURE = 1,
    READ_INVALID_BITS = 2,
    READ_INVALID_HEADER = 3,
    READ_INVALID_SIZE = 4,
    READ_INVALID_DATA = 5
};
enum read_status from_bmp( FILE* f, struct image* img );

/*  serializer   */
enum  write_status  {
    WRITE_OK = 0,
    WRITE_ERROR = 1,
    WRITE_FILE_NULL = 2
};
enum write_status to_bmp( FILE* out, struct image const* img );

#endif //LAB_BMP_ROTATE_IMAGE_H
