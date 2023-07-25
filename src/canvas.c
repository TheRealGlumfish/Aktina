/*
 * canvas.h - Screen canvas implementation and utilities
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "canvas.h"
#include "tuples.h"

// TODO: Use [Static 1] syntax for Canvas *
// TODO: Replace Tuple with Vec3
// TODO: Consider replacing pixelCanvas with a flexible array member
struct Canvas_s
{
    size_t width;
    size_t height;
    Tuple *pixelCanvas;
};

// Canvas constructor and initializer
Canvas *canvasCreate(const size_t width, const size_t height)
{
    Canvas *canvas = malloc(sizeof(Canvas));
    if (canvas == NULL)
    {
        abort();
    }
    *canvas = (Canvas){width, height, malloc(sizeof(Tuple[width * height]))};
    if (canvas->pixelCanvas == NULL)
    {
        abort();
    }
    for (size_t i = 0; i < width; i++)
    {
        for (size_t j = 0; j < height; j++)
        {
            canvas->pixelCanvas[i + j * canvas->width] = color(0, 0, 0); // TODO: Use memset
        }
    }
    return canvas;
}

// Canvas destructor
void canvasDestroy(Canvas *canvas)
{
    free(canvas->pixelCanvas);
    canvas->pixelCanvas = NULL;
    free(canvas);
    canvas = NULL;
}

// Canvas copy constructor
Canvas *canvasCopy(const Canvas *canvas)
{
    Canvas *copyCanvas = malloc(sizeof(Canvas));
    if (copyCanvas == NULL)
    {
        abort();
    }
    *copyCanvas = (Canvas){canvas->width, canvas->height, malloc(sizeof(Tuple[canvas->width * canvas->height]))};
    if (copyCanvas->pixelCanvas == NULL)
    {
        abort();
    }
    memcpy(copyCanvas->pixelCanvas, canvas->pixelCanvas, sizeof(Tuple[canvas->width * canvas->height]));
    return copyCanvas;
}

// Returns the specified pixel from the canvas
Tuple canvasPixel(const Canvas *canvas, const size_t x, const size_t y)
{
    return canvas->pixelCanvas[x + y * canvas->width];
}

// Sets the specified pixel on the canvas
void canvasPixelWrite(Canvas *canvas, const size_t x, const size_t y, const Tuple pixel)
{
    canvas->pixelCanvas[x + y * canvas->width] = pixel;
}

// Returns the canvas width
size_t canvasWidth(const Canvas *canvas)
{
    return canvas->width;
}

// Returns the canvas height
size_t canvasHeight(const Canvas *canvas)
{
    return canvas->height;
}

// Returns a string with the canvas in PPM format
char *canvasPPM(const Canvas *canvas)
{
    Canvas *PPMCanvas = canvasCopy(canvas);
    for (size_t i = 0; i < canvasWidth(PPMCanvas) * canvasHeight(PPMCanvas); i++)
    {
        PPMCanvas->pixelCanvas[i] = tuplePPM(PPMCanvas->pixelCanvas[i]);
    }
    size_t bufferSize = sizeof(char) * snprintf(NULL, 0, "P3\n%lu %lu\n255\n", canvasWidth(PPMCanvas), canvasHeight(PPMCanvas));
    bufferSize += sizeof(char) * 4 * 3 * canvasWidth(PPMCanvas) * canvasHeight(PPMCanvas);
    char *buffer = malloc(bufferSize);
    if (buffer == NULL)
    {
        abort();
    }
    char *bufferPtr = buffer + sprintf(buffer, "P3\n%lu %lu\n255\n", canvasWidth(PPMCanvas), canvasHeight(PPMCanvas));
    for (size_t j = 0; j < canvasHeight(PPMCanvas); j++)
    {
        // size_t lineWidth = 1;
        for (size_t i = 0; i < canvasWidth(PPMCanvas); i++)
        {
            if (i == (canvasWidth(PPMCanvas) - 1) /* || lineWidth == 61*/)
            {
                bufferPtr += 1 + sprintf(bufferPtr, "%3.0f %3.0f %3.0f", PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].x,
                                         PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].y,
                                         PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].z);
                // if (lineWidth == 61)
                // {
                //     *(bufferPtr - 5) = '\n';
                //     *bufferPtr = ' ';
                // }
                // else
                // {
                *(bufferPtr - 1) = '\n';
                // }
                // lineWidth = 4;
            }
            else
            {
                // lineWidth += 12;
                bufferPtr += sprintf(bufferPtr, "%3.0f %3.0f %3.0f ", PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].x,
                                     PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].y,
                                     PPMCanvas->pixelCanvas[i + j * PPMCanvas->width].z);
            }
        }
    }
    *(bufferPtr - 1) = '\0';
    canvasDestroy(PPMCanvas);
    return buffer;
}

// 000 000 000 ... 000 000 000 |000n000 |000
//                            ^       ^
//                           65      67
// 255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\nXXX
// ^           ^           ^           ^           ^           ^
// 1          13          25          37          49          61
