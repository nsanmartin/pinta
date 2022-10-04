#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <dibtable.h>


DibTable* newDibTable(size_t w, size_t h) {
    Uint32* data = malloc(w * h * sizeof(Uint32));
    if (!data) { return NULL; }
    memset(data, 255, w * h * sizeof(Uint32));
    DibTable* rv = malloc(sizeof(DibTable));
    if (!rv) {
        free(data);
        return NULL;
    }
    *rv = (DibTable) {
        .data = data,
        .w = w,
        .h = h,
        .pencil = { .pos = { .x = w/2, .y = h/2 }, .sz = 4 }
    };
    return rv;
}

void freeDibTable(DibTable* table) {
    free(table->data);
    free(table);
}

Uint32* dibTableAt(DibTable* t, int x, int y) {
    size_t ix = t->w * y + x;
    if (ix >= t->w * t->h) {
        printf("index error: %d, %d\n", x, y);
    }
    assert(ix < t->w * t->h);
    return &t->data[ix];
}
