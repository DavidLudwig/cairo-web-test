
#include "ui.h"

// Called whenever the window changes size
void context::on_resize(int new_width, int new_height) {
    // printf("%s: %dx%d -> %dx%d\n", __FUNCTION__, width, height, new_width, new_height);

    // Save the new size
    width = new_width;
    height = new_height;

    // Recreate SDL's texture
    if (tex) {
        SDL_DestroyTexture(tex);
    }
    tex = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    // Recreate the Cairo image surface
    if (surface) {
        cairo_surface_destroy(surface);
    }
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
}

void context::tick(void * _context) {
    return ((context *)_context)->tick();
}

void context::tick() {
    // Create a (temporary) canvas
    cairo_t * cr = cairo_create(surface);

    // Clear the renderer's (next) buffer
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    // Pump and process event(s), if one(s) happened
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            on_resize(e.window.data1, e.window.data2);
        }
    }

    // Draw!
    if (draw) {
        draw(this, cr);
    }

    // Copy Cairo canvas to SDL2 texture
    unsigned char * src = cairo_image_surface_get_data(surface);
    const int pitch = width * 4;    // '4' == 4 bytes per pixel
    SDL_UpdateTexture(tex, nullptr, src, pitch);
    SDL_RenderCopy(sdl_renderer, tex, nullptr, nullptr);

    // Present latest image
    SDL_RenderPresent(sdl_renderer);

    // Clean up
    cairo_destroy(cr);
}

int context::start(
    const char * window_name,
    int window_width,
    int window_height,
    draw_t draw
)
{
    this->draw = draw;
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    sdl_window = SDL_CreateWindow(
        window_name,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        window_width, window_height,
        SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    on_resize(window_width, window_height);
    emscripten_set_main_loop_arg(tick, (void *)this, 60, 1);
    return 0;
}
