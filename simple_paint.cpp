
#include "ui.h"

#include <array>
#include <optional>

static context ctx;

void draw(context * ctx, cairo_t * cr) {
    static bool do_clear = true;

    const Uint8 * keys_down = SDL_GetKeyboardState(NULL);
    if (keys_down[SDL_SCANCODE_DELETE]) {
        do_clear = true;
    }

    if (do_clear) {
        // Fill the canvas with white
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_rectangle(cr, 0, 0, ctx->width, ctx->height);
        cairo_fill(cr);
        do_clear = false;
    }

    // Draw something near the mouse cursor, if it is down
    static std::array<int, 2> pos = {0, 0};
    static std::optional<std::array<int, 2>> last_pos;
    if (SDL_GetMouseState(&pos[0], &pos[1])) {
        const int line_width = 4;
        cairo_set_line_width(cr, line_width);
        cairo_set_source_rgb(cr, 0, 0, 0);
        if (last_pos) {
            cairo_move_to(cr, (*last_pos)[0], (*last_pos)[1]);
            cairo_line_to(cr, pos[0], pos[1]);
            cairo_stroke(cr);
        } else {
            cairo_rectangle(cr, pos[0] - (line_width / 2), pos[1] - (line_width / 2), line_width, line_width);
            cairo_fill(cr);
        }
        last_pos = pos;
    } else {
        last_pos.reset();
    }
}

int main(int, char **) {
    return ctx.start("simple paint", &draw);
}
