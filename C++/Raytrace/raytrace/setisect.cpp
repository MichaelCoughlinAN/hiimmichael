/*
    setisect.cpp

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
    Implements SetIntersection, a class that creates a new solid based
    on the intersection (overlapping portion) of two other solids.
*/

#include "imager.h"

namespace Imager
{
    void SetIntersection::AppendOverlappingIntersections(            
        const Vector&       vantage,
        const Vector&       direction,
        const SolidObject&  aSolid, 
        const SolidObject&  bSolid, 
        IntersectionList&   intersectionList) const

    {
        // Find all the intersections of aSolid with the ray emanating 
        // from the vantage point.
        tempIntersectionList.clear();
        aSolid.AppendAllIntersections(vantage, direction, tempIntersectionList);

        // For each intersection, append to intersectionList 
        // if the point is inside bSolid.
        IntersectionList::const_iterator iter = tempIntersectionList.begin();
        IntersectionList::const_iterator end  = tempIntersectionList.end();
        for (; iter != end; ++iter)
        {
            if (bSolid.Contains(iter->point))
            {
                intersectionList.push_back(*iter);
            }
        }
    }

    void SetIntersection::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        AppendOverlappingIntersections(
            vantage, direction, Left(),  Right(), intersectionList);

        AppendOverlappingIntersections(
            vantage, direction, Right(), Left(),  intersectionList);
    }

    bool SetIntersection::HasOverlappingIntersection(
        const Vector&       vantage,
        const Vector&       direction,
        const SolidObject&  aSolid,
        const SolidObject&  bSolid) const
    {
        // Find all the intersections of aSolid with the ray emanating from vantage.
        tempIntersectionList.clear();
        aSolid.AppendAllIntersections(vantage, direction, tempIntersectionList);

        // Iterate through all the intersections we found with aSolid.
        IntersectionList::const_iterator iter = tempIntersectionList.begin();
        IntersectionList::const_iterator end  = tempIntersectionList.end();
        for (; iter != end; ++iter)
        {
            // If bSolid contains any of the intersections with aSolid, then
            // aSolid and bSolid definitely overlap at that point.
            if (bSolid.Contains(iter->point))
            {
                return true;
            }
        }

        // Either there was no intersection with aSolid in this direction 
        // from the vantage point, or none of them were contained by bSolid.
        return false;
    }
}
