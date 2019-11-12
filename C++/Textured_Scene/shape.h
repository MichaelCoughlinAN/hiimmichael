#ifndef _shape_
#define _shape_

#include <iostream>
#include <limits>
#include "matrix.h"
#include "vector.h"
#include "util.h"
#include "math.h"
#include "ray.h"
#include "surFinish.h"
#include "mesh.h"
#include "texture.h"

#define SOLID 0
#define CHECKER 1
#define TEXTURE 2

class Vec;
class Matrix;
class Ray;
class SurFinish;
class Mesh;
class Texture;

typedef enum ShapeType {
  unknown = 0,
  sphere, 
  polyhedron,
  triangleMesh
};

// Pigment struct
typedef struct {
  int type;
  Vec c1, c2;
  float width;
  Texture image;
} Pigment;

////////////////////////// Shape //////////////////////////

class Shape {
protected:
  ShapeType type;
  Pigment pigment;
  SurFinish appearance;
  Matrix trans;
public:
  Shape(Pigment p, SurFinish sf, Matrix transMat);
  ~Shape();
  
  Pigment getPigment();
  SurFinish getSurFin();
  Matrix getTrans();
  ShapeType getType();
  virtual void print() =0;
  virtual Vec calcNorm(Vec pt) =0;
  virtual int intersect(Ray ray, float &t) =0;
};

////////////////////////// Sphere //////////////////////////

class Sphere : public Shape {
protected:
  Vec center;
  float radius;
public:
  Sphere(Pigment p, SurFinish sf, Matrix transMat, Vec c, float r);
  ~Sphere();
  
  float getRadius();
  Vec getCenter();
  void print();
  Vec calcNorm(Vec pt);
  bool inSphere(Vec pt);
  int intersect(Ray ray, float &t);
};

////////////////////////// Polyhedron //////////////////////////

class Polyhedron : public Shape{
protected:
  int numFace;
  float** coef;
public:
  Polyhedron(Pigment p, SurFinish sf, Matrix transMat, int numF);
  ~Polyhedron();
  
  void addFaceCoef(int rowNum, float a, float b, float c, float d);
 
  Vec calcNorm(Vec pt);
  int intersect(Ray ray, float &t);
  bool inBox(Vec pt);
  void print();
};

////////////////////////// Triangle Mesh //////////////////////////
class TriangleMesh : public Shape{
protected:
  char name[20];
  Mesh* mesh;
public:
  TriangleMesh(Pigment p, SurFinish sf, Matrix transMat, char* filename);
  ~TriangleMesh();
  
  Vec calcNorm(Vec pt);
  int intersect(Ray ray, float &t);
  void print();
};
#endif
