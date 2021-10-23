#include "light.h"

using namespace std;

/// constructor ///
Light::Light(LightType l, Vec lPos, Vec lIntensity, Vec atten){
  type = l;
  pos = lPos;
  intensity = lIntensity;
  attenuation = atten;
}


/// returns a float of the attenuation factor ///
float Light::attenFac(float dis){
  return 1.0/(attenuation.x + attenuation.y*dis + attenuation.z * dis * dis);
}

void Light::setIntensity(Vec i){
  intensity.x = i.x; intensity.y = i.y; intensity.z = i.z;
}