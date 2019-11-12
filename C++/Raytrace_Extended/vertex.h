#ifndef ____vertex__
#define ____vertex__

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include "vector.h"
#include "face.h"

class Face;
typedef std::list<Face*> FPList;
typedef std::list<Face*>::iterator FPIter;

/** A class for individual vertex node
 ** @author Jacy Li, Peiying Wen
 **/
class Vertex {
private:
  Vec vertex; // vertex pos
  Vec norm; // vertex normal
  FPList ptf; // pointers to faces
  int size; // # of adjacent faces
public:
  /** Constructor **/
  Vertex(Vec v);
  
  /** Getters **/
  FPList getFaces();
  Vec getNorm();
  Vec getVertex();
  int getSize();
  
  /** Setters **/
  void setVertex(Vec v);
  
  /** Add a new pointer to associated face **/
  void addFace(Face* face);
  
  /** Calculate the vertex norm **/
  void calcNorm();
};

#endif
