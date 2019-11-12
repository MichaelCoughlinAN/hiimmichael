#include "shape.h"

////////////////////////// Shape //////////////////////////

/// constructor ///
Shape::Shape(Pigment p, SurFinish sf, Matrix transMat) {
  type = unknown;
  pigment = p;
  appearance.setSurFin(sf);
  trans = transMat;
}

/// destructor ///
Shape::~Shape(){}

/// getters ///
Pigment Shape::getPigment(){return pigment;}
SurFinish Shape::getSurFin(){return appearance;}
Matrix Shape::getTrans(){return trans;}
ShapeType Shape::getType(){return type;}

////////////////////////// Sphere //////////////////////////

/// constructor for Sphere ///
Sphere::Sphere(Pigment p, SurFinish sf, Matrix transMat, Vec c, float r) : Shape(p, sf, transMat) {
  type = sphere;
  center = c;
  radius = r;
}

/// destructor for Sphere ///
Sphere::~Sphere(){}

float Sphere::getRadius(){return radius;}
Vec Sphere::getCenter() {return center;}

Vec Sphere::calcNorm(Vec pt){
  Vec c_vec = trans.matVec_mult(center);
  Vec norm = pt - c_vec;
  norm = trans.matDir_mult(norm);
  return norm.normalize();
}

/// checks if the sphere intersect with the given ray ///
int Sphere::intersect (Ray ray, float &tClose){
  float t0, t1;
  Vec c_vec = trans.matVec_mult(center);
  Vec r(radius, radius,radius);
  r = trans.matDir_mult(r);
  tClose = std::numeric_limits<float>::max();
  Vec L = ray.getOrig() - c_vec;
  //at^2 + bt + c = 0
  Vec newDir = Vec(ray.getDir().x/r.x,ray.getDir().y/r.y, ray.getDir().z/r.z);
  Vec newL = Vec(L.x/r.x, L.y/r.y, L.z/r.z);
  
  float a = newDir.dot(newDir);
  float b = 2*newDir.dot(newL);
  float c = newL.dot(newL) - 1;
  
  if (!solveQuadratic(a,b,c,t0, t1)) return 0;
  
  // if the ray origin is inside the circle, set the tClose to t1
  tClose = (t0 < 0) ? t1 : t0;
  
  if (t0 < 0 && t1 <0) return 0;
  else if(t0 <= 0 && t1 >0) return -1;
  else return 1;
}

bool Sphere::inSphere(Vec pt){
  return ((pt - trans.matVec_mult(center)).mag() <= radius);
}

void Sphere::print(){
  printf("Shape type: sphere\n");
  printf("center "); center.print();
  printf("radius = %f\n", radius);
}

////////////////////////// Polygedron //////////////////////////

/// constructor for Polyhedron ///
Polyhedron::Polyhedron(Pigment p, SurFinish sf, Matrix transMat, int numF) : Shape(p, sf, transMat) {
  type = polyhedron;
  numFace = numF;

  // malloc space for storing the half-space, which is a numFace * 4 2D array of floats
  if((coef = (float**) malloc(numFace*sizeof(float*)))!= NULL){
    for (int i = 0; i < numFace; i++) {
      if((coef[i] = (float*) malloc(4*sizeof(float)))== NULL) exit(0);
    }
  } else {
    printf ("out of memory \n");
    exit(0);
  }
}

/// destructor for Polyhedron ///
Polyhedron::~Polyhedron() {}

/// add the half-face coefficients to coef /// 
void Polyhedron::addFaceCoef(int rowNum, float a, float b, float c, float d){
  coef[rowNum][0] = a;
  coef[rowNum][1] = b;
  coef[rowNum][2] = c;
  coef[rowNum][3] = d;
}

/// checks if the polyhedron intersect with the given ray ///
int Polyhedron::intersect(Ray ray, float &t){
  int hit = 0;
  float tClose = std::numeric_limits<float>::max();
  for (int i = 0; i< numFace; i++) {
    float res;
    float a = ray.getDir().x*coef[i][0] + ray.getDir().y*coef[i][1] + ray.getDir().z*coef[i][2];
    float b = ray.getOrig().x*coef[i][0] + ray.getOrig().y*coef[i][1] + ray.getOrig().z*coef[i][2] + coef[i][3];
    if (solveLinear(a,b,res) && res >= 0) {
      Vec pt = ray.calcDest(res);
      if (this->inBox(pt)) {
        hit = 1;
        if (res < tClose) tClose = res;
      }
    }
  }
  t = tClose;
  return hit;
}  

Vec Polyhedron::calcNorm(Vec pt){
  for (int i = 0; i< numFace; i++) {
    if((pt.x*coef[i][0] + pt.y*coef[i][1] + pt.z*coef[i][2] + coef[i][3]) <= 0.0001){
      Vec norm(coef[i][0],coef[i][1],coef[i][2]);
      return norm.normalize();
    }
  }
  return Vec(0,0,0);
}

bool Polyhedron::inBox(Vec pt){
  bool halfspace = true;
  for( int i = 0; i < numFace; i++) {
    halfspace = halfspace && ((coef[i][0]*pt.x + coef[i][1]*pt.y + coef[i][2]*pt.z + coef[i][3]) <= 0001);
  }
  return halfspace;
}


void Polyhedron::print(){
  if (pigment.type == SOLID )
    printf("solid %f %f %f\n", pigment.c1.x, pigment.c1.y, pigment.c1.z);
  else if(pigment.type == CHECKER)
    printf("checker %f %f %f  %f %f %f  %f\n", pigment.c1.x, pigment.c1.y, pigment.c1.z, pigment.c2.x, pigment.c2.y, pigment.c2.z, pigment.width);
}

////////////////////////// Triangle Mesh //////////////////////////

/// constructor ///
TriangleMesh::TriangleMesh(Pigment p, SurFinish sf, Matrix transMat, char* filename) : Shape(p, sf, transMat)
{
  type = triangleMesh;
  strcpy(name, filename);
  mesh = new Mesh();
  mesh->loadMesh(filename);
}

/// destructor ///
TriangleMesh::~TriangleMesh(){}

/// checks if the mesh intersect with the given ray ///
int TriangleMesh::intersect(Ray ray, float &t){
  int hit = 0;
  float t0, t1;
  
  Vec centroid = mesh->getCentroid();
  float radius = mesh->getRadius();
  Vec r(radius, radius, radius);
  r = trans.matDir_mult(r);
  float tClose = std::numeric_limits<float>::max();
  
  Vec L = ray.getOrig() - centroid;
  Vec newDir = Vec(ray.getDir().x/r.x,ray.getDir().y/r.y, ray.getDir().z/r.z);
  Vec newL = Vec(L.x/r.x, L.y/r.y, L.z/r.z);
  
  float a = newDir.dot(newDir);
  float b = 2*newDir.dot(newL);
  float c = newL.dot(newL) - 1;
  
  if (!solveQuadratic(a,b,c,t0, t1)) return hit;
  // if the ray origin is inside the circle, set the tClose to t1

  if (t0 < 0 && t1 <0) return hit;
  
  float res;
  Vec theNorm;
  
  FPList faces = mesh->getFaces();
  //for each triangle in the mesh
  for (FPIter itf = faces.begin(); itf!=faces.end(); itf++) {
    // get face normal
    Vec norm = (*itf)->getNorm();
    //store the vertices of the triangle to v[0], v[1], v[2]
    VPList vertices = (*itf)->getVertices();
    Vec v[3];
    int i = 0;
    for (VPIter iter = vertices.begin(); iter!=vertices.end(); iter++,i++){
      v[i] = (*iter)->getVertex();
      v[i] = trans.matVec_mult(v[i]);
    }
    
    //calculate the ray - plane intersection
    if (ray.getDir().dot(norm) == 0) continue;
    res = - (ray.getOrig() - v[0]).dot(norm)/(ray.getDir().dot(norm));
        
    //if the point is in the triangle, update the closest t
    if (res >= 0 && inTriangle(ray.calcDest(res),v[0],v[1],v[2])) {
      hit = 1;
      if (res < tClose) {
        theNorm = norm;
        tClose = res;
      }
    }
  }
  t = tClose;
  return hit;
}

Vec TriangleMesh::calcNorm(Vec pt){
  FPList faces = mesh->getFaces();
  //for each triangle in the mesh
  for (FPIter itf = faces.begin(); itf!=faces.end(); itf++) {
    Vec norm = (*itf)->getNorm();
    //store the vertices of the triangle to v[0], v[1], v[2]
    VPList vertices = (*itf)->getVertices();
    Vec v[3];
    int i = 0;
    for (VPIter iter = vertices.begin(); iter!=vertices.end(); iter++,i++){
      v[i] = (*iter)->getVertex();
      v[i] = trans.matVec_mult(v[i]);
    }

    //if the point is in the triangle, update the closest t
    if (inTriangle(pt,v[0],v[1],v[2])) {
      if ((v[1] - v[0]).cross(pt - v[0]).normalize() == norm) {
        return norm;
      }
    }
  }
  return Vec(0,0,0);
}

void TriangleMesh::print(){
  Vec fnorm;
  FPList faces = mesh->getFaces();
  for (FPIter itf = faces.begin(); itf!=faces.end(); itf++) {
    VPList vertices = (*itf)->getVertices();
    for (VPIter iter = vertices.begin(); iter!=vertices.end(); iter++){
      printf("Vertices   :");
      (*iter)->getVertex().print();
    }
    fnorm = (*itf)->getNorm();
    printf("face norm   :");
    fnorm.print();
    printf("\n");
  }
}