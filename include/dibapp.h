#ifndef __H_DIBU_APP_H_
#define __H_DIBU_APP_H_

#include <dibtable.h>
#include <dibmedia.h>

typedef struct {
    DibTable* table;
    DibMedia* media;
} DibuApp;

DibuApp* newDibuApp(size_t w, size_t h);
void freeDibuApp(DibuApp* app);
#endif

