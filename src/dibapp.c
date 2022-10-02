#include <stdlib.h>

#include <dibapp.h>
#include <point.h>


DibuApp* newDibuApp(size_t w, size_t h) {

    DibTable* table = newDibTable(w, h);
    if (!table) { return NULL; }
    DibMedia* media = newDibMedia((Dimensions){ .w = w, .h = h});
    if (!media) { return NULL; }
    DibuApp* rv = malloc(sizeof(DibuApp));
    *rv = (DibuApp) {
        .table = table,
        .media = media,
        .quit = false
    };

    return rv;
}

void freeDibuApp(DibuApp* app) {
    freeDibTable(app->table);
    freeDibMedia(app->media);
    free(app);
}
