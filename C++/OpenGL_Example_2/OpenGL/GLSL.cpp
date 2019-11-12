#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <assert.h>
#include "GLSL.h"

// ////////////////////////////////////////////////////////////////////////////////
// 
// GLSLObject - class that encapsulates the OpenGL calls necessary for
// using the OpenGL Shading Language shaders.
//
// Comments or Questions? Contact Pete Willemsen <willemsn@d.umn.edu>
// $Id: GLSL.cpp,v 1.5 2006/12/09 03:39:56 willemsn Exp $
//
// ////////////////////////////////////////////////////////////////////////////////

namespace sivelab
{
    GLSLObject::GLSLObject()
    {
        // no extra output
        m_verbose_level = 1;

        // Perform some checks to see if GLSL vertex shaders and fragment
        // shaders are actually available on the hardware.
        int err = 0;

        // The following four extensions are required to use GLSL Shaders
        if (!GL_ARB_vertex_shader)
        {
            std::cerr << "GL_ARB_vertex_shader is MISSING!" << std::endl;
            err++;
        }

        if (!GL_ARB_fragment_shader)
        {
            std::cerr << "GL_ARB_fragment_shader is MISSING!" << std::endl;
            err++;
        }

        if (!GL_ARB_shader_objects)
        {
            std::cerr << "GL_ARB_shader_objects is MISSING!" << std::endl;
            err++;
        }

        if (!GL_ARB_shading_language_100)
        {
            std::cerr << "GL_ARB_shading_language_100 is MISSING!" << std::endl;
            err++;
        }

        if (err > 0)
        {
            std::cerr << std::endl;
            std::cerr << "The extensions required to use the OpenGL Shading Language are\n";
            std::cerr << "not available on this machine.  The following extensions are required:\n";
            std::cerr << "\tGL_ARB_vertex_shader\n";
            std::cerr << "\tGL_ARB_fragment_shader\n";
            std::cerr << "\tGL_ARB_shader_objects\n";
            std::cerr << "\tGL_ARB_shading_language_100\n" << std::endl;;
            std::cerr << std::endl;
            std::cerr << "Exiting." << std::endl;

            exit(1);
        }
    }

    GLSLObject::~GLSLObject()
    {
    }

    void GLSLObject::setInputandOutput(GLenum input, GLenum output,int n)
    {
        input_type = input;
        output_type = output;
        num_vertices = n;
    }

    //This function is hardcoded for setting the output type to positions!!
    void GLSLObject::setVaryingOutput(int count, int* locations,GLenum buffermode){
        GLint positions = glGetVaryingLocationNV(m_program_object,"gl_Position");
        glTransformFeedbackVaryingsNV(m_program_object,count,&positions,buffermode);
    }

    void GLSLObject::addShader( const std::string& filename, ShaderType shader_type )
    {
        glErrorCheck("glCreateShaderObject( stype )");

        assert( shader_type == VERTEX_SHADER ||
                shader_type == FRAGMENT_SHADER ||
                shader_type == GEOMETRY_SHADER);

        GLenum stype;
        if (shader_type == VERTEX_SHADER)
            stype = GL_VERTEX_SHADER;
        else if (shader_type == FRAGMENT_SHADER)
            stype = GL_FRAGMENT_SHADER;
        else if (shader_type == GEOMETRY_SHADER)
            stype = GL_GEOMETRY_SHADER_EXT;
        else
            return;
    
        // Create the shader object
        GLuint shader = glCreateShader( stype );
        glErrorCheck("glCreateShaderObject( stype )");
    
        // Read the source from the file and load it into the shader
        loadSourceFromFile( filename, shader );

        //
        // Compile the shader
        //
        glCompileShader( shader );
        glErrorCheck("glCompileShaderARB( shader )");

        //
        // Check compilation status
        //
        GLint result;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &result );
        if (result) {
            std::cout << "Shader compilation successful: " << filename << std::endl;
      
            // Add the shader to the appropriate list
            if (shader_type == VERTEX_SHADER) 
                m_vertexshader_objects.push_back( shader );
            else if(shader_type == FRAGMENT_SHADER)
                m_fragmentshader_objects.push_back( shader );
            else
                m_geometryshader_objects.push_back( shader );
        }
        else {
            std::cout << "Shader object compilation failed: " << filename << std::endl;
      
            int logLength = 0;
            glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logLength );
      
            GLchar *error_log = new GLchar[ logLength ];
            glGetShaderInfoLog( shader, logLength, &logLength, error_log );

            std::cout << "GLSL ERROR LOG\n--------------" << std::endl;
            std::cout << error_log << std::endl << std::endl;

            delete [] error_log;
        }
    }

    GLuint GLSLObject::createProgram()
    {
        // Create a program object to link the two shaders together
        m_program_object = glCreateProgram();
        glErrorCheck("glCreateProgram()");
    
        //
        // Attach the vertex shader and fragment shader to the program object
        //
        std::list< GLuint >::iterator li;

        // Vertex Shaders first
        for (li=m_vertexshader_objects.begin(); li!=m_vertexshader_objects.end(); ++li)
        {
            glAttachShader( m_program_object, *li );
            glErrorCheck("glAttachShader( m_program_object, *li ) - Vertex Shader");
        }
        // Fragment Shaders second
        for (li=m_fragmentshader_objects.begin(); li!=m_fragmentshader_objects.end(); ++li)
        {
            glAttachShader( m_program_object, *li );
            glErrorCheck("glAttachShader( m_program_object, *li ) - Fragment Shader");
        }
#if 0
        // Geometry Shaders
        for (li=m_geometryshader_objects.begin(); li!=m_geometryshader_objects.end(); ++li)
        {
            glProgramParameteriEXT(m_program_object, GL_GEOMETRY_INPUT_TYPE_EXT, input_type);
            glProgramParameteriEXT(m_program_object, GL_GEOMETRY_OUTPUT_TYPE_EXT, output_type);
            glProgramParameteriEXT(m_program_object, GL_GEOMETRY_VERTICES_OUT_EXT, num_vertices);
            glAttachObject( m_program_object, *li );
            glErrorCheck("glAttachObjectARB( m_program_object, *li ) - Geomtry Shader");
        }
#endif

        //  need to occur before linking

        

        // Now, link the program
        glLinkProgram( m_program_object );
        glErrorCheck("glLinkProgramARB( m_program_object )");

        // Explicit binding...
//        glBindAttribLocation( m_program_object, posIdx, "in_Position" );
//        glBindAttribLocation( m_program_object, colorIdx, "in_Color" );

//        glBindFragDataLocation( m_program_object, 0, "fragmentColor" );

        bool linked = false;
        glGetProgramiv( m_program_object, GL_LINK_STATUS, (int *)&linked );
        if (linked == false)
        {
            /* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
	  int logLength;
            glGetProgramiv( m_program_object, GL_INFO_LOG_LENGTH, &logLength);
            
            /* The logLength includes the NULL character */
            GLchar *shaderProgramInfoLog = new GLchar[ logLength ];
 
            /* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
            glGetProgramInfoLog( m_program_object, logLength, &logLength, shaderProgramInfoLog );
            
            /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
            /* In this simple program, we'll just leave */
            delete [] shaderProgramInfoLog;
            return 0;
        }
        
        return m_program_object;
    }

    void GLSLObject::activate()
    {
        glUseProgram( m_program_object );
    }

    void GLSLObject::deactivate()
    {
        glUseProgram( 0 );
    }

    int GLSLObject::createUniform(const std::string& name)
    {
        return glGetUniformLocation(m_program_object, name.c_str());  
    }

    void GLSLObject::setReportingVerbosity(int val)
    {
        if (val <= 0)
            m_verbose_level = 0;
        else
            m_verbose_level = val;
    }

    bool GLSLObject::f_stripComments( char* buf )
    {
        char* comment_ptr = strstr(buf, "//");
        if (comment_ptr == 0)
            return 1;  // comment not located, so do not alter the buffer
        else 
        {
            // comment delimiter located, remove comments
            *comment_ptr = '\0';

            // check the strlen, if less than 1, return false
            if (strlen(buf) == 0)
                return false;
            else 
            {
                for (unsigned int i=0; i<strlen(buf); i++)
                {
                    if (buf[i] != ' ')
                        return true;
                }

                // if we make it here, all the characters in the buffer were
                // spaces, so return false...
                return false;
            }
        }
    }

    void GLSLObject::loadSourceFromFile( const std::string& filename, GLuint& shader_obj )
    {
        if (m_verbose_level)
            std::cout << "GLSLObject::loadSourceFromFile( filename=" << filename << " )" << std::endl;
	
        //
        // open the file and load into string array
        //
        std::ifstream shader_file( filename.c_str() );
        if (shader_file.is_open() == false)
        {
            std::cerr << "Error opening file \"" << filename << "\".  Exiting." << std::endl;
            exit(1);
        }

        std::stringstream shader_input_strings;

        // copy the file's buffer into the string stream
        shader_input_strings << shader_file.rdbuf();
        shader_file.close();
        
        const std::string &shader_string = shader_input_strings.str();
        
        const char *strShaderVar = shader_string.c_str();
        GLint iShaderLen = shader_string.size();

        glShaderSource( shader_obj, 1, (const GLchar**)&strShaderVar, (GLint *)&iShaderLen );

#if  0
        int linemax = 1024;
        char *linebuf = new char[ linemax ];
        std::list< std::string > string_list;
        while (shader_file.good() && !shader_file.eof())
        {
            // read a line off the file and append to string list
            shader_file.getline( linebuf, linemax );

            // strip out the comments, following "//"
            if (f_stripComments( linebuf )) 
                string_list.push_back( linebuf );
        }
        shader_file.close();
        delete [] linebuf;

        //
        // allocate the memory, load the source strings, deallocate memory,
        // and return.
        //
        
        GLchar **shader_string = new GLchar*[string_list.size()];

        // Holds the length of each non-null terminated string that
        // will be passed to glShaderSource
        GLint *shader_string_length = new GLint[ string_list.size() ];
    
        unsigned int idx, j;
        std::list< std::string >::const_iterator li;
        for (li=string_list.begin(), idx=0; li!=string_list.end(); ++li, idx++)
        {
            shader_string_length[idx] = li->length();

            shader_string[idx] = new GLchar[li->length() + 2];
            for (j=0; j<li->length(); j++)
                shader_string[idx][j] = (*li)[j];
            shader_string[idx][j+1] = '\n';
            shader_string[idx][j+2] = '\0';
            
            if (m_verbose_level)
                std::cout << "Added \"" << shader_string[idx] << "\", length=" << li->length() << std::endl;
        }

    
        //
        // Load the shader source into the shader object 
        //
        // Needs an array of string

        glShaderSource( shader_obj, string_list.size(), (const GLchar**)shader_string, 0 );


        // Clean up allocated memory
        for (idx=0; idx<string_list.size(); idx++)
            delete [] shader_string[idx];
        delete [] shader_string;
#endif
    }

    void GLSLObject::glErrorCheck( const char* msg )
    {
#if 0
#ifndef NDEBUG
        GLenum err_code;
        err_code = glGetError();
        while (err_code != GL_NO_ERROR) {
            fprintf(stderr, "OpenGL Error: %s, Context[%s]\n", gluErrorString(err_code), msg);
            err_code = glGetError();
        }
#endif
#endif
    }
}

