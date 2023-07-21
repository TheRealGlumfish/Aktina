/*
 * vectors_test.c - Tests on vector and matrix implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <math.h>

#include "src/vectors.h"

#define EPSILON 0.00001
#define cr_expect_dbl(actual, expected) cr_expect(epsilon_eq(dbl, actual, expected, EPSILON))
#define cr_assert_dbl(actual, expected) cr_assert(epsilon_eq(dbl, actual, expected, EPSILON))
#define cr_expect_vec2_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON)))
#define cr_assert_vec2_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON)))
#define cr_expect_vec3_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON)))
#define cr_assert_vec3_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON)))
#define cr_expect_vec4_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON), eq(dbl, actual.w, expected.w, EPSILON)))
#define cr_assert_vec4_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON), eq(dbl, actual.w, expected.w, EPSILON)))

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat2EqExpect(Mat2 actual, Mat2 expected)
{
    for (size_t row = 0; row < 2; row++)
    {
        for (size_t col = 0; col < 2; col++)
        {
            cr_expect_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat2EqAssert(Mat2 actual, Mat2 expected)
{
    for (size_t row = 0; row < 2; row++)
    {
        for (size_t col = 0; col < 2; col++)
        {
            cr_assert_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat3EqExpect(Mat3 actual, Mat3 expected)
{
    for (size_t row = 0; row < 3; row++)
    {
        for (size_t col = 0; col < 3; col++)
        {
            cr_expect_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat3EqAssert(Mat3 actual, Mat3 expected)
{
    for (size_t row = 0; row < 3; row++)
    {
        for (size_t col = 0; col < 3; col++)
        {
            cr_assert_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat4EqExpect(Mat4 actual, Mat4 expected)
{
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            cr_expect_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat4EqAssert(Mat4 actual, Mat4 expected)
{
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            cr_assert_dbl(actual.elem[row][col], expected.elem[row][col]);
        }
    }
}

Test(vector_operations, vector_add)
{
    const Vec4 vecA = {{3, -2, 5, 1}};
    const Vec4 vecB = {{-2, 3, 1, 0}};
    const Vec4 vecC = {{1, 1, 6, 1}};
    cr_expect_vec2_eq(vec2Add(vecA.xyz.xy, vecB.xyz.xy), vecC.xyz.xy);
    cr_expect_vec3_eq(vec3Add(vecA.xyz, vecB.xyz), vecC.xyz);
    cr_expect_vec4_eq(vec4Add(vecA, vecB), vecC);
}

Test(vector_operations, vector_subtract)
{
    const Vec4 vecA = {{3, 2, 1, 1}};
    const Vec4 vecB = {{3, 2, 1, 0}};
    const Vec4 vecC = {{5, 6, 7, 1}};
    const Vec4 vecD = {{5, 6, 7, 0}};
    const Vec4 vecE = {{1, -2, 3, 0}};
    const Vec4 vecF = {{-2, -4, -6, 0}};
    const Vec4 vecG = {{-2, -4, -6, 1}};
    const Vec4 vecH = {{-1, 2, -3, 0}};
    const Vec4 vecI = {0};
    cr_expect_vec2_eq(vec2Sub(vecA.xyz.xy, vecC.xyz.xy), vecF.xyz.xy);
    cr_expect_vec3_eq(vec3Sub(vecA.xyz, vecC.xyz), vecF.xyz);
    cr_expect_vec4_eq(vec4Sub(vecA, vecC), vecF);
    cr_expect_vec2_eq(vec2Sub(vecA.xyz.xy, vecD.xyz.xy), vecG.xyz.xy);
    cr_expect_vec3_eq(vec3Sub(vecA.xyz, vecD.xyz), vecG.xyz);
    cr_expect_vec4_eq(vec4Sub(vecA, vecD), vecG);
    cr_expect_vec2_eq(vec2Sub(vecB.xyz.xy, vecD.xyz.xy), vecF.xyz.xy);
    cr_expect_vec3_eq(vec3Sub(vecB.xyz, vecD.xyz), vecF.xyz);
    cr_expect_vec4_eq(vec4Sub(vecB, vecD), vecF);
    cr_expect_vec2_eq(vec2Sub(vecI.xyz.xy, vecE.xyz.xy), vecH.xyz.xy);
    cr_expect_vec3_eq(vec3Sub(vecI.xyz, vecE.xyz), vecH.xyz);
    cr_expect_vec4_eq(vec4Sub(vecI, vecE), vecH);
}

Test(vector_operations, vector_negate)
{
    const Vec4 vecA = {{1, -2, 3, -4}};
    const Vec4 vecB = {{-1, 2, -3, 4}};
    cr_expect_vec2_eq(vec2Neg(vecA.xyz.xy), vecB.xyz.xy);
    cr_expect_vec3_eq(vec3Neg(vecA.xyz), vecB.xyz);
    cr_expect_vec4_eq(vec4Neg(vecA), vecB);
}

Test(vector_operations, vector_multiply)
{
    const Vec4 vecA = {{1, -2, 3, -4}};
    const Vec4 vecB = {{3.5, -7, 10.5, -14}};
    const Vec4 vecC = {{0.5, -1, 1.5, -2}};
    cr_expect_vec2_eq(vec2Mul(vecA.xyz.xy, 3.5), vecB.xyz.xy);
    cr_expect_vec3_eq(vec3Mul(vecA.xyz, 3.5), vecB.xyz);
    cr_expect_vec4_eq(vec4Mul(vecA, 3.5), vecB);
    cr_expect_vec2_eq(vec2Mul(vecA.xyz.xy, 0.5), vecC.xyz.xy);
    cr_expect_vec3_eq(vec3Mul(vecA.xyz, 0.5), vecC.xyz);
    cr_expect_vec4_eq(vec4Mul(vecA, 0.5), vecC);
}

Test(vector_operations, vector_divide)
{
    const Vec4 vecA = {{1, -2, 3, -4}};
    const Vec4 vecB = {{0.5, -1, 1.5, -2}};
    cr_expect_vec2_eq(vec2Div(vecA.xyz.xy, 2), vecB.xyz.xy);
    cr_expect_vec3_eq(vec3Div(vecA.xyz, 2), vecB.xyz);
    cr_expect_vec4_eq(vec4Div(vecA, 2), vecB);
}

Test(vector_operations, vector_magnitude)
{
    // TODO: Add unit tests for Vec2 and Vec4 types
    const Vec3 vecA = {{1, 0, 0}};
    const Vec3 vecB = {{0, 1, 0}};
    const Vec3 vecC = {{0, 0, 1}};
    const Vec3 vecD = {{1, 2, 3}};
    const Vec3 vecE = {{-1, -2, -3}};
    cr_expect_dbl(vec3Mag(vecA), 1);
    cr_expect_dbl(vec3Mag(vecB), 1);
    cr_expect_dbl(vec3Mag(vecC), 1);
    cr_expect_dbl(vec3Mag(vecD), sqrt(14));
    cr_expect_dbl(vec3Mag(vecE), sqrt(14));
}

Test(vector_operations, vector_normalize)
{
    // TODO: Add unit tests for Vec2 and Vec4 types
    const Vec3 vecA = {{4, 0, 0}};
    const Vec3 vecB = {{1, 2, 3}};
    const Vec3 vecC = {{1, 0, 0}};
    const Vec3 vecD = {{1 / sqrt(14), 2 / sqrt(14), 3 / sqrt(14)}};
    cr_expect_vec3_eq(vec3Norm(vecA), vecC);
    cr_expect_vec3_eq(vec3Norm(vecB), vecD);
}

Test(vector_operations, vector_dot_product)
{
    // TODO: Add unit tests for Vec2 and Vec4 types
    const Vec3 vecA = {{1, 2, 3}};
    const Vec3 vecB = {{2, 3, 4}};
    cr_expect_dbl(vec3Dot(vecA, vecB), 20);
}

Test(vector_operations, vector_cross_product)
{
    // TODO: Add unit tests for Vec2 and Vec4 types
    const Vec3 vecA = {{1, 2, 3}};
    const Vec3 vecB = {{2, 3, 4}};
    const Vec3 vecC = {{2, 3, 4}};
    const Vec3 vecD = {{1, 2, 3}};
    const Vec3 vecE = {{-1, 2, -1}};
    const Vec3 vecF = {{1, -2, 1}};
    cr_expect_vec3_eq(vec3Cross(vecA, vecB), vecE);
    cr_expect_vec3_eq(vec3Cross(vecC, vecD), vecF);
}
