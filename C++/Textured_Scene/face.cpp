#include "face.h"

/** Constructor **/
Face::Face(){
  numV = 0;
}

/** Getters **/
VPList Face::getVertices() { return ptv; }
Vec Face::getNorm() { return norm; }

/** Setters **/
void Face::setNumV(int n){ numV = n; }

/** Add a new pointer to associated vertex **/
void Face::addVertex(Vertex* v){ ptv.push_back(v);}

/** Calculate face normal **/
void Face::calcNorm(){
  Vec v[3];
  int i = 0;
  if ((int)ptv.size()==3) {
    for (VPIter iter = ptv.begin(); iter!=ptv.end(); iter++){
      v[i] = (*iter)->getVertex();
      i++;
    }
    norm = (v[1] - v[0]).cross(v[2] - v[0]);
    norm = norm.normalize();
  }
}