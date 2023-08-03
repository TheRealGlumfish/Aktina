/*
 * rays_test.c - Tests on ray and sphere intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "src/rays.h"
#include "src/vectors.h"

#define EPSILON 0.00001

#define cr_expect_dbl(actual, expected) cr_expect(epsilon_eq(dbl, actual, expected, EPSILON))

#define cr_assert_dbl(actual, expected) cr_assert(epsilon_eq(dbl, actual, expected, EPSILON))

#define cr_expect_point_eq(actual, a, b, c) cr_expect(all(epsilon_eq(dbl, actual.x, a, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, b, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, c, EPSILON), \
                                                          epsilon_eq(dbl, actual.w, 1, EPSILON)))

#define cr_assert_point_eq(actual, a, b, c) cr_assert(all(epsilon_eq(dbl, actual.x, a, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, b, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, c, EPSILON), \
                                                          epsilon_eq(dbl, actual.w, 1, EPSILON)))

#define cr_expect_vector_eq(actual, a, b, c) cr_expect(all(epsilon_eq(dbl, actual.x, a, EPSILON), \
                                                           epsilon_eq(dbl, actual.y, b, EPSILON), \
                                                           epsilon_eq(dbl, actual.z, c, EPSILON), \
                                                           epsilon_eq(dbl, actual.w, 0, EPSILON)))

#define cr_assert_vector_eq(actual, a, b, c) cr_assert(all(epsilon_eq(dbl, actual.x, a, EPSILON), \
                                                           epsilon_eq(dbl, actual.y, b, EPSILON), \
                                                           epsilon_eq(dbl, actual.z, c, EPSILON), \
                                                           epsilon_eq(dbl, actual.w, 0, EPSILON)))

// TODO: Add comparison to the shape parameter
#define shape_eq(actual, expected) all(eq(int, actual.type, expected.type))

#define cr_expect_intersection_eq(actual, expected) cr_expect(all(shape_eq(actual.shape, expected.shape), epsilon_eq(dbl, actual.t, expected.t, EPSILON)))

#define cr_assert_intersection_eq(actual, expected) cr_assert(all(shape_eq(actual.shape, expected.shape), epsilon_eq(dbl, actual.t, expected.t, EPSILON)))

Test(ray_operations, position)
{
    Ray ray = (Ray){point(2, 3, 4), vector(1, 0, 0)};
    cr_expect_point_eq(rayPos(ray, 0), 2, 3, 4);
    cr_expect_point_eq(rayPos(ray, 1), 3, 3, 4);
    cr_expect_point_eq(rayPos(ray, -1), 1, 3, 4);
    cr_expect_point_eq(rayPos(ray, 2.5), 4.5, 3, 4);
}

Test(sphere_operations, interesect)
{
    Ray ray1 = ray(0, 0, -5, 0, 0, 1);
    Shape sphere = sphere(IDENTITY);
    Intersections xs1 = intersect(sphere, ray1);
    Intersection i1 = {sphere, 4};
    Intersection i2 = {sphere, 6};
    cr_assert(eq(sz, xs1.size, 2));
    cr_expect_intersection_eq(xs1.elem[0], i1);
    cr_expect_intersection_eq(xs1.elem[1], i2);
    intersectionsDestroy(&xs1);
    Ray ray2 = ray(0, 1, -5, 0, 0, 1);
    Intersections xs2 = intersect(sphere, ray2);
    Intersection i3 = {sphere, 5};
    Intersection i4 = {sphere, 5};
    cr_assert(eq(sz, xs2.size, 2));
    cr_expect_intersection_eq(xs2.elem[0], i3);
    cr_expect_intersection_eq(xs2.elem[1], i4);
    intersectionsDestroy(&xs2);
    Ray ray3 = ray(0, 2, -5, 0, 0, 1);
    Intersections xs3 = intersect(sphere, ray3);
    cr_assert(eq(sz, xs3.size, 0));
    intersectionsDestroy(&xs3);
    Ray ray4 = ray(0, 0, 0, 0, 0, 1);
    Intersections xs4 = intersect(sphere, ray4);
    Intersection i5 = {sphere, -1};
    Intersection i6 = {sphere, 1};
    cr_assert(eq(sz, xs4.size, 2));
    cr_expect_intersection_eq(xs4.elem[0], i5);
    cr_expect_intersection_eq(xs4.elem[1], i6);
    intersectionsDestroy(&xs4);
    Ray ray5 = ray(0, 0, 5, 0, 0, 1);
    Intersections xs5 = intersect(sphere, ray5);
    Intersection i7 = {sphere, -6};
    Intersection i8 = {sphere, -4};
    cr_assert(eq(sz, xs5.size, 2));
    cr_expect_intersection_eq(xs5.elem[0], i7);
    cr_expect_intersection_eq(xs5.elem[1], i8);
    intersectionsDestroy(&xs5);
}

Test(sphere_operations, hit)
{
    Shape sphere = sphere(IDENTITY);
    Intersection i1 = {sphere, 1};
    Intersection i2 = {sphere, 2};
    Intersections xs;
    intersectionsCopy(&xs, &(Intersections){2, (Intersection[2]){i2, i1}});
    Intersection i = hit(xs);
    cr_expect_intersection_eq(i, i1);
    intersectionsDestroy(&xs);
    Intersection i3 = {sphere, -1};
    Intersection i4 = {sphere, 1};
    Intersections xs2;
    intersectionsCopy(&xs2, &(Intersections){2, (Intersection[2]){i4, i3}});
    i = hit(xs2);
    cr_expect_intersection_eq(i, i4);
    intersectionsDestroy(&xs2);
    Intersection i5 = {sphere, -2};
    Intersection i6 = {sphere, -1};
    Intersections xs3;
    intersectionsCopy(&xs3, &(Intersections){2, (Intersection[2]){i6, i5}});
    i = hit(xs3);
    cr_expect(eq(int, i.shape.type, NO_HIT));
    intersectionsDestroy(&xs3);
    Intersection i7 = {sphere, 5};
    Intersection i8 = {sphere, 7};
    Intersection i9 = {sphere, -3};
    Intersection i10 = {sphere, 2};
    Intersections xs4;
    intersectionsCopy(&xs4, &(Intersections){4, (Intersection[4]){i7, i8, i9, i10}});
    i = hit(xs4);
    cr_expect_intersection_eq(i, i10);
    intersectionsDestroy(&xs4);
}

Test(ray_operations, transform)
{
    Ray ray = ray(1, 2, 3, 0, 1, 0);
    Mat4 matA = translation(3, 4, 5);
    Ray ray2 = rayTransform(ray, matA);
    cr_expect_point_eq(ray2.origin, 4, 6, 8);
    cr_expect_vector_eq(ray2.direction, 0, 1, 0);
    Ray ray3 = ray(1, 2, 3, 0, 1, 0);
    Mat4 matB = scaling(2, 3, 4);
    Ray ray4 = rayTransform(ray3, matB);
    cr_expect_point_eq(ray4.origin, 2, 6, 12);
    cr_expect_vector_eq(ray4.direction, 0, 3, 0);
}

Test(sphere_operations, transform)
{
    Ray ray = ray(0, 0, -5, 0, 0, 1);
    Shape sphere = sphere(scaling(2, 2, 2));
    Intersections xs = intersect(sphere, ray);
    Intersection i1 = {sphere, 3};
    Intersection i2 = {sphere, 7};
    cr_assert(eq(sz, xs.size, 2));
    cr_expect_intersection_eq(xs.elem[0], i1);
    cr_expect_intersection_eq(xs.elem[1], i2);
    intersectionsDestroy(&xs);
    Ray ray2 = ray(0, 0, -5, 0, 0, 1);
    Shape sphere2 = sphere(translation(5, 0, 0));
    Intersections xs2 = intersect(sphere2, ray2);
    cr_assert(eq(sz, xs2.size, 0));
    intersectionsDestroy(&xs2);
}