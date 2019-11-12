#include "Color.h"

Color::Color(float r, float g, float b, float a) {
	
	R = (r * 255.0f);
	G = (g * 255.0f);
	B = (b * 255.0f);
	A = (a * 255.0f);

     

}

uint32_t Color::ToUInt32() const {
	uint32_t r = (uint32_t)(R * 255.0f);
	uint32_t g = (uint32_t)(G * 255.0f);
	uint32_t b = (uint32_t)(B * 255.0f);
	uint32_t a = (uint32_t)(A * 255.0f);

	return (a << 24) | (r << 16) | (g << 8) | b;
}

Color Color::operator + (const Color &c) const {
	return Color(R + c.R, G + c.G, B + c.B, A + c.A);
}

Color Color::operator - (const Color &c) const {
	return Color(R - c.R, G - c.G, B - c.B, A - c.A);
}

Color Color::operator * (float f) const {
	return Color(R * f, G * f, B * f, A * f);
}
