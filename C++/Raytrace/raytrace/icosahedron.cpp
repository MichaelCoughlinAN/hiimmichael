/*
    icosahedron.cpp

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

    Implements the icosahedron - a 20-sided regular polyhedron.
    See:  http://en.wikipedia.org/wiki/Icosahedron
*/

#include "polyhedra.h"

namespace Imager
{
    Icosahedron::Icosahedron(Vector center, double s, const Optics& optics)
        : TriangleMesh(center)
    {
        // As explained in the Wikipedia article http://en.wikipedia.org/wiki/Icosahedron
        // under the "Cartesian coordinates" section, the 12 vertex points are at
        //     (0,    +/-1, +/-p)
        //     (+/-1, +/-p,    0)
        //     (+/-p,    0, +/-1)
        // where p = (1 + sqrt(5))/2, also known as the Golden Ratio.
        // We adjust all of these to be clustered around the specified center location.

        const double p = s * (1.0 + sqrt(5.0)) / 2.0;

        // Add the 12 vertices...

        AddPoint( 0, center.x, center.y + s, center.z + p);
        AddPoint( 1, center.x, center.y + s, center.z - p);
        AddPoint( 2, center.x, center.y - s, center.z + p);
        AddPoint( 3, center.x, center.y - s, center.z - p);

        AddPoint( 4, center.x + s, center.y + p, center.z);
        AddPoint( 5, center.x + s, center.y - p, center.z);
        AddPoint( 6, center.x - s, center.y + p, center.z);
        AddPoint( 7, center.x - s, center.y - p, center.z);

        AddPoint( 8, center.x + p,   center.y, center.z + s);
        AddPoint( 9, center.x + p,   center.y, center.z - s);
        AddPoint(10, center.x - p,   center.y, center.z + s);
        AddPoint(11, center.x - p,   center.y, center.z - s);

        // Add the 20 triangular faces.
        // I built a physical model of an icosahedron
        // and labeled the vertices using the point indices above.
        // I then labeled the faces with lowercase letters as
        // show in the comments for each AddTriangle call below.
        // Each triplet of points in each AddTriangle call is arranged
        // in counterclockwise order as seen from outside the icosahedron,
        // so that vector cross products will work correctly to 
        // calculate the surface normal unit vectors for each face.

        AddTriangle( 2,  8,  0,  optics);    // a
        AddTriangle( 2,  0, 10,  optics);    // b
        AddTriangle( 2, 10,  7,  optics);    // c
        AddTriangle( 2,  7,  5,  optics);    // d
        AddTriangle( 2,  5,  8,  optics);    // e

        AddTriangle( 9,  8,  5,  optics);    // f
        AddTriangle( 9,  5,  3,  optics);    // g
        AddTriangle( 9,  3,  1,  optics);    // h
        AddTriangle( 9,  1,  4,  optics);    // i
        AddTriangle( 9,  4,  8,  optics);    // j

        AddTriangle( 6, 11, 10,  optics);    // k
        AddTriangle( 6, 10,  0,  optics);    // l
        AddTriangle( 6,  0,  4,  optics);    // m
        AddTriangle( 6,  4,  1,  optics);    // n
        AddTriangle( 6,  1, 11,  optics);    // o

        AddTriangle( 7, 10, 11,  optics);    // p
        AddTriangle( 7, 11,  3,  optics);    // q
        AddTriangle( 7,  3,  5,  optics);    // r
        AddTriangle( 0,  8,  4,  optics);    // s
        AddTriangle( 1,  3, 11,  optics);    // t
    }
}
