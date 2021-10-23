#ifndef _COLOR_H_
#define _COLOR_H_

#include <stdint.h>

class Color
{
	public:
		float R, G, B, A;

		Color(float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);

		uint32_t ToUInt32() const;

		Color operator + (const Color &c) const;
		Color operator - (const Color &c) const;
		Color operator * (float f) const;
};

#endif 
