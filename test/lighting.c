/*
 * lighting.c - Draws a shaded sphere on the canvas and outputs it in PPM format on stdout
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
    sphere.material.color = color(0, 0, 1);
    const Light light = light(0, 5, 4, 1, 1, 1);
    const Vec4 cameraOrigin = point(2.5, 2.5, 0);
    const double canvasX = 0;
    const double canvasY = 5;
    const double canvasZ = 10;
    const double canvasSize = 5;
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
                Vec4 hitPoint = rayPos(cameraRay, cameraHit.t);
                Vec4 hitNormal = normal(sphere, hitPoint);
                Vec3 pointColor = lighting(sphere.material, light, hitPoint,
                                           vec4Neg(vec4Norm(cameraRay.direction)), hitNormal, false);
                canvasPixelWrite(canvas, i, j, pointColor);
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
