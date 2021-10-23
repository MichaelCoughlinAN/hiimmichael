#include "vertex.h"

using namespace std;

/** Constructor 
 ** @param v vertex pos
 ** @param i index of the vertex
 **/
Vertex::Vertex(vector v, int i) {
  vertex = v;
  norm = NullVector();
  size = 0;
  index = i;
}

/** Getters **/
vector Vertex::getVertex() { return vertex; }
vector Vertex::getNorm() { return norm; }
FPList Vertex::getFaces() { return ptf; }
int Vertex::getSize() { return size; }
int Vertex::getIndex() { return index; }
FPIter Vertex::getIter() { return iter; }

/** Setters **/

/** Add a face pointer to the FPList 
 ** @param face pointer to the face node being added
 **/
void Vertex::addFace(Face* face){
  ptf.push_back(face);
  size++;
}

/** Calculate the vertex norm **/
void Vertex::calcNorm() {
  vector tmp = NullVector();
  for (iter=ptf.begin();iter!=ptf.end();iter++){
    Face* face = *iter;
    tmp = Add(tmp,face->getNorm());
  }
  norm = Mult(tmp, 1.0/size);
  norm = Normalize(norm);
}
