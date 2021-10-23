
#include <cmath>
#include "imager.h"

namespace Imager
{
    // Rotates counterclockwise around center looking into axis parallel to x-axis.
    SolidObject& SolidObject_Reorientable::RotateX(double angleInDegrees)    
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);

        rDir = Vector(rDir.x, a*rDir.y - b*rDir.z, a*rDir.z + b*rDir.y);
        sDir = Vector(sDir.x, a*sDir.y - b*sDir.z, a*sDir.z + b*sDir.y);
        tDir = Vector(tDir.x, a*tDir.y - b*tDir.z, a*tDir.z + b*tDir.y);

        UpdateInverseRotation();

        return *this;
    }

    // Rotates counterclockwise around center looking into axis parallel to y-axis.
    SolidObject& SolidObject_Reorientable::RotateY(double angleInDegrees)    
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);

        rDir = Vector(a*rDir.x + b*rDir.z, rDir.y, a*rDir.z - b*rDir.x);
        sDir = Vector(a*sDir.x + b*sDir.z, sDir.y, a*sDir.z - b*sDir.x);
        tDir = Vector(a*tDir.x + b*tDir.z, tDir.y, a*tDir.z - b*tDir.x);

        UpdateInverseRotation();

        return *this;
    }

    // Rotates counterclockwise around center looking into axis parallel to z-axis.
    SolidObject& SolidObject_Reorientable::RotateZ(double angleInDegrees)    
    {
        const double angleInRadians = RadiansFromDegrees(angleInDegrees);
        const double a = cos(angleInRadians);
        const double b = sin(angleInRadians);

        rDir = Vector(a*rDir.x - b*rDir.y, a*rDir.y + b*rDir.x, rDir.z);
        sDir = Vector(a*sDir.x - b*sDir.y, a*sDir.y + b*sDir.x, sDir.z);
        tDir = Vector(a*tDir.x - b*tDir.y, a*tDir.y + b*tDir.x, tDir.z);

        UpdateInverseRotation();

        return *this;
    }

    // Appends to 'intersectionList' a list of all the intersections 
    // found starting at the specified vantage point in the specified direction.
    void SolidObject_Reorientable::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        const Vector objectVantage = ObjectPointFromCameraPoint(vantage);
        const Vector objectRay     = ObjectDirFromCameraDir(direction);

        const size_t sizeBeforeAppend = intersectionList.size();

        ObjectSpace_AppendAllIntersections(
            objectVantage, 
            objectRay, 
            intersectionList
        );

        // Iterate only through the items we just appended,
        // skipping over anything that was already in the list
        // before this function was called.
        for (size_t index = sizeBeforeAppend; 
             index < intersectionList.size(); 
             ++index)
        {
            Intersection& intersection = intersectionList[index];

            // Need to transform intersection back into camera space.
            intersection.point = 
                CameraPointFromObjectPoint(intersection.point);

            intersection.surfaceNormal = 
                CameraDirFromObjectDir(intersection.surfaceNormal);
        }
    }
}
