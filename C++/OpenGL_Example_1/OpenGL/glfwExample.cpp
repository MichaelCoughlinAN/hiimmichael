#include <cstdlib>
#include <iostream>
#include <vector>

// These header files are necessary to bring in the OpenGL GLEW
// (Extensions Wrangler) and the GLFW (a portable framework for OpenGL
// applications).
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int CheckGLErrors(const char *s)
{
    int errCount = 0;
    
    return errCount;
}

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        exit (-1);
    // throw std::runtime_error("Error! initialization of glfw failed!");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 1000;
    float aspectRatio = 9.0 / 16.0; // winWidth / (float)winHeight;
    int winHeight = winWidth * aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "FCG4E Examples", NULL, NULL);
    if (!window) {
        std::cerr << "GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    GLenum err=glewInit();
    if(err != GLEW_OK) {
        std::cerr <<"GLEW Error! glewInit failed, exiting."<< std::endl;
        exit(EXIT_FAILURE);
    }

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    // This OpenGL call sets the default background color state. Note
    // that if you only call this once, that is the color that will be
    // used for all subsequent clears of the screen. In this case, we
    // set it to a RGB of 0.7, 0.7, 0.7, which is a light grey.
    glClearColor(0.7, 0.7, 0.7, 1.0);

    // Query the window size that was used to open the GLFW window and
    // then pass that data to the OpenGL viewport call to set the
    // correct buffer sizes for the screen.
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
      {
	// Before any other OpenGL calls occur, we need to clear the
	// background color. This state is instructs the function call
	// to clear the buffers to the default state.
        glClear(GL_COLOR_BUFFER_BIT);

	// If you did have any OpenGL scenes or data to be rendered,
	// it would eventually go here.

        /* Swap front and back buffers since OpenGL uses
	   double-buffering */
        glfwSwapBuffers(window);

        /* Poll for and process events from a mouse, keyboard or
	   joysticks */
        glfwPollEvents();

	// Process the Escape Key event
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
	  glfwSetWindowShouldClose(window, 1);
      }
    
    // Terminate and clean up all OpenGL-related data
    glfwTerminate();
    return 0;
}

