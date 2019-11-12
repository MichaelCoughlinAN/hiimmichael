#include "edge.h"

/** Constructor **/
Edge::Edge(){
  v1 = NULL;
  v2 = NULL;
  f1 = NULL;
  f2 = NULL;
}

/** Getters **/
Vertex* Edge::getv1(){return v1;}
Vertex* Edge::getv2(){return v2;}
Face* Edge::getf1(){return f1;}
Face* Edge::getf2(){return f2;}

/** Add a new pointer to associated vertex **/
void Edge::addVertex(Vertex* v){
  if (v1 == NULL)
    v1 = v;
  else if(v1 !=NULL && v2 == NULL)
    v2 = v;
}

void Edge::addFace(Face* f){
  if (f1 == NULL)
    f1 = f;
  else if(f1 !=NULL && f2 == NULL)
    f2 = f;
}

/** check if the edge node contains both v1 and v2 vertices **/
bool Edge::contains(vector v_1, vector v_2){
  vector ver1 = v1->getVertex();
  vector ver2 = v2->getVertex();

  if ((Equal(v_1, ver1) && Equal(v_2, ver2))||(Equal(v_1, ver2) && Equal(v_2, ver1))) return true;
  else return false;
}
