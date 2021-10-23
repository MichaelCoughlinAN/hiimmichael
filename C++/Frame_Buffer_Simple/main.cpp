// Michael Coughlin
// CS 5721, Spring 2017

#include "Vector2D.h"
#include "Vector3D.h"
#include "FrameBuffer.h"

#include <iostream>
#include <fstream>

using namespace std;

// Colours for PPN files
// Note that this will change to 2D arrays of arrays as opposed
// to the current approach. However, it works perfectly fine, I
// know a different approach would be more efficient.

int whitePPN[1][3] = {{255,255,255}};
int blackPPN[1][3] = {{0,0,0}};
int greenPPN[1][3] = {{0,255,0}};
int redPPN[1][3]   = {{255,0,0}};
int multiPPN[1][3] = {{0,0,0}};

int main() {
     cout << "Homework 1\n"
	<< "CS 5721, Spring 2017\n"
	<< "Michael Coughlin\n\n"
        << "---------------------------------------\n"
	<< "Testing Vector2D Class\n"
	<< "---------------------------------------\n";

   Vector2D a(1.0, 3.0), b(5.0, 3.2), c(0.0, 0.0);

   cout << "Instantiated Vectors: a(1.0, 3.0), b(5.0, 3.2), c(0.0, 0.0)\n"
	<< "Testing addition: c = a + b\n";
   c = a + b;
   cout << "c = [" << c.getX() << ", " << c.getY() << "]\n" << endl
	<< "Testing subtraction: c = b - a\n";
   c = b - a;
   cout << "c = [" << c.getX() << ", " << c.getY() << "]\n" << endl
	<< "Testing scalar multiplication: c = a * 2\n";
c = a * 2;
cout << "c = [" << c.getX() << ", " << c.getY() << "]\n" << endl
	<< "Testing scalar division: c = a / 2\n";
c = a / 2;
cout << "c = [" << c.getX() << ", " << c.getY() << "]\n" << endl
     << "Testing c.zero() method\n";
c.zero();

cout << "c = [" << c.getX() << ", " << c.getY() << "]\n" << endl
     << "Testing setter methods: a.set(1.0, 1.0) b.set(2.0, 2.0)\n";
a.set(1.0, 1.0);
b.set(2.0, 2.0);

cout << "a = [" << a.getX() << ", " << a.getY() << "]" << endl
     << "b = [" << b.getX() << ", " << b.getY() << "]\n" << endl
     << "Testing length methods\n"
     << "a length = " << a.length() << endl
     << "b length = " << b.length() << endl 
     << "\nNormalizing a\n";

double len = a.length();
a.normalize();
cout << "a = [" << a.getX() << ", " << a.getY() << "]" << endl;
cout << "The new a length = " << a.length() << ", old length = " << len << endl << endl
     << "Testing dotproduct c = a.dotProduct(b)\n";
c = a.dotProduct(b);
cout << "c = [" << c.getX() << ", " << c.getY() << "]" << endl;

 cout << endl
      << "---------------------------------------\n"
      << "Testing Vector3D Class\n"
      << "---------------------------------------\n";

 Vector3D e(1.0, 3.0, 1.0), f(5.0, 3.2, 1.0), g(0.0, 0.0, 0.0);

cout << "Instantiated Vectors: e(1.0, 3.0, 1.0), f(5.0, 3.2, 1.0), g(0.0, 0.0)\n"
	<< "Testing addition: g = e + f\n";
   g = e + f;
   cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl
	<< "Testing subtraction: g = e - f\n";
   g = e - f;
    cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl
	<< "Testing scalar multiplication: g = e * 2\n";
g = e * 2;
cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl
	<< "Testing scalar division: g = e / 2\n";
g = e / 2;
cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl
     << "Testing c.zero() method\n";
g.zero();

cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl
     << "Testing setter methods: e.set(1.0, 1.0, 1.0) f.set(2.0, 2.0, 2.0)\n";
e.set(1.0, 1.0, 1.0);
f.set(2.0, 2.0, 2.0);

cout << "e = [" << e.getX() << ", " << e.getY() << ", " << e.getZ() << "]" << endl
     << "f = [" << f.getX() << ", " << f.getY() << ", " << f.getZ() << "]\n" << endl
     << "Testing length methods\n"
     << "e length = " << e.length() << endl
     << "f length = " << f.length() << endl 
     << "\nNormalizing e\n";

double len1 = e.length();
e.normalize();
cout << "e = [" << e.getX() << ", " << e.getY() << ", " << e.getZ() << "]" << endl;
cout << "The new a length = " << e.length() << ", old length = " << len1 << endl << endl
     << "Testing dotproduct g = e.dotProduct(f)\n";
g = e.dotProduct(f);
cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl << "Testing crossProduct g = e.crossProduct(f)\n";
g = e.crossProduct(f);
cout << "g = [" << g.getX() << ", " << g.getY() << ", " << g.getZ() << "]\n" << endl;
 
cout << "---------------------------------------\n"
     << "Testing FrameBuffer Class\n"
     << "---------------------------------------\n"
     << "Creating white, black, red, and green PPN files\n";

 FrameBuffer* white = new FrameBuffer(whitePPN, 145, 89, "white.ppn");
 FrameBuffer* black = new FrameBuffer(blackPPN, 48, 480, "black.ppn");
 FrameBuffer* red   = new FrameBuffer(redPPN, 600, 480, "red.ppn");
 FrameBuffer* green = new FrameBuffer(greenPPN, 10, 10, "green.ppn");
 FrameBuffer* multi = new FrameBuffer(multiPPN, 800, 600, "multi.ppn");

 cout << "Creations of PPM formatted files successful!\n\n";
   
 
 cout << "Image successfully blanked (default: black)\n\n"
      << "Creating multi-coloured PPN file\n(Testing having multiple pixel colour per PPN file)\n\nImage files can be found in the build directory\n" << "Blanking out the multi-coloured .PPN file.\n\n";
 multi->blank();
 
cout << "Exit Success\n";

  return 0;
}
