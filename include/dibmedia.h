#ifndef __H_DIBU_MEDIA_H_
#define __H_DIBU_MEDIA_H_

#include <SDL2/SDL.h>

typedef struct {
    int w, h;
} Dimensions;

typedef struct {
    SDL_Window* window;
    Dimensions dim;
    SDL_Renderer* renderer;
    //SDL_Event event;
} DibMedia;

DibMedia* newDibMedia(Dimensions dim);
void freeDibMedia(DibMedia* media);

#endif

