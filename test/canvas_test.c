/*
 * canvas.h - Tests on screen canvas implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "src/canvas.h"
#include "src/tuples.h"

#define EPSILON 0.00001
#define cr_expect_tuple_eq(a, b) cr_expect(all(epsilon_eq(dbl, a.x, b.x, EPSILON), epsilon_eq(dbl, a.y, b.y, EPSILON), epsilon_eq(a.z, b.z, EPSILON), eq(dbl, a.w, b.w, EPSILON)))

Test(canvas_operations, canvas_create_destroy)
{
    Canvas *canvas = canvasCreate(10, 20);
    cr_assert(eq(u64, canvasWidth(canvas), 10));
    cr_assert(eq(u64, canvasHeight(canvas), 20));
    canvasDestroy(canvas);
}

Test(canvas_operations, canvas_copy)
{
    Canvas *canvas = canvasCreate(10, 20);
    Canvas *copyCanvas = canvasCopy(canvas);
    cr_assert(eq(u64, canvasWidth(copyCanvas), 10));
    cr_assert(eq(u64, canvasHeight(copyCanvas), 20));
    canvasDestroy(copyCanvas);
    canvasDestroy(canvas);
}

Test(canvas_operations, canvas_write_read)
{
    Canvas *canvas = canvasCreate(10, 20);
    canvasPixelWrite(canvas, 2, 3, color(1, 0, 0));
    cr_expect_tuple_eq(canvasPixel(canvas, 2, 3), color(1, 0, 0));
    canvasDestroy(canvas);
}

Test(canvas_operations, canvas_ppm)
{
    char PPMStr1[] = "P3\n"
                     "5 3\n"
                     "255\n"
                     "255   0   0   0   0   0   0   0   0   0   0   0   0   0   0\n"
                     "  0   0   0   0   0   0   0 128   0   0   0   0   0   0   0\n"
                     "  0   0   0   0   0   0   0   0   0   0   0   0   0   0 255";
    char PPMStr2[] = "P3\n"
                     "10 2\n"
                     "255\n"
                     "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                     "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
                     "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
                     "153 255 204 153 255 204 153 255 204 153 255 204 153";
    Canvas *canvas = canvasCreate(5, 3);
    canvasPixelWrite(canvas, 0, 0, color(1.5, 0, 0));
    canvasPixelWrite(canvas, 2, 1, color(0, 0.5, 0));
    canvasPixelWrite(canvas, 4, 2, color(-0.5, 0, 1));
    Canvas *canvas2 = canvasCreate(10, 2);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            canvasPixelWrite(canvas2, j, i, color(1, 0.8, 0.6));
        }
    }
    char *canvasPPMBuff = canvasPPM(canvas);
    cr_expect(eq(str, PPMStr1, canvasPPMBuff));
    char *canvas2PPMBuff = canvasPPM(canvas2);
    cr_expect(eq(str, PPMStr2, canvas2PPMBuff));
    canvasDestroy(canvas);
    canvasDestroy(canvas2);
    free(canvasPPMBuff);
    free(canvas2PPMBuff);
    canvasPPMBuff = NULL;
    canvas2PPMBuff = NULL;
}
