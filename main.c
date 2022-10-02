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

int process_input(int* buttons, int* mouse_x, int* mouse_y) {
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT
            || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
            //close_requested = 1;
            return 1;
        }
    }

    *buttons = SDL_GetMouseState(mouse_x, mouse_y);
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

void update(DibuApp* app, int buttons, int mouse_x, int mouse_y) {

        if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            if (mouse_y >= 0 && mouse_y < WINDOW_HEIGHT && mouse_x >= 0 && mouse_x < WINDOW_WIDTH) {
                size_t sz = app->table->pencil.sz;
                size_t fromx = mouse_x - sz;
                size_t fromy = mouse_y - sz;
                size_t tox = mouse_x + sz - 1;
                size_t toy = mouse_y + sz - 1;

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

int main(void)
{
    DibuApp* app = newDibuApp(WINDOW_WIDTH, WINDOW_HEIGHT);

    int close_requested = 0;
    long previous = get_time_millis();
    long lag = 0;
    const long slice = 2;
    
    while (!close_requested) {
        long current = get_time_millis();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        int mouse_x, mouse_y, buttons;

        close_requested = process_input(&buttons, &mouse_x, &mouse_y);

        for (;!close_requested && lag >= slice; lag -= slice){
            update(app, buttons, mouse_x, mouse_y);
        }
        render(app);
    }
    
    freeDibuApp(app);

}
