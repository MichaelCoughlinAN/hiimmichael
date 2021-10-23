#include <iostream>
#include "algebra.h"
#include "imager.h"
#include "triangle.h"

using namespace std; 

void ReflectiveSphereTest() {

  using namespace Imager;
  Scene scene(Color(0.0, 0.0, 0.0));
  // Dimensions of the chess board.
  const double innerSize   = 4.00;
  const double xBorderSize = 1.00;
  const double yBorderSize = 1.00;
  const double thickness   = 0.25;
  const Color lightSquareColor = Color(0.75, 0.70, 0.10);
  const Color darkSquareColor  = Color(0.30, 0.30, 0.40);
  const Color borderColor      = Color(0.50, 0.30, 0.10);



  // Create the chess board and add it to the scene.
  // Put transparent spheres above the chess board.
      struct sphere_info

      {
	Vector center;
	double radius;
      };

          const sphere_info sinfo[] =
	    {
	      { Vector(-1.8, 0.0, -17.0), 0.72 },
	      { Vector( 0.0, 0.0, -17.0), 0.72 },
	      { Vector(+1.8, 0.0, -17.0), 0.72 }
	    };

	  const size_t numSpheres = sizeof(sinfo) / sizeof(sinfo[0]);

	  for (size_t i=0; i < numSpheres; ++i)
	    {

	      Sphere* sphere = new Sphere(sinfo[i].center, sinfo[i].radius);
	      sphere->SetOpacity(0.17);
	      sphere->SetMatteGlossBalance(0.95, Color(0.4,0.5,0.7), Color(0.8,1.0,0.7));
	      scene.AddSolidObject(sphere);
	    }

	  // Add light sources.
	  scene.AddLightSource(LightSource(Vector(-45.0, +25.0, +50.0), Color(0.4, 0.4, 0.1, 1.0)));
	  scene.AddLightSource(LightSource(Vector( +5.0, +90.0, +40.0), Color(0.5, 0.5, 1.5, 1.0)));
	  scene.AddLightSource(LightSource(Vector(-25.0, +30.0, +40.0), Color(0.3, 0.2, 0.1, 1.0)));
	  const char* filename = "spheres.ppn";
	  scene.SaveImage(filename, 600, 360, 4.5, 3);
	  cout << "Created image " << filename << std::endl;
}





void SphereTest()
{
    using namespace Imager;

    Scene scene(Color(0.0,0.0,0.0));

    const Vector sphereCenter(0.0, 0.0, -40.0);
    const Vector lightDisplacement(-30.0, +120.0, +50.0);

    Sphere* sphere = new Sphere(sphereCenter, 5.5);
    sphere->SetFullMatte(Color(0.6, 0.2, 0.2));
    scene.AddSolidObject(sphere);

    // Add a light source to illuminate the objects in the scene; otherwise we won't see anything!
    scene.AddLightSource(LightSource(sphereCenter + lightDisplacement, Color(0.5, 1.0, 0.3)));

    // Generate a PNG file that displays the scene...
    const char *filename = "sphere.png";
    scene.SaveImage(filename, 400, 400, 3.0, 1);
    std::cout << "Created image " << filename << std::endl;
}


void SphereTriangleTest()
{
    using namespace Imager;

    Scene scene(Color(0.0,0.0,0.0));

    const Vector sphereCenter(0.0, 0.0, -40.0);
    const Vector lightDisplacement(-30.0, +120.0, +50.0);

    Triangle* triangle = new Triangle(sphereCenter, 5.5);
    triangle->SetFullMatte(Color(0.6, 0.2, 0.2));
    scene.AddSolidObject(sphere);

    // Add a light source to illuminate the objects in the scene; otherwise we won't see anything!
    scene.AddLightSource(LightSource(sphereCenter + lightDisplacement, Color(0.5, 1.0, 0.3)));

    // Generate a PNG file that displays the scene...
    const char *filename = "triangle.png";
    scene.SaveImage(filename, 400, 400, 3.0, 1);
    std::cout << "Created image " << filename << std::endl;
}







void MultipleSphereTest()
{
    using namespace Imager;

    // Put spheres with different optical properties next to each other.
    Scene scene(Color(0.0, 0.0, 0.0));

    Sphere* shinySphere = new Sphere(Vector(-1.5, 0.0, -50.0), 1.0);
    shinySphere->SetMatteGlossBalance(
        0.3,    // 30% of reflection is shiny, 70% is dull
        Color(1.0, 1.0, 1.0),   // matte color is white
        Color(1.0, 1.0, 1.0)    // gloss color is white
    );
    shinySphere->SetOpacity(0.6);
    scene.AddSolidObject(shinySphere);

    Sphere* matteSphere = new Sphere(Vector(+1.5, 0.0, -50.0), 1.0);
    matteSphere->SetFullMatte(Color(0.6, 0.6, 0.9));
    matteSphere->SetOpacity(1.0);
    scene.AddSolidObject(matteSphere);

    scene.AddLightSource(LightSource(Vector(-45.0, +10.0, +50.0), Color(1.0, 1.0, 0.3, 1.0)));
    scene.AddLightSource(LightSource(Vector( +5.0, +90.0, -40.0), Color(0.5, 0.5, 1.5, 0.5)));
    scene.AddLightSource(LightSource(Vector(+45.0, -10.0, +40.0), Color(0.1, 0.2, 0.1, 0.5)));

    const char* filename = "multisphere.png";
    scene.SaveImage(filename, 400, 300, 10.0, 1);
    std::cout << "Created image " << filename << std::endl;
}




void UnitTests()
{
    ReflectiveSphereTest(); 
    MultipleSphereTest();
    SphereTest();
    SphereTriangleTest()
}


//---------------------------------------------------------------------------
// Define a new type that is a pointer to a function
// with void return type and taking zero arguments.
typedef void (* COMMAND_FUNCTION) ();

struct CommandEntry
{
    const char* verb;           // the command line option
    COMMAND_FUNCTION command;   // function to call when option encountered
    const char* help;           // usage text that explains the option
};

// You can add more command line options to this program by
// adding another entry to the array below.
// Each item in the ray is a string followed by a 
// function to be called when that string appears 
// on the command line.
const CommandEntry CommandTable[] =
{
    { "scenes", UnitTests,
        "    Runs a series of tests that generate sample images.\n\n\nView README for more information."
    }
};

// Calculate the number of entries in CommandTable[]...
const size_t NUM_COMMANDS = sizeof(CommandTable) / sizeof(CommandTable[0]);


void PrintUsageText()
{
    using namespace std;

    cout <<
        "CS5721 Homework 2, Spring 2017 \nRay Tracing \nBy: Michael Coughlin \n\n" <<
        "The following command line option is supported:\n";

    for (size_t i=0; i < NUM_COMMANDS; ++i)
    {
        cout << "\n";
        cout << CommandTable[i].verb << "\n";
        cout << CommandTable[i].help;
    }

    cout << endl;
}


int main(int argc, const char *argv[])
{
    using namespace std;

    int rc = 1;

    if (argc == 1)
    {
        // No command line arguments are present, so display usage text.
        PrintUsageText();
    }
    else
    {
        // There is at least one command line option present.
        // Search the command table for the matching verb.
        const string verb = argv[1];
        bool found = false;     // did we find a matching verb in the table?
        for (size_t i=0; i < NUM_COMMANDS; ++i)
        {
            if (verb == CommandTable[i].verb)
            {
                found = true;                   // we found a match!
                CommandTable[i].command();      // call the function
                rc = 0;                         // indicate success
                break;                          // stop searching
            }
        }

        if (!found)
        {
            cerr << "ERROR:  Unknown command line option '" << verb << "'" << endl;
        }
    }

    return rc;
}
