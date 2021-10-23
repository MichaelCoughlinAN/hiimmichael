#include "imager.h"

namespace Imager
{
    void SetUnion::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        // Find all intersections with the left solid.
        Left().AppendAllIntersections(vantage, direction, intersectionList);

        // Append all intersections with the right solid.
        Right().AppendAllIntersections(vantage, direction, intersectionList);
    }
}
