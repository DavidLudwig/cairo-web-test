
PIXMAN_SRCS := \
	external/pixman/pixman/pixman-access.c \
	external/pixman/pixman/pixman-access-accessors.c \
	external/pixman/pixman/pixman-arm.c \
	external/pixman/pixman/pixman-bits-image.c \
	external/pixman/pixman/pixman-combine-float.c \
	external/pixman/pixman/pixman-combine32.c \
	external/pixman/pixman/pixman-conical-gradient.c \
	external/pixman/pixman/pixman-edge.c \
	external/pixman/pixman/pixman-edge-accessors.c \
	external/pixman/pixman/pixman-fast-path.c \
	external/pixman/pixman/pixman-general.c \
	external/pixman/pixman/pixman-gradient-walker.c \
	external/pixman/pixman/pixman-image.c \
	external/pixman/pixman/pixman-implementation.c \
	external/pixman/pixman/pixman-linear-gradient.c \
	external/pixman/pixman/pixman-matrix.c \
	external/pixman/pixman/pixman-mips.c \
	external/pixman/pixman/pixman-noop.c \
	external/pixman/pixman/pixman-ppc.c \
	external/pixman/pixman/pixman-radial-gradient.c \
	external/pixman/pixman/pixman-region32.c \
	external/pixman/pixman/pixman-solid-fill.c \
	external/pixman/pixman/pixman-trap.c \
	external/pixman/pixman/pixman-utils.c \
	external/pixman/pixman/pixman-x86.c \
	external/pixman/pixman/pixman.c

CAIRO_SRCS := \
	external/cairo/src/cairo-analysis-surface.c \
	external/cairo/src/cairo-arc.c \
	external/cairo/src/cairo-array.c \
	external/cairo/src/cairo-atomic.c \
	external/cairo/src/cairo-bentley-ottmann-rectangular.c \
	external/cairo/src/cairo-bentley-ottmann-rectilinear.c \
	external/cairo/src/cairo-bentley-ottmann.c \
	external/cairo/src/cairo-boxes-intersect.c \
	external/cairo/src/cairo-boxes.c \
	external/cairo/src/cairo-cache.c \
	external/cairo/src/cairo-clip-boxes.c \
	external/cairo/src/cairo-clip-polygon.c \
	external/cairo/src/cairo-clip-region.c \
	external/cairo/src/cairo-clip-surface.c \
	external/cairo/src/cairo-clip.c \
	external/cairo/src/cairo-color.c \
	external/cairo/src/cairo-composite-rectangles.c \
	external/cairo/src/cairo-compositor.c \
	external/cairo/src/cairo-contour.c \
	external/cairo/src/cairo-damage.c \
	external/cairo/src/cairo-default-context.c \
	external/cairo/src/cairo-device.c \
	external/cairo/src/cairo-error.c \
	external/cairo/src/cairo-font-face-twin-data.c \
	external/cairo/src/cairo-font-face-twin.c \
	external/cairo/src/cairo-font-face.c \
	external/cairo/src/cairo-font-options.c \
	external/cairo/src/cairo-freelist.c \
	external/cairo/src/cairo-gstate.c \
	external/cairo/src/cairo-hash.c \
	external/cairo/src/cairo-image-compositor.c \
	external/cairo/src/cairo-image-source.c \
	external/cairo/src/cairo-image-surface.c \
	external/cairo/src/cairo-line.c \
	external/cairo/src/cairo-matrix.c \
	external/cairo/src/cairo-mesh-pattern-rasterizer.c \
	external/cairo/src/cairo-misc.c \
	external/cairo/src/cairo-mono-scan-converter.c \
	external/cairo/src/cairo-no-compositor.c \
	external/cairo/src/cairo-observer.c \
	external/cairo/src/cairo-path-bounds.c \
	external/cairo/src/cairo-path-fill.c \
	external/cairo/src/cairo-path-fixed.c \
	external/cairo/src/cairo-path-in-fill.c \
	external/cairo/src/cairo-path-stroke-boxes.c \
	external/cairo/src/cairo-path-stroke-polygon.c \
	external/cairo/src/cairo-path-stroke-traps.c \
	external/cairo/src/cairo-path-stroke.c \
	external/cairo/src/cairo-path.c \
	external/cairo/src/cairo-pattern.c \
	external/cairo/src/cairo-pen.c \
	external/cairo/src/cairo-polygon-intersect.c \
	external/cairo/src/cairo-polygon-intersect.c \
	external/cairo/src/cairo-polygon-reduce.c \
	external/cairo/src/cairo-polygon.c \
	external/cairo/src/cairo-raster-source-pattern.c \
	external/cairo/src/cairo-recording-surface.c \
	external/cairo/src/cairo-rectangle.c \
	external/cairo/src/cairo-rectangular-scan-converter.c \
	external/cairo/src/cairo-region.c \
	external/cairo/src/cairo-scaled-font.c \
	external/cairo/src/cairo-shape-mask-compositor.c \
	external/cairo/src/cairo-slope.c \
	external/cairo/src/cairo-spans-compositor.c \
	external/cairo/src/cairo-spans.c \
	external/cairo/src/cairo-spline.c \
	external/cairo/src/cairo-stroke-dash.c \
	external/cairo/src/cairo-stroke-style.c \
	external/cairo/src/cairo-surface-offset.c \
	external/cairo/src/cairo-surface-snapshot.c \
	external/cairo/src/cairo-surface-wrapper.c \
	external/cairo/src/cairo-surface.c \
	external/cairo/src/cairo-tor-scan-converter.c \
	external/cairo/src/cairo-tor22-scan-converter.c \
	external/cairo/src/cairo-toy-font-face.c \
	external/cairo/src/cairo-traps-compositor.c \
	external/cairo/src/cairo-traps.c \
	external/cairo/src/cairo-unicode.c \
	external/cairo/src/cairo-user-font.c \
	external/cairo/src/cairo-wideint.c \
	external/cairo/src/cairo.c

green_circle.html: pixman.o cairo.o green_circle.cpp
	em++ \
		-O2 \
		-s USE_SDL=2 \
		-s USE_LIBPNG=1 \
		-s USE_ZLIB=1 \
		-I external/cairo/src/ \
		-I external/pixman/pixman \
		-I . \
		green_circle.cpp \
		pixman.o \
		cairo.o \
		-o green_circle.html

pixman.o: Makefile $(PIXMAN_SRCS)
	emcc \
		-O2 \
		-I external/pixman/pixman \
		-I . \
		-DPACKAGE \
		-DPIXMAN_NO_TLS \
		-Wno-shift-negative-value \
		-Wno-tautological-constant-out-of-range-compare \
		$(PIXMAN_SRCS) \
		-o pixman.o

cairo.o: Makefile $(CAIRO_SRCS)
	emcc \
		-O2 \
		-I external/cairo/src/ \
		-I external/pixman/pixman \
		-I . \
		-DCAIRO_FEATURES_H \
		-Wno-enum-conversion \
		-Wno-parentheses-equality \
		-Wno-incompatible-pointer-types \
		$(CAIRO_SRCS) \
		-o cairo.o

clean:
	rm -f pixman.o cairo.o green_circle.html* green_circle.js
