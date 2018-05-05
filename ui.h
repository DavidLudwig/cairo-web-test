
#ifndef DAVIDL_UI_H
#define DAVIDL_UI_H

#include <cairo.h>
#include <emscripten.h>
#include <SDL.h>
#include <cairo-ft.h>

#include <array>
#include <functional>
#include <string_view>

struct context;

typedef void (*draw_t)(context *, cairo_t *);

struct context {
    cairo_surface_t * surface = nullptr;
    SDL_Texture * tex = nullptr;
    SDL_Window * sdl_window = nullptr;
    SDL_Renderer * sdl_renderer = nullptr;
    int width = 512;
    int height = 512;
    draw_t draw = nullptr;

    void on_resize(int new_width, int new_height);
    static void tick(void * _draw);
    void tick();
    int start(
        const char * window_name,
        int window_width,
        int window_height,
        draw_t draw
    );
};

#endif
