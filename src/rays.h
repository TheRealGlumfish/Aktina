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

#define MATERIAL (Material){{{1, 1, 1}}, 0.1, 0.9, 0.9, 200, false}

#define material(r, g, b, ambient, diffuse, specular, shininess) (Material){{{r, g, b}}, ambient, diffuse, specular, shininess}

#define light(x, y, z, r, g, b) (Light){point(x, y, z), {{r, g, b}}}

#define sphere(transform, material) (Shape){SPHERE, transform, mat4Inv(transform), material}

#define plane(transform, material) (Shape){PLANE, transform, mat4Inv(transform), material}

// clang-format on

typedef struct
{
    Vec4 origin;
    Vec4 direction;
} Ray;

typedef enum
{
    SPHERE,
    PLANE,
    NO_HIT
} ShapeType;

typedef struct
{
    Vec3 a;
    Vec3 b;
    Mat4 transform;
    Mat4 transformInv;
} StripePattern;

// TODO: Check best way to pack struct
typedef struct
{
    Vec3 color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;
    bool hasPattern;
    StripePattern pattern;
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
    double t;
    Vec4 point;
    Vec4 overPoint;
    Vec4 camera;
    Vec4 normal;
    bool inside;
} Computations;

typedef struct
{
    size_t hsize;
    size_t vsize;
    double fov;
    double pixelSize;
    double halfWidth;
    double halfHeight;
    Mat4 transform;
    Mat4 transformInv;
} Camera;

// typedef struct
// {
//     Vec3 (*function)(Vec4, const void*);
//     void *parameters;
// } Pattern;
// typedef enum
// {
//     STRIPPED
// } PatternType;

void intersectionsCreate(Intersections *dest, size_t size);
void intersectionsCopy(Intersections *dest, const Intersections *src);
void intersectionsDestroy(Intersections *dest);
void intersectionsSort(Intersections *dest);
void intersectionsResize(Intersections *dest, size_t size);
void intersectionsPush(Intersections *dest, Intersection intersection);
Intersection intersectionPop(Intersections *dest);

Vec4 rayPos(Ray ray, double t);
Ray rayTransform(Ray ray, Mat4 mat);
Ray rayPixel(Camera camera, size_t x, size_t y);

Intersections intersect(Shape shape, Ray ray);
Intersection hit(Intersections intersections);
Vec4 normal(Shape shape, Vec4 point);
Vec3 lighting(Material material, Shape object, Light light, Vec4 point, Vec4 eye, Vec4 normal, bool inShadow);

void worldDestroy(World *world);
World defaultWorld(void);
Intersections intersectWorld(World world, Ray ray);

bool isShadowed(World world, size_t lightIndex, Vec4 point);
Computations prepareComputations(Intersection intersection, Ray ray);
Vec3 shadeHit(World world, Computations computations);
Vec3 colorAt(World world, Ray ray);

Camera cameraInit(size_t hsize, size_t vsize, double fov, Mat4 transform);
Canvas *render(Camera camera, World world);

// Vec3 defaultPattern(Vec4 point, const void *parameters);
StripePattern stripePattern(Vec3 colorA, Vec3 colorB, Mat4 transform);
Vec3 stripeAt(StripePattern pattern, Vec4 point);
Vec3 stripeAtObject(Shape shape, Vec4 point);
