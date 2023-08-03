/*
 * rays.h - Ray and sphere intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <stdbool.h>
#include <stddef.h>

#include "vectors.h"

// clang-format off
#define ray(x, y, z, xdir, ydir, zdir) (Ray){point(x, y, z), vector(xdir, ydir, zdir)}

#define sphere(transform) (Shape){SPHERE, transform}
// clang-format on

typedef struct
{
    Vec4 origin;
    Vec4 direction;
} Ray;

typedef enum
{
    SPHERE,
    NO_HIT
} ShapeType;

typedef struct
{
    ShapeType type;
    Mat4 transform;
} Shape;

typedef struct
{
    Shape shape;
    double t;
} Intersection;

typedef struct
{
    size_t size;
    Intersection *elem;
} Intersections;

void intersectionsCreate(Intersections *dest, size_t size);
void intersectionsCopy(Intersections *dest, const Intersections *src);
void intersectionsDestroy(Intersections *dest);
void intersectionsSort(Intersections *dest);

Vec4 rayPos(Ray ray, double t);
Ray rayTransform(Ray ray, Mat4 mat);

Intersections intersect(Shape shape, Ray ray);
Intersection hit(Intersections intersections);
