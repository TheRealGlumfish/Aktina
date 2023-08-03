/*
 * rays.c - Ray and sphere intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "rays.h"
#include "vectors.h"

// Intersection collection constructor.
// If the allocation fails, size is set to zero.
// Important: size must be greater than 0.
void intersectionsCreate(Intersections *dest, const size_t size)
{
    dest->elem = malloc(sizeof(Intersection[size]));
    if (dest->elem == NULL)
    {
        dest->size = 0;
    }
    else
    {
        dest->size = size;
    }
}

// Intersection collection copy constructor.
// If the allocation fails, size is set to zero.
// Important: size must be greater than 0.
void intersectionsCopy(Intersections *dest, const Intersections *src)
{
    dest->elem = malloc(sizeof(Intersection[src->size]));
    if (dest->elem == NULL)
    {
        dest->size = 0;
    }
    else
    {
        dest->size = src->size;
        memcpy(dest->elem, src->elem, sizeof(Intersection[dest->size]));
    }
    intersectionsSort(dest);
}

// Intersection collection destructor
void intersectionsDestroy(Intersections *dest)
{
    free(dest->elem);
    dest->size = 0;
    dest->elem = NULL;
}

// Compares two intersection elements
int intersectionCmp(const void *a, const void *b)
{
    if (fabs(((const Intersection *)a)->t - ((const Intersection *)b)->t) <= MAT_EPSILON)
    {
        return 0;
    }
    else if (((const Intersection *)a)->t > ((const Intersection *)b)->t)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

// Sorts an intersection collection
void intersectionsSort(Intersections *dest)
{
    qsort(dest->elem, dest->size, sizeof(Intersection), intersectionCmp);
}

// Returns a point on the ray
Vec4 rayPos(const Ray ray, const double t)
{
    return vec4Add(ray.origin, vec4Mul(ray.direction, t));
}

// Returns a ray that has been transformed by a transformation matrix
Ray rayTransform(Ray ray, const Mat4 mat)
{
    ray.origin = mat4VecMul(mat, ray.origin);
    ray.direction = mat4VecMul(mat, ray.direction);
    return ray;
}

// Returns the intersection between a shape and a ray.
Intersections intersect(const Shape shape, Ray ray)
{
    switch (shape.type)
    {
    case SPHERE:
    {
        ray = rayTransform(ray, mat4Inv(shape.transform));
        // NOTE: It may be faster to do these opertions using Vec3 functions
        const Vec4 sphereToRay = vec4Sub(ray.origin, point(0, 0, 0));
        const double a = vec4Dot(ray.direction, ray.direction);
        const double b = 2 * vec4Dot(ray.direction, sphereToRay);
        const double c = vec4Dot(sphereToRay, sphereToRay) - 1;
        const double discriminant = (b * b) - (4 * a * c);
        Intersections sphereIntersection; // TODO: Rename
        if (discriminant < 0)
        {
            sphereIntersection.size = 0;
            sphereIntersection.elem = NULL;
            return sphereIntersection;
        }
        double point1 = (-b - sqrt(discriminant)) / (2 * a);
        double point2 = (-b + sqrt(discriminant)) / (2 * a);
        Intersection intersectionPoints[2] = {{shape, point1}, {shape, point2}};
        // TODO: Do manually (no intersectionsCopy) to avoid sorting
        intersectionsCopy(&sphereIntersection, &(Intersections){2, intersectionPoints});
        if (sphereIntersection.elem == NULL)
        {
            abort();
        }
        return sphereIntersection;
        break;
    }
    default:
        abort(); // TODO: Remove
    }
}

// Returns the "hit" (first non-negative) intersection.
// If a "hit" does exist, an intersection with a `NO_HIT` shape type is returned.
// Important: The intersection collection needs to be sorted.
Intersection hit(const Intersections intersections)
{
    for (size_t i = 0; i < intersections.size; i++)
    {
        if (intersections.elem[i].t >= 0)
        {
            return intersections.elem[i];
        }
    }
    return (Intersection){{NO_HIT, {{0}}}, -1};
}
