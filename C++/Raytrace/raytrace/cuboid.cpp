/*
    cuboid.cpp

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
*/

#include "imager.h"

namespace Imager
{
    void Cuboid::ObjectSpace_AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        double u;
        Intersection intersection;
        Vector displacement;

        // Check for intersections with left/right faces: x = +a or x = -a.
        if (fabs(direction.x) > EPSILON)
        {
            // right face (x = +a)
            u = (a - vantage.x) / direction.x;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(+1.0, 0.0, 0.0);
                    intersection.solid = this;
                    intersection.tag = "right face";
                    intersectionList.push_back(intersection);
                }
            }

            // left face (x = -a)
            u = (-a - vantage.x) / direction.x;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(-1.0, 0.0, 0.0);
                    intersection.solid = this;
                    intersection.tag = "left face";
                    intersectionList.push_back(intersection);
                }
            }
        }

        // Check for intersections with front/back faces: y = -b or y = +b.
        if (fabs(direction.y) > EPSILON)
        {
            // front face (y = +b)
            u = (b - vantage.y) / direction.y;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(0.0, +1.0, 0.0);
                    intersection.solid = this;
                    intersection.tag = "front face";
                    intersectionList.push_back(intersection);
                }
            }

            // back face (y = -b)
            u = (-b - vantage.y) / direction.y;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(0.0, -1.0, 0.0);
                    intersection.solid = this;
                    intersection.tag = "back face";
                    intersectionList.push_back(intersection);
                }
            }
        }

        // Check for intersections with top/bottom faces: z = -c or z = +c.
        if (fabs(direction.z) > EPSILON)
        {
            // top face (z = +c)
            u = (c - vantage.z) / direction.z;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(0.0, 0.0, +1.0);
                    intersection.solid = this;
                    intersection.tag = "top face";
                    intersectionList.push_back(intersection);
                }
            }

            // bottom face (z = -c)
            u = (-c - vantage.z) / direction.z;
            if (u > EPSILON)
            {
                displacement = u * direction;
                intersection.point = vantage + displacement;
                if (ObjectSpace_Contains(intersection.point))
                {
                    intersection.distanceSquared = displacement.MagnitudeSquared();
                    intersection.surfaceNormal = Vector(0.0, 0.0, -1.0);
                    intersection.solid = this;
                    intersection.tag = "bottom face";
                    intersectionList.push_back(intersection);
                }
            }
        }
    }
}
