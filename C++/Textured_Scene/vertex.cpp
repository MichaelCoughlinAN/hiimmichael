#include "vertex.h"

using namespace std;

/** Constructor
 ** @param v vertex pos
 ** @param i index of the vertex
 **/
Vertex::Vertex(Vec v) {
  vertex = v;
  size = 0;
}

/** Getters **/
Vec Vertex::getVertex() { return vertex; }
Vec Vertex::getNorm() { return norm; }
FPList Vertex::getFaces() { return ptf; }
int Vertex::getSize() { return size; }

/** Setters **/
void Vertex::setVertex(Vec v){
  vertex = v;
}

/** Add a face pointer to the FPList 
 ** @param face pointer to the face node being added
 **/
void Vertex::addFace(Face* face){
  ptf.push_back(face);
  size++;
}

/** Calculate the vertex norm **/
void Vertex::calcNorm() {
  Vec tmp;
  for (FPIter iter = ptf.begin();iter!=ptf.end();iter++){
    Face* face = *iter;
    tmp = tmp + face->getNorm();
  }
  norm = tmp/size;
  norm = norm.normalize();
}
