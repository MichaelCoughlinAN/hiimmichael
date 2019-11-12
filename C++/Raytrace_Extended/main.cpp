#include "main.h"

using namespace std;
Scene scene;
Image* img;

Vec background(0.0, 0.0, 0.0);
Vec white(1.0, 1.0, 1.0);
Vec black(0.0, 0.0, 0.0);
int debugMode = 0;
float ior_air = 1.0003; // index of refraction of air

/** Texture mapping for spheres
 ** @param pt intersection point
 ** @param n normal at pt
 ** @param p pigment of the object
 ** @return the color of pt at texture coordinate
 **/
Vec sphereMapping(Vec pt, Vec n, Pigment p){
  Vec vn = scene.up; // unit-length vector from the center to the north pole
  Vec tmp[3] = {Vec(1.0, 0.0, 0.0), Vec(0.0, 1.0, 0.0), Vec(0.0, 0.0, 1.0)};
  Vec ve; // unit-length vector from the center to a point on the equator
  for (int i = 0; i<3; i++) {
    if (tmp[i].dot(vn) == 0) { ve = tmp[i]; break; }
  }
  Vec vp = n; // unit-length vector from the center to intersection point
  int s, t;
  float u, v, theta, phi;
  phi = acos(vn.dot(vp) * -1);
  v = phi / PI;
  theta = (acos(vp.dot(ve) / sin(phi))) / (2*PI);
  if ((vn.cross(ve)).dot(vp) > 0) u = theta;
  else u = 1 - theta;
  // find the color of pt at texture cooridnates
  s = (int)p.image.width * u;
  t = (int)p.image.height * v;
  if ((s < p.image.width && s >= 0) && (t < p.image.height && t >= 0))
    return p.image.textures[s][t];
  else return background;
}

/** Cast reflected ray
 ** @param ray incoming ray
 ** @param pt intersection point
 ** @param normal normal of pt
 ** @return reflected ray
 **/
Ray reflect(Ray ray, Vec pt, Vec normal){
  Vec v = ray.getOrig() - pt; v = v.normalize();
  Vec dir = normal * (2 * v.dot(normal)) - v; dir = dir.normalize(); // reflected direction
  Ray t(pt, dir, 0, 9999, ReflectedRay);
  if (debugMode) {
    printf("reflected ray: origin = "); t.getOrig().print();
    printf("reflected ray: direction = "); t.getDir().print();
  }
  return t;
}

/** Cast transmitted ray
 ** @param ray incoming ray
 ** @param pt intersection point
 ** @param normal normal of pt
 ** @param ior2 index of refraction of the object
 ** @return transmitted ray
 **/
Ray transmit(Ray ray, Vec pt, Vec normal, float ior1, float ior2){
  Vec r = ray.getDir();
  float alpha = ior1 / ior2;
  float c1 = normal.dot(r) * -1;
  float c2 = sqrt(1 - pow(alpha,2) * (1 - pow(c1,2)));
  Vec v = r * alpha + normal * (c1 * alpha - c2);
  Ray t(pt, v, 0, 9999, TransmittedRay);
  if (debugMode) {
    printf("transmitted ray origin: "); t.getOrig().print();
    printf("transmitted ray direction: "); t.getDir().print();
  }
  return t;
}

/** Phong lighting model
 ** @param pt intersection point
 ** @param n normal of pt
 ** @param light pointer to the light source
 ** @param obj pointer to the object
 ** @param ray ray
 ** @return color calculated from local shading using phong model
 **/
Vec phongModel(Vec pt, Vec n, Light* light, Shape* obj, Ray ray) {
  float t;
  Vec v = ray.getOrig() - pt; v = v.normalize(); // vector to viewer
  Vec l = light->pos - pt;
  float dis = l.mag(); // distance to light source
  l = l.normalize(); // vector to light source
  Vec ir = n * (2 * n.dot(l)) - l; ir = ir.normalize(); // vector of ideal reflector
  Vec intensity = light->intensity; // light intensity
  Ray shadowRay(pt, l, 0, 9999, ShadowRay);  // shadow ray to the light source
  float f = light->attenFac(dis); // attentuation factor
  Pigment p = obj->getPigment();
  Vec obj_color; // object color
  float scalar; int tmp;
  if (p.type == SOLID) {
    obj_color = p.c1;
  } else if (p.type == CHECKER) {
    scalar = p.width;
    tmp = (int)(pt.x/scalar) + (int)(pt.y/scalar) + (int)(pt.z/scalar);
    if (tmp % 2 == 0) obj_color = p.c1;
    else obj_color = p.c2;
  } else if (p.type == TEXTURE) {
    if (obj->getType() == sphere)
      obj_color = sphereMapping(pt, n, p);
  }
  
  // get the surface parameters
  SurFinish appearance = obj->getSurFin();
  float Ka = appearance.ambient; // ambient coefficient
  float Kd = appearance.diffuse; // diffuse coefficient
  float Ks = appearance.specular; // specular coefficient
  float shininess = appearance.shininess;
  
  // for each object in the scene, see if is blocks the light
  if (light->type != ambient) {
    for (ShapeIter its = scene.shapes.begin(); its != scene.shapes.end(); its++) {
      if ((*its) == obj) continue;
      
      if ((*its)->getType() == sphere) {
        Sphere *shape = dynamic_cast<Sphere*>(*its);
        if (shape->intersect(shadowRay, t) && t < dis)
          return black;
      } else if((*its)->getType() == polyhedron){
        Polyhedron *shape = dynamic_cast<Polyhedron*>(*its);
        if (shape->intersect(shadowRay, t) && t < dis) {
          return black;
        }
      } else if((*its)->getType() == triangleMesh){
        TriangleMesh *shape = dynamic_cast<TriangleMesh*>(*its);
        if (shape->intersect(shadowRay, t) && shadowRay.calcDest(t).mag() < dis)
          return black;
      }
    }
  }
  
  Vec diffuse(0.0, 0.0, 0.0);
  Vec specular(0.0, 0.0, 0.0);
  // if the light is casted from front
  if (n.dot(l) > 0) {
    diffuse = intensity * (Kd * n.dot(l) * f);
    specular = white * (Ks * pow(v.dot(ir),shininess) * f);
    // update light color
    intensity.x = (light->type != ambient) ? diffuse.x * obj_color.x + specular.x : obj_color.x * Ka;
    intensity.y = (light->type != ambient) ? diffuse.y * obj_color.y + specular.y : obj_color.y * Ka;
    intensity.z = (light->type != ambient) ? diffuse.z * obj_color.z + specular.z : obj_color.z * Ka;
  } // if the light is casted from behind
  else {
    intensity.x = (light->type != ambient) ? black.x : obj_color.x * Ka;
    intensity.y = (light->type != ambient) ? black.y : obj_color.y * Ka;
    intensity.z = (light->type != ambient) ? black.z : obj_color.z * Ka;
  }
  
  return intensity;
}

/** Ray Tracer
 ** @param ray the ray to be traced
 ** @param depth recursion depth
 ** @return color value
 **/
Vec trace(Ray ray, int depth){
  if (debugMode) {
    printf("\nrecursion = %d\n", depth);
    printf("ray origin = "); ray.getOrig().print();
    printf("ray direction = "); ray.getDir().print();
  }
  if (depth == 0) return black; // return background color
  
  Vec color, local, reflected, transmitted;
  Vec pt, normal;
  float tClosest = ray.getTmax(); // set dis to a maximum value
  Shape *ObjPtr = NULL; // set the Obj pointer to null
  
  // look for intersection point for each object in the scene
  bool inside = false;
  for (ShapeIter its = scene.shapes.begin(); its != scene.shapes.end(); its++) {
    if ((*its) == ray.ObjPtr) continue;
    float t;
    
    if ((*its)->getType() == sphere) {
      Sphere *shape = dynamic_cast<Sphere*>(*its);
      if (shape->intersect(ray, t)) {
        if (t < tClosest && t > ray.getTmin()) {
          inside = (shape->intersect(ray, t) == -1) ? true : false;
          tClosest = t; // update tClosest
          ObjPtr = (*its); // set ObjPtr to point to the object
        }
      }
    } else if((*its)->getType() == polyhedron){
      Polyhedron *shape = dynamic_cast<Polyhedron*>(*its);
      if (shape->intersect(ray, t)) {
        if (t < tClosest && t > ray.getTmin()) {
          tClosest = t; 
          ObjPtr = (*its);
        }
      }
    } else if((*its)->getType() == triangleMesh){
      TriangleMesh *shape = dynamic_cast<TriangleMesh*>(*its);
      if (shape->intersect(ray, t)) {
        if (t < tClosest && t > ray.getTmin()) {
          tClosest = t;
          ObjPtr = (*its); 
        }
      }
    }
  }
  
  
  if (ObjPtr != NULL) {
    SurFinish appearance = ObjPtr->getSurFin();
    float Kr = appearance.reflective; // reflectivity
    float Kt = appearance.transmission; // transmitivity
    float ior_obj = appearance.ior; // index of refraction
    
    pt = ray.calcDest(tClosest); // set the pos variable pt to the nearest intersection point
    normal = ObjPtr->calcNorm(pt); // normal of intersection point
    if (normal.dot(ray.getDir()) > 0) normal = normal * (-1);
    if(inside) normal = normal * (-1);
    local.setVec(0.0, 0.0, 0.0); // set local shading to black 
    
    // for each light source in the scene
    for (LightIter itl = scene.lights.begin(); itl != scene.lights.end(); itl++){
      Light *LightPtr = (*itl); // pointer to the light source
      
      // calculate local shading according to Phong model
      local = local + phongModel(pt, normal, LightPtr, ObjPtr, ray) / scene.numL;
      
      // Recursively cast reflected and refracted rays
      if (Kr > 0) { // specular reflective
        Ray refl = reflect(ray, pt, normal);
        refl.ObjPtr = ObjPtr;
        reflected = reflected + trace(refl, depth-1)/scene.numL;
      }
      if (Kt > 0 && ior_obj != 0) { // translucent
        Ray refr = transmit(ray, pt, normal, ior_air, ior_obj);
        refr.ObjPtr = ObjPtr;
        transmitted = transmitted + trace(refr, depth-1)/scene.numL;
      }
    }
    
    // update light color
    color.setVec(local + reflected * Kr + transmitted * Kt);
  }
  // if no intersection
  else {
    color.setVec(background); // set color to background color
  }
  
  if (debugMode == 1) {
    printf("\nPrinting information for depth = %d\n", depth);
    Vec orig = ray.getOrig();
    Vec dir = ray.getDir();
    printf("RAY:\n");
    printf("origin = %f %f %f\n", orig.x, orig.y, orig.z);
    printf("direction = %f %f %f\n", dir.x, dir.y, dir.z);
    printf("INTERSECTION:\n");
    printf("intersection point = %f %f %f\n", pt.x, pt.y, pt.z);
    printf("normal = %f %f %f\n", normal.x, normal.y, normal.z);
    printf("LIGHT VISIBILITY:\n");
    printf("local shading = %f %f %f\n", local.x, local.y, local.z);
    printf("reflected shading = %f %f %f\n", reflected.x, reflected.y, reflected.z);
    printf("transmitted shading = %f %f %f\n", transmitted.x, transmitted.y, transmitted.z);
    printf("PIXEL COLOR:\n");
    printf("color = %f %f %f\n", color.x, color.y, color.z);
    printf("\n");
  }
  
  return color;
}

/** Main function **/
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage:\t./hw6 filename\n");
    exit(0);
  }
  
  // Read .in file
  for (int i = 1; i < argc; i++) scene.readfile(argv[i]);
  scene.print();
  
  // Create screen
  img = new Image(scene.w, scene.h);
  float pix[3] = {0.0, 0.0, 0.0};
  Vec wp[9];
  Vec rayDirection;
  Ray rays[9];
  Vec pixColor[9];
  
  // Camera frame parameters
  img->setCamera(scene.eyePos, scene.at, scene.up);
  
  // for each pixel on the screen
  for (int i=0; i<scene.w; i++) {
    for (int j=0; j<scene.h; j++) {
      // supersampling for 9 rays per pixel
      for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
          int idx = row*3 + col;
          wp[idx] = img->normalizePixel(Vec(i+0.5*row,j+0.5*col,0), scene.fovy);
          rayDirection = wp[idx] - img->cf.eyePos;
          rayDirection = rayDirection.normalize();
          rays[idx] = Ray(scene.eyePos, rayDirection, 0, 9999, CameraRay);
          pixColor[idx] = trace(rays[idx], 4);
        }
      }
      // set debug mode
      if (i==scene.w/2 && j==scene.h/2+1) debugMode = 0;
      else debugMode = 0;
      // output color info
      Vec color = (pixColor[0] + pixColor[2] + pixColor[6] + pixColor[8]) * (1.0/16) + (pixColor[1] + pixColor[3] + pixColor[5] + pixColor[7]) * (1.0/8) + pixColor[4] * (1.0/4);
      pix[0] = color.x;
      pix[1] = color.y;
      pix[2] = color.z;
      img->setPixel(pix, i, j);
    }
  }
  // Write pixel color to ppm file
  img->writeToPPM(scene.outname);
  
  return 0;
}