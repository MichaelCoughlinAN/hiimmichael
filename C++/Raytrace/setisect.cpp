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
