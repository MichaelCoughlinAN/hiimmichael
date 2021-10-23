#ifndef _image_
#define _image_

#include <iostream>
#include <fstream>
#include <math.h>
#include "vector.h"

using namespace std;

// Camera Frame
typedef struct {
  Vec eyePos;
  Vec cameraX, cameraY, cameraZ;
} Camera;


class Image {
private:
  float *imageData; // array of all pixel colors
  int width, height;
  Vec bgColor;
public:
  Camera cf; // camera frame
  
  Image();
  Image(int w, int h);
  ~Image();
  void setPixel(const float *pixelValue, const int x, const int y);
  void setCamera(Vec eye, Vec at, Vec up);
  int getWidth();
  int getHeight();
  Vec normalizePixel (Vec p, float fovy);
  void writeToPPM (const char *filename); // save pixel information to output ppm file
};

#endif
