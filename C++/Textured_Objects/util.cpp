#include "util.h"

using namespace std;

/// solve the function ax + b = 0, store the solution to x ///
bool solveLinear(float a, float b, float &x){
    if (a == 0) return false;
    else x = - b / a;
    return true;
}

/// solve the function ax^2 + bx + c = 0, store the solution to x0, x1 ///
bool solveQuadratic(float a, float b, float c, float &x0, float &x1){
  
  if (a == 0) {
    float x;
    if (solveLinear(b, c, x)) {
      x0 = x1 = x;
      return true;
    } else return false;
  }
  
  float delta = b * b - 4 * a * c;
  if (delta < 0) return false;
  else if (delta ==0) x0 = x1 = -0.5 * b / a;
  else {
    x0 = 0.5 * (-b - sqrt(delta)) / a;
    x1 = 0.5 * (-b + sqrt(delta)) / a;
  }
  if (x0 > x1) std::swap(x0, x1);
	return true;
}

/// determine if a point is on the same side with a line ///
bool sameSide(Vec pt, Vec v0, Vec v1, Vec v2){
  Vec cp1 = (v1 - v0).cross(pt - v0);
  Vec cp2 = (v1 - v0).cross(v2 - v0);
  if (cp1.dot(cp2) >= 0) return true;
  else return false;
}

/// determine if a point is inside the triangle ///
bool inTriangle(Vec pt, Vec v0, Vec v1, Vec v2){
  if (sameSide(pt, v0, v1, v2) && sameSide(pt, v1, v2, v0) && sameSide(pt, v2, v0, v1))
    return true;
  else
    return false;
}