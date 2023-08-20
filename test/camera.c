/*
 * camera.c - Draws three spheres and outputs it in PPM format on stdout
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
    Shape floor = sphere(scaling(10, 0.01, 10), MATERIAL);
    floor.material.color = color(1, 0.9, 0.9);
    floor.material.specular = 0;
    Shape leftWall = sphere(mat4Mul(mat4Mul(translation(0, 0, 5), rotationY(-M_PI_4)),
                                    mat4Mul(rotationX(M_PI_2), scaling(10, 0.01, 10))),
                            floor.material);
    Shape rightWall = sphere(mat4Mul(mat4Mul(translation(0, 0, 5), rotationY(M_PI_4)),
                                    mat4Mul(rotationX(M_PI_2), scaling(10, 0.01, 10))),
                            floor.material);
    Shape middle = sphere(translation(-0.5, 1, 0.5), MATERIAL);
    middle.material.color = color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;
    Shape right = sphere(mat4Mul(translation(1.5, 0.5, -0.5), scaling(0.5, 0.5, 0.5)), MATERIAL);
    right.material.color = color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;
    Shape left = sphere(mat4Mul(translation(-1.5, 0.33, -0.75), scaling(0.33, 0.33, 0.33)), MATERIAL);
    left.material.color = color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;
    World world = {1, 6, &light(-10, 10, -10, 1, 1, 1), (Shape []){floor, leftWall, rightWall, middle, right, left}};
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
