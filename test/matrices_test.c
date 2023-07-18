/*
 * matrices.h - Matrix and vector implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "src/matrices.h"

#define EPSILON 0.00001
#define cr_expect_dbl(actual, expected) cr_expect(epsilon_eq(dbl, actual, expected, EPSILON))
#define cr_assert_dbl(actual, expected) cr_assert(epsilon_eq(dbl, actual, expected, EPSILON))
#define cr_expect_tuple_eq(actual, expected) cr_expect(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON), eq(dbl, actual.w, expected.w, EPSILON)))
#define cr_assert_tuple_eq(actual, expected) cr_assert(all(epsilon_eq(dbl, actual.x, expected.x, EPSILON), epsilon_eq(dbl, actual.y, expected.y, EPSILON), epsilon_eq(actual.z, expected.z, EPSILON), eq(dbl, actual.w, expected.w, EPSILON)))

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat2EqExpect(const Mat2 actual, const Mat2 expected)
{
    for (uint64_t row = 0; row < 2; row++)
    {
        for (uint64_t col = 0; col < 2; col++)
        {
            cr_expect_dbl(actual[row][col], expected[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat2EqAssert(const Mat2 a, const Mat2 b)
{
    for (uint64_t row = 0; row < 4; row++)
    {
        for (uint64_t col = 0; col < 4; col++)
        {
            cr_assert_dbl(a[row][col], b[row][col]);
        }
    }
}

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat3EqExpect(const Mat3 actual, const Mat3 expected)
{
    for (uint64_t row = 0; row < 3; row++)
    {
        for (uint64_t col = 0; col < 3; col++)
        {
            cr_expect_dbl(actual[row][col], expected[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat3EqAssert(const Mat3 a, const Mat3 b)
{
    for (uint64_t row = 0; row < 3; row++)
    {
        for (uint64_t col = 0; col < 3; col++)
        {
            cr_assert_dbl(a[row][col], b[row][col]);
        }
    }
}

// Triggers a cr_expect assertion to fail if the matrices are not equal
void mat4EqExpect(const Mat4 actual, const Mat4 expected)
{
    for (uint64_t row = 0; row < 4; row++)
    {
        for (uint64_t col = 0; col < 4; col++)
        {
            cr_expect_dbl(actual[row][col], expected[row][col]);
        }
    }
}

// Triggers a cr_assert assertion to fail if the matrices are not equal
void mat4EqAssert(const Mat4 a, const Mat4 b)
{
    for (uint64_t row = 0; row < 4; row++)
    {
        for (uint64_t col = 0; col < 4; col++)
        {
            cr_assert_dbl(a[row][col], b[row][col]);
        }
    }
}

Test(matrix_operations, matrix)
{
    Mat4 matrix4 = {{1, 2, 3, 4},
                    {5.5, 6.5, 7.5, 8.5},
                    {9, 10, 11, 12},
                    {13.5, 14.5, 15.5, 16.5}};
    cr_expect_dbl(matrix4[0][0], 1);
    cr_expect_dbl(matrix4[0][3], 4);
    cr_expect_dbl(matrix4[1][0], 5.5);
    cr_expect_dbl(matrix4[1][2], 7.5);
    cr_expect_dbl(matrix4[2][2], 11);
    cr_expect_dbl(matrix4[3][0], 13.5);
    cr_expect_dbl(matrix4[3][2], 15.5);
    Mat2 matrix2 = {{-3, 5},
                    {1, -2}};
    cr_expect_dbl(matrix2[0][0], -3);
    cr_expect_dbl(matrix2[0][1], 5);
    cr_expect_dbl(matrix2[1][0], 1);
    cr_expect_dbl(matrix2[1][1], -2);
    Mat3 matrix3 = {{-3, 5, 0},
                    {1, -2, -7},
                    {0, 1, 1}};
    cr_expect_dbl(matrix3[0][0], -3);
    cr_expect_dbl(matrix3[1][1], -2);
    cr_expect_dbl(matrix3[2][2], 1);
}

Test(matrix_operations, matrix_compare)
{
    Mat4 matA = {{1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 8, 7, 6},
                 {5, 4, 3, 2}};
    Mat4 matB = {{1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 8, 7, 6},
                 {5, 4, 3, 2}};
    Mat4 matC = {{2, 3, 4, 5},
                 {6, 7, 8, 9},
                 {8, 7, 6, 5},
                 {4, 3, 2, 1}};
    cr_expect(mat4Eq(matA, matB));
    cr_expect(not(mat4Eq(matA, matC)));
}

Test(matrix_operations, matrix_multiply)
{
    Mat4 matA = {{1, 2, 3, 4},
                 {5, 6, 7, 8},
                 {9, 8, 7, 6},
                 {5, 4, 3, 2}};
    Mat4 matB = {{-2, 1, 2, 3},
                 {3, 2, 1, -1},
                 {4, 3, 6, 5},
                 {1, 2, 7, 8}};
    Mat4 matC = {{20, 22, 50, 48},
                 {44, 54, 114, 108},
                 {40, 58, 110, 102},
                 {16, 26, 46, 42}};
    Mat4 dest;
    mat4Mul(dest, matA, matB);
    mat4EqExpect(dest, matC);
}

Test(matrix_operations, matrix_vec_multiply)
{
    Mat4 matA = {{1, 2, 3, 4},
                 {2, 4, 4, 2},
                 {8, 6, 4, 1},
                 {0, 0, 0, 1}};
    cr_expect_tuple_eq(mat4VecMul(matA, (Tuple){1, 2, 3, 1}), ((Tuple){18, 24, 33, 1}));
}

Test(matrix_operations, matrix_identity)
{
    Mat4 matI = {{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
    Mat4 matA = {{0, 1, 3, 4},
                 {1, 2, 4, 8},
                 {2, 4, 8, 16},
                 {4, 8, 16, 32}};
    Mat4 dest;
    mat4Mul(dest, matA, matI);
    mat4EqExpect(dest, matA);
    cr_expect_tuple_eq(mat4VecMul(matI, (Tuple){1, 2, 3, 4}), ((Tuple){1, 2, 3, 4}));
}

Test(matrix_operations, matrix_transpose)
{
    Mat4 matI = {{1, 0, 0, 0},
                 {0, 1, 0, 0},
                 {0, 0, 1, 0},
                 {0, 0, 0, 1}};
    Mat4 matA = {{0, 9, 3, 0},
                 {9, 8, 0, 8},
                 {1, 8, 5, 3},
                 {0, 0, 5, 8}};
    Mat4 matT = {{0, 9, 1, 0},
                 {9, 8, 8, 0},
                 {3, 0, 5, 5},
                 {0, 8, 3, 8}};
    Mat4 dest;
    mat4Trans(dest, matA);
    mat4EqExpect(dest, matT);
    mat4Trans(dest, matI);
    mat4EqExpect(dest, matI);
}

Test(matrix_operations, matrix_determinant)
{
    Mat2 matA = {{1, 5},
                 {-3, 2}};
    cr_expect_dbl(mat2Det(matA), 17);
}

Test(matrix_operations, submatrix)
{
    Mat3 matA = {{1, 5, 0},
                 {-3, 2, 7},
                 {0, 6, -3}};
    Mat2 matB = {{-3, 2},
                 {0, 6}};
    Mat4 matC = {{-6, 1, 1, 6},
                 {-8, 5, 8, 6},
                 {-1, 0, 8, 2},
                 {-7, 1, -1, 1}};
    Mat3 matD = {{-6, 1, 6},
                 {-8, 8, 6},
                 {-7, -1, 1}};
    Mat2 dest2;
    Mat3 dest3;
    mat3SubM(dest2, 0, 2, matA);
    mat4SubM(dest3, 2, 1, matC);
    mat2EqExpect(dest2, matB);
    mat3EqExpect(dest3, matD);
}

Test(matrix_operations, minor)
{
    Mat3 matA = {{3, 5, 0},
                 {2, -1, -7},
                 {6, -1, 5}};
    cr_expect_dbl(mat3Min(0, 0, matA), -12);
    cr_expect_dbl(mat3Min(1, 0, matA), 25);
}

Test(matrix_operations, cofactor)
{
    Mat3 matA = {{3, 5, 0},
                 {2, -1, -7},
                 {6, -1, 5}};
    cr_expect_dbl(mat3Cof(0, 0, matA), -12);
    cr_expect_dbl(mat3Cof(1, 0, matA), -25);
    Mat3 matB = {{1, 2, 6},
                 {-5, 8, -4},
                 {2, 6, 4}};
    cr_expect_dbl(mat3Cof(0, 0, matB), 56);
    cr_expect_dbl(mat3Cof(0, 1, matB), 12);
    cr_expect_dbl(mat3Cof(0, 2, matB), -46);
    Mat4 matC = {{-2, -8, 3, 5},
                 {-3, 1, 7, 3},
                 {1, 2, -9, 6},
                 {-6, 7, 7, -9}};
    // cr_expect_dbl(mat4Cof(0, 0, matC), 690);
    // cr_expect_dbl(mat4Cof(0, 0, matC), 690);
}

Test(matrix_operations, determinant)
{
}
