#include "vector.h"
/// constructors ///
Vec::Vec(){
  x = 0; y = 0; z = 0;
}

Vec::Vec(float vx, float vy, float vz){
  x = vx; y = vy; z = vz;
}

void Vec::setVec(float vx, float vy, float vz){
  x = vx; y = vy; z = vz;
}

void Vec::setVec(Vec v){
  x = v.x; y = v.y; z = v.z;
}

/// vector math ///
Vec Vec::operator+(const Vec& right){
  float rx = x + right.x;
  float ry = y + right.y;
  float rz = z + right.z;
  Vec r(rx, ry, rz);
  return r;
}

Vec Vec::operator-(const Vec& right){
  float rx = x - right.x;
  float ry = y - right.y;
  float rz = z - right.z;
  Vec r(rx, ry, rz);
  return r;
}

Vec Vec::operator*(const float& scalar){
  float rx = x * scalar;
  float ry = y * scalar;
  float rz = z * scalar;
  Vec r(rx, ry, rz);
  return r;
}

Vec Vec::operator/(const float& scalar){
  if (scalar != 0) {
    float rx = x / scalar;
    float ry = y / scalar;
    float rz = z / scalar;
    Vec r(rx, ry, rz);
    return r;
  }else{
    return (*this);
  }
}

bool Vec::operator==(const Vec& right){
  return ((x - right.x) < 0.001 && (y - right.y) < 0.001 && (z - right.z) < 0.001);
}


float Vec::mag(){
  return sqrt(x*x + y*y + z*z);
}

float Vec::dot(Vec u){
  return x*u.x + y*u.y + z*u.z;
}

Vec Vec::cross(Vec u){
  float cx = y*u.z-z*u.y;
  float cy = z*u.x-x*u.z;
  float cz = x*u.y-y*u.x;
  Vec r(cx, cy, cz);
  return r;
}

Vec Vec::normalize(){
  float rx, ry, rz;
  float norm = mag();
  if (norm!=0) {
    rx = x/norm;
    ry = y/norm;
    rz = z/norm;
    Vec r(rx, ry, rz);
    return r;
  } else {
    Vec r;
    return r;
  }
}

float Vec::dist(Vec u){
  float rx = x-u.x;
  float ry = y-u.y;
  float rz = z-u.z;
  Vec dis(rx, ry, rz);
  return dis.mag();
}

void Vec::print(){
  printf("x = %f y = %f z = %f\n", x, y, z);
}