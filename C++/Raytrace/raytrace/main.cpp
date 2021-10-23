/*
    main.cpp

    Copyright (C) 2013 by Don Cross  -  http://cosinekitty.com/raytrace

    This software is provided 'as-is', without any express or implied
    warranty. In no event will the author be held liable for any damages
    arising from the use of this software.

    Permission is granted to anyone to use this software for any purpose,
    including commercial applications, and to alter it and redistribute it
    freely, subject to the following restrictions:

    1. The origin of this software must not be misrepresented; you must not
       claim that you wrote the original software. If you use this software
       in a product, an acknowledgment in the product documentation would be
       appreciated but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
       misrepresented as being the original software.

    3. This notice may not be removed or altered from any source
       distribution.

    -------------------------------------------------------------------------

    Main source file for my demo 3D ray-tracing image maker.
*/

#include <iostream>
#include "algebra.h"
#include "block.h"
#include "chessboard.h"
#include "planet.h"
#include "polyhedra.h"

void BlockTest()
{
    using namespace Imager;

    // We use a "Scene" object to embody the entire model
    Scene scene(Color(0.37, 0.45, 0.37, 7.0e-6));

    // Create a concrete block object.  
    // We *must* use operator new to create all solids, because the Scene destructor will delete it.
    ConcreteBlock* block = new ConcreteBlock(Vector(0.0, 0.0, -160.0), Optics(Color(0.5, 0.5, 0.5)));
    block->RotateX(-10.0);
    block->RotateY(-15.0);
    scene.AddSolidObject(block);

    // Create a sphere and put it into the scene also.
    Sphere* sphere = new Sphere(Vector(10.0, 3.0, -147.0), 3.5);
    sphere->SetFullMatte(Color(0.6, 0.4, 0.45));
    scene.AddSolidObject(sphere);

    // Add a light source to illuminate the objects in the scene; otherwise we won't see anything!
    scene.AddLightSource(LightSource(Vector( +20.0,  +20.0,  +80.0), Color(0.5, 0.1, 0.1, 0.15)));
    scene.AddLightSource(LightSource(Vector(+100.0, +120.0,  -70.0), Color(0.2, 0.5, 0.4, 1.00)));
    scene.AddLightSource(LightSource(Vector(  +3.0,  +13.0,  +80.0), Color(0.6, 0.5, 0.3, 1.20)));

    // Generate a PNG file that displays the scene...
    const char *filename = "block.png";
    scene.SaveImage(filename, 320, 400, 4.5, 4);
    std::cout << "Wrote " << filename << std::endl;
}

void SphereTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

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
    std::cout << "Wrote " << filename << std::endl;
}


void TorusTest(const char* filename, double glossFactor)
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    const Color white(1.0, 1.0, 1.0);
    Torus* torus1 = new Torus(3.0, 1.0);
    torus1->SetMatteGlossBalance(glossFactor, white, white);
    torus1->Move(+1.5, 0.0, 0.0);

    Torus* torus2 = new Torus(3.0, 1.0);
    torus2->SetMatteGlossBalance(glossFactor, white, white);
    torus2->Move(-1.5, 0.0, 0.0);
    torus2->RotateX(-90.0);

    SetUnion *doubleTorus = new SetUnion(
        Vector(0.0, 0.0, 0.0), 
        torus1, 
        torus2
    );

    scene.AddSolidObject(doubleTorus);

    doubleTorus->Move(0.0, 0.0, -50.0);
    doubleTorus->RotateX(-45.0);
    doubleTorus->RotateY(-30.0);

    // Add a light source to illuminate the objects 
    // in the scene; otherwise we won't see anything!
    scene.AddLightSource(
        LightSource(
            Vector(-45.0, +10.0, +50.0), 
            Color(1.0, 1.0, 0.3, 1.0)
        )
    );

    scene.AddLightSource(
        LightSource(
            Vector(+5.0, +90.0, -40.0), 
            Color(0.5, 0.5, 1.5, 0.5)
        )
    );

    // Generate a PNG file that displays the scene...
    scene.SaveImage(filename, 420, 300, 5.5, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void BitDonutTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Torus* torus = new Torus(3.0, 1.0);

    Sphere* sphere = new Sphere(Vector(-3.0, 0.0, 0.0), 1.5);

    SolidObject* bitDonut = new SetDifference(Vector(), torus, sphere);

    scene.AddSolidObject(bitDonut)
        .Move(0.0, 0.0, -50.0)
        .RotateX(-45.0)
        .RotateY(-30.0)
    ;

    // Add a light source to illuminate the objects in the scene; otherwise we won't see anything!
    scene.AddLightSource(LightSource(Vector(-45.0, +10.0, +50.0), Color(1.0, 1.0, 0.3, 1.0)));
    scene.AddLightSource(LightSource(Vector( +5.0, +90.0, -40.0), Color(0.5, 0.5, 1.5, 0.5)));

    // Generate a PNG file that displays the scene...
    const char *filename = "donutbite.png";
    scene.SaveImage(filename, 300, 300, 6.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void SetIntersectionTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    // Display the intersection of two overlapping spheres.
    const double radius = 1.0;

    Sphere* sphere1 = new Sphere(
        Vector(-0.5, 0.0, 0.0), 
        radius
    );

    sphere1->SetFullMatte(Color(1.0, 1.0, 0.5));

    Sphere* sphere2 = new Sphere(
        Vector(+0.5, 0.0, 0.0), 
        radius
    );

    sphere2->SetFullMatte(Color(1.0, 0.5, 1.0));

    SetIntersection *isect = new SetIntersection(
        Vector(0.0, 0.0, 0.0), 
        sphere1, 
        sphere2
    );

    isect->Move(0.0, 0.0, -50.0);
    isect->RotateY(-12.0);
    isect->RotateX(-28.0);

    scene.AddSolidObject(isect);
    scene.AddLightSource(LightSource(Vector(-5.0, 10.0, +80.0), Color(1.0, 1.0, 1.0)));

    const char *filename = "intersection.png";
    scene.SaveImage(filename, 300, 300, 25.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void SetDifferenceTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    const Color sphereColor(1.0, 1.0, 0.5);

    // Display the intersection of two overlapping spheres.
    Sphere* sphere1 = new Sphere(Vector(-0.5, 0.0, 0.0), 1.0);
    Sphere* sphere2 = new Sphere(Vector(+0.1, 0.0, 0.0), 1.3);

    sphere1->SetFullMatte(sphereColor);
    sphere2->SetFullMatte(sphereColor);

    SetIntersection *diff = new SetDifference(Vector(0.0, 0.0, 0.0), sphere1, sphere2);
    diff->Move(1.0, 0.0, -50.0);
    diff->RotateY(-5.0);

    scene.AddSolidObject(diff);
    scene.AddLightSource(LightSource(Vector(-5.0, 50.0, +20.0), Color(1.0, 1.0, 1.0)));

    const char *filename = "difference.png";
    scene.SaveImage(filename, 300, 300, 20.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void CuboidTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Cuboid *cuboid = new Cuboid(3.0, 4.0, 2.0);
    cuboid->SetFullMatte(Color(1.0, 0.2, 0.5));
    cuboid->Move(0.0, 0.0, -50.0);
    cuboid->RotateX(-115.0);
    cuboid->RotateY(-22.0);

    scene.AddSolidObject(cuboid);
    scene.AddLightSource(LightSource(Vector(-5.0, 50.0, +20.0), Color(1.0, 1.0, 1.0)));

    const char *filename = "cuboid.png";
    scene.SaveImage(filename, 300, 300, 3.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void SpheroidTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Spheroid* spheroid = new Spheroid(4.0, 2.0, 1.0);
    spheroid->Move(0.0, 0.0, -50.0);
    spheroid->RotateX(-12.0);
    spheroid->RotateY(-60.0);

    scene.AddSolidObject(spheroid);
    scene.AddLightSource(LightSource(Vector(+35.0, +50.0, +20.0), Color(0.2, 1.0, 1.0)));
    scene.AddLightSource(LightSource(Vector(-47.0, -37.0, +12.0), Color(1.0, 0.2, 0.2)));

    const char *filename = "spheroid.png";
    scene.SaveImage(filename, 300, 300, 8.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void CylinderTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Cylinder* cylinder = new Cylinder(2.0, 5.0);
    cylinder->SetFullMatte(Color(1.0, 0.5, 0.5));
    cylinder->Move(0.0, 0.0, -50.0);
    cylinder->RotateX(-72.0);
    cylinder->RotateY(-12.0);

    scene.AddSolidObject(cylinder);
    scene.AddLightSource(LightSource(Vector(+35.0, +50.0, +20.0), Color(1.0, 1.0, 1.0)));

    const char *filename = "cylinder.png";
    scene.SaveImage(filename, 300, 300, 6.0, 2);
    std::cout << "Wrote " << filename << std::endl;
}


void SaturnTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));
    Saturn* saturn = new Saturn();
    saturn->Move(0.0, 0.0, -100.0);
    saturn->RotateY(-15.0);
    saturn->RotateX(-83.0);
    scene.AddSolidObject(saturn);
    scene.AddLightSource(LightSource(Vector(+30.0, +26.0, +20.0), Color(1.0, 1.0, 1.0)));

    const char *filename = "saturn.png";
    scene.SaveImage(filename, 500, 250, 4.0, 4);
    std::cout << "Wrote " << filename << std::endl;
}


void PolyhedraTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Optics optics;  // use default optics (white matte finish, opaque)

    Icosahedron* icosahedron = new Icosahedron(Vector(-2.0, 0.0, -50.0), 1.0, optics);
    icosahedron->RotateY(-12.0);
    icosahedron->RotateX(-7.0);
    scene.AddSolidObject(icosahedron);

    Dodecahedron* dodecahedron = new Dodecahedron(Vector(+2.0, 0.0, -50.0), 1.0, optics);
    dodecahedron->RotateX(-12.0);
    dodecahedron->RotateY(-7.0);
    scene.AddSolidObject(dodecahedron);

    scene.AddLightSource(LightSource(Vector(-45.0, +10.0, +50.0), Color(1.0, 1.0, 0.3, 1.0)));
    scene.AddLightSource(LightSource(Vector( +5.0, +90.0, -40.0), Color(0.5, 0.5, 1.5, 0.5)));
    scene.AddLightSource(LightSource(Vector(+45.0, -10.0, +40.0), Color(0.1, 0.5, 0.1, 0.5)));

    const char *filename = "polyhedra.png";
    scene.SaveImage(filename, 600, 300, 12.0, 4);
    std::cout << "Wrote " << filename << std::endl;
}


void DodecahedronOverlapTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    Optics optics;  // use default optics (white matte finish, opaque)

    Dodecahedron* dodecahedron = new Dodecahedron(Vector(+0.0, 0.0, -50.0), 1.0, optics);
    dodecahedron->RotateX(-12.0);
    dodecahedron->RotateY(-7.0);

    // Create a sphere that overlaps with the dodecahedron.
    const Vector sphereCenter(Vector(+1.0, 0.0, -50.0));
    Sphere* sphere = new Sphere(sphereCenter, 1.8);

    SetIntersection* isect = new SetIntersection(
        sphereCenter, 
        dodecahedron, 
        sphere);

    scene.AddSolidObject(isect);

    scene.AddLightSource(LightSource(Vector(-45.0, +10.0, +50.0), Color(1.0, 1.0, 0.3, 1.0)));
    scene.AddLightSource(LightSource(Vector( +5.0, +90.0, -40.0), Color(0.5, 0.5, 1.5, 0.5)));
    scene.AddLightSource(LightSource(Vector(+45.0, -10.0, +40.0), Color(0.1, 0.5, 0.1, 0.5)));

    const char *filename = "overlap.png";
    scene.SaveImage(filename, 400, 300, 12.0, 1);
    std::cout << "Wrote " << filename << std::endl;
}


void AddKaleidoscopeMirrors(Imager::Scene& scene, double width, double depth)
{
    using namespace Imager;

    // Create three cuboids, one for each mirror
    const double a = 2.0 * width;
    const double b = 0.1;           // thickness doesn't really matter
    const double c = 2.0 * depth;

    Optics optics;
    optics.SetMatteGlossBalance(1.0, Color(1.0, 1.0, 1.0), Color(1.0, 1.0, 1.0));

    Cuboid* mirror[3] = {0, 0, 0};
    for (int i=0; i < 3; ++i)
    {
        mirror[i] = new Cuboid(a, b, c);
        mirror[i]->SetUniformOptics(optics);

        scene.AddSolidObject(mirror[i]);
    }

    // Rotate/translate the three mirrors differently.
    // Use the common value 's' that tells how far 
    // the midpoints are from the origin.
    const double s = b + a/sqrt(3.0);

    // Pre-calculate trig functions used more than once.
    const double angle = RadiansFromDegrees(30.0);
    const double ca = cos(angle);
    const double sa = sin(angle);

    // The bottom mirror just moves down (in the -y direction)
    mirror[0]->Translate(0.0, -s, 0.0);
    mirror[0]->SetTag("bottom mirror");
   
    // The upper left mirror moves up and left
    // and rotates +60 degrees around z axis.
    mirror[1]->Translate(-s*ca, s*sa, 0.0);
    mirror[1]->RotateZ(+60.0);
    mirror[1]->SetTag("left mirror");

    // The upper right mirror moves up and right
    // and rotates -60 degrees around z axis.
    mirror[2]->Translate(s*ca, s*sa, 0.0);
    mirror[2]->RotateZ(-60.0);
    mirror[2]->SetTag("right mirror");
}


void KaleidoscopeTest()
{
    using namespace Imager;

    Scene scene(Color(0.0, 0.0, 0.0));

    AddKaleidoscopeMirrors(scene, 0.5, 10.0);

    Optics optics;  // use default optics (white matte finish, opaque)

    Dodecahedron* dodecahedron = new Dodecahedron(Vector(+0.0, 0.0, -50.0), 1.0, optics);
    dodecahedron->RotateX(-12.0);
    dodecahedron->RotateY(-7.0);

    // Create a sphere that overlaps with the dodecahedron.
    const Vector sphereCenter(Vector(+1.0, 0.0, -50.0));
    Sphere* sphere = new Sphere(sphereCenter, 1.8);

    SetIntersection* isect = new SetIntersection(
        sphereCenter, 
        dodecahedron, 
        sphere);

    isect->RotateZ(19.0);
    isect->Translate(0.0, 0.0, 10.0);

    scene.AddSolidObject(isect);

    scene.AddLightSource(LightSource(Vector(-45.0, +10.0, +50.0), Color(1.0, 1.0, 0.3, 1.0), "LS0"));
    scene.AddLightSource(LightSource(Vector( +5.0, +90.0, -40.0), Color(0.5, 0.5, 1.5, 0.5), "LS1"));
    scene.AddLightSource(LightSource(Vector(+45.0, -10.0, +40.0), Color(0.1, 0.5, 0.1, 0.5), "LS2"));
    scene.AddLightSource(LightSource(Vector(  0.0,   0.0,  +0.1), Color(0.5, 0.1, 0.1, 0.1), "LS3"));

    scene.AddDebugPoint(419, 300);
    scene.AddDebugPoint(420, 300);
    scene.AddDebugPoint(421, 300);

    const char *filename = "kaleid.png";
    scene.SaveImage(filename, 600, 600, 6.0, 1);
    std::cout << "Wrote " << filename << std::endl;
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
    std::cout << "Wrote " << filename << std::endl;
}


void ChessBoardTest()
{
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

    ChessBoard* board = new ChessBoard(
        innerSize, 
        xBorderSize, 
        yBorderSize,
        thickness,
        lightSquareColor,
        darkSquareColor,
        borderColor);

    board->Move(-0.35, 0.1, -20.0);

    board->RotateZ(+11.0);
    board->RotateX(-62.0);

    scene.AddSolidObject(board);

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

    const char* filename = "chessboard.png";
    scene.SaveImage(filename, 600, 360, 4.5, 3);
    std::cout << "Wrote " << filename << std::endl;
}


void UnitTests()
{
    Algebra::UnitTest();

    ChessBoardTest();
    DodecahedronOverlapTest();
    MultipleSphereTest();
    TorusTest("torus1.png", 0.0);
    TorusTest("torus2.png", 0.7);
    PolyhedraTest();
    BitDonutTest();
    SaturnTest();
    BlockTest();
    CylinderTest();
    SpheroidTest();
    CuboidTest();
    SetDifferenceTest();
    SetIntersectionTest();
    SphereTest();
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
    { "test", UnitTests,
        "    Runs a series of unit tests that generate sample PNG images.\n"
    },

    { "spheroid", SpheroidTest,
        "    Generates an image of a spheroid.\n"
    },

    { "chessboard", ChessBoardTest,
        "    Chess board and transparent spheres.\n"
    },

    { "block", BlockTest,
        "    Concrete block with a sphere casting a shadow on it.\n"
    },

    { "kaleid", KaleidoscopeTest,
        "    Kaleidoscope using three mirrors.\n"
    },
};

// Calculate the number of entries in CommandTable[]...
const size_t NUM_COMMANDS = sizeof(CommandTable) / sizeof(CommandTable[0]);


void PrintUsageText()
{
    using namespace std;

    cout <<
        "Ray Tracer demo - Copyright (C) 2013 by Don Cross.\n"
        "For more info, see: http://cosinekitty.com/raytrace\n"
        "\n"
        "The following command line options are supported:\n";

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
