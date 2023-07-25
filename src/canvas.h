/*
 * canvas.h - Screen canvas implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>

#include "vectors.h"

typedef struct Canvas_s Canvas;

Canvas *canvasCreate(size_t width, size_t height);
Canvas *canvasCopy(const Canvas *canvas);

Vec3 canvasPixel(const Canvas *canvas, size_t x, size_t y);
void canvasPixelWrite(Canvas *canvas, size_t x, size_t y, Vec3 pixel);

size_t canvasWidth(const Canvas *canvas);
size_t canvasHeight(const Canvas *canvas);

char *canvasPPM(const Canvas *canvas);

#endif
