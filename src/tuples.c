/*
 * tuples.c - 3D tuple (point and vector) implementation
 *
 * Copyright (c) 2023, Dimitrios Alexopoulos All rights reserved.
 */

#include <math.h>

#include "tuples.h"

// Returns a point (w = 1)
Tuple point(double x, double y, double z)
{
    return (Tuple){x, y, z, 1};
}

// Returns a vector (w = 0)
Tuple vector(double x, double y, double z)
{
    return (Tuple){x, y, z, 0};
}

// Adds two tuples
Tuple tupleAdd(Tuple a, Tuple b)
{
    return (Tuple){a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

// Subtracts two tuples
Tuple tupleSub(Tuple a, Tuple b)
{
    return (Tuple){a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

// Negates a tuple
Tuple tupleNeg(Tuple a)
{
    return (Tuple){-a.x, -a.y, -a.z, -a.w};
}

// Scalar multiplication of a tuple by a double
Tuple tupleMul(Tuple a, double c)
{
    return (Tuple){c * a.x, c * a.y, c * a.z, c * a.w};
}

// Scalar division of a tuple by a double
Tuple tupleDiv(Tuple a, double c)
{
    return (Tuple){a.x / c, a.y / c, a.z / c, a.w / c};
}

// Returns the magnitude of the tuple
double tupleMag(Tuple a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2) + pow(a.w, 2));
}

// Returns the normalized tuple
Tuple tupleNorm(Tuple a)
{
    double mag = tupleMag(a);
    return (Tuple){a.x / mag, a.y / mag, a.z / mag, a.w / mag};
}

// Returns the dot product
double tupleDot(Tuple a, Tuple b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

// Returns the cross product (works only on vectors, w = 0)
Tuple tupleCross(Tuple a, Tuple b)
{
    return (Tuple){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x, 0};
}
