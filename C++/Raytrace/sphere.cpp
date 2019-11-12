#include "imager.h"

namespace Imager
{
    void Sphere::AppendAllIntersections(
        const Vector& vantage, 
        const Vector& direction, 
        IntersectionList& intersectionList) const
    {
        // Calculate the coefficients of the quadratic equation 
        //     au^2 + bu + c = 0.
        // Solving this equation gives us the value of u 
        // for any intersection points.
        const Vector displacement = vantage - Center();
        const double a = direction.MagnitudeSquared();
        const double b = 2.0 * DotProduct(direction, displacement);
        const double c = displacement.MagnitudeSquared() - radius*radius;

        // Calculate the radicand of the quadratic equation solution formula.
        // The radicand must be non-negative for there to be real solutions.
        const double radicand = b*b - 4.0*a*c;
        if (radicand >= 0.0)
        {
            // There are two intersection solutions, one involving 
            // +sqrt(radicand), the other -sqrt(radicand).
            // Check both because there are weird special cases, 
            // like the camera being inside the sphere,
            // or the sphere being behind the camera (invisible).
            const double root = sqrt(radicand);
            const double denom = 2.0 * a;
            const double u[2] = {
                (-b + root) / denom,
                (-b - root) / denom
            };

            for (int i=0; i < 2; ++i)
            {
                if (u[i] > EPSILON)
                {
                    Intersection intersection;
                    const Vector vantageToSurface = u[i] * direction;
                    intersection.point = vantage + vantageToSurface;

                    // The normal vector to the surface of 
                    // a sphere is outward from the center.
                    intersection.surfaceNormal = 
                        (intersection.point - Center()).UnitVector();

                    intersection.distanceSquared = 
                        vantageToSurface.MagnitudeSquared();

                    intersection.solid = this;
                    intersectionList.push_back(intersection);
                }
            }
        }
    }
}
