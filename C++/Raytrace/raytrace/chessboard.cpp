/*
    chessboard.cpp

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
*/

#include <cmath>
#include "chessboard.h"

namespace Imager
{
    ChessBoard::ChessBoard(
        double _innerSize, 
        double _xBorderSize, 
        double _yBorderSize, 
        double _thickness,
        const Color&_lightSquareColor, 
        const Color&_darkSquareColor, 
        const Color&_borderColor)
            : Cuboid(
                _innerSize/2.0 + _xBorderSize,
                _innerSize/2.0 + _yBorderSize,
                _thickness/2.0)
            , innerSize(_innerSize)
            , xBorderSize(_xBorderSize)
            , yBorderSize(_yBorderSize)
            , thickness(_thickness)
            , lightSquareColor(_lightSquareColor)
            , darkSquareColor(_darkSquareColor)
            , borderColor(_borderColor)
    {
    }


    int ChessBoard::SquareCoordinate(double xy) const
    {
        double s = floor(8.0 * (xy/innerSize + 0.5));
        if (s < 0.0)
        {
            return 0;
        }
        else if (s > 7.0)
        {
            return 7;
        }
        else
        {
            return static_cast<int>(s);
        }
    }


    Optics ChessBoard::ObjectSpace_SurfaceOptics(
        const Vector& surfacePoint,
        const void *context) const
    {
        // Start with the uniform optics this class inherits,
        // and modify the colors as needed.
        // This allows us to inherit gloss, refraction, etc.
        Optics optics = GetUniformOptics();

        // First figure out which part of the board this is.
        // If the t-coordinate (z in class Vector)
        // is significantly below the top surface, 
        // use the border color.
        if (surfacePoint.z < thickness/2.0 - EPSILON)
        {
            optics.SetMatteColor(borderColor);
        }
        else
        {
            const double half = innerSize / 2.0;

            // Assume this is on the top surface of the board.
            // Figure out whether we are inside the checkered part.
            if (fabs(surfacePoint.x) < half &&
                fabs(surfacePoint.y) < half)
            {
                // We are definitely inside the checkered part
                // of the top surface.
                // Figure out which square we are on, so we
                // can in turn figure out whether it is a light or
                // dark square, so we know how to color it.
                const int x = SquareCoordinate(surfacePoint.x);
                const int y = SquareCoordinate(surfacePoint.y);
                if (0 == ((x + y) & 1))
                {
                    optics.SetMatteColor(darkSquareColor);
                }
                else
                {
                    optics.SetMatteColor(lightSquareColor);
                }
            }
            else
            {
                // Outside the checkered part, so use border color.
                optics.SetMatteColor(borderColor);
            }
        }

        return optics;
    }
}
