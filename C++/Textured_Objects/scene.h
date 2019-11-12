#ifndef ____scene__
#define ____scene__

#include <iostream>
#include <typeinfo>
#include <list>
#include "vector.h"
#include "matrix.h"
#include "ray.h"
#include "image.h"
#include "shape.h"
#include "light.h"
#include "surFinish.h"
#include "texture.h"

class Vec;
class Matrix;
class Ray;
class Image;
class Shape;
class Sphere;
class SurFinish;
class Light;
class Texture;

typedef std::list<Shape*> ShapeList;
typedef std::list<Shape*>::iterator ShapeIter;
typedef std::list<Light*> LightList;
typedef std::list<Light*>::iterator LightIter;

class Scene{
public:
  char outname[NAME_LEN];
  int w, h;
  Vec eyePos, at, up;
  float fovy;
  int numL, numP, numF, numT, numO;
  LightList lights;
  Pigment* pigments;
  SurFinish *sf;
  Matrix* transformations;
  ShapeList shapes;

  Scene();
  void readfile(char* filename);
  void print();
};

#endif 
