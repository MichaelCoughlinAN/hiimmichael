/*  
 *  Vector3D.h
 *
 *  Created by Pete Willemsen on 01/19/2011.
 *  Copyright 2011 Department of Computer Science, University of Minnesota Duluth. All rights reserved.
 *
 * This file is part of the CS5721 Computer Graphics library (libSIVELab).
 *
 * libSIVELab is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libSIVELab is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with libSIVELab.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CS5721_GRAPHICSLIB_VECTOR3__
#define __CS5721_GRAPHICSLIB_VECTOR3__ 1

#include <cassert>
#include <iostream>
#include <cmath>

class Vec2D
{
public:
  float x, y;
};


//! Namespace to hold all classes and functionality for CS 5721.
/** 
 * Namespace will be set to contain classes and functionality related
 * to the projects in CS 5721 Computer Graphics at the University of
 * Minnesota Duluth.
 */
namespace sivelab
{
  //! Class representing a basic 3D vector for use with ray tracers and rasterizers in CS5721
  /**
   *
   */
  class Vector3D {
  public:

    //! Default constructor for the Vector3D class.  Sets all values to 0.
    Vector3D() { data[0]=data[1]=data[2]=0; }

    //! Constructor for the Vector3D class that sets values to provided x, y, and z values.
    Vector3D(const double x, const double y, const double z) { data[0]=x; data[1]=y; data[2]=z; }

    //! Destructor
    ~Vector3D() {}

    //! 
    /**
     */
    const double operator[](const int i) const
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 3); 
      return data[i]; 
    }
    
    //! 
    /** Allows the setting of vector values through the operator[]
     */
    double& operator[](const int i)
    { 
      // do a sanity check to make sure indices are OK!
      assert(i >= 0 && i < 3); 
      return data[i]; 
    }


    //! 
    /** Sets the components, piecewise in the vector.
     */    
    void set(const double x, const double y, const double z) { data[0]=x; data[1]=y; data[2]=z; }

    //! 
    /** Given a vectors, sets the components of the lhs vector.
     */    
    void set(const Vector3D& v) { data[0]=v[0]; data[1]=v[1]; data[2]=v[2]; }
    
    
    //! 
    /** Computes the length of the vector and returns it.
     */    
    double length(void) const
    {
      return sqrt( data[0]*data[0] + 
		   data[1]*data[1] +
		   data[2]*data[2] );
    }


    //! Destructively normalize the vector, making it unit length.
    /** @return the length of the vector prior to normalization.
     */
    double normalize(void);                

    //! Compute the dot product between two vectors. 
    /**
     */
    double dot(const Vector3D &v) const
    {
      return data[0]*v[0] + data[1]*v[1] + data[2]*v[2];
    }

    //! Compute the cross product between two vectors. 
    /**
     */
    Vector3D cross(const Vector3D &v) const
    {
      return Vector3D(data[1] * v[2] - data[2] * v[1],
		      data[2] * v[0] - data[0] * v[2],
		      data[0] * v[1] - data[1] * v[0]);
    }

    Vector3D clamp(double min, double max)
    {
      for (unsigned int i=0; i<3; i++)
	{
	  if (data[i] < min) data[i] = min;
	  if (data[i] > max) data[i] = max;
	}
      return *this;
    }

    float max() const 
    {
      if (data[0] > data[1] && data[0] > data[2])
	return data[0];
      else if (data[1] > data[0] && data[1] > data[2])
	return data[1];
      else
	return data[2];
    }

    //! Vector3D assignment operator.  Let's you do v1 = v2;
    /** @param
     * @return a reference to the Vector3D to allow chaining of operations.
     */
    Vector3D &operator=(const Vector3D &rhs)
    {
      // v1 = v2 --> same as v1.operator=(v2);
      data[0] = rhs.data[0];
      data[1] = rhs.data[1];
      data[2] = rhs.data[2];
      return *this;
    }

    //! 
    Vector3D &operator+=(const Vector3D &rhs)
    {
      data[0] += rhs.data[0];
      data[1] += rhs.data[1];
      data[2] += rhs.data[2];
      return *this;
    }

    Vector3D &operator-=(const Vector3D &rhs)
    {
      data[0] -= rhs.data[0];
      data[1] -= rhs.data[1];
      data[2] -= rhs.data[2];
      return *this;
    }
    
    Vector3D& operator*=(const double c)
    {
      data[0] *= c;
      data[1] *= c;
      data[2] *= c;
      return *this;
    }

    Vector3D& operator/=(const double c)
    {
      data[0] /= c;
      data[1] /= c;
      data[2] /= c;
      return *this;
    }

  private:
    friend std::ostream& operator<<(std::ostream& os, const Vector3D &v);
    friend std::istream& operator>>(std::istream& is, Vector3D &v); 
    
    double data[3];
  };

  const Vector3D operator+(const Vector3D& lhs, const Vector3D& rhs);
  const Vector3D operator-(const Vector3D& lhs, const Vector3D& rhs);
  const Vector3D operator*(const Vector3D& lhs, const double rhs);
  const Vector3D operator*(const double rhs, const Vector3D &lhs);
  const Vector3D operator/(const Vector3D& lhs, const double rhs);

  // good for component wise multiplication of color values
  const Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs);

}

#endif // __CS5721_GRAPHICSLIB_VECTOR3__
