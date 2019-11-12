#include "ray.h"

/** Constructors **/
Ray::Ray(){
  origin = Vec();
  direction = Vec();
  type = UnknownRay;
  tmin = 0;
  tmax = 1000;
  ObjPtr = NULL;
}

Ray::Ray(Vec org, Vec dir, float min, float max, RayType rt){
  origin = org;
  direction = dir;
  type = rt;
  tmin = min;
  tmax = max;
  ObjPtr = NULL;
}

/** Destructor **/
Ray::~Ray() {}

/// getters ///
Vec Ray::getOrig() { return origin; }
Vec Ray::getDir() { return direction; }
float Ray::getTmin() {return tmin;}
float Ray::getTmax() {return tmax;}

Vec Ray::calcDest(float t) { return origin + direction * t; }

