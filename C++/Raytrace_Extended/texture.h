#ifndef _texture_
#define _texture_

#include <math.h>
#include <iostream>
#include <cstdlib>
#include "vector.h"

class Vec;

class Texture {

public:
  char* filename;
  int width;
  int height;
  Vec** textures;
  
  Texture();
  Texture(char *fn);
  ~Texture();
  int allowedSize(int x);
  void readImage();
  void print();

};


#endif
