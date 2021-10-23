#include "surFinish.h"

SurFinish::SurFinish(){
  ambient = 0;
  diffuse = 0;
  specular = 0;
  shininess = 0;
  reflective = 0;
  transmission = 0;
  ior = 0;
}

SurFinish::SurFinish(float a, float d, float s, float alpha, float r, float t, int _ior) {
  ambient = a;
  diffuse = d;
  specular = s;
  shininess = alpha;
  reflective = r;
  transmission = t;
  ior = _ior;
}

void SurFinish::setSurFin(SurFinish sf) {
  ambient = sf.ambient;
  diffuse = sf.diffuse;
  specular = sf.specular;
  shininess = sf.shininess;
  reflective = sf.reflective;
  transmission = sf.transmission;
  ior = sf.ior;
}

void SurFinish::print(){
  printf("Surface Finish:   \n");
  printf("   ambient = %f\n", ambient);
  printf("   diffuse = %f\n", diffuse);
  printf("   specular = %f\n", specular);
  printf("   shininess = %f\n", shininess);
  printf("   reflective = %f\n", reflective);
  printf("   transmission = %f\n", transmission);
  printf("   ior = %f\n", ior);
}

