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

#define MATERIAL (Material){{{1, 1, 1}}, 0.1, 0.9, 0.9, 200}

#define light(x, y, z, r, g, b) (Light){point(x, y, z), {{r, g, b}}};

#define sphere(transform, material) (Shape){SPHERE, transform, mat4Inv(transform), material}
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
    Vec3 color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
} Material;

typedef struct
{
    ShapeType type;
    Mat4 transform;
    Mat4 transformInv;
    Material material;
} Shape;

typedef struct
{
    Vec4 position;
    Vec3 intensity;
} Light;

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
Vec4 normal(Shape shape, Vec4 point);
Vec3 lighting(Material material, Light light, Vec4 point, Vec4 eye, Vec4 normal);
