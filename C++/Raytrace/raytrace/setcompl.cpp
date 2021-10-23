/*
    setcompl.cpp

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
    Implements class SetComplement, which represents the 
    set opposite to the nested solid.  For example,
    the set complement of a solid sphere is an infinite solid
    in all directions, except for a sphere-shaped hole inside it.

    SetComplement exists solely to act as a helper to implement
    set difference: the difference of two sets A and B is:

        A - B = A intersect complement(B).
*/

#include "imager.h"

namespace Imager
{
    void SetComplement::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        const size_t sizeBeforeAppend = intersectionList.size();
        other->AppendAllIntersections(vantage, direction, intersectionList);

        // We need to toggle the direction of the surface normal vector,
        // inverting what used to be thought of as the inside of the solid
        // to being the outside of the complement.
        // If we don't do this, it messes up surface lighting calculations
        // and causes shadows to appear where there should be light.

        for (size_t index = sizeBeforeAppend; 
             index < intersectionList.size(); 
             ++index)
        {
            intersectionList[index].surfaceNormal *= -1.0;
        }
    }
}
