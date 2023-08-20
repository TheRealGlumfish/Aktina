/*
 * rays.h - Ray and sphere intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <stdbool.h>
#include <stddef.h>

#include "canvas.h"
#include "vectors.h"

// clang-format off
#define ray(x, y, z, xdir, ydir, zdir) (Ray){point(x, y, z), vector(xdir, ydir, zdir)}

#define MATERIAL (Material){{{1, 1, 1}}, 0.1, 0.9, 0.9, 200}

#define material(r, g, b, ambient, diffuse, specular, shininess) (Material){{{r, g, b}}, ambient, diffuse, specular, shininess}

#define light(x, y, z, r, g, b) (Light){point(x, y, z), {{r, g, b}}}

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
    size_t lightCount;
    size_t shapeCount;
    Light *lights;
    Shape *shapes;
} World;

typedef struct
{
    Shape shape;
    double t;
} Intersection;

typedef struct
{
    size_t size;
    size_t capacity;
    Intersection *elem;
} Intersections;

typedef struct
{
    Shape shape;
    float t;
    Vec4 point;
    Vec4 camera;
    Vec4 normal;
    bool inside;
} Computations;

typedef struct
{
    size_t hsize;
    size_t vsize;
    float fov;
    float pixelSize;
    float halfWidth;
    float halfHeight;
    Mat4 transform;
    Mat4 transformInv;
} Camera;

void intersectionsCreate(Intersections *dest, size_t size);
void intersectionsCopy(Intersections *dest, const Intersections *src);
void intersectionsDestroy(Intersections *dest);
void intersectionsSort(Intersections *dest);
void intersectionResize(Intersections *dest, size_t size);
void intersectionsInsert(Intersections *dest, Intersection intersection);

Vec4 rayPos(Ray ray, double t);
Ray rayTransform(Ray ray, Mat4 mat);
Ray rayPixel(Camera camera, size_t x, size_t y);

Intersections intersect(Shape shape, Ray ray);
Intersection hit(Intersections intersections);
Vec4 normal(Shape shape, Vec4 point);
Vec3 lighting(Material material, Light light, Vec4 point, Vec4 eye, Vec4 normal);

void worldDestroy(World *world);
World defaultWorld(void);
Intersections intersectWorld(World world, Ray ray);

Computations prepareComputations(Intersection intersection, Ray ray);
Vec3 shadeHit(World world, Computations computations);
Vec3 colorAt(World world, Ray ray);

Camera cameraInit(size_t hsize, size_t vsize, float fov, Mat4 transform);
Canvas *render(Camera camera, World world);
