/*
 * matrices.h - Matrix implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef MATRICES_H
#define MATRICES_H

#include <stdbool.h>
#include <stdint.h>

#include "tuples.h"

#define MAT_EPSILON 0.00001

typedef double Mat2[2][2];
typedef double Mat3[3][3];
typedef double Mat4[4][4];

bool mat2Eq(const Mat2 a, const Mat2 b);
bool mat3Eq(const Mat3 a, const Mat3 b);
bool mat4Eq(const Mat4 a, const Mat4 b);

void mat2Mul(Mat2 dest, const Mat2 a, const Mat2 b);
void mat4Mul(Mat4 dest, const Mat4 a, const Mat4 b);
Tuple mat4VecMul(const Mat4 mat, const Tuple vec);

void mat4Trans(Mat4 dest, const Mat4 a);

double mat2Det(const Mat2 a);

void mat3SubM(Mat2 dest, const uint64_t row, const uint64_t col, const Mat3 a);
void mat4SubM(Mat3 dest, const uint64_t row, const uint64_t col, const Mat4 a);
double mat3Min(const uint64_t row, uint64_t col, const Mat3 a);
double mat3Cof(const uint64_t row, uint64_t col, const Mat3 a);

#endif
