/*
 * vectors_test.c - Tests on vector, matrix and transformation implementation
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

#define cr_expect_vec2_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON)))

#define cr_assert_vec2_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON)))

#define cr_expect_vec3_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON)))

#define cr_assert_vec3_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON)))

#define cr_expect_vec4_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON), \
                                                          epsilon_eq(dbl, actual.w, expected.w, EPSILON)))

#define cr_assert_vec4_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), \
                                                          epsilon_eq(dbl, actual.y, expected.y, EPSILON), \
                                                          epsilon_eq(dbl, actual.z, expected.z, EPSILON), \
                                                          epsilon_eq(dbl, actual.w, expected.w, EPSILON)))

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

Test(matrix_operations, matrix_multiply)
{
    // TODO: Add unit tests for Mat2 and Mat3 types
    Mat4 matA = {{{1, 2, 3, 4},
                  {5, 6, 7, 8},
                  {9, 8, 7, 6},
                  {5, 4, 3, 2}}};
    Mat4 matB = {{{-2, 1, 2, 3},
                  {3, 2, 1, -1},
                  {4, 3, 6, 5},
                  {1, 2, 7, 8}}};
    Mat4 matC = {{{20, 22, 50, 48},
                  {44, 54, 114, 108},
                  {40, 58, 110, 102},
                  {16, 26, 46, 42}}};
    mat4EqExpect(mat4Mul(matA, matB), matC);
}

Test(matrix_operations, matrix_vector_multiply)
{
    Mat4 matA = {{{1, 2, 3, 4},
                  {2, 4, 4, 2},
                  {8, 6, 4, 1},
                  {0, 0, 0, 1}}};
    Vec4 vecA = {{1, 2, 3, 1}};
    Vec4 vecB = {{18, 24, 33, 1}};
    cr_expect_vec4_eq(mat4VecMul(matA, vecA), vecB);
}

Test(matrix_operations, matrix_transpose)
{
    Mat4 matI = {{{1, 0, 0, 0},
                  {0, 1, 0, 0},
                  {0, 0, 1, 0},
                  {0, 0, 0, 1}}};
    Mat4 matA = {{{0, 9, 3, 0},
                  {9, 8, 0, 8},
                  {1, 8, 5, 3},
                  {0, 0, 5, 8}}};
    Mat4 matT = {{{0, 9, 1, 0},
                  {9, 8, 8, 0},
                  {3, 0, 5, 5},
                  {0, 8, 3, 8}}};
    mat4EqExpect(mat4Trans(matA), matT);
    mat4EqExpect(mat4Trans(matI), matI);
}

Test(matrix_operations, matrix_determinant)
{
    Mat2 matA = {{{1, 5},
                  {-3, 2}}};
    cr_assert_dbl(mat2Det(matA), 17);
    Mat4 matB = {{{-2, -8, 3, 5},
                  {-3, 1, 7, 3},
                  {1, 2, -9, 6},
                  {-6, 7, 7, -9}}};
    Mat4 matC = {{{6, 4, 4, 4},
                  {5, 5, 7, 6},
                  {4, -9, 3, -7},
                  {9, 1, 7, -6}}};
    Mat4 matD = {{{-4, 2, -2, -3},
                  {9, 6, 2, 6},
                  {0, -5, 1, -5},
                  {0, 0, 0, 0}}};
    Mat4 matE = {{{-5, 2, 6, -8},
                  {1, -5, 1, 8},
                  {7, 7, -6, -7},
                  {1, -3, 7, 4}}};
    cr_expect_dbl(mat4Det(matB), -4071);
    cr_expect_dbl(mat4Det(matC), -2120);
    cr_expect_dbl(mat4Det(matD), 0);
    cr_expect_dbl(mat4Det(matE), 532);
}

Test(matrix_operations, submatrix)
{
    Mat3 matA = {{{1, 5, 0},
                  {-3, 2, 7},
                  {0, 6, -3}}};
    Mat2 matB = {{{-3, 2},
                  {0, 6}}};
    Mat4 matC = {{{-6, 1, 1, 6},
                  {-8, 5, 8, 6},
                  {-1, 0, 8, 2},
                  {-7, 1, -1, 1}}};
    Mat3 matD = {{{-6, 1, 6},
                  {-8, 8, 6},
                  {-7, -1, 1}}};
    mat2EqExpect(mat3SubM(0, 2, matA), matB);
    mat3EqExpect(mat4SubM(2, 1, matC), matD);
}

Test(matrix_operations, matrix_minor)
{
    Mat3 matA = {{{3, 5, 0},
                  {2, -1, -7},
                  {6, -1, 5}}};
    cr_expect_dbl(mat3Min(0, 0, matA), -12);
    cr_expect_dbl(mat3Min(1, 0, matA), 25);
}

Test(matrix_operations, matrix_cofactor)
{
    Mat3 matA = {{{3, 5, 0},
                  {2, -1, -7},
                  {6, -1, 5}}};
    cr_expect_dbl(mat3Cof(0, 0, matA), -12);
    cr_expect_dbl(mat3Cof(1, 0, matA), -25);
    Mat3 matB = {{{1, 2, 6},
                  {-5, 8, -4},
                  {2, 6, 4}}};
    cr_expect_dbl(mat3Cof(0, 0, matB), 56);
    cr_expect_dbl(mat3Cof(0, 1, matB), 12);
    cr_expect_dbl(mat3Cof(0, 2, matB), -46);
    Mat4 matC = {{{-2, -8, 3, 5},
                  {-3, 1, 7, 3},
                  {1, 2, -9, 6},
                  {-6, 7, 7, -9}}};
    cr_expect_dbl(mat4Cof(0, 0, matC), 690);
    cr_expect_dbl(mat4Cof(0, 1, matC), 447);
    cr_expect_dbl(mat4Cof(0, 2, matC), 210);
    cr_expect_dbl(mat4Cof(0, 3, matC), 51);
    Mat4 matD = {{{-5, 2, 6, -8},
                  {1, -5, 1, 8},
                  {7, 7, -6, -7},
                  {1, -3, 7, 4}}};
    cr_expect_dbl(mat4Cof(2, 3, matD), -160);
    cr_expect_dbl(mat4Cof(3, 2, matD), 105);
}

Test(matrix_operations, matrix_invert)
{
    Mat4 matA = {{{-5, 2, 6, -8},
                  {1, -5, 1, 8},
                  {7, 7, -6, -7},
                  {1, -3, 7, 4}}};
    Mat4 matB = {{{0.21805, 0.45113, 0.24060, -0.04511},
                  {-0.80827, -1.45677, -0.44361, 0.52068},
                  {-0.07895, -0.22368, -0.05263, 0.19737},
                  {-0.52256, -0.81391, -0.30075, 0.30639}}};
    Mat4 matC = {{{8, -5, 9, 2},
                  {7, 5, 6, 1},
                  {-6, 0, 9, 6},
                  {-3, 0, -9, -4}}};
    Mat4 matD = {{{-0.15385, -0.15385, -0.28205, -0.53846},
                  {-0.07692, 0.12308, 0.02564, 0.03077},
                  {0.35897, 0.35897, 0.43590, 0.92308},
                  {-0.69231, -0.69231, -0.76923, -1.92308}}};
    Mat4 matE = {{{9, 3, 0, 9},
                  {-5, -2, -6, -3},
                  {-4, 9, 6, 4},
                  {-7, 6, 6, 2}}};
    Mat4 matF = {{{-0.04074, -0.07778, 0.14444, -0.22222},
                  {-0.07778, 0.03333, 0.36667, -0.33333},
                  {-0.02901, -0.14630, -0.10926, 0.12963},
                  {0.17778, 0.06667, -0.26667, 0.33333}}};
    Mat4 matG = {{{3, -9, 7, 3},
                  {3, -8, 2, -9},
                  {-4, 4, 4, 1},
                  {-6, 5, -1, 1}}};
    Mat4 matH = {{{8, 2, 2, 2},
                  {3, -1, 7, 0},
                  {7, 0, 5, 4},
                  {6, -2, 0, 5}}};
    mat4EqExpect(mat4Inv(matA), matB);
    mat4EqExpect(mat4Inv(matC), matD);
    mat4EqExpect(mat4Inv(matE), matF);
    mat4EqExpect(mat4Mul(mat4Mul(matG, matH), mat4Inv(matH)), matG);
}

Test(matrix_transformations, translation)
{
    cr_expect_point_eq(mat4VecMul(translation(5, -3, 2), point(-3, 4, 5)), 2, 1, 7);
    cr_expect_point_eq(mat4VecMul(mat4Inv(translation(5, -3, 2)), point(-3, 4, 5)), -8, 7, 3);
    cr_expect_vector_eq(mat4VecMul(translation(5, -3, 2), vector(-3, 4, 5)), -3, 4, 5);
}

Test(matrix_transformations, scaling)
{
    cr_expect_point_eq(mat4VecMul(scaling(2, 3, 4), point(-4, 6, 8)), -8, 18, 32);
    cr_expect_vector_eq(mat4VecMul(scaling(2, 3, 4), vector(-4, 6, 8)), -8, 18, 32);
    cr_expect_vector_eq(mat4VecMul(mat4Inv(scaling(2, 3, 4)), vector(-4, 6, 8)), -2, 2, 2);
}

Test(matrix_transformations, reflection)
{
    cr_expect_point_eq(mat4VecMul(scaling(-1, 1, 1), point(2, 3, 4)), -2, 3, 4);
}

Test(matrix_transformations, roation)
{
    cr_expect_point_eq(mat4VecMul(rotationX(M_PI_4), point(0, 1, 0)), 0, M_SQRT1_2, M_SQRT1_2);
    cr_expect_point_eq(mat4VecMul(rotationX(M_PI_2), point(0, 1, 0)), 0, 0, 1);
    cr_expect_point_eq(mat4VecMul(mat4Inv(rotationX(M_PI_4)), point(0, 1, 0)), 0, M_SQRT1_2, -M_SQRT1_2);
    cr_expect_point_eq(mat4VecMul(rotationY(M_PI_4), point(0, 0, 1)), M_SQRT1_2, 0, M_SQRT1_2);
    cr_expect_point_eq(mat4VecMul(rotationY(M_PI_2), point(0, 0, 1)), 1, 0, 0);
    cr_expect_point_eq(mat4VecMul(rotationZ(M_PI_4), point(0, 1, 0)), -M_SQRT1_2, M_SQRT1_2, 0);
    cr_expect_point_eq(mat4VecMul(rotationZ(M_PI_2), point(0, 1, 0)), -1, 0, 0);
}

Test(matrix_transformations, shearing)
{
    cr_expect_point_eq(mat4VecMul(shearing(1, 0, 0, 0, 0, 0), point(2, 3, 4)), 5, 3, 4);
    cr_expect_point_eq(mat4VecMul(shearing(0, 1, 0, 0, 0, 0), point(2, 3, 4)), 6, 3, 4);
    cr_expect_point_eq(mat4VecMul(shearing(0, 0, 1, 0, 0, 0), point(2, 3, 4)), 2, 5, 4);
    cr_expect_point_eq(mat4VecMul(shearing(0, 0, 0, 1, 0, 0), point(2, 3, 4)), 2, 7, 4);
    cr_expect_point_eq(mat4VecMul(shearing(0, 0, 0, 0, 1, 0), point(2, 3, 4)), 2, 3, 6);
    cr_expect_point_eq(mat4VecMul(shearing(0, 0, 0, 0, 0, 1), point(2, 3, 4)), 2, 3, 7);
}

Test(matrix_transformations, chaining)
{
    Mat4 rotation = rotationX(M_PI_2);
    Mat4 scaling = scaling(5, 5, 5);
    Mat4 translation = translation(10, 5, 7);
    Vec4 point = point(1, 0, 1);
    point = mat4VecMul(rotation, point);
    cr_expect_point_eq(point, 1, -1, 0);
    point = mat4VecMul(scaling, point);
    cr_expect_point_eq(point, 5, -5, 0);
    point = mat4VecMul(translation, point);
    cr_expect_point_eq(point, 15, 0, 7);
    cr_expect_point_eq(mat4VecMul(mat4Mul(mat4Mul(translation(10, 5, 7), scaling(5, 5, 5)), rotationX(M_PI_2)), point(1, 0, 1)), 15, 0, 7);
}
