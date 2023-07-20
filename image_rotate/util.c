#include "util.h"

void pixel_copy(struct pixel* p1, struct pixel* p2) {
    p2->r = p1->r;
    p2->g = p1->g;
    p2->b = p1->b;
}

