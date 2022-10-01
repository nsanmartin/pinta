#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <dibtable.h>


DibTable* newDibTable(size_t w, size_t h) {
    int* data = calloc(w * h,  sizeof(int));
    if (!data) { return NULL; }
    DibTable* rv = malloc(sizeof(DibTable));
    if (!rv) { return NULL; }
    *rv = (DibTable) {
        .data = data,
        .w = w,
        .h = h,
        .pencil = { .pos = { .x = w/2, .y = h/2 }, .sz = 4 }
    };
    return rv;
}

void freeDibTable(DibTable* table) {
    free(table);
}

int* dibTableAt(DibTable* t, size_t x, size_t y) {
    size_t ix = t->w * y + x;
    assert(ix < t->w * t->h);
    return &t->data[ix];
}