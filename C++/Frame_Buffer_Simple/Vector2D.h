#ifndef _VECTOR2D_H
#define _VECTOR2D_H

#pragma once
 
#include <math.h>
 
class Vector2D {
 private: 
    float x, y;
    
 public:
    Vector2D(float x = 0, float y = 0);
    ~Vector2D() {};
 
    void rotate(const float angle );
    float length() const;
    float normalize();
    float dotProduct(const Vector2D& v2) const;
    float crossProduct(const Vector2D& v2) const;
    float* vecfData(const Vector2D& v);  
    static Vector2D zero();
    static float distance(const Vector2D& v1, const Vector2D& v2);
 
    Vector2D& operator= (const Vector2D& v2);
    Vector2D& operator+= (const Vector2D& v2);
    Vector2D& operator-= (const Vector2D& v2);
    Vector2D& operator*= (const float scalar);
    Vector2D& operator/= (const float scalar);
    const Vector2D operator+(const Vector2D &v2) const;
    const Vector2D operator-(const Vector2D &v2) const;
    const Vector2D operator*(const float scalar) const;
    const Vector2D operator/(const float scalar) const;
    bool operator== (const Vector2D& v2) const;
    bool operator!= (const Vector2D& v2) const;

    float getX();
    float getY();
    void set(float nX, float nY);
    
};

#endif
