/*
    torus.cpp

    Copyright (C) 2013 by Don Cross  -  http://cosinekitty.com/raytrace

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the author be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
       distribution.

    -------------------------------------------------------------------------
    Implements class Torus, a donut-shaped object.
*/

#include "algebra.h"
#include "imager.h"

namespace Imager
{
    int Torus::SolveIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        double uArray[4]) const
    {
        // Set up the coefficients of a quartic equation for the intersection
        // of the parametric equation P = vantage + u*direction and the 
        // surface of the torus.
        // There is far too much algebra to explain here.
        // See the text of the tutorial for derivation.

        const double T = 4.0 * R * R;
        const double G = T * (direction.x*direction.x + direction.y*direction.y);
        const double H = 2.0 * T * (vantage.x*direction.x + vantage.y*direction.y);
        const double I = T * (vantage.x*vantage.x + vantage.y*vantage.y);
        const double J = direction.MagnitudeSquared();
        const double K = 2.0 * DotProduct(vantage, direction);
        const double L = vantage.MagnitudeSquared() + R*R - S*S;

        const int numRealRoots = Algebra::SolveQuarticEquation(
            J*J,                    // coefficient of u^4
            2.0*J*K,                // coefficient of u^3
            2.0*J*L + K*K - G,      // coefficient of u^2
            2.0*K*L - H,            // coefficient of u^1 = u
            L*L - I,                // coefficient of u^0 = constant term
            uArray                  // receives 0..4 real solutions
        );

        // We need to keep only the real roots.
        // There can be significant roundoff error in quartic solver, 
        // so we have to tolerate more slop than usual.
        const double SURFACE_TOLERANCE = 1.0e-4;   
        int numPositiveRoots = 0;
        for (int i=0; i < numRealRoots; ++i)
        {
            // Compact the array...
            if (uArray[i] > SURFACE_TOLERANCE)
            {
                uArray[numPositiveRoots++] = uArray[i];
            }
        }

        return numPositiveRoots;
    }

    void Torus::ObjectSpace_AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        double u[4];
        const int numSolutions = SolveIntersections(vantage, direction, u);
        for (int i=0; i < numSolutions; ++i)
        {
            Intersection intersection;
            const Vector disp = u[i] * direction;
            intersection.point = vantage + disp;
            intersection.distanceSquared = disp.MagnitudeSquared();
            intersection.surfaceNormal = SurfaceNormal(intersection.point);
            intersection.solid = this;
            intersectionList.push_back(intersection);
        }
    }

    Vector Torus::SurfaceNormal(const Vector& point) const
    {
        // Thanks to the fixed orientation of the torus in object space,
        // it always lies on the xy plane, and centered at <0,0,0>.
        // Therefore, if we drop a line in the z-direction from
        // any point P on the surface of the torus to the xy plane,
        // we find a point P' the same direction as a point Q at the center
        // of the torus tube.  Converting P' to a unit vector and multiplying
        // the result by the magnitude of Q (which is the constant R)
        // gives us the coordinates of Q.  Then the surface normal points
        // in the same direction as the difference P-Q.
        // See the tutorial text for more details.

        const double a = 1.0 - (R / sqrt(point.x*point.x + point.y*point.y));
        return Vector(a*point.x, a*point.y, point.z).UnitVector();
    }

    bool Torus::ObjectSpace_Contains(const Vector& point) const
    {
        // See http://en.wikipedia.org/wiki/Torus "Geometry" section about
        // solution of torus as f(x,y,z) = 0.
        // We calculate the same function f here applied to the given point.
        // If f(x,y,z) <= 0 (with EPSILON tolerance for roundoff error), we
        // consider the point inside the torus.

        const double t = R - std::sqrt(point.x*point.x + point.y*point.y);
        const double f = t*t + point.z*point.z - S*S;
        return f <= EPSILON;
    }
}
