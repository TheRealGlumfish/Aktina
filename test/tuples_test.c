/*
 * operations.c - Tests for operations on tuples
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>

#include "src/tuples.h"

#define EPSILON 0.00001
#define cr_expect_tuple_eq(a, b) cr_expect(all(epsilon_eq(dbl, a.x, b.x, EPSILON), epsilon_eq(dbl, a.y, b.y, EPSILON), epsilon_eq(a.z, b.z, EPSILON), eq(dbl, a.w, b.w, EPSILON)))

Test(tuple_operations, point_and_vector)
{
    cr_expect_tuple_eq(point(4, -4, 3), ((Tuple){4, -4, 3, 1}));
    cr_expect_tuple_eq(vector(4, -4, 3), ((Tuple){4, -4, 3, 0}));
}

Test(tuple_operations, tuple_add)
{
    cr_expect_tuple_eq(tupleAdd((Tuple){3, -2, 5, 1}, (Tuple){-2, 3, 1, 0}), ((Tuple){1, 1, 6, 1}));
}

Test(tuple_operations, tuple_subtract)
{
    cr_expect_tuple_eq(tupleSub(point(3, 2, 1), point(5, 6, 7)), vector(-2, -4, -6));
    cr_expect_tuple_eq(tupleSub(point(3, 2, 1), vector(5, 6, 7)), point(-2, -4, -6));
    cr_expect_tuple_eq(tupleSub(vector(3, 2, 1), vector(5, 6, 7)), vector(-2, -4, -6));
    cr_expect_tuple_eq(tupleSub(vector(0, 0, 0), vector(1, -2, 3)), vector(-1, 2, -3));
}

Test(tuple_operations, tuple_negate)
{
    cr_expect_tuple_eq(tupleNeg((Tuple){1, -2, 3, -4}), ((Tuple){-1, 2, -3, 4}));
}

Test(tuple_operations, tuple_multiply)
{
    cr_expect_tuple_eq(tupleMul((Tuple){1, -2, 3, -4}, 3.5), ((Tuple){3.5, -7, 10.5, -14}));
    cr_expect_tuple_eq(tupleMul((Tuple){1, -2, 3, -4}, 0.5), ((Tuple){0.5, -1, 1.5, -2}));
}

Test(tuple_operations, tuple_divide)
{
    cr_expect_tuple_eq(tupleDiv((Tuple){1, -2, 3, -4}, 2), ((Tuple){0.5, -1, 1.5, -2}));
}

Test(tuple_operations, tuple_magnitude)
{
    cr_expect(epsilon_eq(dbl, tupleMag(vector(1, 0, 0)), 1, EPSILON));
    cr_expect(epsilon_eq(dbl, tupleMag(vector(0, 1, 0)), 1, EPSILON));
    cr_expect(epsilon_eq(dbl, tupleMag(vector(0, 0, 1)), 1, EPSILON));
    cr_expect(epsilon_eq(dbl, tupleMag(vector(1, 2, 3)), sqrt(14), EPSILON));
    cr_expect(epsilon_eq(dbl, tupleMag(vector(-1, -2, -3)), sqrt(14), EPSILON));
}

Test(tuple_operations, tuple_normalize)
{
    cr_expect_tuple_eq(tupleNorm(vector(4, 0, 0)), vector(1, 0, 0));
    cr_expect_tuple_eq(tupleNorm(vector(1, 2, 3)), vector(1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)));
    cr_expect(epsilon_eq(dbl, tupleMag(tupleNorm(vector(1, 2, 3))), 1, EPSILON));
}

Test(tuple_operations, tuple_dot_product)
{
    cr_expect(epsilon_eq(dbl, tupleDot(vector(1, 2, 3), vector(2, 3, 4)), 20, EPSILON));
}

Test(tuple_operations, tuple_cross_product)
{
    cr_expect_tuple_eq(tupleCross(vector(1, 2, 3), vector(2, 3, 4)), vector(-1, 2, -1));
    cr_expect_tuple_eq(tupleCross(vector(2, 3, 4), vector(1, 2, 3)), vector(1, -2, 1));
}

Test(tuple_operations, color_operations)
{
    cr_expect_tuple_eq(color(-0.5, 0.4, 1.7), ((Tuple){-0.5, 0.4, 1.7, 0}));
    cr_expect_tuple_eq(tupleAdd(color(0.9, 0.6, 0.75), color(0.7, 0.1, 0.25)), color(1.6, 0.7, 1.0));
    cr_expect_tuple_eq(tupleSub(color(0.9, 0.6, 0.75), color(0.7, 0.1, 0.25)), color(0.2, 0.5, 0.5));
    cr_expect_tuple_eq(tupleMul(color(0.2, 0.3, 0.4), 2), color(0.4, 0.6, 0.8));
    cr_expect_tuple_eq(tupleProd(color(1, 0.2, 0.4), color(0.9, 1, 0.1)), color(0.9, 0.2, 0.04));
}
