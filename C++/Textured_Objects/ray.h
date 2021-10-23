#ifndef _ray_
#define _ray_

#include <iostream>
#include <fstream>
#include <math.h>
#include "vector.h";
#include "shape.h";

class Vec;
class Shape;

typedef enum RayType {
  UnknownRay = 0,
  CameraRay, // primary rays we cast to the scene
  ShadowRay, 
  ReflectedRay,
  TransmittedRay,
};

class Ray {
private:
  Vec origin;
  Vec direction;
  float tmin; // ray min distance
  float tmax; // ray max distance
  RayType type;
  
public:
  Shape* ObjPtr;
  
  /// constructor ///
  Ray();
  Ray(Vec org, Vec dir, float min, float max, RayType rt);
  
  /// destructor ///
  ~Ray();
  
  /// getters ///
  Vec getOrig();
  Vec getDir();
  float getTmin();
  float getTmax();
  
  /// calculate the destination point ///
  Vec calcDest(float t);
};

#endif
