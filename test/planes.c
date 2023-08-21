/*
 * planes.c - Draws three spheres with a plane as the floor and outputs it in PPM format on stdout
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

// TODO: Find a better solution than _XOPEN_SOURCE
#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif
#ifdef __unix__
#define _XOPEN_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>

#include "src/canvas.h"
#include "src/rays.h"
#include "src/vectors.h"

int main(void)
{
    Shape floor = plane(IDENTITY, MATERIAL);
    floor.material.color = color(1, 1, 1);
    floor.material.specular = 0;
    Shape middle = sphere(translation(-0.5, 1, 0.5), MATERIAL);
    middle.material.color = color(1, 1, 1);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    Shape right = sphere(mat4Mul(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)), MATERIAL);
    right.material.color = color(1, 1, 1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    Shape left = sphere(mat4Mul(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)), MATERIAL);
    left.material.color = color(1, 1, 1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    Light leftLight = light(-10, 10, -10, 1, 0, 0);
    Light middleLight = light(0, 10, -10, 0, 1, 0);
    Light rightLight = light(10, 10, -10, 0, 0, 1);
    World world = {3, 4, (Light[]){leftLight, middleLight, rightLight}, (Shape[]){floor, middle, right, left}};
    Camera camera = cameraInit(2000, 1000, M_PI / 3, viewTransform(point(0, 1.5, -5), point(0, 1, 0), vector(0, 1, 0)));
    Canvas *image = render(camera, world);
    char *imagePPM = canvasPPM(image);
    free(image);
    image = NULL;
    fputs(imagePPM, stdout);
    free(imagePPM);
    imagePPM = NULL;
    return 0;
}
