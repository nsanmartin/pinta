#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

#include <dibapp.h>

#define WINDOW_WIDTH 640UL
#define WINDOW_HEIGHT 480UL

enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };
long get_time_millis() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * MS_PER_SECOND + t.tv_nsec / NS_PER_MS;
}

int process_input(DibuApp* app) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
            app->quit = true;
        } else if (e.type == SDL_MOUSEMOTION
            || e.type == SDL_MOUSEBUTTONDOWN
            || e.type == SDL_MOUSEBUTTONUP ) {

            int x, y;
            if(SDL_GetMouseState( &x, &y ) & SDL_BUTTON_LEFT) {
                if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH) {
                    size_t sz = app->table->pencil.sz;
                    size_t fromx = x - sz;
                    size_t fromy = y - sz;
                    size_t tox = x + sz - 1;
                    size_t toy = y + sz - 1;

                    if (fromx < app->table->w && tox < app->table->w
                        && fromy < app->table->h && toy < app->table->h) {
                        for (size_t i = fromx; i < tox; ++i) {
                            for (size_t j = fromy; j < toy; ++j) {
                                *dibTableAt(app->table, i, j) = 1;
                            }
                            
                        }
                    }
                }
            }
        }
    }

    return 0;
}

void render(DibuApp* app) {

        SDL_RenderClear(app->media->renderer);

        SDL_SetRenderDrawColor(app->media->renderer, 255, 255, 255, 255 );

        SDL_RenderClear(app->media->renderer);
        SDL_SetRenderDrawColor(app->media->renderer, 255, 148, 57, 253 );
        for (size_t i = 0; i < WINDOW_WIDTH; ++i) {
            for (size_t j = 0; j < WINDOW_HEIGHT; ++j) {
                if (*dibTableAt(app->table, i, j) != 0) {
                   if(SDL_RenderDrawPoint(app->media->renderer, i, j)) {
                        fprintf(stderr, "error drawing point");
                        exit(1);
                   }
                }
            }
        }

    SDL_RenderPresent(app->media->renderer);
}


int main(void)
{
    DibuApp* app = newDibuApp(WINDOW_WIDTH, WINDOW_HEIGHT);

    int close_requested = 0;
    long previous = get_time_millis();
    long lag = 0;
    const long slice = 2;
    
    while (!app->quit) {
        long current = get_time_millis();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        process_input(app);

        for (;!close_requested && lag >= slice; lag -= slice){
            //update(app, buttons, mouse_x, mouse_y);
        }
        render(app);
    }
    
    freeDibuApp(app);

}
