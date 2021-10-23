#ifndef _vector_
#define _vector_

#include <math.h>

/** Vector Struct **/
typedef struct {
  float x,y,z;
} vector;

/** Vector Addition **/
vector Add(vector u, vector v);

/** Vector Difference **/
vector Diff(vector u, vector v);

/** Vector Multiplication with a Scalar **/
vector Mult(vector u, float a);

/** Dot Product **/
float Dot(vector u, vector v);

/** Cross Product **/
vector Cross(vector u, vector v);

/** Magnitude of the Vector **/
float Norm(vector u);

/** Normalization **/
vector Normalize(vector u);

/** Distance **/
float Dist(vector u, vector v);

/** Null Vector **/
vector NullVector();

/** Initialization **/
vector NewVec(float x, float y, float z);

/** check if two vectors are equal **/
bool Equal(vector v1, vector v2);

#endif
