#include "mesh.h"

using namespace std;

/** Constructor **/
Mesh::Mesh(){
  vSize = 0;
  fSize = 0;
  eSize = 0;
  radius = 0;
}
/** Getters **/
VPList Mesh::getVertices(){return vertices;}
FPList Mesh::getFaces(){return faces;}
float Mesh::getRadius(){return radius;}
Vec Mesh::getCentroid(){return centroid;}

/** read files and initialize the lists **/
void Mesh::loadMesh(char* name){
  FILE* fin = fopen(name, "r");
  if (fin == NULL) {
    printf("%s is a invalid file name, system exiting\n", name);
    exit(0);
  }
  
  char line[LINE_LEN];
  char indices[LINE_LEN];
  int i, numV, len, idx, lineNum = 0;
  float x,y,z,curLen;
  Vec v;
  Vertex* tmpv;
  Face* tmpf;
  
  while(fgets(line,LINE_LEN,fin) != NULL){
    lineNum++;
    //if the line contains the string OFF, read the next line
    if (strstr(line, "OFF") != NULL) {
      lineNum++;
      // read next line to get the number of vertices and faces
      if (fgets(line,LINE_LEN,fin)!=NULL)
        sscanf(line, "%d %d %d", &vSize, &fSize, &eSize);
      if((vptr = (Vertex **)malloc(vSize*sizeof(Vertex *)))!= NULL);
    } /** Reading vertex **/
    else if(lineNum>=3 && lineNum<vSize+3) {
      sscanf(line, "%f %f %f", &x, &y, &z);
      /** Adding new vertex **/
      v = Vec(x, y, z);
      tmpv = new Vertex(v);
      vertices.push_back(tmpv); // add vertex to vertices list
      vptr[lineNum - 3] = tmpv;
    }
    /** Reading faces **/
    else if(lineNum>= vSize+3 && lineNum < vSize+fSize+3) {
      //store the index information into indices
      sscanf(line, "%d %[^:]", &numV, indices);
      tmpf = new Face();
      tmpf->setNumV(numV);
      
      /** adding indices **/
      for (i = 0; sscanf(indices+i, "%d%n", &idx, &len)==1; i+=len) {
        tmpv = vptr[idx];
        tmpf->addVertex(tmpv);
        tmpv->addFace(tmpf);
      }
      tmpf->calcNorm();
      faces.push_back(tmpf);
    }
  }
  
  // Calculate vertice norm and centroid
  for (VPIter itv = vertices.begin(); itv!= vertices.end(); itv++) {
    (*itv)->calcNorm();
    centroid = centroid + (*itv)->getVertex();
  }
  centroid = centroid/(float)vSize;
  radius = 0;
  for (VPIter itv = vertices.begin(); itv!= vertices.end(); itv++) {
    curLen = (centroid - (*itv)->getVertex()).mag();
    if (radius<curLen) radius = curLen;
  }
}