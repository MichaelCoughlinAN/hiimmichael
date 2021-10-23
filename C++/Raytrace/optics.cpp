#include <cmath>
#include "imager.h"

namespace Imager
{
    void Optics::ValidateReflectionColor(const Color& color) const
    {
        // A color is valid for reflection if all its
        // components are in the range 0..1.
        // Otherwise, it is possible for multiple reflections
        // to keep "amplifying" light beyond any limit.
        if (color.red < 0.0 || color.red > 1.0)
        {
            throw ImagerException("Invalid red color component.");
        }

        if (color.green < 0.0 || color.green > 1.0)
        {
            throw ImagerException("Invalid green color component.");
        }

        if (color.blue < 0.0 || color.blue > 1.0)
        {
            throw ImagerException("Invalid blue color component.");
        }
    }

    void Optics::SetMatteColor(const Color& _matteColor)
    {
        ValidateReflectionColor(_matteColor);
        matteColor = _matteColor;
    }

    void Optics::SetGlossColor(const Color& _glossColor)
    {
        ValidateReflectionColor(_glossColor);
        glossColor = _glossColor;
    }

    void Optics::SetMatteGlossBalance(
        double glossFactor,
        const Color& rawMatteColor,
        const Color& rawGlossColor)
    {
        // Make sure the raw colors have realistic values.
        // Otherwise very high component values can defeat
        // the purpose of trying to balance reflected light
        // levels to realistic ranges.
        ValidateReflectionColor(rawMatteColor);
        ValidateReflectionColor(rawGlossColor);

        // glossFactor must be in the range 0..1.
        if (glossFactor < 0.0 || glossFactor > 1.0)
        {
            throw ImagerException("Gloss factor must be in the range 0..1");
        }
        
        // Scale the glossy and matte parts of reflected light 
        // so that an object does not reflect more light than hits it.
        SetMatteColor((1.0 - glossFactor) * rawMatteColor);
        SetGlossColor(glossFactor * rawGlossColor);
    }

    void Optics::SetOpacity(double _opacity)
    {
        if (_opacity < 0.0 || _opacity > 1.0)
        {
            throw ImagerException("Invalid opacity.");
        }
        opacity = _opacity;
    }
}
