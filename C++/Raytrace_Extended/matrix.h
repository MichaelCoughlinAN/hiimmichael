#ifndef _matrix_
#define _matrix_

#include <math.h>
#include <iostream>
#include "vector.h"

class Vec;

class Matrix{
public:
  float mat[4][4];
  
  /// constructor ///
  
  // default to be an identity matrix
  Matrix();
  
  // set the mat to an all-zero matrix
  void zeroMat();
  
  // set the mat to an identity matrix
  void identityMat();
  
  // addition between matrices
  Matrix operator+(const Matrix& right);
  
  // substraction between matrices
  Matrix operator-(const Matrix& right);
  
  // matrix - scalar multiplication
  Matrix operator*(const float& scalar);
  
  // multiplication between matrices
  Matrix mult(Matrix m);
  
  // returns the transpose of this matrix
  Matrix transpose();
  
  // returns the determinant of the matrix
  float det();
  
  // returns the inverse of the matrix
  Matrix inverse();
  
  // the transformation of a point
  // returns the point vector after transformation
  Vec matVec_mult(Vec pt);
  
  // the transformation of a direction vector
  // returns the direction vector after transformation
  Vec matDir_mult(Vec dir);
  
  //construct the translation matrix
  void translate(Vec pos);
  
  //construct the scale matrix
  void scale(Vec scal);
  
  //print the matrix
  void print();
};

#endif
