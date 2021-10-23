#ifndef VECTOR3D_H
#define VECTOR3D_H

#pragma once
 
#include <math.h>
 
class Vector3D {
 private: 
  float x, y, z;
    
 public:
    Vector3D(float x = 0, float y = 0, float z = 0);
   ~Vector3D() {};
 
    float length() const;
    float normalize();
    float dotProduct(const Vector3D& v3) const;
    float crossProduct(const Vector3D& v3) const;
    float* vecfData(const Vector3D& v); 
    static Vector3D zero();
 
    Vector3D& operator= (const Vector3D& v3);
    Vector3D& operator+= (const Vector3D& v3);
    Vector3D& operator-= (const Vector3D& v3);
    Vector3D& operator*= (const float scalar);
    Vector3D& operator/= (const float scalar);
    const Vector3D operator+(const Vector3D &v3) const;
    const Vector3D operator-(const Vector3D &v3) const;
    const Vector3D operator*(const float scalar) const;
    const Vector3D operator/(const float scalar) const;
    bool operator== (const Vector3D& v3) const;
    bool operator!= (const Vector3D& v3) const;
    
    float getX();
    float getY();
    float getZ();
    void set(float nX, float nY, float nZ);
    
};

#endif
