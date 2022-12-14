#include <point.h>
#include <dibmedia.h>
#include <dibmem.h>


int sdl_media_init(DibMedia* media) {
    
    if (SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER) < 0) {
        fprintf(stderr, "Couldn't initialize SDL\n");
        return -1;
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
        return -1;
    }
    
    media->renderer = SDL_CreateRenderer(
        media->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (media->renderer == NULL) {
        SDL_DestroyWindow(media->window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return -1;
    }

    media->texture = SDL_CreateTexture(
        media->renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STATIC,
        media->dim.w,
        media->dim.h
    );

    if (media->texture == NULL) {
        SDL_DestroyWindow(media->window);
        SDL_DestroyRenderer(media->renderer);
        fprintf(stderr, "SDL_CreateTexture Error: %s\n", SDL_GetError());
        return -1;
    }
    return 0;
}

void freeDibMedia(DibMedia* media) {
    SDL_DestroyTexture(media->texture);
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

    if(sdl_media_init(rv) != 0) {
        free(rv);
        return NULL;
    }
    return rv;
}
