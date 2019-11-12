/*
    dodecahedron.cpp

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

    Implements the dodecahedron - a 12-sided regular polyhedron.
    See:  http://en.wikipedia.org/wiki/Dodecahedron
*/

#include "polyhedra.h"

namespace Imager
{
    Dodecahedron::Dodecahedron(Vector center, double s, const Optics& optics)
        : TriangleMesh(center)
    {
        // Set debugging tag to generic term.  
        // User may overwrite this tag later, for more specificity.
        SetTag("Dodecahedron");

        // Set up constants p, r that are sized proportionally to scale parameter s.
        const double phi = (sqrt(5.0) + 1.0) / 2.0;     // the Golden Ratio
        const double p = s * phi;
        const double r = s / phi;
        const double edge = 2.0 * r;

        // Using the specified center point, arrange the 20 vertices around it.
        AddPoint( 0, center.x - r, center.y + p, center.z    );
        AddPoint( 1, center.x + r, center.y + p, center.z    );
        AddPoint( 2, center.x + s, center.y + s, center.z - s);
        AddPoint( 3, center.x,     center.y + r, center.z - p);
        AddPoint( 4, center.x - s, center.y + s, center.z - s);
        AddPoint( 5, center.x - s, center.y + s, center.z + s);
        AddPoint( 6, center.x,     center.y + r, center.z + p);
        AddPoint( 7, center.x + s, center.y + s, center.z + s);
        AddPoint( 8, center.x + p, center.y,     center.z + r);
        AddPoint( 9, center.x + p, center.y,     center.z - r);
        AddPoint(10, center.x + s, center.y - s, center.z - s);
        AddPoint(11, center.x,     center.y - r, center.z - p);
        AddPoint(12, center.x - s, center.y - s, center.z - s);
        AddPoint(13, center.x - p, center.y,     center.z - r);
        AddPoint(14, center.x - p, center.y,     center.z + r);
        AddPoint(15, center.x - s, center.y - s, center.z + s);
        AddPoint(16, center.x,     center.y - r, center.z + p);
        AddPoint(17, center.x + s, center.y - s, center.z + s);
        AddPoint(18, center.x + r, center.y - p, center.z    );
        AddPoint(19, center.x - r, center.y - p, center.z    );

        // Define the 12 pentagonal faces of the dodecahedron.
        AddFace( 0,  1,  2,  3,  4, optics, edge);        // a
        AddFace( 0,  5,  6,  7,  1, optics, edge);        // b
        AddFace( 1,  7,  8,  9,  2, optics, edge);        // c 
        AddFace( 2,  9, 10, 11,  3, optics, edge);        // d
        AddFace( 3, 11, 12, 13,  4, optics, edge);        // e
        AddFace( 4, 13, 14,  5,  0, optics, edge);        // f
        AddFace( 5, 14, 15, 16,  6, optics, edge);        // g
        AddFace( 6, 16, 17,  8,  7, optics, edge);        // h
        AddFace( 8, 17, 18, 10,  9, optics, edge);        // i
        AddFace(10, 18, 19, 12, 11, optics, edge);        // j
        AddFace(12, 19, 15, 14, 13, optics, edge);        // k
        AddFace(19, 18, 17, 16, 15, optics, edge);        // l
    }

    void Dodecahedron::AddFace(
        int aPointIndex, int bPointIndex, int cPointIndex, int dPointIndex, int ePointIndex, 
        const Optics& optics, 
        double edge)
    {
        // This method is a thin wrapper for AddPentagon that adds some sanity checking.
        // It makes sure that the edges AB, BC, CD, DE, EA are all of the same length.
        // This is to help me track down bugs.

        CheckEdge(aPointIndex, bPointIndex, edge);
        CheckEdge(bPointIndex, cPointIndex, edge);
        CheckEdge(cPointIndex, dPointIndex, edge);
        CheckEdge(dPointIndex, ePointIndex, edge);
        CheckEdge(ePointIndex, aPointIndex, edge);

        AddPentagon(aPointIndex, bPointIndex, cPointIndex, dPointIndex, ePointIndex, optics);
    }

    void Dodecahedron::CheckEdge(int aPointIndex, int bPointIndex, double edge) const
    {
        // Look at two consecutive vertices that bound a face.
        const Vector a = GetPointFromIndex(aPointIndex);
        const Vector b = GetPointFromIndex(bPointIndex);

        // The vector difference between the two points represents the edge between them.
        const Vector diff = b - a;

        // The length of the edge should match the expected value as passed in the 'edge' parameter.
        const double distance = diff.Magnitude();

        // If the error is more than one part in a million, something is definitely wrong!
        const double error = fabs((distance - edge) / edge);
        if (error > 1.0e-6)
        {
            throw ImagerException("Dodecahedron edge is incorrect.");
        }
    }
}
