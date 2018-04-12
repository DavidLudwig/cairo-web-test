
#include <cairo.h>
#include <emscripten.h>
#include <SDL.h>
#include <cairo-ft.h>


static cairo_surface_t * surface = NULL;
static cairo_t * cr = NULL;
static SDL_Texture * tex = NULL;
static SDL_Window * sdl_window = nullptr;
static SDL_Renderer * sdl_renderer = nullptr;
static FT_Library ft_lib = nullptr;
static FT_Face ft_font = nullptr;
static cairo_font_face_t * cr_font = nullptr;

void draw() {
    // Clear the renderer's (next) buffer
    SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer);

    // Fill the canvas with black
    cairo_move_to(cr, 0, 0);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, 512, 512);
    cairo_fill(cr);

    // Draw text, in white
    cairo_set_font_face(cr, cr_font);
    cairo_set_font_size(cr, 80);
    const char * text = "Hello World!";
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text, &extents);
    cairo_move_to(
        cr,
        256 - (extents.width/2 + extents.x_bearing),
        256 - (extents.height/2 + extents.y_bearing)
    );
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_show_text(cr, text);

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
        "Hello World",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        512,
        512,
        SDL_WINDOW_OPENGL);
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, 0);
    tex = SDL_CreateTexture(sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 512, 512);
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 512, 512);
    cr = cairo_create(surface);
    FT_Error ft_status;
    ft_status = FT_Init_FreeType(&ft_lib);
    const char * font_file_name = "assets/Vegur-Bold.ttf";
    FT_New_Face(ft_lib, font_file_name, 0, &ft_font);
    cr_font = cairo_ft_font_face_create_for_ft_face(ft_font, 0);
    emscripten_set_main_loop(draw, 60, 1);
    return 0;
}
