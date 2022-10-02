#include <stdlib.h>

#include <point.h>
#include <dibmedia.h>


void sdl_media_init(DibMedia* media) {
    
    if (SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        exit (1);
    }

    atexit (SDL_Quit);

    media->window = SDL_CreateWindow(
        "pinta",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        media->dim.w,
        media->dim.h,
        SDL_WINDOW_SHOWN
    );
    
    if (media->window == NULL) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        exit(1);
    }
    
    media->renderer = SDL_CreateRenderer(
        media->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (media->renderer == NULL) {
        SDL_DestroyWindow(media->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        exit(1);
    }
}

void freeDibMedia(DibMedia* media) {
    SDL_DestroyRenderer(media->renderer);
    SDL_DestroyWindow(media->window); 
    free(media);
}

DibMedia* newDibMedia(Dimensions dim) {

    DibMedia* rv = malloc(sizeof(DibMedia));
    if (!rv) {
        return NULL;
    }

    *rv = (DibMedia) {
        .window   = NULL,
        .dim      = dim,
        .renderer = NULL
    };

    sdl_media_init(rv);
    return rv;
}
