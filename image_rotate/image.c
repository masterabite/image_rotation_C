#include "image.h"

#include <stdio.h>
#include <allocate.h>

bool read_image(struct image* im, FILE* f) {
    if (im->data == NULL) {
        im->data = malloc(sizeof(struct pixel)*(size_t)(im->width*im->height));
    }

    size_t padding = get_bmp_padding_from_image(im);
    uint8_t rubbish[3];

    for (size_t i = 0; (size_t)im->height > i; ++i) {
        if(!read_pixel_line(f, (im->data + (im->height - i - 1) * im->width), im->width) |
            (fread(rubbish, padding, 1, f) != 1)) {
            return false;
        }
    }

    return true;
}

/* создаёт копию изображения, которая повёрнута на 90 градусов */
struct image image_rotate( struct image const source ) {

    struct image image_new = {0};
    image_new.width = source.height;
    image_new.height = source.width;
    image_new.data = malloc(sizeof(struct pixel)*(size_t)(source.width*source.height));
    size_t cur = 0;

    for (size_t j = 0; (size_t)source.width > j; ++j) {
        for (size_t i = (size_t)source.height-1; i >= 0; --i) {
            image_new.data[cur++] = source.data[i*source.width+j];
            if (i==0) {
                break;
            }
        }
    }
    return image_new;
}

bool write_image(struct image const* img, FILE* f) {
    size_t padding = get_bmp_padding_from_image(img);
    uint8_t rubbish[3];


    for (size_t i = 0; (size_t)img->height > i; ++i) {
        if (!write_pixel_line(f, (img->data + (img->height - i - 1) * img->width), img->width)) {
            return false;
        }
        if (fwrite(rubbish, padding, 1, f) != 1) {
            return false;
        }
    }
    return true;
}

enum read_status from_bmp( FILE* f, struct image* img ) {
    enum read_status result;
    if (fseek(f, 0, SEEK_SET) != 0) {
        result = WRITE_ERROR;
    } else {
        struct bmp_header header = {0};
        read_bmp_header(f, &header);
        result = bmp_header_verify(&header);

        img->width = header.biWidth;
        img->height = header.biHeight;

        if (!read_image(img, f)) {
            result = READ_INVALID_DATA;
        }
    }
    if (result != READ_OK) {
        free(img->data);
    }
    return result;
}

enum write_status to_bmp( FILE* out, struct image const* img ) {
    enum write_status result = WRITE_OK;

    if (fseek(out, 0, SEEK_SET) != 0) {
         result = WRITE_ERROR;
    } else
    if (out == NULL) {
        result = WRITE_FILE_NULL;
    } else {
        struct bmp_header header = get_bmp_header_from_image(img);
        if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1 | !write_image(img, out)) {
            result = WRITE_ERROR;
        }
    }

    if (result != WRITE_OK) {
        free(img->data);
    }
    return result;
}
