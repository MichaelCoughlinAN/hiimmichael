#ifndef _util_
#define _util_

#include <iostream>
#include <math.h>
#include "vector.h"

class Vec;

/// solve the function ax + b = 0, store the solution to x ///
bool solveLinear(float a, float b, float &x);

/// solve the quadratic equation and store the smaller solution to t0, the larger one to t1 ///
bool solveQuadratic(float a, float b, float c, float &t0, float &t1);

bool sameSide(Vec pt, Vec v0, Vec v1, Vec v2);
bool inTriangle(Vec pt, Vec v0, Vec v1, Vec v2);

#endif
