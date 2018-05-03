
#include <cairo.h>
#include <emscripten.h>
#include <SDL.h>
#include <cairo-ft.h>

static cairo_surface_t * surface = NULL;
static SDL_Texture * tex = NULL;
static SDL_Window * sdl_window = nullptr;
static SDL_Renderer * sdl_renderer = nullptr;
static int width = 512;
static int height = 512;

// Called whenever the window changes size
void on_resize(int new_width, int new_height) {
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

void draw() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_RESIZED) {
            on_resize(e.window.data1, e.window.data2);
        }
    }

    // Create a (temporary) canvas
    cairo_t * cr = cairo_create(surface);

    // Clear the renderer's (next) buffer
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    // Fill the canvas with black
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    // Draw a green circle
    cairo_set_line_width(cr, 10);
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_arc(cr, width/2, height/2, 100, 0, 2 * M_PI);
    cairo_stroke_preserve(cr);

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

int main(int, char **) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    sdl_window = SDL_CreateWindow(
        "green circle",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    on_resize(width, height);
    emscripten_set_main_loop(draw, 60, 1);
    return 0;
}
