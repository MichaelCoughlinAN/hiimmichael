#include "face.h"

/** Constructor **/
Face::Face(){
  norm = NullVector();
  numV = 0;
}

/** Getters **/
VPList Face::getVertices() { return ptv; }
vector Face::getNorm() { return norm; }
VPIter Face::getIter() { return iter; }

/** Setters **/
void Face::setNumV(int n){ numV = n;}

/** Add a new pointer to associated vertex **/
void Face::addVertex(Vertex* v){ ptv.push_back(v);}

/** Calculate face normal **/
void Face::calcNorm(){
  iter = ptv.begin();
  vector v[3];
  int i = 0;
  if ((int)ptv.size()==3) {
    for (; iter!=ptv.end(); iter++) {
      v[i] = (*iter)->getVertex();
      i++;
    }
    norm = Cross(Diff(v[1], v[0]),Diff(v[2], v[0]));
    norm = Normalize(norm);
  }
}