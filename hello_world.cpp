
#include "ui.h"
#include <cairo-ft.h>

static FT_Library ft_lib = nullptr;
static FT_Face ft_font = nullptr;
static cairo_font_face_t * cr_font = nullptr;
static context ctx;

void draw(context * ctx, cairo_t * cr) {
    // Fill the canvas with black
    cairo_move_to(cr, 0, 0);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, ctx->width, ctx->height);
    cairo_fill(cr);

    // Draw text, in white
    cairo_set_font_face(cr, cr_font);
    cairo_set_font_size(cr, 80);
    const char * text = "Hello World!";
    cairo_text_extents_t extents;
    cairo_text_extents(cr, text, &extents);
    cairo_move_to(
        cr,
        (ctx->width/2) - (extents.width/2 + extents.x_bearing),
        (ctx->height/2) - (extents.height/2 + extents.y_bearing)
    );
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_show_text(cr, text);
}

int main(int, char **) {
    FT_Error ft_status;
    ft_status = FT_Init_FreeType(&ft_lib);
    const char * font_file_name = "assets/Vegur-Bold.ttf";
    FT_New_Face(ft_lib, font_file_name, 0, &ft_font);
    cr_font = cairo_ft_font_face_create_for_ft_face(ft_font, 0);

    return ctx.start("Hello World", 512, 512, &draw);
}
