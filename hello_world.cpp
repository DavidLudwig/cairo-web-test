
#include <cairo.h>
#include <emscripten.h>
#include <SDL.h>
#include <cairo-ft.h>

static cairo_surface_t * surface = NULL;
static SDL_Texture * tex = NULL;
static SDL_Window * sdl_window = nullptr;
static SDL_Renderer * sdl_renderer = nullptr;
static FT_Library ft_lib = nullptr;
static FT_Face ft_font = nullptr;
static cairo_font_face_t * cr_font = nullptr;
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

    // Clear the renderer's (next) buffer
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    // Create a (temporary) canvas
    cairo_t * cr = cairo_create(surface);

    // Fill the canvas with black
    cairo_move_to(cr, 0, 0);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_fill(cr);

    // Draw text, in white
    cairo_set_font_face(cr, cr_font);
    cairo_set_font_size(cr, 80);
    const char * text = "Hello World!";
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text, &extents);
    cairo_move_to(
        cr,
        (width/2) - (extents.width/2 + extents.x_bearing),
        (height/2) - (extents.height/2 + extents.y_bearing)
    );
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_show_text(cr, text);

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
        "Hello World",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    on_resize(width, height);
    FT_Error ft_status;
    ft_status = FT_Init_FreeType(&ft_lib);
    const char * font_file_name = "assets/Vegur-Bold.ttf";
    FT_New_Face(ft_lib, font_file_name, 0, &ft_font);
    cr_font = cairo_ft_font_face_create_for_ft_face(ft_font, 0);
    emscripten_set_main_loop(draw, 0, 1);
    return 0;
}
