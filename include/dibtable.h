#ifndef __H_DIBU_TABLE_H_ 
#define __H_DIBU_TABLE_H_ 

#include <point.h>
#include <dibpencil.h>

typedef struct {
    int* data;
    size_t w,h;
    DibPencil pencil;
} DibTable;

DibTable* newDibTable(size_t w, size_t h);
void freeDibTable(DibTable* table);

int* dibTableAt(DibTable* table, size_t x, size_t y);
#endif
