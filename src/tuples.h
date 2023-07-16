/*
 * tuples.h - 3D tuple (point and vector) implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#ifndef TUPLES_H
#define TUPLES_H

#define color(red, green, blue) vector(red, green, blue)
#define PPM_DEPTH 255

// TODO: Change w to a bool
typedef struct
{
    double x, y, z;
    double w; // point when w = 1, vector when w = 0
} Tuple;

Tuple point(const double x, const double y, const double z);
Tuple vector(const double x, const double y, const double z);

Tuple tupleAdd(const Tuple a, const Tuple b);
Tuple tupleSub(const Tuple a, const Tuple b);
Tuple tupleNeg(const Tuple a);
Tuple tupleMul(const Tuple a, const double c);
Tuple tupleDiv(const Tuple a, const double c);

double tupleMag(const Tuple a);
Tuple tupleNorm(const Tuple a);

double tupleDot(const Tuple a, const Tuple b);
Tuple tupleCross(const Tuple a, const Tuple b);
Tuple tupleProd(const Tuple a, const Tuple b);
Tuple tuplePPM(const Tuple a);

void tick(Tuple *projectile_position, Tuple *projectile_velocity, Tuple gravity_vector, Tuple wind_vector);

#endif
