/*
 * sphere.c - Draws two spheres on the canvas and outputs it in PPM format on stdout
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

#include "src/canvas.h"
#include "src/rays.h"

int main(void)
{
    Canvas *canvas = canvasCreate(2048, 2048);
    Shape sphere = sphere(mat4Mul(translation(2.5, 2.5, 9), scaling(2, 2, 2)), MATERIAL);
    Shape sphere2 = sphere(translation(1.8, 3.2, 8), MATERIAL);
    Vec3 sphereColor = {{255, 0, 0}};
    Vec3 sphere2Color = {{0, 255, 0}};
    Vec4 cameraOrigin = point(2.5, 2.5, 0);
    double canvasX = 0;
    double canvasY = 5;
    double canvasZ = 10;
    double canvasSize = 5;
    Vec4 canvasPoint = point(canvasX, canvasY, canvasZ);
    Ray cameraRay = {.origin = cameraOrigin};
    for (size_t i = 0; i < canvasWidth(canvas); i++)
    {
        for (size_t j = 0; j < canvasHeight(canvas); j++)
        {
            canvasPoint.x = canvasX + ((double)i / canvasWidth(canvas)) * canvasSize;
            canvasPoint.y = canvasY - ((double)j / canvasHeight(canvas)) * canvasSize;
            cameraRay.direction = vec4Sub(canvasPoint, cameraOrigin);
            Intersections cameraIntersections = intersect(sphere, cameraRay);
            Intersection cameraHit = hit(cameraIntersections);
            if (cameraHit.shape.type == SPHERE)
            {
                canvasPixelWrite(canvas, i, j, sphereColor);
            }
            intersectionsDestroy(&cameraIntersections);
            cameraIntersections = intersect(sphere2, cameraRay);
            cameraHit = hit(cameraIntersections);
            if (cameraHit.shape.type == SPHERE)
            {
                canvasPixelWrite(canvas, i, j, sphere2Color);
            }
            intersectionsDestroy(&cameraIntersections);
        }
    }
    char *ppmOutput = canvasPPM(canvas);
    fputs(ppmOutput, stdout);
    free(canvas);
    canvas = NULL;
    free(ppmOutput);
    ppmOutput = NULL;
    return 0;
}
