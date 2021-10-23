#include "Vector2D.h"
 
//-----------------------------------------------------------------------------
// Purpose: Constructor
//-----------------------------------------------------------------------------
Vector2D::Vector2D( float x, float y )
{
    this->x = x;
    this->y = y;
}
 
//-----------------------------------------------------------------------------
// Purpose: Rotate a vector
//-----------------------------------------------------------------------------
void Vector2D::rotate( const float angle )
{
    float xt = (x * cosf(angle)) - (y * sinf(angle));
    float yt = (y * cosf(angle)) + (x * sinf(angle));
    x = xt;
    y = yt;
}
 
//-----------------------------------------------------------------------------
// Purpose: Get vector magnitude
//-----------------------------------------------------------------------------
float Vector2D::length() const
{
    return sqrtf(x * x + y * y);
}
 
//-----------------------------------------------------------------------------
// Purpose: Convert vector to a unit vector and return previous magnitude
//-----------------------------------------------------------------------------
float Vector2D::normalize()
{
    float mag = length();
 
    if(mag != 0.0)
    {
        x /= mag;
        y /= mag;
    }
 
    return mag;
}
 
//-----------------------------------------------------------------------------
// Purpose: Dot Product
//-----------------------------------------------------------------------------
float Vector2D::dotProduct( const Vector2D &v2 ) const
{
    return (x * v2.x) + (y * v2.y);
}
 
//-----------------------------------------------------------------------------
// Purpose: Cross Product
//-----------------------------------------------------------------------------
float Vector2D::crossProduct( const Vector2D &v2 ) const
{
    return (x * v2.y) - (y * v2.x);
}
 
//-----------------------------------------------------------------------------
// Purpose: Return an empty vector
//-----------------------------------------------------------------------------
Vector2D Vector2D::zero()
{
    return Vector2D(0, 0);
}
 
//-----------------------------------------------------------------------------
// Purpose: Get distance between two vectors
//-----------------------------------------------------------------------------
float Vector2D::distance( const Vector2D& v1, const Vector2D& v2)
{
    return sqrtf( pow((v2.x - v1.x), 2 ) + pow((v2.y - v1.y), 2) );
}
 
Vector2D& Vector2D::operator= ( const Vector2D& v2 )
{
    if (this == &v2)
        return *this;
 
    x = v2.x;
    y = v2.y;
 
    return *this;
}
 
Vector2D& Vector2D::operator+= ( const Vector2D& v2 )
{
    x += v2.x;
    y += v2.y;
 
    return *this;
}
 
Vector2D& Vector2D::operator-= ( const Vector2D& v2 )
{
    x -= v2.x;
    y -= v2.y;
 
    return *this;
}
 
Vector2D& Vector2D::operator*= ( const float scalar )
{
    x *= scalar;
    y *= scalar;
 
    return *this;
}
 
Vector2D& Vector2D::operator/= ( const float scalar )
{
    x /= scalar;
    y /= scalar;
 
    return *this;
}
 
const Vector2D Vector2D::operator+( const Vector2D &v2 ) const
{
    return Vector2D(*this) += v2;
}
 
const Vector2D Vector2D::operator-( const Vector2D &v2 ) const
{
    return Vector2D(*this) -= v2;
}
 
const Vector2D Vector2D::operator*( const float scalar ) const
{
    return Vector2D(*this) *= scalar;
}
 
const Vector2D Vector2D::operator/( const float scalar ) const
{
    return Vector2D(*this) /= scalar;
}
 
bool Vector2D::operator== ( const Vector2D& v2 ) const
{
    return ((x == v2.x) && (y == v2.y));
}
 
bool Vector2D::operator!= ( const Vector2D& v2 ) const
{
    return !((x == v2.x) && (y == v2.y));
}


void Vector2D::set(float nX, float nY) {
    x = nX;
    y = nY;
}

float Vector2D::getX() {
  return x;
}

float Vector2D::getY() {
  return y;
}

float* Vector2D::vecfData(const Vector2D& v) {
  float* vecf = new float[2];

  vecf[0] = (float) v.x;  // v[0] is the first component of a Vector2D object
  vecf[1] = (float) v.y;

  return vecf;
}
