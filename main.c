#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL.h>

#include <dibapp.h>
#include <point.h>

#define WINDOW_WIDTH 640UL
#define WINDOW_HEIGHT 480UL

int lastx, lasty;
bool mouse_up;

typedef struct {
    double slope, yintercept;
} Line;

typedef struct {
    int min, max;
} SortedPair;

SortedPair sortedPairFrom(int a, int b) {
    if (a <= b) {
        return (SortedPair) { .min = a, .max = b };
    } else {
        return (SortedPair) { .min = b, .max = a };
    }
}

enum { NS_PER_SECOND = 1000000000, MS_PER_SECOND = 1000, NS_PER_MS = 1000000 };
long get_time_millis() {
    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);
    return t.tv_sec * MS_PER_SECOND + t.tv_nsec / NS_PER_MS;
}

Line get_line(int x0, int x1, int y0, int y1) {
    Line rv;
    rv.slope = (double)(y1-y0) / (double)(x1-x0);
    rv.yintercept = y0 - rv.slope*x0;
    return rv;
}

void draw_dot(int x, int y, DibTable* t) {
    size_t sz = t->pencil.sz;
    size_t fromx = x - sz;
    size_t fromy = y - sz;
    size_t tox = x + sz - 1;
    size_t toy = y + sz - 1;

    if (fromx < t->w && tox < t->w && fromy < t->h && toy < t->h) {
        for (size_t i = fromx; i < tox; ++i) {
            for (size_t j = fromy; j < toy; ++j) {
                *dibTableAt(t, i, j) = 1;
            }
            
        }
    }
}

int process_input(void* data) {
    DibuApp* app = (DibuApp*) data;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_q)) {
            app->quit = true;
            return 0;
        }

        int x, y;
        bool left_button = SDL_GetMouseState( &x, &y ) & SDL_BUTTON_LEFT;

        if (left_button && e.type == SDL_MOUSEBUTTONDOWN) {
            mouse_up = false;
            lastx = x;
            lasty = y;

            if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH) {
                draw_dot(x, y, app->table);
            }

        } else if (!mouse_up && e.type == SDL_MOUSEMOTION) {
            if (abs(lastx-x) > abs(lasty-y)) {
                Line l = get_line(lastx, x, lasty, y);
                SortedPair xs = sortedPairFrom(lastx, x);
                for (size_t i = xs.min; i < xs.max; ++i) {
                    int j = l.yintercept + l.slope * i;
                    draw_dot(i, j, app->table);
                }
            } else {
                SortedPair ys = sortedPairFrom(lasty, y);
                if (lastx == x) {
                    for (size_t i = ys.min; i < ys.max; ++i) {
                        draw_dot(x, i, app->table);
                    }
                } else {
                    Line l = get_line(lastx, x, lasty, y);
                    for (size_t i = ys.min; i < ys.max; ++i) {
                        int j = (i - l.yintercept) / l.slope;
                        draw_dot(j, i, app->table);
                    }
                }
            }
            lastx = x;
            lasty = y;

        } 
        if (e.type == SDL_MOUSEBUTTONUP ) {
            mouse_up = true;
        }
    }

    return 0;
}

void render(DibuApp* app) {

    SDL_UpdateTexture(app->media->texture, NULL, app->table->data, 640 * sizeof(Uint32));
    SDL_RenderClear(app->media->renderer);
    SDL_RenderCopy(app->media->renderer, app->media->texture, NULL, NULL);
    SDL_RenderPresent(app->media->renderer);
}


int main(void)
{
    DibuApp* app = newDibuApp(WINDOW_WIDTH, WINDOW_HEIGHT);

    long previous = get_time_millis();
    long lag = 0;
    mouse_up = true;

    //SDL_Thread* threadID = SDL_CreateThread(process_input,"process_input", (void*) app);   

    while (!app->quit) {
        long current = get_time_millis();
        long elapsed = current - previous;
        previous = current;
        lag += elapsed;

        process_input(app);
        render(app);
    }
    //SDL_WaitThread( threadID, NULL );   
    freeDibuApp(app);

}
