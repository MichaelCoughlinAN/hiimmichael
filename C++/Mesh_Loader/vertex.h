#ifndef ____vertex__
#define ____vertex__

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
#include "vector.h"
#include "face.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Face;
typedef std::list<Face*> FPList;
typedef std::list<Face*>::iterator FPIter;

/** A class for individual vertex node
 ** @author Jacy Li, Peiying Wen
 **/
class Vertex {
private:
  vector vertex; // vertex pos
  vector norm; // vertex normal
  FPList ptf; // pointers to faces
  FPIter iter; // iterator for the list of pointers to faces
  int size; // # of adjacent faces
  int index; // index of this vertex
public:
  /** Constructor **/
  Vertex(vector v, int i);
  /** Getters **/
  FPList getFaces();
  vector getNorm();
  vector getVertex();
  int getSize();
  int getIndex();
  FPIter getIter();
  /** Setters **/
  void setVertex(vector v);
  /** Add a new pointer to associated face **/
  void addFace(Face* face);
  /** Calculate the vertex norm **/
  void calcNorm();
};

#endif
