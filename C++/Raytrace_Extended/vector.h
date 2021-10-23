#ifndef _vector_
#define _vector_

#include <iostream>
#include <math.h>
#include <cstdio>

#define PI 3.14159265395

class Vec {
public:
  float x;
  float y;
  float z;
  
  Vec();
  Vec(float vx, float vy, float vz);
  
  void setVec(float vx, float vy, float vz);
  void setVec(Vec v);

  /// vector math ///
  Vec operator+(const Vec& right);
  Vec operator-(const Vec& right);
  Vec operator*(const float& scalar);
  Vec operator/(const float& scalar);
  bool operator==(const Vec& right);
  float mag();
  float dot(Vec u);
  Vec cross(Vec u);
  Vec normalize();
  float dist(Vec u);
  void print();
};



#endif
