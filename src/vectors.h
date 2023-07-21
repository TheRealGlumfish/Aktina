/*
 * vectors.h - Vector and matrix implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef VECTORS_H
#define VECTORS_H

#define MAT_EPSILON 0.00001

#include <stdbool.h>
#include <stddef.h>

typedef union Vec2
{
    struct
    {
        double x, y;
    };
    struct
    {
        double u, v;
    };
    double elem[2];
} Vec2;

typedef union Vec3
{
    struct
    {
        double x, y, z;
    };
    struct
    {
        double u, v, w;
    };
    struct
    {
        double r, g, b;
    };
    struct
    {
        Vec2 xy;
        double _ignored;
    };
    double elem[3];
} Vec3;

typedef union Vec4
{
    struct
    {
        double x, y, z, w;
    };
    struct
    {
        Vec3 xyz;
        double _ignored;
    };
    double elem[4];
} Vec4;

typedef union Mat2
{
    double elem[2][2];
    Vec2 cols[2];
} Mat2;

typedef union Mat3
{
    double elem[3][3];
    Vec3 cols[3];
} Mat3;

typedef union Mat4
{
    double elem[4][4];
    Vec4 cols[4];
} Mat4;

Vec2 vec2Add(Vec2 a, Vec2 b);
Vec2 vec2Sub(Vec2 a, Vec2 b);
Vec2 vec2Mul(Vec2 a, double b);
Vec2 vec2Div(Vec2 a, double b);
Vec2 vec2Neg(Vec2 a);

double vec2Mag(Vec2 a);
Vec2 vec2Norm(Vec2 a);
double vec2Dot(Vec2 a, Vec2 b);
Vec2 vec2Prod(Vec2 a, Vec2 b);

Vec3 vec3Add(Vec3 a, Vec3 b);
Vec3 vec3Sub(Vec3 a, Vec3 b);
Vec3 vec3Mul(Vec3 a, double b);
Vec3 vec3Div(Vec3 a, double b);
Vec3 vec3Neg(Vec3 a);

double vec3Mag(Vec3 a);
Vec3 vec3Norm(Vec3 a);
double vec3Dot(Vec3 a, Vec3 b);
Vec3 vec3Cross(Vec3 a, Vec3 b);
Vec3 vec3Prod(Vec3 a, Vec3 b);

Vec4 vec4Add(Vec4 a, Vec4 b);
Vec4 vec4Sub(Vec4 a, Vec4 b);
Vec4 vec4Mul(Vec4 a, double b);
Vec4 vec4Div(Vec4 a, double b);
Vec4 vec4Neg(Vec4 a);

double vec4Mag(Vec4 a);
Vec4 vec4Norm(Vec4 a);
double vec4Dot(Vec4 a, Vec4 b);
Vec4 vec4Prod(Vec4 a, Vec4 b);

bool mat2Eq(Mat2 a, Mat2 b);
bool mat3Eq(Mat3 a, Mat3 b);

Mat2 mat2Mul(Mat2 a, Mat2 b);
Mat3 mat3Mul(Mat3 a, Mat3 b);
Mat4 mat4Mul(Mat4 a, Mat4 b);

Vec2 mat2VecMul(Mat2 mat, Vec2 vec);
Vec3 mat3VecMul(Mat3 mat, Vec3 vec);
Vec4 mat4VecMul(Mat4 mat, Vec4 vec);

Mat2 mat2Trans(Mat2 a);
Mat3 mat3Trans(Mat3 a);
Mat4 mat4Trans(Mat4 a);

double mat2Det(Mat2 a);

Mat2 mat3SubM(size_t row, size_t col, Mat3 a);
Mat3 mat4SubM(size_t row, size_t col, Mat4 a);

double mat3Min(size_t row, size_t col, Mat3 a);
double mat3Cof(size_t row, size_t col, Mat3 a);

#endif
