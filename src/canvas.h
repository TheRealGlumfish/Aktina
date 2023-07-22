/*
 * canvas.h - Screen canvas implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stddef.h>

#include "tuples.h"

typedef struct Canvas_s Canvas;

Canvas *canvasCreate(size_t width, size_t height);
void canvasDestroy(Canvas *canvas);
Canvas *canvasCopy(const Canvas *canvas);

Tuple canvasPixel(const Canvas *canvas, size_t x, size_t y);
void canvasPixelWrite(Canvas *canvas, size_t x, size_t y, Tuple pixel);

size_t canvasWidth(const Canvas *canvas);
size_t canvasHeight(const Canvas *canvas);

char *canvasPPM(const Canvas *canvas);

#endif
