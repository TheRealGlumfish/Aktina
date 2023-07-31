/*
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <stdbool.h>

#include "vectors.h"

// clang-format off
#define ray(x, y, z, xdir, ydir, zdir) (Ray){point(x, y, z), vector(0, 0, 1)}
// clang-format on

typedef struct
{
    Vec4 origin;
    Vec4 direction;
} Ray;

typedef struct
{
} Sphere;

typedef struct
{
    bool hasIntersect;
    Vec2 tVal;
} Intersections;

Vec4 rayPos(Ray ray, double t);
Intersections intersect(Sphere sphere, Ray ray);
