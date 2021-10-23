#include "light.h"
Light::Light(Vec3 position, Vec3 colors) {
	this->colors = colors * 10000;
	this->position = position;
}