#ifndef ____mesh__
#define ____mesh__

#include <list>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "face.h"
#include "vertex.h"
#include "edge.h"
#include "vector.h"

#define LINE_LEN 50
#define NAME_LEN 20
#define SMOOTH 1
#define FLAT 2

class Vertex;
class Face;
class Edge;
typedef std::list<Edge*> EPList;
typedef std::list<Edge*>::iterator EPIter;

/** A class for individual face node
 ** @author Jacy Li, Peiying Wen
 **/

class Mesh{
private:
  VPList vertices; // list of vertices
  Vertex** vptr;
  FPList faces; // list of faces
  EPList edges; // list of edges
  VPIter itv;
  FPIter itf;
  EPIter ite;
  int vSize; // # of vertices
  int fSize; // # of faces
  int eSize; // # of edges
  char name[NAME_LEN];
  vector centroid;
  float radius;
  float smoothID;
  float flatID;
  float edgeID;
  float vertexID;
public:
  /** Constructor **/
  Mesh(char* filename);
  /** Getters **/
  VPList getVertices();
  FPList getFaces();
  vector getCentroid();
  float getRadius();

  /** readFiles and initialize the lists **/
  void readFile();
  void printList();
  void drawFace(int shadingMode);
  void drawEdge();
  void drawVertex();
};

#endif
