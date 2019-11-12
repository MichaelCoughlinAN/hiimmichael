
#ifndef __ANGEL_SHADER__
#define __ANGEL_SHADER__

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <cmath>
#include <iostream>

//  Define M_PI in the case it's not defined in the math header file
#ifndef M_PI
#  define M_PI  3.14159265358979323846
#endif

// Define a helpful macro for handling offsets into buffer objects
#define BUFFER_OFFSET(offset) ((GLvoid*) (offset))

namespace Angel
{
	//  Helper function to load vertex and fragment shader files
	GLuint InitShader( const char* vertexShaderFile,
			   const char* fragmentShaderFile );

	//  Degrees-to-radians constant 
	const GLfloat  DegreesToRadians = M_PI / 180.0;

}

#define Print(x) do { std::cerr << #x " = " << (x) << std::endl; } while(0)

//  Globally use our namespace in our example programs.
using namespace Angel;

#endif