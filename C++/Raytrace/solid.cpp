#include "imager.h"

namespace Imager
{
    bool SolidObject::Contains(const Vector& point) const
    {
        // FIXFIXFIX:  This function does not handle the "corner case":
        // multiple intersections found at the same point but for
        // different facets of the solid.

        if (isFullyEnclosed)
        {
            // This method assumes that the solid's surfaces fully
            // enclose a volume of space without any gaps or cracks.
            // Pick an arbitrary direction in space and count the number
            // of times we enter and exit this solid.
            const Vector direction(0.0, 0.0, 1.0);

            enclosureList.clear();
            AppendAllIntersections(point, direction, enclosureList);

            int enterCount = 0;     // number of times we enter the solid
            int exitCount  = 0;     // number of times we exit the solid

            IntersectionList::const_iterator iter = enclosureList.begin();
            IntersectionList::const_iterator end  = enclosureList.end();
            for (; iter != end; ++iter)
            {
                const Intersection& intersection = *iter;

                // Calculate the dot product of the direction with 
                // the surface normal.  
                const double dotprod = DotProduct(
                    direction, 
                    intersection.surfaceNormal);

                // If it is positive, we are exiting the solid.
                // If it is negative, we are entering the solid.  
                if (dotprod > EPSILON)
                {
                    ++exitCount;
                }
                else if (dotprod < -EPSILON)
                {
                    ++enterCount;
                }
                else
                {
                    // If the dot product is too close to zero, 
                    // something odd is going on because we 
                    // should not have found an intersection
                    // with a plane in the first place.
                    throw ImagerException("Ambiguous transition.");
                }
            }

            // If the original point is within this solid,
            // we have exited the object one more time than we entered.
            // Otherwise, we have exited and entered the same number of times.
            switch (exitCount - enterCount)
            {
            case 0:
                return false;   // point is outside the solid

            case 1:
                return true;    // point is inside the solid

            default:
                // This can happen only if the solid's surfaces
                // do not properly enclose a volume of space without
                // gaps.  Either the surfaces need to be corrected
                // so as to perfectly seal the interior volume
                // or this instance should be constructed with 
                // isFullyEnclosed initialized to false.
                throw ImagerException("Cannot determine containment.");
            }
        }
        else
        {
            // Whoever constructed this object has indicated that
            // it should not be considered to contain any points.
            return false;
        }
    }
}
