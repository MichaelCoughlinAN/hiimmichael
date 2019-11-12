#include "Vector3D.h"
 
// Constructor
Vector3D::Vector3D(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}
 
 
// Get vector length
float Vector3D::length() const {
    return sqrtf(x * x + y * y + z * z);
}
 
// Convert vector to a unit vector and return previous magnitude
float Vector3D::normalize() {
    float mag = length();
 
    if(mag != 0.0)
    {
        x /= mag;
        y /= mag;
	z /= mag;
    }
 
    return mag;
}
 

// Dot Product
float Vector3D::dotProduct(const Vector3D &v3) const {
  return (x * v3.x) + (y * v3.y) + (z * v3.z);
}
 
// Cross Product
float Vector3D::crossProduct(const Vector3D &v3) const {
  return (y * v3.z - z * v3.y,
	  z * v3.x - x * v3.z,
	  x * v3.y - y * v3.x);
}
 

// Return an empty vector
Vector3D Vector3D::zero() {
  return Vector3D(0, 0, 0);
}
 
 
Vector3D& Vector3D::operator= (const Vector3D& v3)
{
    if (this == &v3)
        return *this;
 
    x = v3.x;
    y = v3.y;
    z = v3.z;
 
    return *this;
}
 
Vector3D& Vector3D::operator+= (const Vector3D& v3) {
    x += v3.x;
    y += v3.y;
    z += v3.z;
    
    return *this;
}
 
Vector3D& Vector3D::operator-= (const Vector3D& v3) {
    x -= v3.x;
    y -= v3.y;
    z -= v3.z;
    
    return *this;
}
 
Vector3D& Vector3D::operator*= (const float scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    
    return *this;
}
 
Vector3D& Vector3D::operator/= (const float scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
 
    return *this;
}
 
const Vector3D Vector3D::operator+(const Vector3D &v3) const
{
    return Vector3D(*this) += v3;
}
 
const Vector3D Vector3D::operator-(const Vector3D &v3) const
{
    return Vector3D(*this) -= v3;
}
 
const Vector3D Vector3D::operator*(const float scalar) const
{
    return Vector3D(*this) *= scalar;
}
 
const Vector3D Vector3D::operator/(const float scalar) const
{
    return Vector3D(*this) /= scalar;
}
 
bool Vector3D::operator== (const Vector3D& v3) const
{
  return ((x == v3.x) && (y == v3.y) && (z == v3.z));
}
 
bool Vector3D::operator!= (const Vector3D& v3) const
{
  return !((x == v3.x) && (y == v3.y) && (z == v3.z));
}


void Vector3D::set(float nX, float nY, float nZ) {
    x = nX;
    y = nY;
    z = nZ;
}

float Vector3D::getX() {
  return x;
}

float Vector3D::getY() {
  return y;
}

float Vector3D::getZ() {
  return z;
}

float* Vector3D::vecfData(const Vector3D& v) {
  float* vecf = new float[3];

  vecf[0] = (float) v.x;  // v[0] is the first component of a Vector2D object
  vecf[1] = (float) v.y;
  vecf[1] = (float) v.z;

  return vecf;
}

