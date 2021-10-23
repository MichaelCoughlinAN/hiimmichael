/*
    triangle.cpp

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

    Implementation of class TriangleMesh, a solid object composed
    of nothing but triangular faces.
*/

#include <cmath>
#include "imager.h"

namespace Imager
{
    // Adds another triangular facet to this solid object.
    // aPointIndex, bPointIndex, cPointIndex are integer indices 
    // into the  list of points already added.
    // This allows a point to be referenced multiple times and have its 
    // location changed later without the caller having to change the (x,y,z) 
    // coordinates in multiple places.
    // Each triangle may have its own optical properties 
    // (matte, gloss, refraction, opacity).
    void TriangleMesh::AddTriangle(
        int aPointIndex, 
        int bPointIndex, 
        int cPointIndex, 
        const Optics& optics)
    {
        ValidatePointIndex(aPointIndex);
        ValidatePointIndex(bPointIndex);
        ValidatePointIndex(cPointIndex);
        if ((aPointIndex == bPointIndex) || 
            (aPointIndex == cPointIndex) || 
            (bPointIndex == cPointIndex))
        {
            // This is an error, because the triangle cannot include 
            // the same point twice (otherwise it has no area).
            throw ImagerException("Not allowed to use the same point index twice within a triangle.");
        }
        triangleList.push_back(Triangle(aPointIndex, bPointIndex, cPointIndex, optics));
    }

    void TriangleMesh::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        // Iterate through all the triangles in this solid object, 
        // looking for every intersection.
        TriangleList::const_iterator iter = triangleList.begin();
        TriangleList::const_iterator end  = triangleList.end();
        for (; iter != end; ++iter)
        {
            const Triangle& tri = *iter;
            const Vector& aPoint = pointList[tri.a];
            const Vector& bPoint = pointList[tri.b];
            const Vector& cPoint = pointList[tri.c];

            // The variables u, v, w are deliberately left 
            // uninitialized for efficiency; they are only 
            // assigned values if we find an intersection.
            double u, v, w;     

            // Sometimes we have to try more than one ordering of the points (A,B,C) 
            // in order to get a valid solution to the intersection equations.
            // Take advantage of C++ short-circuit boolean or "||" operator:
            // as soon as one of the function calls returns true, we don't call any more.
            if (AttemptPlaneIntersection(vantage, direction, aPoint, bPoint, cPoint, u, v, w) ||
                AttemptPlaneIntersection(vantage, direction, bPoint, cPoint, aPoint, u, v, w) ||
                AttemptPlaneIntersection(vantage, direction, cPoint, aPoint, bPoint, u, v, w))
            {
                // We found an intersection of the direction with the plane that passes through the points (A,B,C).
                // Figure out whether the intersection point is inside the triangle (A,B,C) or outside it.
                // We are interested only in intersections that are inside the triangle.
                // The trick here is that the values v,w are fractions that will be 0..1 along the
                // line segments AB and BC (or whichever ordered triple of points we found the solution for).
                // If we just checked that both v and w are in the range 0..1, we would be finding
                // intersections with a parallelogram ABCD, where D is the fourth point that completes the
                // parallelogram whose other vertices are ABC.
                // But checking instead that v + w <= 1.0 constrains the set of points
                // to the interior or border of the triangle ABC.
                if ((v >= 0.0) && (w >= 0.0) && (v + w <= 1.0) && (u >= EPSILON))
                {
                    // We have found an intersection with one of the triangular facets!
                    // Also determine whether the intersection point is in "front" of the vantage (positively along the direction)
                    // by checking for (u >= EPSILON).  Note that we allow for a little roundoff error by checking
                    // against EPSILON instead of 0.0, because this method is called using vantage = a point on this surface,
                    // in order to calculate surface lighting, and we don't want to act like the surface is shading itself!
                    if (u >= EPSILON)
                    {
                        // We have found a new intersection to be added to the list.
                        const Vector displacement = u * direction;

                        Intersection intersection;
                        intersection.distanceSquared = displacement.MagnitudeSquared();
                        intersection.point = vantage + displacement;
                        intersection.surfaceNormal = NormalVector(tri);
                        intersection.solid = this;
                        intersection.context = &tri;   // remember which triangle we hit, for SurfaceOptics().

                        intersectionList.push_back(intersection);
                    }
                }
            }
        }
    }

    Vector TriangleMesh::NormalVector(const Triangle& triangle) const
    {
        // We could make this run faster if we cached the normal vector for each triangle,
        // but that will mean carefully remembering to update the cache every time the vertex values 
        // in pointList are changed.

        // The normal vector is the normalized (unit magnitude) vector cross product of
        // the vectors AB and BC.  Because A,B,C are always counterclockwise as seen 
        // from outside the solid surface, the right-hand rule for cross products 
        // causes the normal vector to point outward from the solid object.
        const Vector& a = pointList[triangle.a];
        const Vector& b = pointList[triangle.b];
        const Vector& c = pointList[triangle.c];

        return CrossProduct(b - a, c - b).UnitVector();
    }

    SolidObject& TriangleMesh::Translate(double dx, double dy, double dz)
    {
        SolidObject::Translate(dx, dy, dz);     // chain to base class method, so that center gets translated correctly.

        PointList::iterator iter = pointList.begin();
        PointList::iterator end  = pointList.end();
        for (; iter != end; ++iter)
        {
            Vector& point = *iter;
            point.x += dx;
            point.y += dy;
            point.z += dz;
        }

        return *this;
    }

    SolidObject& TriangleMesh::RotateX(double angleInDegrees)
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);
        const Vector center = Center();
        PointList::iterator iter = pointList.begin();
        PointList::iterator end  = pointList.end();
        for (; iter != end; ++iter)
        {
            Vector& point = *iter;
            const double dy = point.y - center.y;
            const double dz = point.z - center.z;
            point.y = center.y + (a*dy - b*dz);
            point.z = center.z + (a*dz + b*dy);
        }

        return *this;
    }

    SolidObject& TriangleMesh::RotateY(double angleInDegrees)
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);
        const Vector center = Center();
        PointList::iterator iter = pointList.begin();
        PointList::iterator end  = pointList.end();
        for (; iter != end; ++iter)
        {
            Vector& point = *iter;
            const double dx = point.x - center.x;
            const double dz = point.z - center.z;
            point.x = center.x + (a*dx + b*dz);
            point.z = center.z + (a*dz - b*dx);
        }

        return *this;
    }

    SolidObject& TriangleMesh::RotateZ(double angleInDegrees)
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);
        const Vector center = Center();
        PointList::iterator iter = pointList.begin();
        PointList::iterator end  = pointList.end();
        for (; iter != end; ++iter)
        {
            Vector& point = *iter;
            const double dx = point.x - center.x;
            const double dy = point.y - center.y;
            point.x = center.x + (a*dx - b*dy);
            point.y = center.y + (a*dy + b*dx);
        }

        return *this;
    }

    Optics TriangleMesh::SurfaceOptics(
        const Vector& surfacePoint, 
        const void *context) const
    {
        // Each triangular face may have different optics,
        // so we take advantage of the fact that 'context' is
        // set to point to whichever Triangle the ray intersected.
        const Triangle& triangle = *static_cast<const Triangle *>(context);
        return triangle.optics;
    }
}
