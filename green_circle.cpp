
#include "ui.h"

static context ctx;

void draw(context * ctx, cairo_t * cr) {
    // Fill the canvas with black
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, ctx->width, ctx->height);
    cairo_fill(cr);

    // Draw a green circle
    cairo_set_line_width(cr, 10);
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_arc(cr, ctx->width/2, ctx->height/2, 100, 0, 2 * M_PI);
    cairo_stroke_preserve(cr);
}

int main(int, char **) {
    return ctx.start("green circle", 512, 512, &draw);
}
