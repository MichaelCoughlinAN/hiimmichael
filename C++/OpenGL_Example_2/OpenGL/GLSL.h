#ifndef __GLSL_CLASS_H__
#define __GLSL_CLASS_H__

// ////////////////////////////////////////////////////////////////////////////////
// 
// GLSLObject - class that encapsulates the OpenGL calls necessary for
// using the OpenGL Shading Language shaders.
//
// Comments or Questions? Contact Pete Willemsen <willemsn@d.umn.edu>
// $Id: GLSL.h,v 1.4 2006/12/09 03:39:56 willemsn Exp $
//
// To add a shader, create or instance the GLSLObject.  Then provide
// the file containing the OpenGL Shading Language shader as an
// argument to the addShader member:
//
//    GLSLObject shader;
//    shader.addShader("vertexshader.glsl", GLSLObject::VERTEX_SHADER);
//
// After the shaders have been added, create the shader program by
// compiling and linking the shader with createProgram call:
//
//    shader.createProgram();
//
// To activate and deactivate your shader, call the activate and
// deactivate calls as necessary.
//
// Caveats/Issues:
// While the code has been tested to work with two shaders (a vertex
// shader combined with a fragment shader), it can support adding
// additional shaders to the chain.  It is unlikely that this will
// actually work well if used.
//
// I also need to include some checks into the constructor that
// determine if the OpenGLSL is available.
// 
// ////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <list>

#include <GL/glew.h>

namespace sivelab
{
  class GLSLObject {
  public:
    enum ShaderType {
      VERTEX_SHADER,
      FRAGMENT_SHADER,
      GEOMETRY_SHADER
    };

    GLSLObject();
    ~GLSLObject();

    // Adds either a VERTEX or FRAGMENT shader to the shader program
    // represented by an instance of GLSLObject.
    void addShader( const std::string& filename, ShaderType shader_type );

    //Set the input and output type for the geometry shader
    void setInputandOutput(GLenum input, GLenum output,int n);

    //Sets the varying variables to record into buffer
    void setVaryingOutput(int,int*,GLenum);
      
    // Compiles, links, and sets up a shader to be used on the
    // hardware.
    GLuint createProgram();

    // Activate and deactivate the shader on the hardware.
    void activate();
    void deactivate();

    // Creates a reference to a uniform variable in the shader code.
    // The value returned can be used in OpenGL calls for setting
    // uniform variable values (glUniform calls).
    int createUniform(const std::string& name);

    // void createUniform(const std::string& name);
    // int getUniform(const std::string& name);

    // Set the reporting verbosity level.  Currently, setting the value
    // to anything other than 0 will cause the code to generate more
    // output, such as the shader text that was loaded and other
    // messages.  This is probably only needed for debugging purposes.
    void setReportingVerbosity(int val);

  protected:
    void loadSourceFromFile( const std::string& filename, GLuint& shader_obj );

  private:
    GLuint              m_program_object;
    //GLuint              m_program_object;
    std::list< GLuint > m_vertexshader_objects;
    std::list< GLuint > m_fragmentshader_objects;
    std::list< GLuint > m_geometryshader_objects;
    //std::list< GLuint > m_vertexshader_objects;
    //std::list< GLuint > m_fragmentshader_objects;
    //std::list< GLuint > m_geometryshader_objects;

    int m_verbose_level;
    GLenum input_type;
    GLenum output_type;
    int num_vertices;

    // 

    bool f_stripComments( char* buf );
    void glErrorCheck( const char* msg );
  };
}

#endif // __GLSL_CLASS_H__
