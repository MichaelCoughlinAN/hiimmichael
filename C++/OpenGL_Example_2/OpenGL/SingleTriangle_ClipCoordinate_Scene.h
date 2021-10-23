#ifndef __SINGLE_TRIANGLE_CLIP_COORDINATES_H__
#define __SINGLE_TRIANGLE_CLIP_COORDINATES_H__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLSL.h"

class SingleTriangle_ClipCoordinate_Scene 
{
public:
    SingleTriangle_ClipCoordinate_Scene();
    ~SingleTriangle_ClipCoordinate_Scene();
    
    void initialize();
    void render();
    
private:
    int numVertices;
    GLuint m_triangleVBO[1], m_VAO;
    sivelab::GLSLObject shader;
};

#endif
