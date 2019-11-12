/*
    cylinder.cpp

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
*/

#include "algebra.h"
#include "imager.h"

namespace Imager
{
    void Cylinder::ObjectSpace_AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        // Look for intersections with the disks on the top and/or bottom of the cylinder.
        if (fabs(direction.z) > EPSILON)
        {
            AppendDiskIntersection(vantage, direction, +b, intersectionList);
            AppendDiskIntersection(vantage, direction, -b, intersectionList);
        }

        // Look for intersections with the curved lateral surface of the cylinder.
        double u[2];
        const int numRoots = Algebra::SolveQuadraticEquation(
            direction.x*direction.x + direction.y*direction.y,
            2.0*(vantage.x*direction.x + vantage.y*direction.y),
            vantage.x*vantage.x + vantage.y*vantage.y - a*a,
            u
        );

        for (int i=0; i < numRoots; ++i)
        {
            if (u[i] > EPSILON)
            {
                Intersection intersection;
                Vector displacement = u[i] * direction;
                intersection.point = vantage + displacement;

                // We found an intersection with the infinitely-extended lateral surface,
                // but the z-component must be within + or - b.

                if (fabs(intersection.point.z) <= b)
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(intersection.point.x, intersection.point.y, 0.0).UnitVector();
                    intersection.solid = this;

                    intersectionList.push_back(intersection);
                }
            }
        }
    }

    void Cylinder::AppendDiskIntersection(const Vector& vantage, const Vector& direction, double zDisk, IntersectionList& intersectionList) const
    {
        const double u = (zDisk - vantage.z) / direction.z;
        if (u > EPSILON)
        {
            Intersection intersection;
            Vector displacement = u * direction;
            intersection.point = vantage + displacement;
            const double x = intersection.point.x;
            const double y = intersection.point.y;
            if (x*x + y*y <= a*a)
            {
                intersection.distanceSquared = displacement.MagnitudeSquared();
                intersection.surfaceNormal = Vector(0.0, 0.0, (zDisk > 0.0) ? +1.0 : -1.0);
                intersection.solid = this;

                intersectionList.push_back(intersection);
            }
        }
    }
}
