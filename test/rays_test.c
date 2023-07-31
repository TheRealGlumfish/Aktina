/*
 * rays_test.c - Tests on ray intersections
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "src/rays.h"

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
    Sphere sphere;
    Intersections xs1 = intersect(sphere, ray1);
    cr_assert(xs1.hasIntersect);
    cr_expect_dbl(xs1.tVal.x, 4);
    cr_expect_dbl(xs1.tVal.y, 6);
    Ray ray2 = ray(0, 1, -5, 0, 0, 1);
    Intersections xs2 = intersect(sphere, ray2);
    cr_assert(xs2.hasIntersect);
    cr_expect_dbl(xs2.tVal.x, 5);
    cr_expect_dbl(xs2.tVal.y, 5);
    Ray ray3 = ray(0, 2, -5, 0, 0, 1);
    Intersections xs3 = intersect(sphere, ray3);
    cr_expect(not(xs3.hasIntersect));
    Ray ray4 = ray(0, 0, 0, 0, 0, 1);
    Intersections xs4 = intersect(sphere, ray4);
    cr_assert(xs4.hasIntersect);
    cr_expect_dbl(xs4.tVal.x, -1);
    cr_expect_dbl(xs4.tVal.y, 1);
    Ray ray5 = ray(0, 0, 5, 0, 0, 1);
    Intersections xs5 = intersect(sphere, ray5);
    cr_assert(xs5.hasIntersect);
    cr_expect_dbl(xs5.tVal.x, -6);
    cr_expect_dbl(xs5.tVal.y, -4);
}
