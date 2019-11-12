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
