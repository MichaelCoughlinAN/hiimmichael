#ifndef ____edge__
#define ____edge__

#include <iostream>
#include <list>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "face.h"
#include "vertex.h"
#include "vector.h"

class Vertex;
class Face;

/** A class for individual face node
 ** @author Jacy Li, Peiying Wen
 **/
class Edge{
private:
  Vertex* v1; // pointer to vertices
  Vertex* v2; // pointer to vertices
  Face* f1; //pointer to faces
  Face* f2; //pointer to faces
public:
  /** Constructor **/
  Edge();
  
  /** Getters **/
  Vertex* getv1();
  Vertex* getv2();
  Face* getf1();
  Face* getf2();
  
  /** Add a new pointer to associated vertex **/
  void addVertex(Vertex* v);
  void addFace(Face* f);
  
  bool contains(vector v_1, vector v_2);
};


#endif /* defined(____edge__) */
