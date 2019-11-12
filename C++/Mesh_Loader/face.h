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

/** A class for individual face node
 ** @author Jacy Li, Peiying Wen
 **/
class Face{
private:
  vector norm; // face norm
  VPList ptv; // pointers to vertices
  VPIter iter; // iterator for the list of pointers to vertices
  int numV;
public:
  /** Constructor **/
  Face();
  /** Getters **/
  VPList getVertices();
  vector getNorm();
  VPIter getIter();
  /** Setters **/
  void setNumV(int n);
  /** Add a new pointer to associated vertex **/
  void addVertex(Vertex* v);
  /** Calculate the face norm **/
  void calcNorm();
};


#endif
