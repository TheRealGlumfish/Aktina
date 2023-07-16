/*
 * tuples.c - 3D tuple (point and vector) implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>

#include "tuples.h"

// NOTE: Consider making tuples double[4] type
// Returns a point (w = 1)
Tuple point(const double x, const double y, const double z)
{
    return (Tuple){x, y, z, 1};
}

// Returns a vector (w = 0)
Tuple vector(const double x, const double y, const double z)
{
    return (Tuple){x, y, z, 0};
}

// Adds two tuples
Tuple tupleAdd(const Tuple a, const Tuple b)
{
    return (Tuple){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

// Subtracts two tuples
Tuple tupleSub(const Tuple a, const Tuple b)
{
    return (Tuple){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

// Negates a tuple
Tuple tupleNeg(const Tuple a)
{
    return (Tuple){-a.x, -a.y, -a.z, -a.w};
}

// Scalar multiplication of a tuple by a double
Tuple tupleMul(const Tuple a, const double c)
{
    return (Tuple){c * a.x, c * a.y, c * a.z, c * a.w};
}

// Scalar division of a tuple by a double
Tuple tupleDiv(const Tuple a, const double c)
{
    return (Tuple){a.x / c, a.y / c, a.z / c, a.w / c};
}

// Returns the magnitude of the tuple
double tupleMag(const Tuple a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
}

// Returns the normalized tuple
Tuple tupleNorm(const Tuple a)
{
    double mag = tupleMag(a);
    return (Tuple){a.x / mag, a.y / mag, a.z / mag, a.w / mag};
}

// Returns the dot product
double tupleDot(const Tuple a, const Tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Returns the cross product (works only on vectors, w = 0)
Tuple tupleCross(const Tuple a, const Tuple b)
{
    return (Tuple){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
}

// Returns the Hadamard product
Tuple tupleProd(const Tuple a, const Tuple b)
{
    return (Tuple){a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w};
}

// Scales and limits the value of the tuple to be between 0-255 so it can be used in a PPM file
Tuple tuplePPM(const Tuple a)
{
    return (Tuple){.x = fmin(fmax(0, a.x * PPM_DEPTH), PPM_DEPTH),
                   .y = fmin(fmax(0, a.y * PPM_DEPTH), PPM_DEPTH),
                   .z = fmin(fmax(0, a.z * PPM_DEPTH), PPM_DEPTH),
                   .w = fmin(fmax(0, a.w * PPM_DEPTH), PPM_DEPTH)};
}

void tick(Tuple *projectilePosition, Tuple *projectileVelocity, Tuple gravityVector, Tuple windVector)
{
    *projectilePosition = tupleAdd(*projectilePosition, *projectileVelocity);
    *projectileVelocity = tupleAdd(*projectileVelocity, tupleAdd(gravityVector, windVector));
}
