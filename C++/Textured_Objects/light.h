#ifndef ____light__
#define ____light__

#include <iostream>
#include "vector.h"

class Vec;

typedef enum LightType {
  ambient = 0,
  diffuse = 1
};

class Light{
public:
  LightType type;
  Vec pos;
  Vec intensity;
  Vec attenuation;
  
  Light(LightType type, Vec lPos, Vec lIntensity, Vec atten);
  float attenFac(float dis);
  void setIntensity(Vec i);
};

#endif 
