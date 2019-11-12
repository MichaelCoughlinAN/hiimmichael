/*
    block.h

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

#ifndef __DDC_BLOCK_H
#define __DDC_BLOCK_H

#include "imager.h"

namespace Imager
{
    // A ConcreteBlock is a large cuboid with the union of two smaller cuboids subtracted from it.
    // ConcreteBlock = SetDifference(LargeCuboid, SetUnion(SmallCuboid1, SmallCuboid2))

    class ConcreteBlock: public SetDifference
    {
    public:
        ConcreteBlock(const Vector& _center, const Optics& _optics)
            : SetDifference(Vector(), CreateLargeCuboid(_optics), CreateSmallCuboidUnion(_optics))
        {
            Move(_center);
        }

    private:
        static SolidObject* CreateLargeCuboid(const Optics& _optics)
        {
            Cuboid* cuboid = new Cuboid(8.0, 16.0, 8.0);
            cuboid->SetUniformOptics(_optics);
            return cuboid;
        }

        static SolidObject* CreateSmallCuboidUnion(const Optics& _optics)
        {
            // We add a little bit in the z dimension (8.01 instead of 8.0)
            // to guarantee completely engulfing the hole.

            Cuboid *topCuboid    = new Cuboid(6.0, 6.5, 8.01);     
            Cuboid *bottomCuboid = new Cuboid(6.0, 6.5, 8.01);

            topCuboid->SetUniformOptics(_optics);
            bottomCuboid->SetUniformOptics(_optics);

            topCuboid->Move   (0.0, +7.5, 0.0);
            bottomCuboid->Move(0.0, -7.5, 0.0);

            return new SetUnion(Vector(), topCuboid, bottomCuboid);
        }
    };
}

#endif // __DDC_BLOCK_H
