/*
    chessboard.h

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

    Example of overriding the surface optics to make a variety of colors
    on the surface of a single solid object.
    Implements a chess board with alternately colored squares.
    The checkered part has a common width and height, along with
    a separate border dimension in the x and y directions.
    The board has a thickness too.  The sides and bottom of the board
    have the same color as the border around the top.
*/

#ifndef __DDC_IMAGER_CHESSBOARD_H
#define __DDC_IMAGER_CHESSBOARD_H

#include "imager.h"

namespace Imager
{
    class ChessBoard: public Cuboid
    {
    public:
        ChessBoard(
            double _innerSize, 
            double _xBorderSize, 
            double _yBorderSize,
            double _thickness,
            const Color& _lightSquareColor,
            const Color& _darkSquareColor,
            const Color& _borderColor);

    protected:
        // This method override provides the variety of colors
        // for the light squares, dark squares, and border.
        virtual Optics ObjectSpace_SurfaceOptics(
            const Vector& surfacePoint,
            const void *context) const;

        int SquareCoordinate(double xy) const;

    private:
        double innerSize;
        double xBorderSize;
        double yBorderSize;
        double thickness;
        Color  lightSquareColor;
        Color  darkSquareColor;
        Color  borderColor;
    };
}

#endif // __DDC_IMAGER_CHESSBOARD_H
