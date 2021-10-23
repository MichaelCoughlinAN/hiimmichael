#ifndef ____main__
#define ____main__

#define MAX_DEPTH 3

#include <iostream>
#include <list>
#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "image.h"
#include "shape.h"
#include "light.h"
#include "surFinish.h"
#include "scene.h"

class Vec;
class Matrix;
class Ray;
class Image;
class Shape;
class Sphere;
class SurFinish;
class Light;
class Scene;

Vec sphereMapping(Vec pt, Vec n, Pigment p);
Ray reflect(Ray ray, Vec pt, Vec normal);
Ray transmit(Ray ray, Vec pt, Vec normal, float ior1, float ior2);
Vec phongModel(Vec pt, Vec n, Light* light, Shape* obj, Ray ray);
Vec trace(Ray ray, int depth);


#endif
