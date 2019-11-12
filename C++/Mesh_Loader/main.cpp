#include "main.h"
#include "mats.h"

using namespace std;

MeshList meshes;
MeshIter itm;
GLfloat norms[12];
float objAngle = 0, lightAngle = 0, scal = 1;
int drawingMode = FACEMODE;
int projectionMode = PERSPECTIVE;
int modelMode = FREEZE;
int shadingMode = SMOOTH;
bool flat = false;
bool rotateLight = false;
vector c;
bool light0 = true, light1 = true;
int width = 500, height = 500;
int i;
float zoom = 1.0;
vector eyePos = NewVec(0, 0, 10.0);
vector uv = NewVec(0.0, 0.0, 1.0);
vector axis = NewVec(1.0,1.0,1.0);
float xPos = 0;
float viewingWidth = VIEW_W;
/** Paramaters for click-and-drag rotation from the user **/
int interactionMode = 0;
vector lastPoint, curPoint, direction, rotAxis;
float rot_angle;

/** Initialization **/
void init() {
  // Create environment
  glEnable(GL_DEPTH_TEST);
  glLineWidth(1.0);
  glPointSize(1.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);
  glClearColor(0.0,0.0,0.0,0.5);
  setMaterial();
  setLight();
}

/** Resize window **/
void resize(int w, int h){
  width = w; height = h;
  if (height == 0) height = 1; //prevent a divide by zero, when window is too short
  if (projectionMode==PERSPECTIVE) glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projectionMode==PERSPECTIVE)
    gluPerspective(60.0, width/(GLdouble)height,0.1,1000);
  else glOrtho(0,width,height,0,0.1,1000);
  glMatrixMode(GL_MODELVIEW);
}

/** Set material parameters **/
void setMaterial() {
  int t = MAT_BRIGHT_SILVER; // set material property
  GLfloat mat_ambient[] = {material_props[t][0],material_props[t][1],material_props[t][2]};
  GLfloat mat_diffuse[] = {material_props[t][3],material_props[t][4],material_props[t][5]};
  GLfloat mat_specular[] = {material_props[t][6],material_props[t][7],material_props[t][8]};
  GLfloat mat_shininess[] = {material_props[t][9]};
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

/** Set lighting parameters **/
void setLight(){
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glShadeModel (GL_SMOOTH);
  // Moving light
  GLfloat light_diffuse[] = {.3,.3,.7,.5};
  GLfloat light_specular[] = {.3,.3,.7,.5};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  // Still light
  GLfloat light1_ambient[] = { 1.0,1.0,1.0, 1.0 };
  GLfloat light1_diffuse[] = { 1.0,1.0,1.0, 1.0 };
  GLfloat light1_position[] = { -2.0, 2.0, 1.0, 0.0 };
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  // Enable light setting
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  
}

/** Update animations
 ** @param value TimerFunc parameter
 **/
void update(){
  if (modelMode==ANIMATE) objAngle+=0.2;
  if (rotateLight) lightAngle+=0.3;
  glutPostRedisplay();
}


/** Display **/
void display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projectionMode==PERSPECTIVE){
    gluPerspective(60.0, width/(GLdouble)height, 0.1,1000);
    viewingWidth = (Norm(eyePos))*tan(30*PI/180)*2*(width/height);
  }else{
    viewingWidth = VIEW_W;
    glOrtho(-viewingWidth/2.0,viewingWidth/2.0,-viewingWidth/2.0,viewingWidth/2.0,0.1,100);
  }
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(eyePos.x,eyePos.y,eyePos.z,  0.0, 0.0, 0.0,  0.0,1.0,0.0);
  GLfloat light_position[] = { 10.0, 0.0, 10.0, 0.0 };
  // Display and rotate the light source around the centered object
  glPushMatrix();
  glRotatef(lightAngle, 0.0, 1.0,0);
  glTranslatef(light_position[0],light_position[1],light_position[2]);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glTranslatef(-light_position[0],-light_position[1],-light_position[2]);
  glPopMatrix();
  // Draw each individual mesh
  for (itm = meshes.begin(), i = 0; itm != meshes.end(); itm++, i++){
    scal = (.4*VIEW_W/itm->getRadius())/(float)meshes.size();
    //scale the mesh according to its radius and the number of meshes loaded
    glPushMatrix();
    glScalef(scal, scal, scal);
    xPos = (2*i+1)*(.5*viewingWidth/(float)meshes.size())-viewingWidth/2.0;
    glTranslatef(xPos, 0, 0);
    glRotatef(rot_angle,rotAxis.x,rotAxis.y,rotAxis.z); // Rotation for user drag-and-click interaction
    glRotatef(objAngle, axis.x, axis.y, axis.z); // Rotation for mesh animation
    switch (drawingMode) {
      case FACEMODE: itm->drawFace(shadingMode);break;
      case VERTEXMODE: itm->drawVertex(); break;
      case EDGEMODE: itm->drawEdge();
      default: break;
    }
    glTranslatef(-xPos, 0, 0);
    glPopMatrix();
  }
  glutSwapBuffers();
}

/** Handle keyboard input from the user **/
void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'a': // model animate/freeze
      modelMode = !modelMode; break;
    case 's': // flat/smooth shading
      flat = !flat;
      if (flat) shadingMode = FLAT;
      else shadingMode = SMOOTH;
      break;
    case 'v': // vertex mode
      drawingMode = VERTEXMODE; break;
    case 'e': // edge mode
      drawingMode = EDGEMODE; break;
    case 'f': // face mode (default)
      drawingMode = FACEMODE; break;
    case 'l': // light animate/freeze
      rotateLight=!rotateLight; break;
    case 'p': // parallel/perspective projection
      projectionMode = !projectionMode; break;
    case 'q':
    case 'Q':
    case ESCAPE_KEY: exit(0); break;
    default: break;
  }
  glutPostRedisplay();
}

/** Handle special keyboard input from the user **/
void handleSpecialKeyboard(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_UP: //Zoom in
      if (eyePos.z>1) eyePos = Diff(eyePos, uv); break;
    case GLUT_KEY_DOWN: // zoom out
      if (eyePos.z<999) eyePos = Add(eyePos, uv); break;
    default: break;
  }
  glutPostRedisplay();
}

/** Handle mouse click **/
void clickedMouse(int button, int state, int x, int y){
  switch(state){
    case GLUT_DOWN:
      interactionMode = ROTATE;
      lastPoint = trackBallMapping(x,y);
      break;
    case GLUT_UP:
      interactionMode = NONE;
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

/** Handle mouse movement **/
void activeMotion(int x, int y){
  if (interactionMode == ROTATE){
    curPoint = trackBallMapping(x,y); // map the mouse pos to a logical sphere location
    direction = Diff(curPoint,lastPoint);
    float velocity = Norm(direction);
    if (velocity > 0.0001) {
      rotAxis = Cross(lastPoint,curPoint); // normal to this plane = axis about which to rotate
      rot_angle = velocity * 0.6;
      rot_angle = rot_angle*180/PI;
    }
  }
  glutPostRedisplay();
}

/** Calculate the 3D position of a projected unit vector onto the xy-plane **/
vector trackBallMapping(float mx, float my){
  vector v = NewVec((2.0*mx-width)/width,(height-2.0*my)/height,0.0);
  float d = Norm(v);
  if (d<1.0) d = 1.0;
  v.z = sqrt(1.001-d*d);
  return Normalize(v);
}

/** MAIN FUNCTION **/
int main(int argc,char **argv) {
  // Read command line
  if (argc < 2) {
    cout << "Please provide a list of file names" << endl;
    exit(0);
  } else {
    for (i=1; i<argc; i++){
      if (strstr(argv[i], ".off") != NULL) {
        Mesh* obj = new Mesh(argv[i]);
        obj->readFile();
        meshes.push_back(*obj);
      } else {
        cout << "Invalid file name. Usage: *.off" << endl;
        exit(0);
      }
    }
  }
  // Render OpenGL calls
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize(width, height);
  glutCreateWindow("MESHLAB");
  glutReshapeFunc(resize);
  glutDisplayFunc(display);
  glutIdleFunc(update);
  glutKeyboardFunc(handleKeyboard);
  glutSpecialFunc(handleSpecialKeyboard);
  glutMouseFunc(clickedMouse);
  glutMotionFunc(activeMotion);
  init();
  glutMainLoop();
  return(0);
}
