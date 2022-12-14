#include <point.h>
#include <dibmem.h>

bool point_eq(Point p, Point q) {
    return p.x == q.x && p.y == q.y;
}

VecPoints* newVecPoints(size_t capacity) {
    Point* data = malloc(capacity * sizeof(Point));
    if (!data) {
        return NULL;
    }
    VecPoints* rv = malloc(sizeof(VecPoints));
    if (!rv) {
        free(data);
        return NULL;
    }
    *rv = (VecPoints) {
        .beg = data,
        .capacity = capacity,
        .end = data
    };

    return rv;
}
