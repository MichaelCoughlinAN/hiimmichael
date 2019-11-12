#include "image.h"

/** Constructor **/
Image::Image(){
  width = 0;
  height = 0;
  bgColor = Vec(0,0,0);
}

Image::Image(int w, int h){
  width = w;
  height = h;
  imageData = new float[w*h*3];
  bgColor = Vec(0.0, 0.0, 0.0);
}

/** Destructor **/
Image::~Image() {
  delete [] imageData;
}

/** Getters **/
int Image::getWidth() { return width; }
int Image::getHeight() { return height; }

/** Set the color of a particular pixel
 ** @param pixelValues color information
 ** @param x x-coordinate of the pixel
 ** @param y y-coordinate of the pixel
 **/
void Image::setPixel(const float *pixelValues, const int x, const int y){
  imageData[(y * width + x) * 3] = pixelValues[0];
  imageData[(y * width + x) * 3 + 1] = pixelValues[1];
  imageData[(y * width + x) * 3 + 2] = pixelValues[2];
}

/** Set the camera frame 
 ** @param eye
 ** @param at the center of the scene (where the camera is pointing at)
 ** @param up the "up" direction of the camera
 **/
void Image::setCamera(Vec eye, Vec at, Vec up) {
  cf.eyePos = eye;
  cf.cameraZ = (at - eye).normalize() * (-1.0);
  cf.cameraX = (up.cross(cf.cameraZ)).normalize();
  cf.cameraY = cf.cameraZ.cross(cf.cameraX);
}

/** Map the pixel center defined in raster frame to that defined in camera frame
 ** @param p vector pos of pixel
 ** @param fovy y-field of view in degrees
 ** @return pos of the pixel relative to the camera
 **/
Vec Image::normalizePixel (Vec p, float fovy){
  Vec np, wp;
  float aspectRatio = (float)width/height;
  float h = tan(fovy/2.0 * PI/180)*2.0;
  float w = h * aspectRatio;
  // compute the coordinates of p in the camera coordinates
  np.x = w * (p.x/width - 0.5);
  np.y = h * (-1.0 * (p.y/height) + 0.5);
  np.z = -1.0;
  // compute the coorinates of p in world coordinates
  wp = cf.eyePos + cf.cameraX * np.x + cf.cameraY * np.y + cf.cameraZ * np.z;
  return wp;
}

/** Write ppm file
 ** @param filename the name of output file
 **/
void Image::writeToPPM (const char *filename) {
  ofstream ofs;
  ofs.open(filename, ios::out);
  ofs << "P6\n" << width << " " << height << "\n255\n";
  float *pixel = imageData;
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      unsigned char r = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[0], 1/2.2) * 255 + 0.5f)));
      unsigned char g = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[1], 1/2.2) * 255 + 0.5f)));
      unsigned char b = (unsigned char)(std::max(0.f, std::min(255.f, powf(pixel[2], 1/2.2) * 255 + 0.5f)));
      ofs << r << g << b;
      pixel += 3;
    }
  }
  ofs.close();
}
