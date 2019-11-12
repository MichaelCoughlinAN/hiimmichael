/*  
 *  Vector3D.cpp
 *
 *  Created by Pete Willemsen on 01/19/2011.
 *  Copyright 2011 Department of Computer Science, University of Minnesota Duluth. All rights reserved.
 *
 * This file is part of SIVELAB Computer Graphics library (sivelabGraphics).
 *
 * sivelabGraphics is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * sivelabGraphics is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with sivelabGraphics.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Vector3D.h"

using namespace std;

namespace sivelab
{
  ostream &operator<<(ostream& os, const sivelab::Vector3D& v)
  {
    os << '[' << v[0] << ' ' << v[1] << ' ' << v[2] << ']';
    return os;
  }

  istream &operator>>(istream& is, sivelab::Vector3D& v)
  {
    double x=0, y=0, z=0;
    is >> x >> y >> z;
    v.set(x,y,z);
    return is;
  }

  const sivelab::Vector3D operator+(const sivelab::Vector3D &lhs, const sivelab::Vector3D &rhs)
  {
    return sivelab::Vector3D(lhs) += rhs;
  }

  const sivelab::Vector3D operator-(const sivelab::Vector3D &lhs, const sivelab::Vector3D &rhs)
  {
    return sivelab::Vector3D(lhs) -= rhs;
  }

  const sivelab::Vector3D operator*(const sivelab::Vector3D &lhs, const double rhs)
  {
    return sivelab::Vector3D(lhs) *= rhs;
  }

  const sivelab::Vector3D operator*(const double rhs, const sivelab::Vector3D &lhs)
  {
    return sivelab::Vector3D(lhs) *= rhs;
  }


  const sivelab::Vector3D operator/(const sivelab::Vector3D &lhs, const double rhs)
  {
    return sivelab::Vector3D(lhs) /= rhs;
  }

  const Vector3D operator*(const Vector3D& lhs, const Vector3D& rhs)
  {
    sivelab::Vector3D retVec(lhs);
    retVec[0] *= rhs[0];
    retVec[1] *= rhs[1];
    retVec[2] *= rhs[2];
    return retVec;
  }
}

using namespace sivelab;

double Vector3D::normalize(void)
{
  const double vector_length = sqrt( data[0]*data[0] + 
				     data[1]*data[1] +
				     data[2]*data[2] );
  if (vector_length > 0.0)
    {
      data[0] /= vector_length;
      data[1] /= vector_length;
      data[2] /= vector_length;
    }
  
  return vector_length;
}

