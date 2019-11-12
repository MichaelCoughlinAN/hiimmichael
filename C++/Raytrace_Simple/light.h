#ifndef LIGHT_H
#define LIGHT_H

#include <vector>
#include "vec3.h"
using namespace std;


class Light {
public:
	Vec3 position;
	Vec3 colors;
	Light(Vec3, Vec3);
};

#endif