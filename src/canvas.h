/*
 * canvas.h - Screen canvas implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <stdint.h>

#include "tuples.h"

typedef struct Canvas_s Canvas;

Canvas *canvasCreate(const uint64_t width, const uint64_t height);
void canvasDestroy(Canvas *canvas);
Canvas *canvasCopy(Canvas *canvas);

Tuple canvasPixel(Canvas *canvas, const uint64_t x, const uint64_t y);
void canvasPixelWrite(Canvas *canvas, const uint64_t x, const uint64_t y, const Tuple pixel);

uint64_t canvasWidth(Canvas *canvas);
uint64_t canvasHeight(Canvas *canvas);

char *canvasPPM(Canvas *canvas);

#endif
