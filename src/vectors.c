/*
 * vectors.c - Vector and matrix implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#include "vectors.h"

// Adds two vectors
Vec2 vec2Add(Vec2 a, Vec2 b)
{
    Vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

// Subtracts two vectors
Vec2 vec2Sub(Vec2 a, Vec2 b)
{
    Vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

// Scalar-vector multiplication
Vec2 vec2Mul(Vec2 a, double b)
{
    Vec2 result;
    result.x = a.x * b;
    result.y = a.y * b;
    return result;
}

// Scalar-vector division
Vec2 vec2Div(Vec2 a, double b)
{
    Vec2 result;
    result.x = a.x / b;
    result.y = a.y / b;
    return result;
}

// Negates a vector
Vec2 vec2Neg(Vec2 a)
{
    Vec2 result;
    result.x = -a.x;
    result.y = -a.y;
    return result;
}

// Returns the magnitude of a vector
double vec2Mag(Vec2 a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

// TODO: Check generated assembly
// Normalizes a vector
Vec2 vec2Norm(Vec2 a)
{
    return vec2Div(a, vec2Mag(a));
}

// Returns the dot product of two vectors
double vec2Dot(Vec2 a, Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

// Hadamard product of two vectors
Vec2 vec2Prod(Vec2 a, Vec2 b)
{
    Vec2 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    return result;
}

// Adds two vectors
Vec3 vec3Add(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

// Subtracts two vectors
Vec3 vec3Sub(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

// Scalar-vector multiplication
Vec3 vec3Mul(Vec3 a, double b)
{
    Vec3 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    return result;
}

// Scalar-vector division
Vec3 vec3Div(Vec3 a, double b)
{
    Vec3 result;
    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    return result;
}

// Negates a vector
Vec3 vec3Neg(Vec3 a)
{
    Vec3 result;
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    return result;
}

// Returns the magnitude of a vector
double vec3Mag(Vec3 a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
}

// Normalizes a vector
Vec3 vec3Norm(Vec3 a)
{
    return vec3Div(a, vec3Mag(a));
}

// Returns the dot product of two vectors
double vec3Dot(Vec3 a, Vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product of two vectors
Vec3 vec3Cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

// Hadamard product of two vectors
Vec3 vec3Prod(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    return result;
}

// Adds two vectors
Vec4 vec4Add(Vec4 a, Vec4 b)
{
    Vec4 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;
    return result;
}

// Subtracts two vectors
Vec4 vec4Sub(Vec4 a, Vec4 b)
{
    Vec4 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;
    return result;
}

// Scalar-vector multiplication
Vec4 vec4Mul(Vec4 a, double b)
{
    Vec4 result;
    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;
    return result;
}

// Scalar-vector division
Vec4 vec4Div(Vec4 a, double b)
{
    Vec4 result;
    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.w = a.w / b;
    return result;
}

// Negates a vector
Vec4 vec4Neg(Vec4 a)
{
    Vec4 result;
    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;
    return result;
}

// Returns the magnitude of a vector
double vec4Mag(Vec4 a)
{
    return sqrt(a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w);
}

// Normalizes a vector
Vec4 vec4Norm(Vec4 a)
{
    return vec4Div(a, vec4Mag(a));
}

// Returns the dot product of two vectors
double vec4Dot(Vec4 a, Vec4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Hadamard product of two vectors
Vec4 vec4Prod(Vec4 a, Vec4 b)
{
    Vec4 result;
    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;
    result.w = a.w * b.w;
    return result;
}

// TODO: Maybe add const to the arguments of the vector and matrix functions
// TODO: Vectorize by treating the elements as vectors
// Checks for equality of 2*2 matrices
bool mat2Eq(Mat2 a, Mat2 b)
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (fabs(a.elem[i][j] - b.elem[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// Checks for equality of 3*3 matrices
bool mat3Eq(Mat3 a, Mat3 b)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (fabs(a.elem[i][j] - b.elem[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// Checks for equality of 4*4 matrices
bool mat4Eq(Mat4 a, Mat4 b)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (fabs(a.elem[i][j] - b.elem[i][j]) >= MAT_EPSILON)
            {
                return false;
            }
        }
    }
    return true;
}

// TODO: Try vectorizing by accessing the columns
// Multiplies two 2*2 matrices
Mat2 mat2Mul(Mat2 a, Mat2 b)
{
    Mat2 result;
    result.elem[0][0] = a.elem[0][0] * b.elem[0][0] + a.elem[0][1] * b.elem[1][0];
    result.elem[0][1] = a.elem[0][0] * b.elem[0][1] + a.elem[0][1] * b.elem[1][1];
    result.elem[1][0] = a.elem[1][0] * b.elem[0][0] + a.elem[1][1] * b.elem[1][0];
    result.elem[1][1] = a.elem[1][0] * b.elem[0][1] + a.elem[1][1] * b.elem[1][1];
    return result;
}

// Multiplies two 3*3 matrices and stores the result
Mat3 mat3Mul(Mat3 a, Mat3 b)
{
    Mat3 result = {0};
    for (size_t row = 0; row < 3; row++)
    {
        for (size_t col = 0; col < 3; col++)
        {
            for (size_t i = 0; i < 3; i++) // NOTE: Consider unrolling and benchmark
            {
                result.elem[row][col] += a.elem[row][i] * b.elem[i][col];
            }
        }
    }
    return result;
}

// Multiplies two 4*4 matrices
Mat4 mat4Mul(Mat4 a, Mat4 b)
{
    Mat4 result = {0};
    for (size_t row = 0; row < 4; row++)
    {
        for (size_t col = 0; col < 4; col++)
        {
            for (size_t i = 0; i < 4; i++) // NOTE: Consider unrolling and benchmark
            {
                result.elem[row][col] += a.elem[row][i] * b.elem[i][col];
            }
        }
    }
    return result;
}

// Matrix-vector product
Vec2 mat2VecMul(Mat2 mat, Vec2 vec)
{
    Vec2 result;
    result.x = vec.x * mat.elem[0][0] + vec.y * mat.elem[0][1];
    result.y = vec.x * mat.elem[1][0] + vec.y * mat.elem[1][1];
    return result;
}

// Matrix-vector product
Vec3 mat3VecMul(Mat3 mat, Vec3 vec)
{
    Vec3 result;
    result.x = vec.x * mat.elem[0][0] + vec.y * mat.elem[0][1] + vec.z * mat.elem[0][2];
    result.y = vec.x * mat.elem[1][0] + vec.y * mat.elem[1][1] + vec.z * mat.elem[1][2];
    result.z = vec.x * mat.elem[2][0] + vec.y * mat.elem[2][1] + vec.z * mat.elem[2][2];
    return result;
}

// TODO: Check if the matrix can be accessed via its columns and thus vectorized
// Matrix-vector product
Vec4 mat4VecMul(Mat4 mat, Vec4 vec)
{
    Vec4 result;
    result.x = vec.x * mat.elem[0][0] + vec.y * mat.elem[0][1] + vec.z * mat.elem[0][2] + vec.w * mat.elem[0][3];
    result.y = vec.x * mat.elem[1][0] + vec.y * mat.elem[1][1] + vec.z * mat.elem[1][2] + vec.w * mat.elem[1][3];
    result.z = vec.x * mat.elem[2][0] + vec.y * mat.elem[2][1] + vec.z * mat.elem[2][2] + vec.w * mat.elem[2][3];
    result.w = vec.x * mat.elem[3][0] + vec.y * mat.elem[3][1] + vec.z * mat.elem[3][2] + vec.w * mat.elem[3][3];
    return result;
}

// Transposes a 3*3 matrix and stores the result
Mat2 mat2Trans(Mat2 a)
{
    Mat2 result;
    for (size_t i = 0; i < 2; i++) // NOTE: Consider unrolling
    {
        for (size_t j = 0; j < 2; j++)
        {
            result.elem[i][j] = a.elem[j][i];
            result.elem[j][i] = a.elem[i][j];
        }
    }
    return result;
}

// Transposes a 3*3 matrix and stores the result
Mat3 mat3Trans(Mat3 a)
{
    Mat3 result;
    for (size_t i = 0; i < 3; i++) // NOTE: Consider skipping [0][0] and [2][2] and doing out of loop
    {
        for (size_t j = 0; j < 3; j++)
        {
            result.elem[i][j] = a.elem[j][i];
            result.elem[j][i] = a.elem[i][j];
        }
    }
    return result;
}

// Transposes a 4*4 matrix and stores the result
Mat4 mat4Trans(Mat4 a)
{
    Mat4 result;
    for (size_t i = 0; i < 4; i++) // NOTE: Consider skipping [0][0] and [3][3] and doing out of loop
    {
        for (size_t j = 0; j < 4; j++)
        {
            result.elem[i][j] = a.elem[j][i];
            result.elem[j][i] = a.elem[i][j];
        }
    }
    return result;
}

// Determinant of a 2*2 matrix
double mat2Det(Mat2 a)
{
    return a.elem[0][0] * a.elem[1][1] - a.elem[1][0] * a.elem[0][1];
}

// Submatrix of a 3*3 matrix
Mat2 mat3SubM(size_t row, size_t col, Mat3 a)
{
    size_t skipRow = 0;
    size_t skipCol = 0;
    Mat2 result;
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            if (i == row || j == col)
            {
                if (i == row)
                {
                    skipRow = 1;
                    result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
                }
                if (j == col)
                {
                    skipCol = 1;
                    result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
                }
            }
            else
            {
                result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
            }
        }
        skipCol = 0;
    }
    return result;
}

// Submatrix of a 4*4 matrix
Mat3 mat4SubM(size_t row, size_t col, Mat4 a)
{
    size_t skipRow = 0;
    size_t skipCol = 0;
    Mat3 result;
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            if (i == row || j == col)
            {
                if (i == row)
                {
                    skipRow = 1;
                    result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
                }
                if (j == col)
                {
                    skipCol = 1;
                    result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
                }
            }
            else
            {
                result.elem[i][j] = a.elem[i + skipRow][j + skipCol];
            }
        }
        skipCol = 0;
    }
    return result;
}

// Calculates the minor of a 3*3 matrix
double mat3Min(size_t row, size_t col, Mat3 a)
{
    return mat2Det(mat3SubM(row, col, a));
}

// Calculates the cofactor of a 3*3 matrix
double mat3Cof(size_t row, size_t col, Mat3 a)
{
    if (row % 2 != col % 2)
    {
        return -mat3Min(row, col, a);
    }
    else
    {
        return mat3Min(row, col, a);
    }
}
