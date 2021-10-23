#include "mesh.h"

using namespace std;

/** Constructor **/
Mesh::Mesh(char* filename){
  strcpy(name,filename);
  centroid = NullVector();
  radius = 0;
  fSize = 0;
  vSize = 0;
  eSize = 0;
  smoothID = 0;
  flatID = 0;
  edgeID = 0;
  vertexID = 0;
  
}
/** Getters **/
VPList Mesh::getVertices(){return vertices;}
FPList Mesh::getFaces(){return faces;}
vector Mesh::getCentroid(){return centroid;}
float Mesh::getRadius(){return radius;}

void Mesh::readFile(){
  //if((FILE* fin = fopen(name, "r"))==Null) exit(0);
  FILE* fin = fopen(name, "r");
  if (fin == NULL) {
    printf("%s is a invalid file name, system exiting\n", name);
    exit(0);
  }
  char line[LINE_LEN];
  char indices[LINE_LEN];
  int i, numV, len, idx, lineNum = 0;
  float x,y,z,curLen;
  vector v;
  Vertex* tmpv;
  Face* tmpf;
  Edge* tmpe;
  
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
      v = NewVec(x,y,z);
      tmpv = new Vertex(v, lineNum-1);
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
        /*for (itv=vertices.begin(),j=0; itv!=vertices.end(); itv++,j++){
         if (idx == j) {
         tmpv = (*itv);
         tmpf->addVertex(tmpv);
         tmpv->addFace(tmpf);
         break;
         }
         }*/
        tmpv = vptr[idx];
        tmpf->addVertex(tmpv);
        tmpv->addFace(tmpf);
      }
      tmpf->calcNorm();
      faces.push_back(tmpf);
      
      /** Adding new edge **/
      Vertex* v[numV];
      VPList verList = tmpf->getVertices();
      //load the three vertices on the face to array v[]
      for (itv= verList.begin(),i=0; itv!=verList.end(); itv++, i++)
        v[i] = (*itv);
      //loop through v0-v1, v1-v2, v2-v0 pair
      for (i = 0; i< (int)verList.size(); i++) {
        bool inEdges = false;
        //loop through the edge list to find if both vertices are in the list
        for (ite = edges.begin(); ite!=edges.end(); ite++) {
          if ((*ite)->contains(v[i]->getVertex(),v[(i+1)%(int)verList.size()]->getVertex())){
            inEdges = true;
            (*ite)->addFace(tmpf);
            break;
          }
        }
        if (!inEdges){
          tmpe = new Edge();
          tmpe->addVertex(v[i]);
          tmpe->addVertex(v[(i+1)%(int)verList.size()]);
          tmpe->addFace(tmpf);
          edges.push_back(tmpe);
          eSize++;
        }
      }
    }
  }
  
  // Calculate vertice norm and centroid
  for (itv = vertices.begin(); itv!= vertices.end(); itv++) {
    (*itv)->calcNorm();
    centroid = Add(centroid, (*itv)->getVertex());
    curLen = Norm((*itv)->getVertex());
    if (radius<curLen) radius = curLen;
  }
  centroid = Mult(centroid, 1.0/(float)vSize);
}


/** Draw faces **/
void Mesh::drawFace(int shadingMode){
  VPList tmpVPL;
  vector n, v;
  
  if (shadingMode == FLAT) {
    if (flatID == 0) {
      if ((flatID = glGenLists(1))!=0) {
        glNewList(flatID,GL_COMPILE);
        glBegin(GL_TRIANGLES);
        for (itf = faces.begin(); itf!=faces.end(); itf++){
          n = (*itf)->getNorm();
          glNormal3f(n.x, n.y, n.z);
          tmpVPL = (*itf)->getVertices();
          for (itv = tmpVPL.begin(); itv != tmpVPL.end(); itv++) {
            v = (*itv)->getVertex();
            v = Diff(v,centroid);
            glVertex3f(v.x, v.y, v.z);
          }
        }
        glEnd();
        glEndList();
      }
    } else glCallList(flatID);
  } else {
    if (smoothID == 0) {
      if ((smoothID = glGenLists(1))!=0) {
        glNewList(smoothID,GL_COMPILE);
        glBegin(GL_TRIANGLES);
        for (itf = faces.begin(); itf!=faces.end(); itf++){
          tmpVPL = (*itf)->getVertices();
          for (itv = tmpVPL.begin(); itv != tmpVPL.end(); itv++) {
            n = (*itv)->getNorm();
            glNormal3f(n.x, n.y, n.z);
            v = (*itv)->getVertex();
            v = Diff(v,centroid);
            glVertex3f(v.x, v.y, v.z);
          }
        }
        glEnd();
        glEndList();
      }
    } else glCallList(smoothID);
  }
}

/** Draw vertices **/
void Mesh::drawVertex(){
  vector v;
  if (vertexID == 0) {
    if ((vertexID = glGenLists(1))!=0) {
      glNewList(vertexID,GL_COMPILE);
      glBegin(GL_POINTS);
      for (itv = vertices.begin(); itv!=vertices.end();itv++) {
        v = (*itv)->getVertex();
        v = Diff(v,centroid);
        glVertex3f(v.x,v.y,v.z);
      }
      glEnd();
      glEndList();
    }
  } else glCallList(vertexID);
}

/** Draw edges **/
void Mesh::drawEdge(){
  vector v1, v2, n1, n2;
  VPList verList;
  if (edgeID == 0) {
    if ((edgeID = glGenLists(1))!=0) {
      glNewList(edgeID, GL_COMPILE);
      glBegin(GL_LINES);
      for (ite = edges.begin(); ite!= edges.end(); ite++) {
          n1 = ((*ite)->getv1())->getNorm();
          n2 = ((*ite)->getv2())->getNorm();
          v1 = ((*ite)->getv1())->getVertex();
          v2 = ((*ite)->getv2())->getVertex();
          v1 = Diff(v1,centroid);
          v2 = Diff(v2,centroid);

          glNormal3f(n1.x, n1.y, n1.z);
          glVertex3f(v1.x, v1.y, v1.z);
          glNormal3f(n2.x, n2.y, n2.z);
          glVertex3f(v2.x, v2.y, v2.z);
      }
      glEnd();
      glEndList();
    }
  } else glCallList(edgeID);
}

void Mesh::printList(){
  VPList verList, ptf;
  FPList fList;
  int i;
  
  cout << "Mesh Centroid:   " <<centroid.x << ", " <<centroid.y << ", " << centroid.z << endl;
  cout << "Printing vertices list.. " << endl;
  for (itv=vertices.begin(); itv!=vertices.end(); itv++){
    cout << " " << endl;
    vector v = (*itv)->getVertex();
    cout << "vertex pos: " << v.x << " " << v.y << " " << v.z << endl;
    vector vn = (*itv)->getNorm();
    cout << "vertex norm: " << vn.x << " " << vn.y << " " << vn.z << endl;
    int fs = (*itv)->getSize();
    cout << "contains " << fs << " faces: " << endl;
    FPIter itf = (*itv)->getIter();
    FPList ptf = (*itv)->getFaces();
    for (itf=ptf.begin(); itf!=ptf.end(); itf++){
      Face* f = (*itf);
      vector fn = f->getNorm();
      cout << "  " << "face norm: " << fn.x << " "<< fn.y << " " << fn.z << endl;
      cout << "  " << "this face contains vertices: " << endl;
      VPIter i = f->getIter();
      VPList vl = f->getVertices();
      for (i=vl.begin(); i!=vl.end(); i++){
        vector fv = (*i)->getVertex();
        cout << "    " << fv.x << " " << fv.y << " " << fv.z << endl;
      }
    }
  }
  
  cout << "Edge list.. there are " << eSize << " edges" <<  endl;
  
  for (ite = edges.begin(), i = 0; ite != edges.end(); ite++, i++) {
    cout << "Edge No." << i << endl;
    vector v1 = (*ite)->getv1()->getVertex();
    vector v2 = (*ite)->getv2()->getVertex();
    cout << "  " << "vertex id: " << (*ite)->getv1()->getIndex() << endl;
    cout << "  " << "vertex pos: " << v1.x << " " << v1.y << " " << v1.z << endl;
    cout << "  " << "vertex id: " << (*ite)->getv2()->getIndex() << endl;
    cout << "  " << "vertex pos: " << v2.x << " " << v2.y << " " << v2.z << endl;
    
    cout << "  " << "this f1 contains vertices: " << endl;
    ptf = (*ite)->getf1()->getVertices();
    for (itv = ptf.begin(); itv!=ptf.end(); itv++) {
      cout << "    " << (*itv)->getIndex() << endl;
    }
    cout << "  " << "this f2 contains vertices: " << endl;
    ptf = (*ite)->getf2()->getVertices();
    for (itv = ptf.begin(); itv!=ptf.end(); itv++) {
      cout << "    " << (*itv)->getIndex() << endl;
    }
  }
}





