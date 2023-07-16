/*
 * matrices.c - Matrix implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "matrices.h"
#include "tuples.h"

// Checks for equality of 2*2 matrices
bool mat2Eq(const Mat2 a, const Mat2 b)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (fabs(a[i][j] - b[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// Checks for equality of 3*3 matrices
bool mat3Eq(const Mat3 a, const Mat3 b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (fabs(a[i][j] - b[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// Checks for equality of 4*4 matrices
bool mat4Eq(const Mat4 a, const Mat4 b)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (fabs(a[i][j] - b[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// NOTE: Unused and untested; remove
// Multiplies two 2*2 matrices and stores the result
// Important: dest cannot point to either a or b
void mat2Mul(Mat2 dest, const Mat2 a, const Mat2 b)
{
    dest[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    dest[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    dest[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    dest[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1];
}

// Multiplies two 4*4 matrices and stores the result
// Important: dest cannot point to either a or b
void mat4Mul(Mat4 dest, const Mat4 a, const Mat4 b)
{
    for (uint64_t row = 0; row < 4; row++)
    {
        for (uint64_t col = 0; col < 4; col++)
        {
            for (uint64_t i = 0; i < 4; i++) // NOTE: Consider unrolling and benchmark
            {
                dest[row][col] += a[row][i] * b[i][col];
            }
        }
    }
}

// Returns the matrix-vector product
Tuple mat4VecMul(const Mat4 mat, const Tuple vec)
{
    return (Tuple){.x = vec.x * mat[0][0] + vec.y * mat[0][1] + vec.z * mat[0][2] + vec.w * mat[0][3],
                   .y = vec.x * mat[1][0] + vec.y * mat[1][1] + vec.z * mat[1][2] + vec.w * mat[1][3],
                   .z = vec.x * mat[2][0] + vec.y * mat[2][1] + vec.z * mat[2][2] + vec.w * mat[2][3],
                   .w = vec.x * mat[3][0] + vec.y * mat[3][1] + vec.z * mat[3][2] + vec.w * mat[3][3]};
}

// Transposes a 4*4 matrix and stores the result
// Important: dest cannot point to a
void mat4Trans(Mat4 dest, const Mat4 a)
{
    for (uint64_t i = 0; i < 4; i++) // NOTE: Consider skipping [0][0] and [3][3] and doing out of loop
    {
        for (uint64_t j = 0; j < 4; j++)
        {
            dest[i][j] = a[j][i];
            dest[j][i] = a[i][j];
        }
    }
}

double mat2Det(const Mat2 a)
{
    return a[0][0] * a[1][1] - a[1][0] * a[0][1];
}

void mat3SubM(Mat2 dest, const uint64_t row, const uint64_t col, const Mat3 a)
{
}

// Stores the submatrix of a in dest
void mat4SubM(Mat3 dest, const uint64_t row, const uint64_t col, const Mat4 a)
{
    for (uint64_t i = 0; i < 4; i++)
    {
        for (uint64_t j = 0; j < 4; j++)
        {
            if (i == row || j == col)
            {
                continue;
            }
        }
    }
}
