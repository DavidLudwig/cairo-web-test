
#include <cairo.h>
#include <emscripten.h>
#include <SDL.h>

static cairo_surface_t * surface = NULL;
static cairo_t * cr = NULL;
static SDL_Texture * tex = NULL;
static SDL_Window * sdl_window = nullptr;
static SDL_Renderer * sdl_renderer = nullptr;

void draw() {
    // Clear the renderer's (next) buffer
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    // Fill the canvas with black
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, 512, 512);
    cairo_fill(cr);

    // Draw a green circle
    cairo_set_line_width(cr, 10);
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_arc(cr, 256, 256, 100, 0, 2 * M_PI);
    cairo_stroke_preserve(cr);

    // Copy Cairo canvas to SDL2 texture
    unsigned char * src = cairo_image_surface_get_data(surface);
    SDL_UpdateTexture(tex, nullptr, src, 512*4);
    SDL_RenderCopy(sdl_renderer, tex, nullptr, nullptr);

    // Present latest image
    SDL_RenderPresent(sdl_renderer);
}

int main(int, char **) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    sdl_window = SDL_CreateWindow(
        "green circle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        512,
        512,
        SDL_WINDOW_OPENGL);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    tex = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 512, 512);
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 512, 512);
    cr = cairo_create(surface);
    emscripten_set_main_loop(draw, 60, 1);
    return 0;
}
