
#include "ui.h"

static context ctx;
static cairo_surface_t * image = nullptr;

void draw(context * ctx, cairo_t * cr) {
    // Fill the canvas with black
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_rectangle(cr, 0, 0, ctx->width, ctx->height);
    cairo_fill(cr);

    // Draw the image in the top-left
    cairo_set_source_surface(cr, image, 0, 0);
    cairo_paint(cr);
}

int main(int, char **) {
    image = cairo_image_surface_create_from_png("assets/sample.png");
    return ctx.start("an image", &draw);
}
