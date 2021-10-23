#include "scene.h"

Scene::Scene(){
  w = 0; h = 0;
  eyePos = Vec(0.0,0.0,0.0); at = Vec(0.0,0.0,-1.0); up = Vec(0.0,1.0,0.0); fovy = 90;
  numL = 0; numP = 0; numF = 0; numT = 0; numO = 0;
  pigments = NULL;
  sf = NULL;
  transformations = NULL;
}

void Scene::readfile(char* filename){
  //open the file
  FILE* fin = fopen(filename, "r");
  //if the file is not found, exit the program
  if (fin == NULL) {
    printf("%s is a invalid file name, system exiting\n", filename);
    exit(0);
  }
  
  char line[LINE_LEN];
  int numFace, p, s, t, idx, len, shapeCount = 0;
  float x, y, z, r, g, b, width, radius, a, c, d;
  float ka, kd, ks, shininess, kr, kt, ior;
  char rest[LINE_LEN];
  char _rest[LINE_LEN];
  char type[LINE_LEN];
  char name[LINE_LEN];
  char fn[LINE_LEN];
  
  //read the file by lines
  for (int lineNum = 0; fgets(line, LINE_LEN, fin) != NULL; lineNum++) {
    // store the first line to be the output file name
    if (lineNum == 0) {
      strcpy(outname, line);
    } //the second line to be the width and height of the image
    else if (lineNum == 1) {
      sscanf(line, "%d %d", &w, &h);
    } //store the thrid line to be the eye position
    else if (lineNum == 2) {
      sscanf(line, "%f %f %f", &eyePos.x, &eyePos.y, &eyePos.z);
    } //store the forth line to the at position
    else if (lineNum == 3) {
      sscanf(line, "%f %f %f", &at.x, &at.y, &at.z);
    } //store the fifth line to the up vector
    else if (lineNum == 4) {
      sscanf(line, "%f %f %f", &up.x, &up.y, &up.z);
    } //store read value to fovy
    else if (lineNum == 5) {
      sscanf(line, "%f", &fovy);
    } //from the 7th line, read the number of lights
    else if (lineNum == 6) {
      sscanf(line, "%d", &numL);
    } //read each light's information and push the light in to a list of Light*
    else if (numL != 0 && (lineNum > 6 && lineNum <= 6 + numL)) {
      Vec pos, intensity, atten; Light* l;
      sscanf(line, "%f %f %f %f %f %f %f %f %f", &pos.x, &pos.y, &pos.z, &intensity.x, &intensity.y, &intensity.z, &atten.x, &atten.y, &atten.z);
      if (lineNum == 7) l= new Light(ambient, pos,intensity,atten);
      else l = new Light(diffuse,pos,intensity, atten);
      lights.push_back(l);
    } // from 7 + numL th line, store the number of the pigments, and malloc the corresponding number of pigments in the pigments array
    else if (lineNum == (7 + numL)) {
      sscanf(line, "%d", &numP);
      if(numP != 0) {
        if((pigments = (Pigment *)malloc(numP*sizeof(Pigment))) == NULL) {
          printf("out of Memory when allocating memory for pigments, exiting\n");
          exit(0);
        }
      }
    }// parse the pigment line, store te pigment in the array
    else if (numP != 0 && (lineNum > (7 + numL) && lineNum <= (7 + numL + numP))) {
      sscanf(line, "%s %[^:]", type, rest);
      if (strstr(type, "solid") != NULL) {
        pigments[lineNum - 8 - numL].type = SOLID;
        sscanf(rest, "%f %f %f", &r, &g, &b);
        pigments[lineNum - 8 - numL].c1.setVec(r,g,b);
      } else if (strstr(type, "checker") != NULL) {
        pigments[lineNum - 8 - numL].type = CHECKER;
        sscanf(rest, "%f %f %f %f %f %f %f", &r, &g, &b, &x, &y, &z, &width);
        pigments[lineNum - 8 - numL].c1.setVec(r,g,b);
        pigments[lineNum - 8 - numL].c2.setVec(x,y,z);
        pigments[lineNum - 8 - numL].width = width;
      } else if (strstr(type, "texture") != NULL) {
        pigments[lineNum - 8 - numL].type = TEXTURE;
        sscanf(rest, "%s", fn);
        Texture img(fn);
        img.readImage();
        img.print();
        pigments[lineNum - 8 - numL].image = img;
      }
    }
    else if (lineNum == (8 + numL + numP)) {
      sscanf(line, "%d", &numF);
      if(numF != 0) {
        if ((sf = (SurFinish *)malloc(numF*sizeof(SurFinish))) == NULL) {
          printf("out of Memory when allocating memory for surface finishes, exiting\n");
          exit(0);
        }
      }
    } else if (numF != 0 && (lineNum > (8 + numL + numP) && lineNum <= (8 + numL + numP + numF))) {
      sscanf(line, "%f %f %f %f %f %f %f", &ka, &kd, &ks, &shininess, &kr, &kt, &ior);
      SurFinish newSF(ka, kd, ks, shininess, kr, kt, ior);
      sf[lineNum - 9 - numL - numP].setSurFin(newSF);
    } else if (lineNum == (9 + numL + numP + numF)) {
      sscanf(line, "%d", &numT);
      if(numT != 0 && (transformations = (Matrix *)malloc(numT*sizeof(Matrix))) == NULL) {
        printf("out of Memory when allocating memory for transformations, exiting\n");
        exit(0);
      }
    } else if (numT != 0 && (lineNum > (9 + numL + numP + numF) && lineNum <= (9 + numL + numP + numF + numT))) {
      sscanf(line, "%s %f %f %f", type, &x, &y, &z);
      if (strstr(type, "scale")!= NULL) {
        transformations[lineNum - 10 - numL - numP - numF].scale(Vec(x, y, z));
      } else if (strstr(type, "translate")!= NULL) {
        transformations[lineNum - 10 - numL - numP - numF].translate(Vec(x, y, z));
      }
    } else if (lineNum == (10 + numL + numP + numF + numT)) {
      sscanf(line, "%d", &numO); shapeCount = numO;
    } else if (shapeCount > 0 && (lineNum > (10 + numL + numP + numF + numT))) {
      sscanf(line, "%d %d %d %[^:]", &p, &s, &t, rest);
      Pigment _pigment;
      SurFinish _sf;
      Matrix _trans;
      int totalLen = 0;
      if(numP > 0) _pigment = pigments[p];
      if(numF > 0) _sf = sf[s];
      if(numT > 0) {
        for (int i = 0; i < t;) {
          sscanf(rest+i, "%d%n", &idx, &len);
          _trans = _trans.mult(transformations[idx]);
          i+=len; totalLen +=len;
        }
      }
      sscanf(rest+totalLen, "%s %[^:]", type, _rest);
      
      if (strstr(type, "sphere")!= NULL) {
        sscanf(_rest, "%f %f %f %f", &x, &y, &z, &radius);
        Vec center(x, y, z);
        shapes.push_back(new Sphere(_pigment, _sf, _trans, center, radius));
      } else if (strstr(type, "polyhedron")!= NULL) {
        sscanf(_rest, "%d", &numFace);
        Polyhedron *poly = new Polyhedron(_pigment, _sf, _trans, numFace);
        for (int i = 0; i< numFace; i++) {
          if(fgets(line, LINE_LEN, fin) != NULL) {
            lineNum++;
            sscanf(line, "%f %f %f %f", &a, &b, &c, &d);
            poly->addFaceCoef(i, a, b, c, d);
          }
        }
        shapes.push_back(poly);
      } else if(strstr(type, "trianglemesh")!= NULL) {
        sscanf(_rest, "%s", name);
        shapes.push_back(new TriangleMesh(_pigment, _sf, _trans, name));
      }
      shapeCount--;
    }
  }
}

void Scene::print(){
  printf("image size: width = %d, height =  %d\n", w, h);
  printf("eye position:  "); eyePos.print();
  printf("at position   "); at.print();
  printf("up position   "); up.print();
  printf("fovy = %f\n", fovy);
  
  for (LightIter itl = lights.begin(); itl != lights.end(); itl++) {
    printf("light position:   "); (*itl)->pos.print();
    printf("light intensity:   "); (*itl)->intensity.print();
    printf("light attenuation:   "); (*itl)->attenuation.print();
    
  }
  
  printf("number of pigments:  %d\n", numP);
  for (int i = 0; i < numP ; i++) {
    if (pigments[i].type == SOLID )
      printf("solid %f %f %f\n", pigments[i].c1.x, pigments[i].c1.y, pigments[i].c1.z);
    else if(pigments[i].type == CHECKER)
      printf("checker %f %f %f  %f %f %f  %f\n", pigments[i].c1.x, pigments[i].c1.y, pigments[i].c1.z, pigments[i].c2.x, pigments[i].c2.y, pigments[i].c2.z, pigments[i].width);
  }
  
  printf("number of surface finishes:  %d\n", numF);
  for (int i = 0; i < numF; i++)
    sf[i].print();
  
  printf("number of Transformations:  %d\n", numT);
  for (int i = 0; i < numT; i++)
    transformations[i].print();
  
  for (ShapeIter its = shapes.begin(); its != shapes.end(); its++) {
    if ((*its)->getType() == sphere) {
      Sphere *tmp = dynamic_cast<Sphere*>(*its);
      tmp->print();
    } else if((*its)->getType() == polyhedron){
      Polyhedron *tmp = dynamic_cast<Polyhedron*>(*its);
      tmp->print();
    } else if((*its)->getType() == triangleMesh){
      TriangleMesh *tmp = dynamic_cast<TriangleMesh*>(*its);
      tmp->print();
    }
  }
}