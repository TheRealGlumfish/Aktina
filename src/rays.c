/*
 * rays.c - Ray intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>

#include "rays.h"
#include "vectors.h"

Vec4 rayPos(const Ray ray, const double t)
{
    return vec4Add(ray.origin, vec4Mul(ray.direction, t));
}

Intersections intersect(const Sphere sphere, const Ray ray)
{
    Vec4 sphereToRay = vec4Sub(ray.origin, point(0, 0, 0));
    double a = vec4Dot(ray.direction, ray.direction);
    double b = 2 * vec4Dot(ray.direction, sphereToRay);
    double c = vec4Dot(sphereToRay, sphereToRay) - 1;
    double discriminant = (b * b) - (4 * a * c);
    if (discriminant < 0)
    {
        return (Intersections){false};
    }
    Vec2 tValues;
    tValues.x = (-b - sqrt(discriminant)) / (2 * a);
    tValues.y = (-b + sqrt(discriminant)) / (2 * a);
    return (Intersections){true, tValues};
}
