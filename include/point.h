#ifndef __H_DIB_POINT_H_
#define __H_DIB_POINT_H_

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point* beg;
    size_t capacity;
    Point* end;
} VecPoints;

bool point_eq(Point p, Point q) ;

VecPoints* newVecPoints(size_t cap);
#endif
