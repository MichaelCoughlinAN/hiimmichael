#ifndef ____surFinish__
#define ____surFinish__

#include <iostream>
#include <cstdio>

class SurFinish{
public:
  float ambient, diffuse, specular, shininess, reflective, transmission, ior;
  
  SurFinish();
  SurFinish(float a, float d, float s, float alpha, float r, float t, int _ior);
  
  void setSurFin(SurFinish sf);
  void print();
};

#endif 
