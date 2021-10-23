#ifndef ____face__
#define ____face__

#include <iostream>
#include <list>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "vertex.h"
#include "vector.h"

class Vertex;
typedef std::list<Vertex*> VPList;
typedef std::list<Vertex*>::iterator VPIter;


class Face {
private:
  Vec norm; // face norm
  VPList ptv; // pointers to vertices
  int numV;
public:
  /** Constructor **/
  Face();
  
  /** Getters **/
  VPList getVertices();
  Vec getNorm();
  VPIter getIter();
  
  /** Setters **/
  void setNumV(int n);
  /** Add a new pointer to associated vertex **/
  void addVertex(Vertex* v);
  /** Calculate the face norm **/
  void calcNorm();
};


#endif
