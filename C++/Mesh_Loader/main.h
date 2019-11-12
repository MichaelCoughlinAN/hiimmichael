#ifndef ____main__
#define ____main__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "mesh.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define ESCAPE_KEY 27
#define VERTEXMODE 1
#define EDGEMODE 2
#define FACEMODE 3
#define PARALLEL 0
#define PERSPECTIVE 1
#define FREEZE 1
#define ANIMATE 0
#define PI 3.14159265
#define VIEW_W 5
#define ROTATE 1
#define NONE 0

class Mesh;
typedef std::list<Mesh> MeshList;
typedef std::list<Mesh>::iterator MeshIter;

void init();
void resize(int w, int h);
void setMaterial();
void setLight();
void update();
void display();
void handleKeyboard(unsigned char key, int x, int y);
void handleSpecialKeyboard(int key, int x, int y);
void clickedMouse(int button, int state, int x, int y);
void activeMotion(int x, int y);
vector trackBallMapping(float mx, float my);

#endif