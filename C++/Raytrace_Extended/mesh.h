#ifndef ____mesh__
#define ____mesh__

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <cstring>
#include "face.h"
#include "vertex.h"
#include "vector.h"

#define SMOOTH 1
#define FLAT 2
#define LINE_LEN 60
#define NAME_LEN 20

class Vertex;
class Face;

/** A class for individual face node
 ** @author Jacy Li, Peiying Wen
 **/
class Mesh{
private:
  VPList vertices; // list of vertices
  Vertex** vptr;
  FPList faces; // list of faces
  int vSize; // # of vertices
  int fSize; // # of faces
  int eSize;
  float radius;
  Vec centroid;
public:
  /** Constructor **/
  Mesh();
  
  /** Getters **/
  VPList getVertices();
  FPList getFaces();
  float getRadius();
  Vec getCentroid();
  
  /** readFiles and initialize the lists **/
  void loadMesh(char* name);
};

#endif
