/*
 * rays_test.c - Tests on ray and sphere intersections
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

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>

#include "src/canvas.h"
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

#define cr_expect_vec3_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON)))

#define cr_assert_vec3_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON)))

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
    Shape sphere = sphere(IDENTITY, MATERIAL);
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
    Shape sphere = sphere(IDENTITY, MATERIAL);
    Intersection i1 = {sphere, 1};
    Intersection i2 = {sphere, 2};
    Intersections xs;
    intersectionsCopy(&xs, &(Intersections){2, 2, (Intersection[2]){i2, i1}});
    Intersection i = hit(xs);
    cr_expect_intersection_eq(i, i1);
    intersectionsDestroy(&xs);
    Intersection i3 = {sphere, -1};
    Intersection i4 = {sphere, 1};
    Intersections xs2;
    intersectionsCopy(&xs2, &(Intersections){2, 2, (Intersection[2]){i4, i3}});
    i = hit(xs2);
    cr_expect_intersection_eq(i, i4);
    intersectionsDestroy(&xs2);
    Intersection i5 = {sphere, -2};
    Intersection i6 = {sphere, -1};
    Intersections xs3;
    intersectionsCopy(&xs3, &(Intersections){2, 2, (Intersection[2]){i6, i5}});
    i = hit(xs3);
    cr_expect(eq(int, i.shape.type, NO_HIT));
    intersectionsDestroy(&xs3);
    Intersection i7 = {sphere, 5};
    Intersection i8 = {sphere, 7};
    Intersection i9 = {sphere, -3};
    Intersection i10 = {sphere, 2};
    Intersections xs4;
    intersectionsCopy(&xs4, &(Intersections){4, 4, (Intersection[4]){i7, i8, i9, i10}});
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
    Shape sphere = sphere(scaling(2, 2, 2), MATERIAL);
    Intersections xs = intersect(sphere, ray);
    Intersection i1 = {sphere, 3};
    Intersection i2 = {sphere, 7};
    cr_assert(eq(sz, xs.size, 2));
    cr_expect_intersection_eq(xs.elem[0], i1);
    cr_expect_intersection_eq(xs.elem[1], i2);
    intersectionsDestroy(&xs);
    Ray ray2 = ray(0, 0, -5, 0, 0, 1);
    Shape sphere2 = sphere(translation(5, 0, 0), MATERIAL);
    Intersections xs2 = intersect(sphere2, ray2);
    cr_assert(eq(sz, xs2.size, 0));
    intersectionsDestroy(&xs2);
}

Test(sphere_operations, normal)
{
    Shape sphere = sphere(IDENTITY, MATERIAL);
    cr_expect_vector_eq(normal(sphere, point(1, 0, 0)), 1, 0, 0);
    cr_expect_vector_eq(normal(sphere, point(0, 1, 0)), 0, 1, 0);
    cr_expect_vector_eq(normal(sphere, point(0, 0, 1)), 0, 0, 1);
    cr_expect_vector_eq(normal(sphere, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3)), sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
    cr_expect_dbl(vec4Mag(normal(sphere, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3))), 1);
    Shape sphere2 = sphere(translation(0, 1, 0), MATERIAL);
    cr_expect_vector_eq(normal(sphere2, point(0, 1.70711, -0.70711)), 0, 0.70711, -0.70711);
    Shape sphere3 = sphere(mat4Mul(scaling(1, 0.5, 1), rotationZ(M_PI / 5)), MATERIAL);
    cr_expect_vector_eq(normal(sphere3, point(0, M_SQRT1_2, -M_SQRT1_2)), 0, 0.97014, -0.24254);
}

Test(materials, lighting)
{
    Material m = MATERIAL;
    Vec4 position = point(0, 0, 0);
    Vec4 vecEye = vector(0, 0, -1);
    Vec4 vecNormal = vector(0, 0, -1);
    Light light = light(0, 0, -10, 1, 1, 1);
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light, position, vecEye, vecNormal, false), (color(1.9, 1.9, 1.9)));
    Vec4 vecEye2 = vector(0, -M_SQRT1_2, -M_SQRT1_2);
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light, position, vecEye2, vecNormal, false), (color(1, 1, 1)));
    Light light2 = light(0, 10, -10, 1, 1, 1);
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light2, position, vecEye, vecNormal, false), (color(0.7364, 0.7364, 0.7364)));
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light2, position, vecEye2, vecNormal, false), (color(1.6364, 1.6364, 1.6364)));
    Light light3 = light(0, 0, 10, 1, 1, 1);
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light3, position, vecEye, vecNormal, false), (color(0.1, 0.1, 0.1)));
    cr_assert_vec3_eq(lighting(m, sphere(IDENTITY, m), light, position, vecEye, vecNormal, true), (color(0.1, 0.1, 0.1)));
}

Test(world, interesect_world)
{
    World world = defaultWorld();
    Ray ray = ray(0, 0, -5, 0, 0, 1);
    Intersections worldIntersections = intersectWorld(world, ray);
    cr_assert(eq(sz, worldIntersections.size, 4));
    cr_expect_dbl(worldIntersections.elem[0].t, 4);
    cr_expect_dbl(worldIntersections.elem[1].t, 4.5);
    cr_expect_dbl(worldIntersections.elem[2].t, 5.5);
    cr_expect_dbl(worldIntersections.elem[3].t, 6);
    intersectionsDestroy(&worldIntersections);
    worldDestroy(&world);
}

Test(sphere_operations, prepare_computations)
{
    Ray ray1 = ray(0, 0, -5, 0, 0, 1);
    Shape sphere1 = sphere(IDENTITY, MATERIAL);
    Intersection i1 = {sphere1, 4};
    Computations comps = prepareComputations(i1, ray1);
    Intersection compsIntersection = {comps.shape, comps.t};
    cr_expect_intersection_eq(compsIntersection, i1);
    cr_expect_point_eq(comps.point, 0, 0, -1);
    cr_expect_vector_eq(comps.camera, 0, 0, -1);
    cr_expect_vector_eq(comps.normal, 0, 0, -1);
    cr_expect(not(comps.inside));
    Ray ray2 = ray(0, 0, 0, 0, 0, 1);
    Intersection i2 = {sphere1, 1};
    Computations comps2 = prepareComputations(i2, ray2);
    cr_expect_point_eq(comps2.point, 0, 0, 1);
    cr_expect_vector_eq(comps2.camera, 0, 0, -1);
    cr_expect_vector_eq(comps2.normal, 0, 0, -1);
    cr_expect(comps2.inside);
    Shape sphere2 = sphere(translation(0, 0, 1), MATERIAL);
    Intersection i3 = {sphere2, 5};
    Computations comps3 = prepareComputations(i3, ray1);
    cr_expect(lt(dbl, comps3.overPoint.z, -MAT_EPSILON / 2));
    cr_expect(gt(dbl, comps3.point.z, comps.overPoint.z));
}

Test(world, shade_hit)
{
    World world1 = defaultWorld();
    Ray ray1 = ray(0, 0, -5, 0, 0, 1);
    Intersection i1 = {world1.shapes[0], 4};
    Computations comps1 = prepareComputations(i1, ray1);
    cr_expect_vec3_eq(shadeHit(world1, comps1), (color(0.38066, 0.47583, 0.2855)));
    worldDestroy(&world1);
    World world2 = defaultWorld();
    world2.lights[0] = light(0, 0.25, 0, 1, 1, 1);
    Ray ray2 = ray(0, 0, 0, 0, 0, 1);
    Intersection i2 = {world2.shapes[1], 0.5};
    Computations comps2 = prepareComputations(i2, ray2);
    cr_expect_vec3_eq(shadeHit(world2, comps2), (color(0.90498, 0.90498, 0.90498)));
    worldDestroy(&world2);
    Shape sphere1 = sphere(IDENTITY, MATERIAL);
    Shape sphere2 = sphere(translation(0, 0, 10), MATERIAL);
    World world3 = {1, 2, &(Light){point(0, 0, -10), color(1, 1, 1)},
                    (Shape[2]){sphere1, sphere2}};
    Ray ray3 = ray(0, 0, 5, 0, 0, 1);
    Intersection i3 = {sphere2, 4};
    Computations comps3 = prepareComputations(i3, ray3);
    cr_expect_vec3_eq(shadeHit(world3, comps3), (color(0.1, 0.1, 0.1)));
}

Test(world, color_at)
{
    World world1 = defaultWorld();
    Ray ray1 = ray(0, 0, -5, 0, 1, 0);
    Ray ray2 = ray(0, 0, -5, 0, 0, 1);
    cr_expect_vec3_eq(colorAt(world1, ray1), (color(0, 0, 0)));
    cr_expect_vec3_eq(colorAt(world1, ray2), (color(0.38066, 0.47583, 0.2855)));
    worldDestroy(&world1);
    World world2 = defaultWorld();
    world2.shapes[0].material.ambient = 1;
    world2.shapes[1].material.ambient = 1;
    Ray ray3 = ray(0, 0, 0.75, 0, 0, -1);
    cr_expect_vec3_eq(colorAt(world2, ray3), world2.shapes[1].material.color);
    worldDestroy(&world2);
}

Test(world, camera)
{
    const Camera cameraH = cameraInit(200, 125, M_PI_2, IDENTITY);
    cr_expect_dbl(cameraH.pixelSize, 0.01);
    const Camera cameraV = cameraInit(125, 200, M_PI_2, IDENTITY);
    cr_expect_dbl(cameraV.pixelSize, 0.01);
}

Test(world, ray_pixel)
{
    Camera camera1 = cameraInit(201, 101, M_PI_2, IDENTITY);
    Ray ray1 = rayPixel(camera1, 100, 50);
    cr_expect_point_eq(ray1.origin, 0, 0, 0);
    cr_expect_vector_eq(ray1.direction, 0, 0, -1);
    Ray ray2 = rayPixel(camera1, 0, 0);
    cr_expect_point_eq(ray2.origin, 0, 0, 0);
    cr_expect_vector_eq(ray2.direction, 0.66519, 0.33259, -0.66851);
    Camera camera2 = cameraInit(201, 101, M_PI_2, mat4Mul(rotationY(M_PI_4), translation(0, -2, 5)));
    Ray ray3 = rayPixel(camera2, 100, 50);
    cr_expect_point_eq(ray3.origin, 0, 2, -5);
    cr_expect_vector_eq(ray3.direction, M_SQRT1_2, 0, -M_SQRT1_2);
}

Test(world, render)
{
    World world = defaultWorld();
    Camera camera = cameraInit(11, 11, M_PI_2, viewTransform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0)));
    Canvas *image = render(camera, world);
    cr_expect_vec3_eq(canvasPixel(image, 5, 5), (color(0.38066, 0.47583, 0.2855)));
    worldDestroy(&world);
    free(image);
    image = NULL;
}

Test(world, is_shadowed)
{
    World world = defaultWorld();
    cr_expect(not(isShadowed(world, 0, point(0, 10, 0))));
    cr_expect(isShadowed(world, 0, point(10, -10, 10)));
    cr_expect(not(isShadowed(world, 0, point(-20, 20, -20))));
    cr_expect(not(isShadowed(world, 0, point(-2, 2, -2))));
    worldDestroy(&world);
}

Test(plane_operations, normal)
{
    Shape plane = plane(IDENTITY, MATERIAL);
    cr_expect_vector_eq(normal(plane, point(0, 0, 0)), 0, 1, 0);
    cr_expect_vector_eq(normal(plane, point(10, 0, -10)), 0, 1, 0);
    cr_expect_vector_eq(normal(plane, point(-5, 0, 150)), 0, 1, 0);
}

Test(plane_operations, intersect)
{
    Shape plane = plane(IDENTITY, MATERIAL);
    Ray ray1 = ray(0, 10, 0, 0, 0, 1);
    Intersections xs1 = intersect(plane, ray1);
    cr_assert(eq(sz, xs1.size, 0));
    intersectionsDestroy(&xs1);
    Ray ray2 = ray(0, 0, 0, 0, 0, 1);
    Intersections xs2 = intersect(plane, ray2);
    cr_assert(eq(sz, xs2.size, 0));
    intersectionsDestroy(&xs2);
    Ray ray3 = ray(0, 1, 0, 0, -1, 0);
    Intersection i1 = {plane, 1};
    Intersections xs3 = intersect(plane, ray3);
    cr_assert(eq(sz, xs3.size, 1));
    cr_expect_intersection_eq(xs3.elem[0], i1);
    intersectionsDestroy(&xs3);
    Ray ray4 = ray(0, -1, 0, 0, 1, 0);
    Intersections xs4 = intersect(plane, ray4);
    cr_expect_intersection_eq(xs4.elem[0], i1);
    intersectionsDestroy(&xs4);
}

Test(patterns, stripe_pattern)
{
    const Vec3 black = color(0, 0, 0);
    const Vec3 white = color(1, 1, 1);
    StripePattern pattern = stripePattern(white, black, IDENTITY);
    cr_expect_vec3_eq(pattern.a, white);
    cr_expect_vec3_eq(pattern.b, black);
    cr_expect_vec3_eq(stripeAt(pattern, point(0, 0, 0)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(0, 1, 0)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(0, 2, 0)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(0, 0, 1)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(0, 0, 2)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(0.9, 0, 0)), white);
    cr_expect_vec3_eq(stripeAt(pattern, point(1, 0, 0)), black);
    cr_expect_vec3_eq(stripeAt(pattern, point(-0.1, 0, 0)), black);
    cr_expect_vec3_eq(stripeAt(pattern, point(-1, 0, 0)), black);
    cr_expect_vec3_eq(stripeAt(pattern, point(-1.1, 0, 0)), white);
}

Test(materials, pattern)
{
    Material m;
    m.ambient = 1;
    m.diffuse = 0;
    m.specular = 0;
    m.pattern = stripePattern(color(1, 1, 1), color(0, 0, 0), IDENTITY);
    m.hasPattern = true;
    Vec4 eyev = vector(0, 0, -1);
    Vec4 normalv = vector(0, 0, -1);
    Light light = light(0, 0, -10, 1, 1, 1);
    Vec3 c1 = lighting(m, sphere(IDENTITY, m), light, point(0.9, 0, 0), eyev, normalv, false);
    Vec3 c2 = lighting(m, sphere(IDENTITY,m), light, point(1.1, 0, 0), eyev, normalv, false);
    cr_expect_vec3_eq(c1, (color(1, 1, 1)));
    cr_expect_vec3_eq(c2, (color(0, 0, 0)));
}

Test(patterns, transformations)
{
    const Vec3 white = color(1, 1, 1);
    const Vec3 black = color(0, 0, 0);
    Shape sphere1 = sphere(scaling(2, 2, 2), MATERIAL);
    sphere1.material.hasPattern = true;
    sphere1.material.pattern = stripePattern(white, black, IDENTITY);
    const Vec3 c1 = stripeAtObject(sphere1, point(1.5, 0, 0));
    cr_expect_vec3_eq(c1, white);
    Shape sphere2 = sphere(IDENTITY, MATERIAL);
    sphere2.material.hasPattern = true;
    sphere2.material.pattern = stripePattern(white, black, scaling(2, 2, 2));
    const Vec3 c2 = stripeAtObject(sphere2, point(1.5, 0, 0));
    cr_expect_vec3_eq(c2, white);
    Shape sphere3 = sphere(scaling(2, 2, 2), MATERIAL);
    sphere3.material.hasPattern = true;
    sphere3.material.pattern = stripePattern(white, black, translation(0.5, 0, 0));
    const Vec3 c3 = stripeAtObject(sphere3, point(2.5, 0, 0));
    cr_expect_vec3_eq(c3, white);
}
