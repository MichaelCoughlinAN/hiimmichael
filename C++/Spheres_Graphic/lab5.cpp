// Michael Coughlin
// CS 5721, Spring 2017
// Lab 5

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
#include "GL/glut.h"

GLuint width = 800, height = 480;
GLdouble width_step = 2.0f / width;
GLdouble height_step = 2.0f / height;
const int MAX_RAY_DEPTH = 3;


template<typename ItemType>
class Vector3D {
public:

    ItemType x, y, z;

    // Vector constructors.
    Vector3D() : x(ItemType(0)), y(ItemType(0)), z(ItemType(0)) {}
    Vector3D(ItemType xx) : x(xx), y(xx), z(xx) {}
    Vector3D(ItemType xx, ItemType yy, ItemType zz) : x(xx), y(yy), z(zz) {}

    // Vector normalisation.
    Vector3D& normalize() {
        ItemType nor = x * x + y * y + z * z;
        if (nor > 1) {
            ItemType invNor = 1 / sqrt(nor);
            x *= invNor, y *= invNor, z *= invNor;
        }
        return *this;
    }
  
    // Vector operators.
    Vector3D<ItemType> operator * (const ItemType &f) const { return Vector3D<ItemType>(x * f, y * f, z * f); }
    Vector3D<ItemType> operator * (const Vector3D<ItemType> &v) const { return Vector3D<ItemType>(x * v.x, y * v.y, z * v.z); }
    ItemType dot(const Vector3D<ItemType> &v) const { return x * v.x + y * v.y + z * v.z; }
    Vector3D<ItemType> operator - (const Vector3D &v) const { return Vector3D<ItemType>(x - v.x, y - v.y, z - v.z); }
    Vector3D<ItemType> operator + (const Vector3D &v) const { return Vector3D<ItemType>(x + v.x, y + v.y, z + v.z); }
    Vector3D<ItemType>& operator += (const Vector3D &v) { x += v.x, y += v.y, z += v.z; return *this; }
    Vector3D<ItemType>& operator *= (const Vector3D &v) { x *= v.x, y *= v.y, z *= v.z; return *this; }
    Vector3D<ItemType> operator - () const { return Vector3D<ItemType>(-x, -y, -z); }   
};

template<typename ItemType>
class Sphere {
public:

    // Sphere variables.
    Vector3D<ItemType> center;                         /// position of the sphere
    ItemType radius, radius2;                      /// sphere radius and radius^2
    Vector3D<ItemType> surfaceColor, emissionColor;    /// surface color and emission (light)
    ItemType transparency, reflection;             /// surface transparency and reflectivity

    // Sphere constructor.
    // position(c), radius(r), surface color(sc), reflectivity(refl), transparency(transp), emission color(ec)
    Sphere(const Vector3D<ItemType> &c, const ItemType &r, const Vector3D<ItemType> &sc, 
        const ItemType &refl = 0, const ItemType &transp = 0, const Vector3D<ItemType> &ec = 0) : 
        center(c), radius(r), surfaceColor(sc), reflection(refl),
        transparency(transp), emissionColor(ec), radius2(r * r)
    {}

    // compute a ray-sphere intersection using the geometric solution
    bool intersect(const Vector3D<ItemType> &rayorig, const Vector3D<ItemType> &raydir, ItemType *t0 = NULL, ItemType *t1 = NULL) const {
        // we start with a vector (l) from the ray origin (rayorig) to the center of the curent sphere.
        Vector3D<ItemType> l = center - rayorig;
        // tca is a vector length in the direction of the normalise raydir.
        // its length is streched using dot until it forms a perfect right angle triangle with the l vector.
        ItemType tca = l.dot(raydir);
        // if tca is < 0, the raydir is going in the opposite direction.  No need to go further.  Return false.
        if (tca < 0) return false;
        // if we keep on into the code, it's because the raydir may still hit the sphere.
        // l.dot(l) gives us the l vector length to the power of 2.  Then we use Pythagoras' theorem.
        // remove the length tca to the power of two (tca * tca) and we get a distance from the center of the sphere to the power of 2 (d2).
        ItemType d2 = l.dot(l) - (tca * tca);
        // if this distance to the center (d2) is greater than the radius to the power of 2 (radius2), the raydir direction is missing the sphere.
        // No need to go further.  Return false.
        if (d2 > radius2) return false;
        // Pythagoras' theorem again: radius2 is the hypotenuse and d2 is one of the side.Substraction gives the third side to the power of 2.
        // Using sqrt, we obtain the length thc.  thc is how deep tca goes into the sphere.
        ItemType thc = sqrt(radius2 - d2);
        if (t0 != NULL && t1 != NULL) {
            // remove thc to tca and you get the length from the ray origin to the surface hit point of the sphere.
            *t0 = tca - thc;
            // add thc to tca and you get the length from the ray origin to the surface hit point of the back side of the sphere.
            *t1 = tca + thc;
        }
        // There is a intersection with a sphere, t0 and t1 have surface distances values.  Return true.
        return true;
    }
};

std::vector<Sphere<double>*> spheres;

// function to mix 2 ItemType variables.
template<typename ItemType>
ItemType mix(const ItemType &a, const ItemType &b, const ItemType &mix) {
    return b * mix + a * (ItemType(1) - mix);
}

// This is the main trace function. It takes a ray as argument (defined by its origin
// and direction). We test if this ray intersects any of the geometry in the scene.
// If the ray intersects an object, we compute the intersection point, the normal
// at the intersection point, and shade this point using this information.
// Shading depends on the surface property (is it transparent, reflective, diffuse).
// The function returns a color for the ray. If the ray intersects an object, it
// returns the color of the object at the intersection point, otherwise it returns
// the background color.
template<typename ItemType>
Vector3D<ItemType> trace(const Vector3D<ItemType> &rayorig, const Vector3D<ItemType> &raydir, 
    const std::vector<Sphere<ItemType> *> &spheres, const int &depth)
{
    ItemType tnear = INFINITY;
    const Sphere<ItemType> *sphere = NULL;
    // Try to find intersection of this raydir with the spheres in the scene
    for (unsigned i = 0; i < spheres.size(); ++i) {
        ItemType t0 = INFINITY, t1 = INFINITY;
        if (spheres[i]->intersect(rayorig, raydir, &t0, &t1)) {
            // is the rayorig inside the sphere (t0 < 0)?  If so, use the second hit (t0 = t1)
            if (t0 < 0) t0 = t1;
            // tnear is the last sphere intersection (or infinity).  Is t0 in front of tnear?
            if (t0 < tnear) {
                // if so, update tnear to this closer t0 and update the closest sphere
                tnear = t0;
                sphere = spheres[i];
            }
        }
    }
    
    // At this moment in the program, we have the closest sphere (sphere) and the closest hit position (tnear)
    // For this pixel, if there's no intersection with a sphere, return a Vector3D with the background color.
    if (!sphere) return Vector3D<ItemType>(.5); // Grey background color.
    // if we keep on with the code, it is because we had an intersection with at least one sphere.

    Vector3D<ItemType> surfaceColor = 0; // initialisation of the color of the ray/surface of the object intersected by the ray.
    Vector3D<ItemType> phit = rayorig + (raydir * tnear); // point of intersection.
    Vector3D<ItemType> nhit = phit - sphere->center; // normal at the intersection point.

    // if the normal and the view direction are not opposite to each other,
    // reverse the normal direction.
    if (raydir.dot(nhit) > 0) nhit = -nhit;
    nhit.normalize(); // normalize normal direction
   
    ItemType bias = 1e-5; // add some bias to the point from which we will be tracing

    // Do we have transparency or reflection?
    if ((sphere->transparency > 0 || sphere->reflection > 0) && depth < MAX_RAY_DEPTH) {
        ItemType IdotN = raydir.dot(nhit); // raydir.normal
        // I and N are not pointing in the same direction, so take the invert.
        ItemType facingratio = std::max(ItemType(0), -IdotN);
        // change the mix value between reflection and refraction to tweak the effect (fresnel effect)
        ItemType fresneleffect = mix<ItemType>(pow(1 - facingratio, 3), 1, 0.1);
        // compute reflection direction (not need to normalize because all vectors
        // are already normalized)
        Vector3D<ItemType> refldir = raydir - nhit * 2 * raydir.dot(nhit);
        Vector3D<ItemType> reflection = trace(phit + (nhit * bias), refldir, spheres, depth + 1);
        Vector3D<ItemType> refraction = 0;
        // if the sphere is also transparent compute refraction ray (transmission)
        if (sphere->transparency) {
            ItemType ior = 1.2, eta = 1 / ior;
            ItemType k = 1 - eta * eta * (1 - IdotN * IdotN);
            Vector3D<ItemType> refrdir = raydir * eta - nhit * (eta *  IdotN + sqrt(k));
            refraction = trace(phit - nhit * bias, refrdir, spheres, depth + 1);
        }
        // the result is a mix of reflection and refraction (if the sphere is transparent)
        surfaceColor = (reflection * fresneleffect + refraction * (1 - fresneleffect) * sphere->transparency) * sphere->surfaceColor;
    }
    else {
        // it's a diffused object, no need to raytrace any further
        // Look at all sphere to find lights
        double shadow = 1.0;
        for (unsigned i = 0; i < spheres.size(); ++i) {
            if (spheres[i]->emissionColor.x > 0) {
                // this is a light
                Vector3D<ItemType> transmission = 1.0;
                Vector3D<ItemType> lightDirection = spheres[i]->center - phit;
                lightDirection.normalize();
                ItemType light_angle = (acos(raydir.dot(lightDirection)) / ( sqrt(raydir.dot(raydir)) * sqrt(lightDirection.dot(lightDirection))));
                ItemType light_incidence = sin(light_angle);
                for (unsigned j = 0; j < spheres.size(); ++j) {
                    if (i != j) {
                        ItemType t0, t1;
                        // Does the ray from point hit to the light intersect an object?
                        // If so, calculate the shadow.
                        if (spheres[j]->intersect(phit + (nhit * bias), lightDirection, &t0, &t1)) {
                            shadow = std::max(0.0, shadow - (1.0 - spheres[j]->transparency));
                            transmission = transmission * spheres[j]->surfaceColor * shadow;
                            //break;
                        }
                    }
                }
                // For each light found, we add light transmission to the pixel.
                surfaceColor += sphere->surfaceColor * transmission * 
                    std::max(ItemType(0), nhit.dot(lightDirection)) * spheres[i]->emissionColor;
            }
        }
    }
    return surfaceColor + sphere->emissionColor;
}

// Main rendering function. We compute a camera ray for each pixel of the image,
// trace it and return a color. If the ray hits a sphere, we return the color of the
// sphere at the intersection point, else we return the background color.
Vector3D<double> *image = new Vector3D<double>[width * height];
static Vector3D<double> cam_pos = Vector3D<double>(0);

template<typename ItemType>
void render(const std::vector<Sphere<ItemType> *> &spheres) {
    Vector3D<ItemType> *pixel = image;
    ItemType invWidth = 1 / ItemType(width), invHeight = 1 / ItemType(height);
    ItemType fov = 30, aspectratio = ItemType(width) / ItemType(height);
    ItemType angle = tan(M_PI * 0.5 * fov / ItemType(180));

    // Trace rays
    for (GLuint y = 0; y < height; ++y) {
        for (GLuint x = 0; x < width; ++x, ++pixel) {
            ItemType xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
            ItemType yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
            Vector3D<ItemType> raydir(xx, yy, -1);
            raydir.normalize();
            *pixel = trace(cam_pos, raydir, spheres, 0);
        }
    }
}

//---------------------------------------------- OPEN GL ------------------------------------------------------

void advanceDisplay(void) {
    cam_pos.z = cam_pos.z - 2;
    glutPostRedisplay();
}

void backDisplay(void) {
    cam_pos.z = cam_pos.z + 2;
    glutPostRedisplay();
}

void resetDisplay(void) {
    Vector3D<double> new_cam_pos;
    new_cam_pos = cam_pos;
    cam_pos = new_cam_pos;
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN) {
            glutIdleFunc(advanceDisplay);
        }
        break;

    case GLUT_MIDDLE_BUTTON:
        if(state == GLUT_DOWN) {
            glutIdleFunc(resetDisplay);
        }
        break;

    case GLUT_RIGHT_BUTTON:
        if(state == GLUT_DOWN) {
            glutIdleFunc(backDisplay);
        }
        break;
    }
}

GLuint tex = 0;

void display(void) {
    int i;
    float x, y;
    render<double>(spheres); // Creates the image and put it to memory in image[].

    std::vector< unsigned char > buf;
    buf.reserve( width * height * 3);
    for( size_t y = 0; y < height; ++y) {
        for( size_t x = 0; x < width; ++x) {
            // flip vertically (height-y) because the OpenGL texture origin is in the lower-left corner
            // flip horizontally (width-x) because...the original code did so
            size_t i = (height-y) * width + (width-x);
            buf.push_back( (unsigned char)( std::min(double(1), image[i].x) * 255.0 ) );
            buf.push_back( (unsigned char)( std::min(double(1), image[i].y) * 255.0 ) );
            buf.push_back( (unsigned char)( std::min(double(1), image[i].z) * 255.0 ) );
        }
    }

    /* clear all pixels */
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, &buf[0]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(-1, -1);
    glTexCoord2i(1, 0);
    glVertex2i(1, -1);
    glTexCoord2i(1, 1);
    glVertex2i(1,  1);
    glTexCoord2i(0, 1);
    glVertex2i(-1,  1);
    glEnd();
    glutSwapBuffers();
}

int main(int argc, char **argv)
{ 
    // position, radius, surface color, reflectivity, transparency, emission color
    spheres.push_back(new Sphere<double>(Vector3D<double>(0, -10004, -20), 10000, Vector3D<double>(0.2), 0.0, 0.0));

    spheres.push_back(new Sphere<double>(Vector3D<double>(3, 0, -15), 2, Vector3D<double>(1.00, 0.1, 0.1), 0.65, 0.1));
  
    // light
    spheres.push_back(new Sphere<double>(Vector3D<double>(-10, 20, 0), 3, Vector3D<double>(0), 0, 0, Vector3D<double>(3)));
    spheres.push_back(new Sphere<double>(Vector3D<double>(0, 10, 0), 3, Vector3D<double>(0), 0, 0, Vector3D<double>(1)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(10,10);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1 );
    glTexImage2D(GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); 

    glutMainLoop();

    delete [] image;
    while (!spheres.empty() ) {
        Sphere<double> *sph = spheres.back();
        spheres.pop_back();
        delete sph;
    }
    return 0;
}
