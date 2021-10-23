#include "vector.h"

/** Addition
 ** @param u first vector
 ** @param v second vector
 ** @return resulting vector
 **/
vector Add(vector u, vector v) {
  vector w;
  w.x=u.x+v.x;
  w.y=u.y+v.y;
  w.z=u.z+v.z;
  return w;
}

/** Difference
 ** @param u first vector
 ** @param v second vector
 ** @return resulting vector
 **/
vector Diff(vector u, vector v) {
  vector w;
  w.x=u.x-v.x;
  w.y=u.y-v.y;
  w.z=u.z-v.z;
  return w;
}

/** Multiplication
 ** @param u vector
 ** @param v scalar
 ** @return resulting vector
 **/
vector Mult(vector u, float a) {
  vector w;
  w.x=u.x*a;
  w.y=u.y*a;
  w.z=u.z*a;
  return w;
}

/** Dot Product
 ** @param u first vector
 ** @param v second vector
 ** @return dot product of the two vectors
 **/
float Dot(vector u, vector v) {
  float a=u.x*v.x + u.y*v.y + u.z*v.z;
  return a;
}

/** Cross Product
 ** @param u first vector
 ** @param v second vector
 ** @return cross product of the two vectors
 **/
vector Cross(vector u, vector v){
  vector crossProd;
  crossProd.x = u.y*v.z-u.z*v.y;
  crossProd.y = u.z*v.x-u.x*v.z;
  crossProd.z = u.x*v.y-u.y*v.x;
  return crossProd;
}

/** Magnitude
 ** @param u vector
 ** @return the magnitude of the vector
 **/
float Norm (vector u) { return sqrt(Dot(u,u)); }

/** Normalization
 ** @param u vector
 ** @return unit vector
 **/
vector Normalize(vector u){
  float norm = Norm(u);
  vector v = NullVector();
    if (norm!=0) {
        v.x = u.x/norm;
        v.y = u.y/norm;
        v.z = u.z/norm;
    }
  return v;
}

/** Distance
 ** @param u first vector
 ** @param v second vector
 ** @return distance between two vectors
 **/
float Dist(vector u, vector v) {
  vector w=Diff(u,v);
  return Norm(w);
}

/** Null Vector
 ** @return a null vector
 **/
vector NullVector() {
  vector w;
  w.x=0; w.y=0; w.z=0;
  return w;
}

/** Initializion 
 ** @param x 
 ** @param y
 ** @param z
 ** @return a vector of x, y, z
 **/
vector NewVec(float x, float y, float z) {
    vector w;
    w.x=x; w.y=y; w.z=z;
    return w;
}

/** check if two vectors are equivalent
 ** @param v1
 ** @param v2
 ** @return a boolan value
 **/
bool Equal(vector v1, vector v2) {
  if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) return true;
  else return false;
}